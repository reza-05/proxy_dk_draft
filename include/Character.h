#pragma once
#include <string>
#include <iostream>

namespace ProxyMystery {

class Character {
protected:
    std::string m_name;
    std::string m_id;

public:
    Character(const std::string& name, const std::string& id);
    virtual ~Character() = default;

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getId() const;

    // Pure virtual functions (demonstrating Polymorphism)
    virtual void displayProfile() const = 0;
    virtual std::string getRoleDescription() const = 0;
};

} // namespace ProxyMystery
