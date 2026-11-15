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
                    ? "Bro, trust me, I was at " + location + " organizing the slides for Room 302!"
                    : "As the CR, I was strictly at " + location + " monitoring the official attendance folder for Room 302.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Everything looked 100% fine in Room 302. But honestly, " + witness + " seemed awfully fidgety."
                    : "I swear I noticed someone scribbling rapid proxy signatures when sir turned toward the whiteboard.";
            } else {
                response = "Ask " + witness + ", they know I take my section responsibilities seriously!";
            }
            break;

        case Archetype::BACKBENCHER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Arey mama, I was chilling at " + location + ". No cap!"
                    : "I was hanging out at " + location + ", observing everyone's movements in Room 302.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Nobody did anything wrong! We were just planning to go to Rocket for cha! Why interrogate me like proctor sir?!"
                    : "Mama, look closely at " + proxyKingName + ". Shady moves around the podium right before roll call.";
            } else {
                response = "Check with " + witness + ". We were literally at CDS together having breakfast.";
            }
            break;

        case Archetype::TOPPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "I was briefly at " + location + " reviewing lab experiment proofs."
                    : "I was seated at " + location + " in Room 302 with my lab report open before 8:00 AM sharp.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "I don't bother looking around during class. But " + witness + " was wandering near the desk."
                    : "Proxies undermine academic integrity! I saw someone slip extra attendance slips near the desk.";
            } else {
                response = witness + " can verify my code was being copied by half the room.";
            }
            break;

        case Archetype::SLEEPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "*Yawns* Uhh... I think I was awake at " + location + "..."
                    : "*Wipes eyes* I was dead asleep at " + location + " in Room 302 until the lab ended.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "I didn't see anything... I just had a dream that someone promised to buy me cha at Rocket."
                    : "I half-opened my eyes and saw someone signing two names hurriedly in row 3!";
            } else {
                response = "*Stretches* Ask " + witness + ", their snoring on the next bench woke me up.";
            }
            break;

        case Archetype::LATECOMER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "Boardbazar traffic was brutal, so I barely reached " + location + " when roll call started!"
                    : "The IUT bus was stuck! I grabbed a quick cha at Rocket and sprinted to " + location + " right as sir called names.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "I was too exhausted from running to notice. Maybe " + witness + " knows something?"
                    : "When I rushed past the podium into Room 302, the sheet already had extra signatures!";
            } else {
                response = witness + " saw me sprinting up to Room 302 completely out of breath!";
            }
            break;

        case Archetype::GOSSIP_MASTER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                response = isLie
                    ? "I was definitely at " + location + ", but you didn't hear that from me."
                    : "I was stationed at " + location + ", gathering all the latest department tea.";
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                response = isLie
                    ? "Overheard at CDS: rumor has it that " + witness + " charges 50 taka per proxy signature!"
                    : "Listen closely: the real Proxy King was seen passing tokens outside CDS before class!";
            } else {
                response = "Go ask " + witness + ", but don't tell them I sent you!";
            }
            break;
    }

    return response;
}

} // namespace ProxyMystery
