@echo off
REM ===================================================================
REM  PROXY DILO KE? -- Windows Build & Run Script
REM  CSE 4302: Object Oriented Programming Lab Term Project (IUT)
REM ===================================================================

chcp 65001 > nul
echo ===================================================================
echo   [PROXY DILO KE?] Building with C++20 compiler...
echo ===================================================================

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] 'g++' compiler not found in PATH!
    echo Please install MinGW-w64 (MSYS2 or w64devkit) and ensure g++ is in your PATH.
    pause
    exit /b 1
)

echo Compiling source files from src/ with headers from include/...
g++ -std=c++20 -Wall -Wextra -Iinclude src/CaseFile.cpp src/Character.cpp src/Detective.cpp src/Exceptions.cpp src/GameEngine.cpp src/Personality.cpp src/Statement.cpp src/Suspect.cpp src/main.cpp -o proxydiloke.exe

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Compilation failed! Please ensure your compiler supports C++20.
    pause
    exit /b %errorlevel%
)

echo.
echo [SUCCESS] Build completed successfully: proxydiloke.exe
echo Launching the game...
echo ===================================================================
echo.

proxydiloke.exe

pause
