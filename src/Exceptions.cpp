#include "Exceptions.h"

namespace ProxyMystery {

ProxyGameException::ProxyGameException(const std::string& message)
    : m_message(message) {}

const char* ProxyGameException::what() const noexcept {
    return m_message.c_str();
}

InvalidInputException::InvalidInputException(const std::string& message)
    : ProxyGameException("[Error] Invalid Input: " + message) {}

FileNotFoundException::FileNotFoundException(const std::string& filePath)
    : ProxyGameException("[Error] File Not Found or Inaccessible: " + filePath) {}

SuspectUnavailableException::SuspectUnavailableException(const std::string& suspectName)
    : ProxyGameException("[Warning] Suspect " + suspectName + " is currently unavailable or already exposed.") {}

GameOverException::GameOverException(const std::string& reason)
    : ProxyGameException("[Notice] Game Over: " + reason) {}

} // namespace ProxyMystery
