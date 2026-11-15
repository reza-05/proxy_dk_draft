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
                    ? "Ami to " + location + ", roll call er shomoy pechon theke ke kemon kore daak ditsilo kheyal kori nai."
                    : "Ami first row te boshe nijer roll call er shomoy 'Present sir' bolsilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Amar kache shob shobdor daak normal lagse, tobe " + witness + " ektu nervous chilo."
                    : "Sir jokhon matha nichu kore roll daktesilo, pechoner row theke ek e golar shure 2-3 bar 'Yes sir' ashse!";
            } else {
                response = "First row er shobai ke jiges koro, ami nijer roll chara kono extra daak dei nai.";
            }
            break;

        case Archetype::BACKBENCHER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Arey mama, ami to " + location + ". Kono extra roll call e daak dei nai!"
                    : "Mama ami shanti moto " + location + " boshe chil kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Amra to pechone phone chalaitsilam, sir roll dakse amra nijer ta disi, baki k ki bolse jani na."
                    : "Mama, " + proxyKingName + " er dike ektu takao. O roll call er shomoy gala choto kore onner roll e 'Present sir' bolsilo!";
            } else {
                response = "Pechoner bench e " + witness + " chilo, jiges koro ami gala change korsilam kina.";
            }
            break;

        case Archetype::TOPPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Ami to " + location + " lab er calculation bujhtesilam."
                    : "Ami shokal 8:00 tar age thekei 302 er first row te boshe lab report ready kortesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami lab e busy chilam, tobe " + witness + " roll call er shomoy ektu suspicious lagtesilo."
                    : "Sir matha nichu kore roll call korar shomoy pechon theke 2 ta voice imitation shunsilam! Hall er absent cheleder roll dhorsilo!";
            } else {
                response = "First row er shobai jane ami shuru thekei code kortesilam, onner roll e daak dite jabo kon dukkhe?";
            }
            break;

        case Archetype::SLEEPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "*Hai tule* Bhai... ami mone hoi " + location + " chilam..."
                    : "*Chokh moshe* Mama ami 302 te " + location + " matha niche diye ghumaitesilam.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Ami to ghum e chilam bhai, ke kar roll e 'Yes sir' bolse amar ki daay?"
                    : "Adho-ghume chokh khule dekhsilam amar pasher chele ta gala mota kore arekjon er 'Present sir' bole dilo!";
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
                    ? "Ami to matro dhuklam bhai, ami ashar agei shob roll call shesh!"
                    : "Ami dorja diye dhukar shomoy e shunlam amar roll call er age ke jani pechon theke fake 'Yes sir' bole felse!";
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
                    ? "Shunsilam " + witness + " naki hall er friend der proxy dewar kotha ditsilo, ami nishchit na kintu!"
                    : "Shuno, hall theke 3 jon ashei nai ajke, kintu roll call e tader response ashse! Oita nishchoi gang er kaaj.";
            } else {
                response = "Jaia " + witness + " re jiges koro, kintu amar naam nio na abar!";
            }
            break;
    }

    return response;
}

} // namespace ProxyMystery
