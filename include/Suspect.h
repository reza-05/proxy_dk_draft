#pragma once
#include <vector>
#include <string>
#include "Character.h"
#include "Enums.h"
#include "Statement.h"

namespace ProxyMystery {

class Suspect : public Character {
private:
    Archetype m_archetype;
    RoleType m_role;
    bool m_isExposed;
    bool m_isSilenced;
    std::string m_trueLocation;
    std::string m_fakeLocation;
    std::vector<Statement> m_history;

public:
    Suspect(const std::string& name, const std::string& id, Archetype archetype,
            RoleType role, const std::string& trueLoc, const std::string& fakeLoc);
    ~Suspect() override = default;

    Statement interrogate(QuestionTopic topic, int round,
                          const std::string& proxyKingName,
                          const std::string& witnessName);

    [[nodiscard]] bool hasContradiction(std::string& outDetails) const;
    void exposeRole();

    [[nodiscard]] bool isExposed() const;
    [[nodiscard]] bool isSilenced() const;
    void setSilenced(bool silenced);

    [[nodiscard]] RoleType getRole() const;
    [[nodiscard]] Archetype getArchetype() const;
    [[nodiscard]] const std::vector<Statement>& getHistory() const;
    [[nodiscard]] const std::string& getTrueLocation() const;

    void displayProfile() const override;
    std::string getRoleDescription() const override;
};

} // namespace ProxyMystery
