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
                    ? "Arey bhai bisshash kor, ami to " + location + "! 302 er slide ready kortesilam!"
                    : "Ami CR hoye " + location + "! 302 er official attendance sheet strictly monitor kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "302 te shob e normal chilo bhai. But " + witness + " re ektu nervous lagtesilo."
                    : "Sir jokhon whiteboard er dike ghursilo, ami dekhsi ke jani sheet e 2-3 ta fake sign maira dilo!";
            } else {
                response = "Tora " + witness + " re jiges kor, o jane ami CR hishebe koto serious!";
            }
            break;

        case Archetype::BACKBENCHER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Arey mama, ami to " + location + " chil kortesilam. Kono churi kori nai!"
                    : "Mama ami shanti moto " + location + " boshe shobar kando-karkhana observe kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Keu kono proxy dei nai mama! Proctor sir er moto amar piche lagso ken?!"
                    : "Mama, " + proxyKingName + " er dike ektu bhalo kore takao. Roll call er agei podium er kache ghurgur kortesilo!";
            } else {
                response = "Check kor " + witness + " er shathe. Amra eksathe chil kortesilam.";
            }
            break;

        case Archetype::TOPPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami to " + location + " lab er calculation recheck kortesilam."
                    : "Ami shokal 8:00 tar age thekei 302 er " + location + " khata khule boshe chilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami lab e onnoder dike takai na. Tobe " + witness + " table er kache ghurtisilo."
                    : "Proxy dewa puro unfair! Sir takanor age ke jani table er upore pen chalaia shoray felse!";
            } else {
                response = witness + " jane amar theke shobai lab er code copy kortesilo, ami proxy dite jabo ken?";
            }
            break;

        case Archetype::SLEEPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "*Hai tule* Bhai... ami mone hoi " + location + " chilam..."
                    : "*Chokh moshe* Mama ami 302 te " + location + " ghum e behush chilam lab shesh howa porjonto.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami toh ghumaitesilam... shopne mone hoi dekhsilam " + witness + " hete jacche."
                    : "Ami adho-ghume chokh khule dekhsilam ke jani sheet er moddhe 2ta sign dhorse!";
            } else {
                response = "*High tulte tulte* " + witness + " re jiga, or snore e amar ghum bhaangsilo.";
            }
            break;

        case Archetype::LATECOMER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Boardbazar er traffic e pura atka chilam mama! Tai " + location + " thaka obosthay roll call shuru hoise."
                    : "IUT bus late korsilo! Rocket e ek cup cha kheye dauraia " + location + " ashsi thik sir jokhon naam daktese!";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Dauraye ashte ashte matha ghurtesilo, " + witness + " mone hoi kichu ekta janbe!"
                    : "Ami dauraia 302 te dhukar shomoy e dekhsilam sheet e enroll er cheye beshi checkmark chilo!";
            } else {
                response = witness + " nije dekhse ami 302 te dauraia dhukte giye hapaitesilam!";
            }
            break;

        case Archetype::GOSSIP_MASTER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami oboshshoi " + location + " chilam, kintu eta kintu ami bolinai!"
                    : "Ami " + location + " daraye department er shob latest khobor collect kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "CDS e shunsilam " + witness + " naki 50 taka kore per proxy sign er deal nitasilo!"
                    : "Kan khule shuno: ashol Proxy King class er agei code share kortesilo!";
            } else {
                response = "Jaia " + witness + " re jiges koro, kintu amar naam nio na abar!";
            }
            break;
    }

    return response;
}

} // namespace ProxyMystery
