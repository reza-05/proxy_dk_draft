#pragma once
#include <string>
#include "Enums.h"

namespace ProxyMystery {

class Personality {
public:
    static std::string formatDialogue(Archetype archetype, QuestionTopic topic,
                                      const std::string& location, const std::string& witness,
                                      bool isLie, const std::string& proxyKingName);
};

} // namespace ProxyMystery
