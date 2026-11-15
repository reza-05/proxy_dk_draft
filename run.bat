@echo off
REM ===================================================================
REM  PROXY DILO KE? -- Windows Auto-Detect Build & Run Script
REM  CSE 4302: Object Oriented Programming Lab Term Project (IUT)
REM ===================================================================

chcp 65001 > nul
echo ===================================================================
echo   [PROXY DILO KE?] Detecting compiler and building...
echo ===================================================================

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] 'g++' compiler not found in PATH!
    echo Please install MinGW-w64 or add g++ to your Windows PATH.
    pause
    exit /b 1
)

set SRCS=src/CaseFile.cpp src/Character.cpp src/Detective.cpp src/Exceptions.cpp src/GameEngine.cpp src/Personality.cpp src/Statement.cpp src/Suspect.cpp src/main.cpp

REM 1. Try modern C++20 standard
echo Compiling with -std=c++20...
g++ -std=c++20 -Wall -Wextra -Iinclude %SRCS% -o proxydiloke.exe 2>nul
if %errorlevel% equ 0 goto build_success

REM 2. Fallback to C++17
echo Compiler does not recognize -std=c++20. Falling back to -std=c++17...
g++ -std=c++17 -Wall -Wextra -Iinclude %SRCS% -o proxydiloke.exe 2>nul
if %errorlevel% equ 0 goto build_success

REM 3. Fallback to C++14 (Supports legacy MinGW GCC 6.3.0)
echo Falling back to -std=c++14 (legacy MinGW support)...
g++ -std=c++14 -Wall -Wextra -Iinclude %SRCS% -o proxydiloke.exe
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Compilation failed! Please verify your GCC installation.
    pause
    exit /b %errorlevel%
)

:build_success
echo.
echo ===================================================================
echo [SUCCESS] Build completed successfully: proxydiloke.exe
echo Launching the game...
echo ===================================================================
echo.

proxydiloke.exe

pause
