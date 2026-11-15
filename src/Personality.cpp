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
                    ? "Bro, trust me, I was " + location + " sorting the course lecture slides!"
                    : "As the CR, I was strictly " + location + " monitoring the official attendance folder.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Everything looked 100% fine to me. But honestly, " + witness + " seemed awfully fidgety."
                    : "I swear I noticed someone scribbling rapid signatures when the teacher turned around.";
            } else {
                response = "Ask " + witness + ", they know I take my section responsibilities seriously!";
            }
            break;

        case Archetype::BACKBENCHER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Arey mama, I was chilling at " + location + ". No cap!"
                    : "I was hanging out at " + location + ", observing everyone's movements.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Nobody did anything wrong! Why you interrogating me like proctor sir?!"
                    : "Mama, look closely at " + proxyKingName + ". Shady moves around the podium.";
            } else {
                response = "Check with " + witness + ". We were literally splitting peanuts.";
            }
            break;

        case Archetype::TOPPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "I was briefly at " + location + " reviewing chapter 4 proofs."
                    : "I was seated at " + location + " with my notebook open before 8:00 AM sharp.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "I don't bother looking at other students. But " + witness + " was walking around."
                    : "Proxies undermine academic integrity! I saw someone slip a pen near the desk.";
            } else {
                response = witness + " can verify my notes were being copied by half the room.";
            }
            break;

        case Archetype::SLEEPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "*Yawns* Uhh... I think I was awake at " + location + "..."
                    : "*Wipes eyes* I was dead asleep at " + location + " until the bell rang.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "I didn't see anything... except maybe " + witness + " walking in my dream?"
                    : "I half-opened my eyes and saw someone signing two sheets in row 2!";
            } else {
                response = "*Stretches* Ask " + witness + ", their snoring woke me up.";
            }
            break;

        case Archetype::LATECOMER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Boardbazar traffic was brutal, so I was already at " + location + " when roll call started!"
                    : "The IUT bus broke down! I barely ran to " + location + " right as sir took the sheet.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "I was too exhausted to notice. Maybe " + witness + " knows something?"
                    : "When I rushed past the podium, the attendance sheet had extra checkmarks already!";
            } else {
                response = witness + " saw me sprinting up the stairs out of breath!";
            }
            break;

        case Archetype::GOSSIP_MASTER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "I was definitely at " + location + ", but you didn't hear that from me."
                    : "I was stationed at " + location + ", gathering all the latest department tea.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Rumor has it that " + witness + " charges 50 taka per proxy signature!"
                    : "Listen closely: the real Proxy King whispers codes before roll call.";
            } else {
                response = "Go ask " + witness + ", but don't tell them I sent you!";
            }
            break;
    }

    return response;
}

} // namespace ProxyMystery
