#include "Detective.h"

namespace ProxyMystery {

Detective::Detective(const std::string& name, const std::string& id)
    : Character(name, id), m_score(0) {}

void Detective::addScore(int points) {
    m_score += points;
}

void Detective::deductScore(int points) {
    m_score -= points;
    if (m_score < 0) {
        m_score = 0;
    }
}

int Detective::getScore() const {
    return m_score;
}

void Detective::displayProfile() const {
    std::cout << "[Detective] " << m_name << " (ID: " << m_id << ") | Investigation Points: "
              << m_score << "\n";
}

std::string Detective::getRoleDescription() const {
    return "Member of the Student Investigation Squad tasked with exposing the Proxy Gang.";
}

} // namespace ProxyMystery
