#include "GambleEngine.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace ProxyMystery {

GambleEngine::GambleEngine() {
    std::random_device rd;
    m_rng.seed(rd());
}

GambleResult GambleEngine::playRussianRoulette(const std::string& suspectName, bool isGuilty,
                                              const std::string& proxyKingName) {
    GambleResult result;
    std::uniform_int_distribution<int> chamberDist(1, 6);
    int bulletChamber = 1; // Chamber 1 has the live round
    int chosenChamber = chamberDist(m_rng);

    std::cout << "\n======================================================\n";
    std::cout << "  HIGH STAKES INTERROGATION: RUSSIAN ROULETTE (1 in 6)  \n";
    std::cout << "======================================================\n";
    std::cout << "You look " << suspectName << " dead in the eye.\n";
    std::cout << "\"You're lying, and we both know it. Let's see how much you value your secret.\"\n";
    std::cout << "Spinning the cylinder... [ * | . | . | . | . | . ]\n";
    std::cout << "Click... Clack... Shhhk...\n";

    if (chosenChamber == bulletChamber) {
        // BANG! (Failure)
        result.success = false;
        result.pointsDelta = -5;
        result.message = "💥 [BANG!] The gamble backfires violently! The Course Instructor steps in:\n"
                         "\"Detectives! What is this unruliness during lab?! -5 Points for harassment!\"\n"
                         + suspectName + " is terrified and refuses to speak for the rest of this round!";
        result.revealedClue = "";
    } else {
        // CLICK! (Success)
        result.success = true;
        result.pointsDelta = 8;
        if (isGuilty) {
            // Find a letter from Proxy King's name
            char hintChar = '?';
            for (char c : proxyKingName) {
                if (std::isalpha(c)) {
                    hintChar = std::toupper(c);
                    break;
                }
            }
            result.message = "⚡ [CLICK!] Safe! " + suspectName + " cracks under the intense pressure!\n"
                             "\"FINE! Stop! I'll talk! Someone in our gang has the letter '"
                             + std::string(1, hintChar) + "' in their name!\"\n"
                             "(+8 Investigation Points awarded for breaking the suspect!)";
            result.revealedClue = "Letter hint: Name contains '" + std::string(1, hintChar) + "'";
        } else {
            result.message = "⚡ [CLICK!] Safe! " + suspectName + " bursts into tears of innocence:\n"
                             "\"I swear on my GPA, I'm innocent! I saw " + proxyKingName + " acting suspiciously near the sheets!\"\n"
                             "(+8 Investigation Points awarded!)";
            result.revealedClue = "Confidential tip: Check suspect " + proxyKingName;
        }
    }

    return result;
}

GambleResult GambleEngine::playNarratorGamble(int playerGuess, const std::string& proxyKingName,
                                             const std::string& innocentSampleName) {
    GambleResult result;
    std::uniform_int_distribution<int> dist(1, 4);
    int narratorNumber = dist(m_rng);

    std::cout << "\n--- THE NARRATOR'S GAMBLE (1 - 4) ---\n";
    std::cout << "Narrator chose: [" << narratorNumber << "] | Your guess: [" << playerGuess << "]\n";

    if (playerGuess == narratorNumber) {
        result.success = true;
        result.pointsDelta = 6;
        std::uniform_int_distribution<int> rewardDist(1, 2);
        if (rewardDist(m_rng) == 1 && !proxyKingName.empty()) {
            char hintChar = std::toupper(proxyKingName.back());
            result.message = "✨ CORRECT GUESS! The Narrator smiles and drops a classified lab hint!\n"
                             "HINT: The Proxy King's name ends with the letter '" + std::string(1, hintChar) + "'!\n"
                             "(+6 Points added to your team score!)";
            result.revealedClue = "The Proxy King's name ends with letter '" + std::string(1, hintChar) + "'";
        } else {
            result.message = "✨ CORRECT GUESS! Forensic attendance analysis complete!\n"
                             "CONFIRMED INNOCENT: [" + innocentSampleName + "] has an unbreakable alibi!\n"
                             "(+6 Points added to your team score!)";
            result.revealedClue = "[" + innocentSampleName + "] is 100% innocent!";
        }
    } else {
        result.success = false;
        result.pointsDelta = -3;
        result.message = "❌ WRONG GUESS! The Narrator collects the penalty.\n"
                         "Penalty: -3 Points from your squad's score!";
        result.revealedClue = "";
    }

    return result;
}

} // namespace ProxyMystery
