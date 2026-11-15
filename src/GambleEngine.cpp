#include "GambleEngine.h"
#include <iostream>

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
    std::cout << "Tumi " << suspectName << " er chokhe chokh rakhla.\n";
    std::cout << "\"Mama tumi micha kotha bolteso, amra 2 jon e jani. Dekhi tomar koto shahosh!\"\n";
    std::cout << "Revolver er cylinder ghurtese... [ * | . | . | . | . | . ]\n";
    std::cout << "Click... Clack... Shhhk...\n";

    if (chosenChamber == bulletChamber) {
        // BANG! (Failure)
        result.success = false;
        result.pointsDelta = -5;
        result.message = "💥 [GULI PHUTSE! BANG!] Gamble ulta kheye gelo! Course Instructor shune felse:\n"
                         "\"Ekhane lab er moddhe eshob ki hocche?! -5 Points disciplinary penalty!\"\n"
                         + suspectName + " voy peye gese, ei round e ar kono kotha bolbe na!";
        result.revealedClue = "";
    } else {
        // CLICK! (Success)
        result.success = true;
        result.pointsDelta = 8;
        if (isGuilty) {
            char hintChar = '?';
            for (char c : proxyKingName) {
                if (std::isalpha(c)) {
                    hintChar = std::toupper(c);
                    break;
                }
            }
            result.message = "⚡ [CLICK!] Bacha gelo! " + suspectName + " pressure e bhenge porlo!\n"
                             "\"Thamen bhai! Ami boltesi! Amader gang er karor naam e '"
                             + std::string(1, hintChar) + "' letter ta ache!\"\n"
                             "(+8 Investigation Points squad er score e jog hoise!)";
            result.revealedClue = "Letter hint: Naam e ache '" + std::string(1, hintChar) + "'";
        } else {
            result.message = "⚡ [CLICK!] Bacha gelo! " + suspectName + " kende kende bollo:\n"
                             "\"Bhai GPA er koshom, ami nirdosh! Ami dekhsilam " + proxyKingName + " sheet er kache ghurgur kortesilo!\"\n"
                             "(+8 Investigation Points squad er score e jog hoise!)";
            result.revealedClue = "Tip: Suspect " + proxyKingName + " re check koro";
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
    std::cout << "Narrator er secret number chilo: [" << narratorNumber << "] | Tomar guess: [" << playerGuess << "]\n";

    if (playerGuess == narratorNumber) {
        result.success = true;
        result.pointsDelta = 6;
        std::uniform_int_distribution<int> rewardDist(1, 2);
        if (rewardDist(m_rng) == 1 && !proxyKingName.empty()) {
            char hintChar = std::toupper(proxyKingName.back());
            result.message = "✨ MILSE! Narrator heshe ekta confidential clue dilo!\n"
                             "HINT: Proxy King er naam er shesh letter hocche '" + std::string(1, hintChar) + "'!\n"
                             "(+6 Points squad er score e jog hoise!)";
            result.revealedClue = "Proxy King er naam er shesh letter '" + std::string(1, hintChar) + "'";
        } else {
            result.message = "✨ MILSE! Forensic attendance alibi confirm hoise!\n"
                             "CONFIRMED INNOCENT: [" + innocentSampleName + "] er solid alibi ache!\n"
                             "(+6 Points squad er score e jog hoise!)";
            result.revealedClue = "[" + innocentSampleName + "] 100% nirdosh!";
        }
    } else {
        result.success = false;
        result.pointsDelta = -3;
        result.message = "❌ VUL GUESS! Narrator penalty dhorlo.\n"
                         "Penalty: -3 Points kata gelo squad er score theke!";
        result.revealedClue = "";
    }

    return result;
}

} // namespace ProxyMystery
