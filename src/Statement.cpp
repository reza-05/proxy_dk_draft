#include "Statement.h"

namespace ProxyMystery {

Statement::Statement(int round, QuestionTopic topic, const std::string& dialogue,
                     const std::string& locationClaim, const std::string& witnessClaim, bool isLie)
    : m_round(round),
      m_topic(topic),
      m_dialogue(dialogue),
      m_locationClaim(locationClaim),
      m_witnessClaim(witnessClaim),
      m_isLie(isLie) {}

int Statement::getRound() const {
    return m_round;
}

QuestionTopic Statement::getTopic() const {
    return m_topic;
}

const std::string& Statement::getDialogue() const {
    return m_dialogue;
}

const std::string& Statement::getLocationClaim() const {
    return m_locationClaim;
}

const std::string& Statement::getWitnessClaim() const {
    return m_witnessClaim;
}

bool Statement::isLie() const {
    return m_isLie;
}

} // namespace ProxyMystery
