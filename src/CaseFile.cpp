#include "CaseFile.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>

namespace ProxyMystery {

static std::string pickRandomOption(const std::string& input, std::mt19937& rng) {
    std::vector<std::string> parts;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, ';')) {
        if (!item.empty()) {
            parts.push_back(item);
        }
    }
    if (parts.empty()) return input;
    std::uniform_int_distribution<size_t> dist(0, parts.size() - 1);
    return parts[dist(rng)];
}

void CaseFile::createDefaultConfigIfNotExists(const std::string& filePath) {
    std::ifstream check(filePath);
    if (check.is_open()) {
        check.close();
        return; // File already exists
    }

    std::ofstream out(filePath);
    if (!out.is_open()) {
        throw FileNotFoundException(filePath);
    }

    out << "# Name|ID|Archetype(0:CR, 1:Backbencher, 2:Topper, 3:Sleeper, 4:Latecomer, 5:Gossip)|TrueLocations(;)|FakeLocations(;)\n";
    out << "Tanvir|210041101|0|Room 302 er first row te boshe chilam;Podium er kache multimedia projector on kortesilam;Sir er table er samne attendance sheet check kortesilam|Pechoner bench e boshe adda ditesilam;Department office e duster ante gesilam;Corridor e CR der shathe kotha boltisilam\n";
    out << "Sakib|210041123|1|Room 302 er last bench e chil kortesilam;Pechoner row te boshe cricket score dekhtesilam;Corner desk e boshe headphone e gaan shuntesilam|CDS e breakfast khaitesilam;Rocket e cha khaitesilam;Hostel er shamne chill kortesilam\n";
    out << "Nabila|210041145|2|Room 302 er first row te lab report likhtesilam;First bench e slide notes revision ditsilam;Lab manual dekhe algorithm trace kortesilam|Corridor e lab partner er shathe chilam;Library theke reference book ante gesilam;Department office e notice board dekhtesilam\n";
    out << "Rafi|210041156|3|Room 302 er 3 number desk e ghumaitesilam;AC er thanda batash e matha nichu kore ghumaitesilam;Pechoner row te desk e matha thikaye ghumaitesilam|Washroom e mukhe pani dite gesilam;Hostel e late kore uthsi tai ghum bhange nai;Medical center e matha bathar medicine nite gesilam\n";
    out << "Fahim|210041178|4|Boardbazar jam e atka theke dauraya ashsi;Gazipur chourasta theke auto paowa jacchilo na;Shokal 7:30 er IUT bus miss kore dauraya ashsi|Rocket e cha order disilam tai late hoise;Main gate e ID card check e line chilo;Hostel er room e bag fele ashsilam\n";
    out << "Farhana|210041199|5|Room 302 er majhkhaner row te boshsilam;Dorjar pashe boshe ke k ashse count kortesilam;Row 3 te boshe friend er shathe kotha boltisilam|CDS e kotha boltisilam tai deri hoise;Corridor e 2nd year der jhamelar khobor shuntesilam;Cafeteria te gossip kortesilam\n";

    out.close();
}

void CaseFile::loadSuspectsFromFile(const std::string& filePath,
                                   std::vector<Suspect>& outSuspects,
                                   std::string& outProxyKingName) {
    createDefaultConfigIfNotExists(filePath);

    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw FileNotFoundException(filePath);
    }

    std::string line;
    struct RawEntry {
        std::string name;
        std::string id;
        Archetype arch;
        std::string trueLoc;
        std::string fakeLoc;
    };
    std::vector<RawEntry> rawList;

    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string name, id, archStr, trueLoc, fakeLoc;

        if (std::getline(ss, name, '|') &&
            std::getline(ss, id, '|') &&
            std::getline(ss, archStr, '|') &&
            std::getline(ss, trueLoc, '|') &&
            std::getline(ss, fakeLoc)) {

            int archInt = std::stoi(archStr);
            Archetype arch = static_cast<Archetype>(archInt);
            rawList.push_back({name, id, arch, trueLoc, fakeLoc});
        }
    }
    in.close();

    if (rawList.empty()) {
        throw ProxyGameException("No suspects loaded from " + filePath);
    }

    // Shuffle and assign hidden roles dynamically using high-entropy seed
    unsigned int seed = std::random_device{}() ^ 
        static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 g(seed);
    std::vector<size_t> indices(rawList.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }
    std::shuffle(indices.begin(), indices.end(), g);

    size_t kingIdx = indices[0];
    size_t memberIdx = (indices.size() > 1) ? indices[1] : indices[0];

    outProxyKingName = rawList[kingIdx].name;

    outSuspects.clear();
    for (size_t i = 0; i < rawList.size(); ++i) {
        RoleType role = RoleType::HONEST_STUDENT;
        if (i == kingIdx) {
            role = RoleType::PROXY_KING;
        } else if (i == memberIdx && memberIdx != kingIdx) {
            role = RoleType::PROXY_MEMBER;
        }

        std::string chosenTrueLoc = pickRandomOption(rawList[i].trueLoc, g);
        std::string chosenFakeLoc = pickRandomOption(rawList[i].fakeLoc, g);

        outSuspects.emplace_back(rawList[i].name, rawList[i].id, rawList[i].arch,
                                role, chosenTrueLoc, chosenFakeLoc);
    }
}

void CaseFile::saveCaseArchive(const std::string& filePath,
                               const std::string& caseSummary) {
    std::ofstream out(filePath, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "[Warning] Unable to write case archive to " << filePath << "\n";
        return;
    }

    out << "=====================================================\n";
    out << caseSummary << "\n";
    out << "=====================================================\n\n";
    out.close();
}

} // namespace ProxyMystery
