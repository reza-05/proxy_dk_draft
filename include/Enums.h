#pragma once
#include <string>

namespace ProxyMystery {

enum class RoleType {
    HONEST_STUDENT,
    PROXY_MEMBER,
    PROXY_KING
};

enum class Archetype {
    CR,
    BACKBENCHER,
    TOPPER,
    SLEEPER,
    LATECOMER,
    GOSSIP_MASTER
};

enum class QuestionTopic {
    LOCATION_DURING_ROLLCALL = 1,
    SUSPICIOUS_ACTIVITY = 2,
    ALIBI_AND_WITNESS = 3
};

inline std::string roleToString(RoleType role) {
    switch (role) {
        case RoleType::HONEST_STUDENT: return "Innocent Student";
        case RoleType::PROXY_MEMBER:   return "Proxy Gang Member";
        case RoleType::PROXY_KING:     return "THE PROXY KING (Mastermind)";
        default:                       return "Unknown";
    }
}

inline std::string archetypeToString(Archetype arch) {
    switch (arch) {
        case Archetype::CR:            return "The CR (Class Representative)";
        case Archetype::BACKBENCHER:   return "The Backbencher";
        case Archetype::TOPPER:        return "The Topper";
        case Archetype::SLEEPER:       return "The Sleeper";
        case Archetype::LATECOMER:     return "The Latecomer";
        case Archetype::GOSSIP_MASTER: return "The Gossip Master";
        default:                       return "Student";
    }
}

inline std::string topicToString(QuestionTopic topic) {
    switch (topic) {
        case QuestionTopic::LOCATION_DURING_ROLLCALL: return "Where were you during attendance?";
        case QuestionTopic::SUSPICIOUS_ACTIVITY:      return "Did you see anyone near the teacher's desk?";
        case QuestionTopic::ALIBI_AND_WITNESS:        return "Who can confirm your alibi?";
        default:                                      return "General inquiry";
    }
}

} // namespace ProxyMystery
