#include "CaseFile.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <iostream>

namespace ProxyMystery {

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

    out << "# Name|ID|Archetype(0:CR, 1:Backbencher, 2:Topper, 3:Sleeper, 4:Latecomer, 5:Gossip)|TrueLocation|FakeLocation\n";
    out << "Tanvir|210041101|0|Front podium checking sheet|Back bench chatting\n";
    out << "Sakib|210041123|1|Last row corner bench|Library reading room\n";
    out << "Nabila|210041145|2|First row taking lecture notes|Outside room 402 corridor\n";
    out << "Rafi|210041156|3|Row 4 desk sleeping soundly|Near the teacher's podium\n";
    out << "Fahim|210041178|4|Back door entering breathless|Cafeteria getting tea\n";
    out << "Farhana|210041199|5|Water dispenser hallway|Near the attendance desk\n";

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

    // Shuffle and assign hidden roles
    std::random_device rd;
    std::mt19937 g(rd());
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

        outSuspects.emplace_back(rawList[i].name, rawList[i].id, rawList[i].arch,
                                role, rawList[i].trueLoc, rawList[i].fakeLoc);
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
