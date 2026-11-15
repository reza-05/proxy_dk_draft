#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Detective.h"
#include "Suspect.h"

namespace ProxyMystery {

class GameEngine {
private:
    std::vector<Detective> m_detectives;
    std::vector<Suspect> m_suspects;
    std::string m_proxyKingName;
    int m_currentRound;
    static constexpr int MAX_ROUNDS = 4;
    int m_actionsLeft;
    static constexpr int ACTIONS_PER_ROUND = 3;
    std::vector<std::string> m_evidenceLog;
    bool m_isGameOver;
    bool m_detectivesWon;
    std::string m_configPath;
    std::string m_archivePath;

    void printBanner() const;
    void printMenu() const;
    void handleInterrogate();
    void handleReviewLog() const;
    void handleChallengeContradiction();
    void handleClassVote();
    void handleDossier() const;
    void endRound();
    void checkGameConditions();
    [[nodiscard]] int getTeamScore() const;
    void addTeamScore(int points);
    void deductTeamScore(int points);

public:
    GameEngine(std::string configPath = "data/case_config.txt",
               std::string archivePath = "data/case_archive.txt");

    void setupDetectives();
    void startGame();
};

} // namespace ProxyMystery
