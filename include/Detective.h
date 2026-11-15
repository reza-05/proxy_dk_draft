#pragma once
#include "Character.h"

namespace ProxyMystery {

class Detective : public Character {
private:
    int m_score;

public:
    Detective(const std::string& name, const std::string& id);
    ~Detective() override = default;

    void addScore(int points);
    void deductScore(int points);
    [[nodiscard]] int getScore() const;

    void displayProfile() const override;
    std::string getRoleDescription() const override;
};

} // namespace ProxyMystery
