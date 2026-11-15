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
              << " | Actions Baki: " << m_actionsLeft << "/" << ACTIONS_PER_ROUND
              << " | Squad Score: " << getTeamScore() << " pts\n";
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "  [1] Suspect re Jera koro              (Cost: 1 Action)\n";
    std::cout << "  [2] Contradiction Dhoro / Batpar dhora! (Cost: 1 Action)\n";
    std::cout << "  [3] High-Stakes Russian Roulette       (Risk-Reward Gamble)\n";
    std::cout << "  [4] Narrator er 1-4 Gamble             (Secret Clue er jonno)\n";
    std::cout << "  [5] Evidence & Case Log Dekho\n";
    std::cout << "  [6] Suspect Dossier Dekho\n";
    std::cout << "  [7] Classroom Trial & Vote Dao         (Round Shesh korar Vote)\n";
    std::cout << "  [8] Khela bondho kore Exit koro\n";
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Ekta option choose koro (1-8): ";
}

void GameEngine::handleInterrogate() {
    if (m_actionsLeft <= 0) {
        std::cout << "\n⚠️ Ei round er shob action sesh! Please Classroom Trial & Vote [7] dao.\n";
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

    std::cout << "Suspect select koro (1-" << m_suspects.size() << ") ba cancel korte 0: ";
    int choice;
    if (!(std::cin >> choice) || choice < 0 || choice > static_cast<int>(m_suspects.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputException("Invalid suspect selection.");
    }

    if (choice == 0) return;
    size_t sIdx = choice - 1;

    if (m_suspects[sIdx].isExposed()) {
        throw SuspectUnavailableException(m_suspects[sIdx].getName() + " already exposed hoye gese!");
    }
    if (m_suspects[sIdx].isSilenced()) {
        throw SuspectUnavailableException(m_suspects[sIdx].getName() + " voy peye gese, kotha bolbe na!");
    }

    std::cout << "\n--- JIGESHBADER TOPIC SELECT KORO ---\n";
    std::cout << "  [1] Roll call er shomoy tumi koi chila?\n";
    std::cout << "  [2] Podium ba sir er desk er kache kaoke suspicious dekhso?\n";
    std::cout << "  [3] Lecture er shomoy tomar alibi ke confirm korbe?\n";
    std::cout << "Topic select koro (1-3): ";

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
        std::cout << "🎉 DHOMA-DHAM DHORA KHAISI! Contradiction dhora porse!\n";
        std::cout << "Details: " << details << "\n";
        std::cout << "(+3 Investigation Points squad er score e jog hoise!)\n";
        addTeamScore(3);
    } else {
        std::cout << "❌ Kono contradiction paowa jay nai!\n";
        std::cout << details << "\n";
        std::cout << "Suspect er kotha thik ache. (-1 Point bina karone challenge korar jonno)\n";
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

    std::cout << "\n💥 Teacher bolen: \"" << m_suspects[sIdx].getName()
              << ", shamne eshe nijer student ID khata dekhaw!\"\n";
    m_suspects[sIdx].exposeRole();
    RoleType role = m_suspects[sIdx].getRole();

    if (role == RoleType::PROXY_KING) {
        std::cout << "\n🏆 BINGO! KHELA KHOTOM! 👑\n";
        std::cout << "👑 " << m_suspects[sIdx].getName() << " E ASHELE PROXY KING!\n";
        std::cout << "Bag er bhitor theke aro 5 ta fake attendance card paowa gese!\n";
        std::cout << "(+10 Investigation Points squad er score e jog hoise!)\n";
        addTeamScore(10);
        m_detectivesWon = true;
        m_isGameOver = true;
    } else if (role == RoleType::PROXY_MEMBER) {
        std::cout << "\n🎯 TARGET HIT! " << m_suspects[sIdx].getName() << " PROXY GANG ER OPERATIVE!\n";
        std::cout << "O onner proxy ditsilo, but ashol Mastermind ekhono dhora pore nai!\n";
        std::cout << "(+5 Investigation Points squad er score e jog hoise!)\n";
        addTeamScore(5);
    } else {
        std::cout << "\n❌ SERIOUS VUL! " << m_suspects[sIdx].getName() << " EKDOM INNOCENT CHILO!\n";
        std::cout << "\"Bhai amar attendance 95%, amar upore doubt korlen?!\"\n";
        std::cout << "(-3 Points penalty vul allegation dewar jonno!)\n";
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
        std::cout << "🎉 VICTORY! Student Investigation Squad jitse!\n";
        std::cout << "IUT Room 302 er Proxy Syndicate pura bhenge dewa hoise!\n";
    } else {
        std::cout << "💀 DEFEAT! Shomoy shesh hoye gese!\n";
        std::cout << "Ashol Proxy King chilo: [" << m_proxyKingName << "]!\n";
        std::cout << "O 100% proxy attendance niye pass kore ber hoye gelo!\n";
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

    std::cout << "\n📢 INCIDENT REPORT (WEEK 2, SHOKAL 8:00 AM, ROOM 302):\n";
    std::cout << "Sir dekhlen 40 jon enrolled student er jaygay sheet e 45 ta sign pore gese!\n";
    std::cout << "CDS e khabar ar Rocket e cha sesh kore keu 5 ta batpar proxy dise!\n";
    std::cout << "Round 4 shesh howar agei Proxy King re dhoro!\n";

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
