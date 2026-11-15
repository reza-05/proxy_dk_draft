#pragma once
#include <string>
#include "Enums.h"

namespace ProxyMystery {

class Statement {
private:
    int m_round;
    QuestionTopic m_topic;
    std::string m_dialogue;
    std::string m_locationClaim;
    std::string m_witnessClaim;
    bool m_isLie;

public:
    Statement(int round, QuestionTopic topic, const std::string& dialogue,
              const std::string& locationClaim, const std::string& witnessClaim, bool isLie);

    [[nodiscard]] int getRound() const;
    [[nodiscard]] QuestionTopic getTopic() const;
    [[nodiscard]] const std::string& getDialogue() const;
    [[nodiscard]] const std::string& getLocationClaim() const;
    [[nodiscard]] const std::string& getWitnessClaim() const;
    [[nodiscard]] bool isLie() const;
};

} // namespace ProxyMystery
