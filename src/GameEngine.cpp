#include "GameEngine.h"
#include "CaseFile.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

namespace ProxyMystery {

GameEngine::GameEngine(std::string configPath, std::string archivePath)
    : m_currentRound(1),
      m_actionsLeft(ACTIONS_PER_ROUND),
      m_isGameOver(false),
      m_detectivesWon(false),
      m_configPath(std::move(configPath)),
      m_archivePath(std::move(archivePath)) {}

void GameEngine::printBanner() const {
    std::cout << "\n";
    std::cout << "======================================================================\n";
    std::cout << "   ____  ____  ______  ____  __   ____  ____   ___       __  ________ \n";
    std::cout << "  / __ \\/ __ \\/ __ \\ \\/ /\\ \\/ /  / __ \\/  _/  /   |     / / / /_  __/ \n";
    std::cout << " / /_/ / /_/ / / / /\\  /  \\  /  / / / // /   / /| |    / / / / / /    \n";
    std::cout << "/ ____/ _, _/ /_/ / / /   / /  / /_/ // /   / ___ |   / /_/ / / /     \n";
    std::cout << "/_/   /_/ |_|\\____/ /_/  /_/  /_____/___/  /_/  |_|   \\____/ /_/      \n";
    std::cout << "                --- THE IUT ATTENDANCE MYSTERY ---                    \n";
    std::cout << "======================================================================\n";
    std::cout << "   4 Investigators. A Room Full of Suspects. Expose the Proxy King!   \n";
    std::cout << "======================================================================\n\n";
}

int GameEngine::getTeamScore() const {
    int total = 0;
    for (const auto& det : m_detectives) {
        total += det.getScore();
    }
    return total;
}

void GameEngine::addTeamScore(int points) {
    if (m_detectives.empty()) return;
    int share = points / static_cast<int>(m_detectives.size());
    int rem = points % static_cast<int>(m_detectives.size());
    for (size_t i = 0; i < m_detectives.size(); ++i) {
        m_detectives[i].addScore(share + (i == 0 ? rem : 0));
    }
}

void GameEngine::deductTeamScore(int points) {
    if (m_detectives.empty()) return;
    int share = points / static_cast<int>(m_detectives.size());
    for (auto& det : m_detectives) {
        det.deductScore(share);
    }
}

void GameEngine::setupDetectives() {
    printBanner();
    std::cout << "Enter number of student detectives (1 to 4) [Default: 4]: ";
    std::string input;
    std::getline(std::cin, input);

    int count = 4;
    if (!input.empty()) {
        try {
            count = std::stoi(input);
            if (count < 1 || count > 4) count = 4;
        } catch (...) {
            count = 4;
        }
    }

    std::vector<std::string> defaultNames = {"Shifat (Lead Detective)", "Abrar", "Saraf", "Ariyan"};
    for (int i = 0; i < count; ++i) {
        std::cout << "Enter Detective #" << (i + 1) << " Name [Default: " << defaultNames[i] << "]: ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty()) {
            name = defaultNames[i];
        }
        std::string id = "DET-" + std::to_string(210041000 + i + 1);
        m_detectives.emplace_back(name, id);
    }

    std::cout << "\n✅ Detective Squad Registered! The teacher hands you the attendance binder.\n";
}

void GameEngine::printMenu() const {
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << " ROUND " << m_currentRound << "/" << MAX_ROUNDS
              << " | Actions Left: " << m_actionsLeft << "/" << ACTIONS_PER_ROUND
              << " | Squad Score: " << getTeamScore() << " pts\n";
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "  [1] Interrogate a Suspect             (Cost: 1 Action)\n";
    std::cout << "  [2] Challenge a Contradiction (Liar!) (Cost: 1 Action)\n";
    std::cout << "  [3] High-Stakes Russian Roulette      (Killer's Confrontation)\n";
    std::cout << "  [4] The Narrator's Gamble             (Guess 1-4 for Bonuses)\n";
    std::cout << "  [5] Review Evidence & Case Log\n";
    std::cout << "  [6] Inspect Suspect Dossier\n";
    std::cout << "  [7] Call Class Trial & Cast Vote      (End of Round Accusation)\n";
    std::cout << "  [8] Concede & Exit Game\n";
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Choose an action (1-8): ";
}

void GameEngine::handleInterrogate() {
    if (m_actionsLeft <= 0) {
        std::cout << "\n⚠️ No actions left in Round " << m_currentRound
                  << "! You must Call Class Trial & Cast Vote [7] to proceed.\n";
        return;
    }

    std::cout << "\n--- CHOOSE A SUSPECT TO QUESTION ---\n";
    for (size_t i = 0; i < m_suspects.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << m_suspects[i].getName()
                  << " (" << archetypeToString(m_suspects[i].getArchetype()) << ")";
        if (m_suspects[i].isExposed()) {
            std::cout << " [EXPOSED]";
        } else if (m_suspects[i].isSilenced()) {
            std::cout << " [SILENCED]";
        }
        std::cout << "\n";
    }

    std::cout << "Select suspect (1-" << m_suspects.size() << ") or 0 to cancel: ";
    int choice;
    if (!(std::cin >> choice) || choice < 0 || choice > static_cast<int>(m_suspects.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Invalid suspect selection.");
    }

    if (choice == 0) return;
    size_t sIdx = choice - 1;

    if (m_suspects[sIdx].isExposed()) {
        throw SuspectUnavailableException(m_suspects[sIdx].getName() + " has already been exposed!");
    }
    if (m_suspects[sIdx].isSilenced()) {
        throw SuspectUnavailableException(m_suspects[sIdx].getName() + " is terrified and refuses to speak!");
    }

    std::cout << "\n--- SELECT QUESTION TOPIC ---\n";
    std::cout << "  [1] Where were you during attendance roll call?\n";
    std::cout << "  [2] Did you notice anyone acting suspicious near the teacher's podium?\n";
    std::cout << "  [3] Who can verify your alibi during lecture?\n";
    std::cout << "Select topic (1-3): ";

    int tChoice;
    if (!(std::cin >> tChoice) || tChoice < 1 || tChoice > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Invalid topic selection.");
    }

    QuestionTopic topic = static_cast<QuestionTopic>(tChoice);
    size_t witnessIdx = (sIdx + 1) % m_suspects.size();
    std::string witnessName = m_suspects[witnessIdx].getName();

    Statement stmt = m_suspects[sIdx].interrogate(topic, m_currentRound, m_proxyKingName, witnessName);

    std::cout << "\n======================================================\n";
    std::cout << " 🗣️  " << m_suspects[sIdx].getName() << " answers:\n";
    std::cout << " \"" << stmt.getDialogue() << "\"\n";
    std::cout << "======================================================\n";

    std::ostringstream logEntry;
    logEntry << "[R" << m_currentRound << "] " << m_suspects[sIdx].getName() << ": \""
             << stmt.getDialogue() << "\"";
    m_evidenceLog.push_back(logEntry.str());

    --m_actionsLeft;
}

void GameEngine::handleChallengeContradiction() {
    if (m_actionsLeft <= 0) {
        std::cout << "\n⚠️ No actions left this round! Please vote to conclude the round.\n";
        return;
    }

    std::cout << "\n--- ACCUSE A SUSPECT OF CONTRADICTION ---\n";
    for (size_t i = 0; i < m_suspects.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << m_suspects[i].getName()
                  << " (" << m_suspects[i].getHistory().size() << " statements recorded)\n";
    }
    std::cout << "Select suspect to challenge (1-" << m_suspects.size() << ") or 0 to cancel: ";

    int choice;
    if (!(std::cin >> choice) || choice < 0 || choice > static_cast<int>(m_suspects.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Invalid choice for contradiction challenge.");
    }
    if (choice == 0) return;

    size_t sIdx = choice - 1;
    std::string details;
    bool caught = m_suspects[sIdx].hasContradiction(details);

    std::cout << "\n------------------------------------------------------\n";
    std::cout << "  INVESTIGATION CHALLENGE: " << m_suspects[sIdx].getName() << "\n";
    std::cout << "------------------------------------------------------\n";
    if (caught) {
        std::cout << "🎉 BUSTED! Contradiction Proven!\n";
        std::cout << "Details: " << details << "\n";
        std::cout << "(+3 Investigation Points awarded!)\n";
        addTeamScore(3);
    } else {
        std::cout << "❌ No contradiction found!\n";
        std::cout << details << "\n";
        std::cout << "The suspect's story holds up. (-1 Point for baseless challenge)\n";
        deductTeamScore(1);
    }
    std::cout << "------------------------------------------------------\n";

    --m_actionsLeft;
}

void GameEngine::handleRussianRoulette() {
    std::cout << "\n--- RUSSIAN ROULETTE / KILLER'S GAMBLE ---\n";
    std::cout << "Select a suspect to corner with high-stakes interrogation:\n";
    for (size_t i = 0; i < m_suspects.size(); ++i) {
        if (!m_suspects[i].isExposed() && !m_suspects[i].isSilenced()) {
            std::cout << "  [" << (i + 1) << "] " << m_suspects[i].getName() << "\n";
        }
    }
    std::cout << "Choose (1-" << m_suspects.size() << ") or 0 to cancel: ";

    int choice;
    if (!(std::cin >> choice) || choice < 0 || choice > static_cast<int>(m_suspects.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Invalid suspect index for Russian Roulette.");
    }
    if (choice == 0) return;

    size_t sIdx = choice - 1;
    bool isGuilty = (m_suspects[sIdx].getRole() != RoleType::HONEST_STUDENT);

    GambleResult gr = m_gambleEngine.playRussianRoulette(m_suspects[sIdx].getName(), isGuilty, m_proxyKingName);

    std::cout << "\n" << gr.message << "\n";
    if (gr.pointsDelta > 0) {
        addTeamScore(gr.pointsDelta);
    } else {
        deductTeamScore(-gr.pointsDelta);
        m_suspects[sIdx].setSilenced(true);
    }

    if (!gr.revealedClue.empty()) {
        m_evidenceLog.push_back("[CLUE] " + gr.revealedClue);
    }
}

void GameEngine::handleNarratorGamble() {
    std::cout << "\n--- THE NARRATOR'S 1-4 GAMBLE ---\n";
    std::cout << "The Narrator offers a gamble: Guess a number between 1 and 4.\n";
    std::cout << "Enter your guess (1-4): ";

    int guess;
    if (!(std::cin >> guess) || guess < 1 || guess > 4) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Guess must be between 1 and 4.");
    }

    std::string innocentName = "Unknown";
    for (const auto& s : m_suspects) {
        if (s.getRole() == RoleType::HONEST_STUDENT) {
            innocentName = s.getName();
            break;
        }
    }

    GambleResult gr = m_gambleEngine.playNarratorGamble(guess, m_proxyKingName, innocentName);
    std::cout << "\n" << gr.message << "\n";

    if (gr.pointsDelta > 0) {
        addTeamScore(gr.pointsDelta);
    } else {
        deductTeamScore(-gr.pointsDelta);
    }

    if (!gr.revealedClue.empty()) {
        m_evidenceLog.push_back("[NARRATOR CLUE] " + gr.revealedClue);
    }
}

void GameEngine::handleReviewLog() const {
    std::cout << "\n======================================================\n";
    std::cout << "                 CASE EVIDENCE LOG                     \n";
    std::cout << "======================================================\n";
    if (m_evidenceLog.empty()) {
        std::cout << "No statements or clues recorded yet. Go interrogate someone!\n";
    } else {
        for (size_t i = 0; i < m_evidenceLog.size(); ++i) {
            std::cout << " [" << (i + 1) << "] " << m_evidenceLog[i] << "\n";
        }
    }
    std::cout << "======================================================\n";
}

void GameEngine::handleDossier() const {
    std::cout << "\n======================================================\n";
    std::cout << "               CLASS SUSPECT DOSSIER                   \n";
    std::cout << "======================================================\n";
    for (const auto& s : m_suspects) {
        s.displayProfile();
        std::cout << "------------------------------------------------------\n";
    }
}

void GameEngine::handleClassVote() {
    std::cout << "\n======================================================\n";
    std::cout << "          CLASSROOM TRIAL & EXPULSION VOTE            \n";
    std::cout << "======================================================\n";
    std::cout << "The Squad must now vote on a suspect to officially accuse!\n";

    for (size_t i = 0; i < m_suspects.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << m_suspects[i].getName()
                  << " (" << archetypeToString(m_suspects[i].getArchetype()) << ")";
        if (m_suspects[i].isExposed()) {
            std::cout << " [ALREADY EXPOSED]";
        }
        std::cout << "\n";
    }
    std::cout << "Enter the suspect number you are voting against: ";

    int choice;
    if (!(std::cin >> choice) || choice < 1 || choice > static_cast<int>(m_suspects.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Invalid suspect selection for vote.");
    }

    size_t sIdx = choice - 1;
    if (m_suspects[sIdx].isExposed()) {
        std::cout << "⚠️ That student has already been revealed! Vote cancelled.\n";
        return;
    }

    std::cout << "\n💥 The Teacher demands: \"" << m_suspects[sIdx].getName()
              << ", step forward and show your student handbook!\"\n";
    m_suspects[sIdx].exposeRole();
    RoleType role = m_suspects[sIdx].getRole();

    if (role == RoleType::PROXY_KING) {
        std::cout << "\n🏆 BINGO! JACKPOT!\n";
        std::cout << "👑 " << m_suspects[sIdx].getName() << " IS THE PROXY KING!\n";
        std::cout << "Found hiding multiple attendance cards in their bag!\n";
        std::cout << "(+10 Investigation Points awarded!)\n";
        addTeamScore(10);
        m_detectivesWon = true;
        m_isGameOver = true;
    } else if (role == RoleType::PROXY_MEMBER) {
        std::cout << "\n🎯 SUCCESS! " << m_suspects[sIdx].getName() << " is a PROXY GANG OPERATIVE!\n";
        std::cout << "They were signing fake initials, but the mastermind remains uncaught!\n";
        std::cout << "(+5 Investigation Points awarded!)\n";
        addTeamScore(5);
    } else {
        std::cout << "\n❌ DISASTER! " << m_suspects[sIdx].getName() << " is an INNOCENT STUDENT!\n";
        std::cout << "\"How could you suspect me?! I have 95% attendance!\"\n";
        std::cout << "(-3 Points penalty for false accusation!)\n";
        deductTeamScore(3);
    }

    endRound();
}

void GameEngine::endRound() {
    if (m_isGameOver) return;

    ++m_currentRound;
    m_actionsLeft = ACTIONS_PER_ROUND;

    // Reset silence states for new round
    for (auto& s : m_suspects) {
        s.setSilenced(false);
    }

    if (m_currentRound > MAX_ROUNDS) {
        m_isGameOver = true;
        m_detectivesWon = false;
    } else {
        std::cout << "\n🔔 The bell rings! Entering Round " << m_currentRound << " of " << MAX_ROUNDS << "!\n";
    }
}

void GameEngine::checkGameConditions() {
    std::cout << "\n======================================================\n";
    std::cout << "                 CASE CLOSED SUMMARY                  \n";
    std::cout << "======================================================\n";

    if (m_detectivesWon) {
        std::cout << "🎉 VICTORY! The Student Investigation Squad triumphs!\n";
        std::cout << "The Proxy Syndicate has been dismantled at IUT!\n";
    } else {
        std::cout << "💀 DEFEAT! Time ran out!\n";
        std::cout << "The real Proxy King was: [" << m_proxyKingName << "]!\n";
        std::cout << "They successfully escaped punishment and graduated with 100% proxy attendance!\n";
    }

    std::cout << "\nFINAL TEAM SCORE: " << getTeamScore() << " POINTS\n";
    std::cout << "DETECTIVE ROSTER:\n";
    for (const auto& det : m_detectives) {
        det.displayProfile();
    }
    std::cout << "======================================================\n";

    // Save archive file
    std::ostringstream archiveReport;
    archiveReport << "CASE REPORT: IUT Attendance Mystery\n"
                  << "Result: " << (m_detectivesWon ? "VICTORY (Proxy King Caught)" : "DEFEAT (Proxy King Escaped)") << "\n"
                  << "Proxy King: " << m_proxyKingName << "\n"
                  << "Final Score: " << getTeamScore() << " pts\n"
                  << "Detectives: ";
    for (const auto& d : m_detectives) {
        archiveReport << d.getName() << " (" << d.getScore() << " pts), ";
    }
    CaseFile::saveCaseArchive(m_archivePath, archiveReport.str());
    std::cout << "📁 Case record archived successfully to: " << m_archivePath << "\n";
}

void GameEngine::startGame() {
    try {
        CaseFile::loadSuspectsFromFile(m_configPath, m_suspects, m_proxyKingName);
    } catch (const std::exception& e) {
        std::cerr << "[Exception] " << e.what() << "\n";
        return;
    }

    setupDetectives();

    std::cout << "\n📢 INCIDENT REPORT (WEEK 2, 8:00 AM CSE LAB):\n";
    std::cout << "Sir noticed that out of 40 enrolled students, 45 signed the sheet!\n";
    std::cout << "5 illegal proxies were placed. Uncover the Proxy King before Round 4 ends!\n";

    while (!m_isGameOver) {
        printMenu();
        int opt;
        if (!(std::cin >> opt)) {
            if (std::cin.eof()) {
                m_isGameOver = true;
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n⚠️ Invalid choice. Please enter a number between 1 and 8.\n";
            continue;
        }

        try {
            switch (opt) {
                case 1: handleInterrogate(); break;
                case 2: handleChallengeContradiction(); break;
                case 3: handleRussianRoulette(); break;
                case 4: handleNarratorGamble(); break;
                case 5: handleReviewLog(); break;
                case 6: handleDossier(); break;
                case 7: handleClassVote(); break;
                case 8:
                    std::cout << "\nExiting investigation. Goodbye!\n";
                    m_isGameOver = true;
                    break;
                default:
                    throw InvalidInputException("Selection must be between 1 and 8.");
            }
        } catch (const ProxyGameException& pge) {
            std::cout << "\n" << pge.what() << "\n";
        } catch (const std::exception& ex) {
            std::cout << "\n[Standard Error] " << ex.what() << "\n";
        }
    }

    checkGameConditions();
}

} // namespace ProxyMystery
