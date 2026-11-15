#pragma once
#include <string>
#include <random>

namespace ProxyMystery {

struct GambleResult {
    bool success;
    int pointsDelta;
    std::string message;
    std::string revealedClue;
};

class GambleEngine {
private:
    std::mt19937 m_rng;

public:
    GambleEngine();

    // Russian Roulette: 6-chamber cylinder, 1 chamber triggers backfire
    GambleResult playRussianRoulette(const std::string& suspectName, bool isGuilty,
                                    const std::string& proxyKingName);

    // Narrator's 1-4 Gamble
    GambleResult playNarratorGamble(int playerGuess, const std::string& proxyKingName,
                                   const std::string& innocentSampleName);
};

} // namespace ProxyMystery
