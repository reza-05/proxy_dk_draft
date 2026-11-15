#pragma once
#include <string>
#include <vector>
#include "Suspect.h"

namespace ProxyMystery {

class CaseFile {
public:
    static void loadSuspectsFromFile(const std::string& filePath,
                                    std::vector<Suspect>& outSuspects,
                                    std::string& outProxyKingName);

    static void saveCaseArchive(const std::string& filePath,
                                const std::string& caseSummary);

    static void createDefaultConfigIfNotExists(const std::string& filePath);
};

} // namespace ProxyMystery
