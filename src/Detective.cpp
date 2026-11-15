#include "Detective.h"
#include "TerminalColor.h"

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
    std::cout << Color::BOLD_CYAN << "🕵️  [Detective] " << Color::BOLD_WHITE << m_name
              << Color::DIM << " (" << m_id << ")" << Color::RESET
              << " | Score: " << Color::BOLD_YELLOW << m_score << " pts" << Color::RESET << "\n";
}

std::string Detective::getRoleDescription() const {
    return "Member of the Student Investigation Squad tasked with exposing the Proxy Gang.";
}

} // namespace ProxyMystery
