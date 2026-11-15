#include "GameEngine.h"
#include "CaseFile.h"
#include "Exceptions.h"
#include "TerminalColor.h"
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
    std::cout << Color::BOLD_CYAN << "+------------------------------------------------------------------+\n";
    std::cout << "|                                                                  |\n";
    std::cout << "|       " << Color::BOLD_YELLOW << "██████╗ ██████╗  ██████╗ ██╗  ██╗██╗   ██╗" << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|       " << Color::BOLD_YELLOW << "██╔══██╗██╔══██╗██╔═══██╗╚██╗██╔╝╚██╗ ██╔╝" << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|       " << Color::BOLD_YELLOW << "██████╔╝██████╔╝██║   ██║ ╚███╔╝  ╚████╔╝ " << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|       " << Color::BOLD_YELLOW << "██╔═══╝ ██╔══██╗██║   ██║ ██╔██╗   ╚██╔╝  " << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|       " << Color::BOLD_YELLOW << "██║     ██║  ██║╚██████╔╝██╔╝ ██╗   ██║   " << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|       " << Color::BOLD_YELLOW << "╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝   " << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|                                                                  |\n";
    std::cout << "|             " << Color::BOLD_WHITE << "D I L O   K E ?   (Room 302 Mystery)" << Color::BOLD_CYAN << "                 |\n";
    std::cout << "|                                                                  |\n";
    std::cout << "+------------------------------------------------------------------+\n";
    std::cout << "|      " << Color::YELLOW << "IUT Attendance Mystery: 45 Responses, 40 Students!" << Color::BOLD_CYAN << "          |\n";
    std::cout << "|    " << Color::WHITE << "4 Detectives. A Room Full of Suspects. Catch the King!" << Color::BOLD_CYAN << "        |\n";
    std::cout << "+------------------------------------------------------------------+\n" << Color::RESET << "\n";
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
    std::cout << Color::BOLD_WHITE << "Enter number of student detectives (1 to 4) [Default: 4]: " << Color::RESET;
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
        std::cout << "Enter Detective #" << (i + 1) << " Name [Default: " << Color::CYAN << defaultNames[i] << Color::RESET << "]: ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty()) {
            name = defaultNames[i];
        }
        std::string id = "DET-" + std::to_string(210041000 + i + 1);
        m_detectives.emplace_back(name, id);
    }

    std::cout << "\n" << Color::BOLD_GREEN << "✅ Detective Squad Registered! Sir bolen: 'Proxy dhora na pora porjonto shobai 302 tei thakbe!'" << Color::RESET << "\n";
}

void GameEngine::printMenu() const {
    std::cout << "\n" << Color::BOLD_CYAN << "+------------------------------------------------------------------+\n";
    std::cout << "| " << Color::BOLD_WHITE << "ROUND " << m_currentRound << "/" << MAX_ROUNDS << Color::RESET
              << Color::BOLD_CYAN << "  |  Actions Baki: " << (m_actionsLeft > 0 ? Color::BOLD_GREEN : Color::BOLD_RED)
              << m_actionsLeft << "/" << ACTIONS_PER_ROUND << Color::RESET
              << Color::BOLD_CYAN << "  |  Squad Score: " << Color::BOLD_YELLOW << getTeamScore() << " pts" << Color::RESET
              << Color::BOLD_CYAN << "             |\n";
    std::cout << "+------------------------------------------------------------------+\n" << Color::RESET;
    std::cout << "  " << Color::BOLD_CYAN << "[1]" << Color::RESET << " Suspect re Jera koro              " << Color::DIM << "(Cost: 1 Action)\n" << Color::RESET;
    std::cout << "  " << Color::BOLD_CYAN << "[2]" << Color::RESET << " " << Color::BOLD_YELLOW << "Contradiction Dhoro / Batpar dhora!" << Color::RESET << " " << Color::DIM << "(Cost: 1 Action)\n" << Color::RESET;
    std::cout << "  " << Color::BOLD_CYAN << "[3]" << Color::RESET << " " << Color::BOLD_MAGENTA << "High-Stakes Russian Roulette" << Color::RESET << "       " << Color::DIM << "(Risk-Reward Gamble)\n" << Color::RESET;
    std::cout << "  " << Color::BOLD_CYAN << "[4]" << Color::RESET << " " << Color::MAGENTA << "Narrator er 1-4 Gamble" << Color::RESET << "             " << Color::DIM << "(Secret Clue er jonno)\n" << Color::RESET;
    std::cout << "  " << Color::BOLD_CYAN << "[5]" << Color::RESET << " Evidence & Case Log Dekho\n";
    std::cout << "  " << Color::BOLD_CYAN << "[6]" << Color::RESET << " Suspect Dossier Dekho\n";
    std::cout << "  " << Color::BOLD_CYAN << "[7]" << Color::RESET << " " << Color::BOLD_RED << "Classroom Trial & Vote Dao" << Color::RESET << "         " << Color::DIM << "(Round Shesh korar Vote)\n" << Color::RESET;
    std::cout << "  " << Color::BOLD_CYAN << "[8]" << Color::RESET << " " << Color::DIM << "Khela bondho kore Exit koro\n" << Color::RESET;
    std::cout << Color::BOLD_CYAN << "----------------------------------------------------------------------\n" << Color::RESET;
    std::cout << Color::BOLD_WHITE << "Ekta option choose koro (1-8): " << Color::RESET;
}

void GameEngine::handleInterrogate() {
    if (m_actionsLeft <= 0) {
        std::cout << "\n" << Color::BOLD_RED << "⚠️ Ei round er shob action sesh! Please Classroom Trial & Vote [7] dao.\n" << Color::RESET;
        return;
    }

    std::cout << "\n" << Color::BOLD_CYAN << "--- CHOOSE A SUSPECT TO QUESTION ---\n" << Color::RESET;
    for (size_t i = 0; i < m_suspects.size(); ++i) {
        std::cout << "  " << Color::CYAN << "[" << (i + 1) << "]" << Color::RESET << " "
                  << Color::BOLD_WHITE << m_suspects[i].getName() << Color::RESET
                  << " (" << archetypeToString(m_suspects[i].getArchetype()) << ")";
        if (m_suspects[i].isExposed()) {
            std::cout << " " << Color::BOLD_RED << "[EXPOSED]" << Color::RESET;
        } else if (m_suspects[i].isSilenced()) {
            std::cout << " " << Color::BOLD_MAGENTA << "[SILENCED]" << Color::RESET;
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

    std::cout << "\n" << Color::BOLD_CYAN << "--- JIGESHBADER TOPIC SELECT KORO ---\n" << Color::RESET;
    std::cout << "  [1] Roll call er shomoy tumi koi chila?\n";
    std::cout << "  [2] Roll call e kaoke gala change kore fake response dite dekhso/shunso?\n";
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

    std::cout << "\n" << Color::BOLD_CYAN << "+------------------------------------------------------------------+\n";
    std::cout << "| 🗣️  " << Color::BOLD_WHITE << m_suspects[sIdx].getName() << Color::DIM << " ("
              << archetypeToString(m_suspects[sIdx].getArchetype()) << ") bollo:\n" << Color::RESET;
    std::cout << Color::BOLD_CYAN << "+------------------------------------------------------------------+\n";
    std::cout << Color::BOLD_YELLOW << "  \"" << stmt.getDialogue() << "\"\n" << Color::RESET;
    std::cout << Color::BOLD_CYAN << "+------------------------------------------------------------------+\n" << Color::RESET;

    std::ostringstream logEntry;
    logEntry << "[R" << m_currentRound << "] " << m_suspects[sIdx].getName() << ": \""
             << stmt.getDialogue() << "\"";
    m_evidenceLog.push_back(logEntry.str());

    --m_actionsLeft;
}

void GameEngine::handleChallengeContradiction() {
    if (m_actionsLeft <= 0) {
        std::cout << "\n" << Color::BOLD_RED << "⚠️ No actions left this round! Please vote to conclude the round.\n" << Color::RESET;
        return;
    }

    std::cout << "\n" << Color::BOLD_CYAN << "--- ACCUSE A SUSPECT OF CONTRADICTION ---\n" << Color::RESET;
    for (size_t i = 0; i < m_suspects.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << Color::BOLD_WHITE << m_suspects[i].getName() << Color::RESET
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
        std::cout << Color::BOLD_GREEN << "🎉 DHOMA-DHAM DHORA KHAISI! Contradiction dhora porse!\n";
        std::cout << "Details: " << details << "\n";
        std::cout << "(+3 Investigation Points squad er score e jog hoise!)\n" << Color::RESET;
        addTeamScore(3);
    } else {
        std::cout << Color::BOLD_RED << "❌ Kono contradiction paowa jay nai!\n";
        std::cout << details << "\n";
        std::cout << "Suspect er kotha thik ache. (-1 Point bina karone challenge korar jonno)\n" << Color::RESET;
        deductTeamScore(1);
    }
    std::cout << "------------------------------------------------------\n";

    --m_actionsLeft;
}

void GameEngine::handleRussianRoulette() {
    std::cout << "\n" << Color::BOLD_MAGENTA << "--- RUSSIAN ROULETTE / KILLER'S GAMBLE ---\n" << Color::RESET;
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
    std::cout << "\n" << Color::BOLD_CYAN << "--- THE NARRATOR'S 1-4 GAMBLE ---\n" << Color::RESET;
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
    std::cout << "\n" << Color::BOLD_CYAN << "======================================================\n";
    std::cout << "                 CASE EVIDENCE LOG                     \n";
    std::cout << "======================================================\n" << Color::RESET;
    if (m_evidenceLog.empty()) {
        std::cout << Color::DIM << "No statements or clues recorded yet. Go interrogate someone!\n" << Color::RESET;
    } else {
        for (size_t i = 0; i < m_evidenceLog.size(); ++i) {
            std::cout << " " << Color::CYAN << "[" << (i + 1) << "]" << Color::RESET << " "
                      << Color::WHITE << m_evidenceLog[i] << Color::RESET << "\n";
        }
    }
    std::cout << Color::BOLD_CYAN << "======================================================\n" << Color::RESET;
}

void GameEngine::handleDossier() const {
    std::cout << "\n" << Color::BOLD_CYAN << "======================================================\n";
    std::cout << "               CLASS SUSPECT DOSSIER                   \n";
    std::cout << "======================================================\n" << Color::RESET;
    for (const auto& s : m_suspects) {
        s.displayProfile();
        std::cout << Color::DIM << "------------------------------------------------------\n" << Color::RESET;
    }
}

void GameEngine::handleClassVote() {
    std::cout << "\n" << Color::BOLD_RED << "======================================================\n";
    std::cout << "          CLASSROOM TRIAL & EXPULSION VOTE            \n";
    std::cout << "======================================================\n" << Color::RESET;
    std::cout << Color::BOLD_WHITE << "The Squad must now vote on a suspect to officially accuse!\n" << Color::RESET;

    for (size_t i = 0; i < m_suspects.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << Color::BOLD_WHITE << m_suspects[i].getName() << Color::RESET
                  << " (" << archetypeToString(m_suspects[i].getArchetype()) << ")";
        if (m_suspects[i].isExposed()) {
            std::cout << " " << Color::BOLD_RED << "[ALREADY EXPOSED]" << Color::RESET;
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
        std::cout << Color::YELLOW << "⚠️ That student has already been revealed! Vote cancelled.\n" << Color::RESET;
        return;
    }

    std::cout << "\n" << Color::BOLD_WHITE << "💥 Teacher bolen: \"" << m_suspects[sIdx].getName()
              << ", shamne eshe nijer phone unlock koro!\"\n" << Color::RESET;
    m_suspects[sIdx].exposeRole();
    RoleType role = m_suspects[sIdx].getRole();

    if (role == RoleType::PROXY_KING) {
        std::cout << "\n" << Color::BOLD_YELLOW << "🏆 BINGO! KHELA KHOTOM! 👑\n";
        std::cout << "👑 " << m_suspects[sIdx].getName() << " E ASHELE PROXY KING!\n";
        std::cout << "Phone er WhatsApp e 5 jon absent friend er 'Present sir' daak dewar confession paowa gese!\n";
        std::cout << "(+10 Investigation Points squad er score e jog hoise!)\n" << Color::RESET;
        addTeamScore(10);
        m_detectivesWon = true;
        m_isGameOver = true;
    } else if (role == RoleType::PROXY_MEMBER) {
        std::cout << "\n" << Color::BOLD_GREEN << "🎯 TARGET HIT! " << m_suspects[sIdx].getName() << " PROXY GANG ER OPERATIVE!\n";
        std::cout << "O gala change kore arekjon er fake roll call ditsilo, but ashol Mastermind ekhono dhora pore nai!\n";
        std::cout << "(+5 Investigation Points squad er score e jog hoise!)\n" << Color::RESET;
        addTeamScore(5);
    } else {
        std::cout << "\n" << Color::BOLD_RED << "❌ SERIOUS VUL! " << m_suspects[sIdx].getName() << " EKDOM INNOCENT CHILO!\n";
        std::cout << "\"Sir ami shudhu nijer roll call e 'Present sir' bolsilam, onner ta dei nai!\"\n";
        std::cout << "(-3 Points penalty vul allegation dewar jonno!)\n" << Color::RESET;
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
        std::cout << "\n" << Color::BOLD_CYAN << "🔔 The bell rings! Entering Round " << m_currentRound << " of " << MAX_ROUNDS << "!\n" << Color::RESET;
    }
}

void GameEngine::checkGameConditions() {
    std::cout << "\n" << Color::BOLD_CYAN << "======================================================\n";
    std::cout << "                 CASE CLOSED SUMMARY                  \n";
    std::cout << "======================================================\n" << Color::RESET;

    if (m_detectivesWon) {
        std::cout << Color::BOLD_GREEN << "🎉 VICTORY! Student Investigation Squad jitse!\n";
        std::cout << "IUT Room 302 er Proxy Syndicate pura bhenge dewa hoise!\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "💀 DEFEAT! Shomoy shesh hoye gese!\n";
        std::cout << "Ashol Proxy King chilo: [" << m_proxyKingName << "]!\n";
        std::cout << "O 100% proxy attendance niye pass kore ber hoye gelo!\n" << Color::RESET;
    }

    std::cout << "\n" << Color::BOLD_YELLOW << "FINAL TEAM SCORE: " << getTeamScore() << " POINTS\n" << Color::RESET;
    std::cout << "DETECTIVE ROSTER:\n";
    for (const auto& det : m_detectives) {
        det.displayProfile();
    }
    std::cout << Color::BOLD_CYAN << "======================================================\n" << Color::RESET;

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
    std::cout << Color::DIM << "📁 Case record archived successfully to: " << m_archivePath << Color::RESET << "\n";
}

void GameEngine::startGame() {
    try {
        CaseFile::loadSuspectsFromFile(m_configPath, m_suspects, m_proxyKingName);
    } catch (const std::exception& e) {
        std::cerr << "[Exception] " << e.what() << "\n";
        return;
    }

    setupDetectives();

    std::cout << "\n" << Color::BOLD_YELLOW << "📢 INCIDENT REPORT (WEEK 2, SHOKAL 8:00 AM, ROOM 302):\n" << Color::RESET;
    std::cout << Color::WHITE << "Sir class e matha gune dekhlen 40 jon student boshe ache, kintu roll call e 45 jon 'Present sir' bolse!\n";
    std::cout << "Pechon theke gala change kore 5 ta absent friend er fake proxy daak dewa hoise!\n";
    std::cout << "Round 4 shesh howar agei Proxy King re dhoro!\n" << Color::RESET;

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
            std::cout << "\n" << Color::BOLD_RED << "⚠️ Invalid choice. Please enter a number between 1 and 8.\n" << Color::RESET;
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
            std::cout << "\n" << Color::BOLD_RED << pge.what() << Color::RESET << "\n";
        } catch (const std::exception& ex) {
            std::cout << "\n" << Color::BOLD_RED << "[Standard Error] " << ex.what() << Color::RESET << "\n";
        }
    }

    checkGameConditions();
}

} // namespace ProxyMystery
