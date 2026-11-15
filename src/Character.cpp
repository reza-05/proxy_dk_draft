#include "Character.h"

namespace ProxyMystery {

Character::Character(const std::string& name, const std::string& id)
    : m_name(name), m_id(id) {}

const std::string& Character::getName() const {
    return m_name;
}

const std::string& Character::getId() const {
    return m_id;
}

} // namespace ProxyMystery
