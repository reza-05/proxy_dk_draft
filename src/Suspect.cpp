#include "Suspect.h"
#include "Personality.h"
#include "TerminalColor.h"
#include <sstream>

namespace ProxyMystery {

Suspect::Suspect(const std::string& name, const std::string& id, Archetype archetype,
                 RoleType role, const std::string& trueLoc, const std::string& fakeLoc)
    : Character(name, id),
      m_archetype(archetype),
      m_role(role),
      m_isExposed(false),
      m_isSilenced(false),
      m_trueLocation(trueLoc),
      m_fakeLocation(fakeLoc) {}

Statement Suspect::interrogate(QuestionTopic topic, int round,
                              const std::string& proxyKingName,
                              const std::string& witnessName) {
    bool isLie = (m_role != RoleType::HONEST_STUDENT);
    std::string locClaim;

    if (m_role == RoleType::HONEST_STUDENT) {
        locClaim = m_trueLocation;
    } else {
        // Liars switch their claims across rounds or topics, producing contradiction!
        if (round % 2 == 1) {
            locClaim = m_fakeLocation;
        } else {
            locClaim = m_trueLocation; // Slip of the tongue!
        }
    }

    std::string dialogue = Personality::formatDialogue(m_archetype, topic, locClaim,
                                                       witnessName, isLie, proxyKingName);

    Statement stmt(round, topic, dialogue, locClaim, witnessName, isLie);
    m_history.push_back(stmt);
    return stmt;
}

bool Suspect::hasContradiction(std::string& outDetails) const {
    if (m_history.size() < 2) {
        outDetails = "Not enough statements recorded yet for " + m_name + " to identify contradictions.";
        return false;
    }

    // Check location contradiction
    std::string firstLoc = "";
    int firstRound = -1;

    for (const auto& stmt : m_history) {
        if (stmt.getTopic() == QuestionTopic::LOCATION_DURING_ROLLCALL) {
            if (firstLoc.empty()) {
                firstLoc = stmt.getLocationClaim();
                firstRound = stmt.getRound();
            } else if (firstLoc != stmt.getLocationClaim()) {
                std::ostringstream oss;
                oss << m_name << " claimed to be at [" << firstLoc << "] in Round " << firstRound
                    << ", but later claimed to be at [" << stmt.getLocationClaim()
                    << "] in Round " << stmt.getRound() << "!";
                outDetails = oss.str();
                return true;
            }
        }
    }

    outDetails = m_name + "'s statements remain consistent so far.";
    return false;
}

void Suspect::exposeRole() {
    m_isExposed = true;
}

bool Suspect::isExposed() const {
    return m_isExposed;
}

bool Suspect::isSilenced() const {
    return m_isSilenced;
}

void Suspect::setSilenced(bool silenced) {
    m_isSilenced = silenced;
}

RoleType Suspect::getRole() const {
    return m_role;
}

Archetype Suspect::getArchetype() const {
    return m_archetype;
}

const std::vector<Statement>& Suspect::getHistory() const {
    return m_history;
}

const std::string& Suspect::getTrueLocation() const {
    return m_trueLocation;
}

void Suspect::displayProfile() const {
    std::cout << Color::BOLD_CYAN << "👤 [Suspect] " << Color::BOLD_WHITE << m_name
              << " " << Color::DIM << "(" << archetypeToString(m_archetype) << ")" << Color::RESET << "\n"
              << "   ID: " << Color::WHITE << m_id << Color::RESET << " | Status: ";
    if (m_isExposed) {
        std::cout << Color::BOLD_RED << "[EXPOSED: " << roleToString(m_role) << "]";
    } else {
        std::cout << Color::BOLD_YELLOW << "[Under Investigation]";
    }
    std::cout << Color::RESET << "\n"
              << "   Statements on record: " << Color::CYAN << m_history.size() << Color::RESET << "\n";
}

std::string Suspect::getRoleDescription() const {
    return archetypeToString(m_archetype);
}

} // namespace ProxyMystery
