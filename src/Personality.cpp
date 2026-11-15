#include "Personality.h"

namespace ProxyMystery {

std::string Personality::formatDialogue(Archetype archetype, QuestionTopic topic,
                                      const std::string& location, const std::string& witness,
                                      bool isLie, const std::string& proxyKingName) {
    std::string response;

    switch (archetype) {
        case Archetype::CR:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami to " + location + ", sheet ta kokhon pechone gelo kheyal kori nai."
                    : "Ami sir er theke attendance sheet ta niye first row theke pass kora shuru korsilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Amar kache shob normal e lagtesilo, tobe " + witness + " ektu fidgety chilo."
                    : "Sheet ta jokhon pechoner row te gelo, tokhon shobai taratari sign kortesilo, oikhan thekei sign barse!";
            } else {
                response = "Sir ke jiges koro, sir nijei class er shurute amar haate sheet disilo.";
            }
            break;

        case Archetype::BACKBENCHER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Arey mama, ami to " + location + ". Kono ghapla kori nai!"
                    : "Mama ami shanti moto " + location + " boshe chil kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Amra to pechone phone chalaitsilam, sheet ashse sign disi, shamne ki hoise jani na."
                    : "Mama, " + proxyKingName + " er dike ektu takao. O sheet ta niye ghurgur kortesilo!";
            } else {
                response = "Pechoner bench e " + witness + " chilo, jiges koro amra ki kortesilam.";
            }
            break;

        case Archetype::TOPPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami to " + location + " lab er calculation recheck kortesilam."
                    : "Ami shokal 8:00 tar age thekei 302 er first row te boshe lab report ready kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami lab e busy chilam, tobe " + witness + " sheet ta niye onekderi kortesilo."
                    : "First row te sheet jokhon chilo shob normal chilo. Pechone jawar por extra sign gulo porese!";
            } else {
                response = "First row er shobai jane ami shuru thekei code kortesilam, proxy dite jabo kon dukkhe?";
            }
            break;

        case Archetype::SLEEPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "*Hai tule* Bhai... ami mone hoi " + location + " chilam..."
                    : "*Chokh moshe* Mama ami 302 te " + location + " matha niche diye ghumaitesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami to ghum e chilam bhai, ke kar proxy dise amar ki daay?"
                    : "Adho-ghume chokh khule dekhsilam ke jani sheet er moddhe 2-3 ta sign maira dilo!";
            } else {
                response = "*High tulte tulte* " + witness + " re jiga, or dhakkay amar ghum bhaangsilo.";
            }
            break;

        case Archetype::LATECOMER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami to " + location + ". Tai class shuru howar 5 minute pore 302 te dhuksi."
                    : "Boardbazar jam e bus atkay gesilo! Ami dauraia 302 te dhuksi jokhon sir roll call dhorsilo!";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami to matro dhuklam bhai, ami ashar agei shob sign kora shesh!"
                    : "Ami late kore dhuke dekhi sheet ta already ghura shesh, oikhan thekei ghapla hoise!";
            } else {
                response = witness + " nije dekhse ami shobari sheshe dauraia 302 te dhuksi!";
            }
            break;

        case Archetype::GOSSIP_MASTER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami to " + location + " chilam, kintu eta kintu ami bolinai!"
                    : "Ami 302 te boshe shobai k k ashse dekhsilam, shob roll count kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Shunsilam " + witness + " naki tader roll sign kore dise, ami nishchit na kintu!"
                    : "Shuno, hall theke 3 jon ashei nai ajke, kintu sheet e tader sign ase! Eta nishchoi gang er kaaj.";
            } else {
                response = "Jaia " + witness + " re jiges koro, kintu amar naam nio na abar!";
            }
            break;
    }

    return response;
}

} // namespace ProxyMystery
