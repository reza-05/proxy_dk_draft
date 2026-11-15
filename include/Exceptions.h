#pragma once
#include <exception>
#include <string>

namespace ProxyMystery {

class ProxyGameException : public std::exception {
protected:
    std::string m_message;

public:
    explicit ProxyGameException(const std::string& message);
    [[nodiscard]] const char* what() const noexcept override;
};

class InvalidInputException : public ProxyGameException {
public:
    explicit InvalidInputException(const std::string& message);
};

class FileNotFoundException : public ProxyGameException {
public:
    explicit FileNotFoundException(const std::string& filePath);
};

class SuspectUnavailableException : public ProxyGameException {
public:
    explicit SuspectUnavailableException(const std::string& suspectName);
};

class GameOverException : public ProxyGameException {
public:
    explicit GameOverException(const std::string& reason);
};

} // namespace ProxyMystery
