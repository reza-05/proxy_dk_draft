# PROXY DILO KE? — The IUT Attendance Mystery
### CSE 4302: Object Oriented Programming Lab Term Project (C++20)

---

## 1. Project Overview & Storyline
**"Proxy Dilo Ke? The IUT Attendance Mystery"** is a social deduction and text-based investigation game set in a university classroom. During an 8:00 AM lab, 45 signatures were found on the attendance sheet despite only 40 students being present. Five illegal proxies were placed by a clandestine syndicate.

A team of up to 4 student detectives must interrogate suspects, analyze alibis, cross-reference statements to catch contradictions, and face high-stakes gambles (Russian Roulette & Narrator's Gamble) to unmask the **Proxy King** before Round 4 ends.

---

## 2. How to Compile and Run

### Prerequisites
* Operating System: Linux, macOS, or Windows (via WSL or MinGW)
* Compiler: `g++` or `clang++` supporting **C++20** standard (`-std=c++20`)
* Build utility: `make` (optional, standard compile command also provided)

### Compilation Commands
Using `make` (recommended):
```bash
make
```

Or direct compilation with `g++`:
```bash
g++ -std=c++20 -Wall -Wextra -Iinclude src/*.cpp -o proxydiloke
```

### Execution
Run the compiled binary:
```bash
./proxydiloke
```
Or with `make`:
```bash
make run
```

---

## 3. Sample Data Files & Conventions

External configuration files are located under the `data/` folder:
* **`data/case_config.txt`**: Contains suspect configurations and dialogue blueprints.
  - Format: `Name|ID|Archetype(0-5)|TrueLocation|FakeLocation`
  - If missing, the game automatically generates default student suspects with authentic campus archetypes.
* **`data/case_archive.txt`**: Automatically records persistent game logs, final squad scores, detective rosters, and victory/defeat records using `std::ofstream`.

---

## 4. Class Descriptions & Responsibilities

| Class Name | Header / Source | Purpose | Key Fields | Key Methods |
| :--- | :--- | :--- | :--- | :--- |
| **`Character`** | `Character.h` / `Character.cpp` | Abstract base class establishing character identity. | `m_name`, `m_id` | `getName()`, `displayProfile() = 0`, `getRoleDescription() = 0` |
| **`Detective`** | `Detective.h` / `Detective.cpp` | Derived from `Character`. Represents a human investigator. | `m_score` | `addScore()`, `deductScore()`, `displayProfile() override` |
| **`Suspect`** | `Suspect.h` / `Suspect.cpp` | Derived from `Character`. Represents automated student suspects. | `m_archetype`, `m_role`, `m_isExposed`, `m_history`, `m_trueLocation`, `m_fakeLocation` | `interrogate()`, `hasContradiction()`, `exposeRole()`, `displayProfile() override` |
| **`Statement`** | `Statement.h` / `Statement.cpp` | Encapsulates a single question-and-answer record. | `m_round`, `m_topic`, `m_dialogue`, `m_locationClaim`, `m_isLie` | `getDialogue()`, `getLocationClaim()`, `isLie()` |
| **`Personality`** | `Personality.h` / `Personality.cpp` | Formats realistic dialogue responses based on student archetypes (CR, Backbencher, etc.). | N/A (Static Utility) | `formatDialogue()` |
| **`GambleEngine`** | `GambleEngine.h` / `GambleEngine.cpp` | Russian Roulette (1 in 6) and Narrator's Gamble (1-4) risk-reward system. | `m_rng` (Mersenne Twister) | `playRussianRoulette()`, `playNarratorGamble()` |
| **`CaseFile`** | `CaseFile.h` / `CaseFile.cpp` | Handles File I/O for loading suspects and archiving results. | N/A | `loadSuspectsFromFile()`, `saveCaseArchive()` |
| **`GameEngine`** | `GameEngine.h` / `GameEngine.cpp` | Coordinates the game loop, menus, action points, and scoring. | `m_detectives`, `m_suspects`, `m_evidenceLog`, `m_currentRound` | `startGame()`, `handleInterrogate()`, `handleClassVote()` |

---

## 5. Object-Oriented Relationships & Architecture

### A. Inheritance Hierarchy
```
             ┌─────────────────┐
             │    Character    │  (Abstract Base Class)
             └────────┬────────┘
                      │
           ┌──────────┴──────────┐
           ▼                     ▼
  ┌─────────────────┐   ┌─────────────────┐
  │    Detective    │   │     Suspect     │
  └─────────────────┘   └─────────────────┘
```
* **Why used:** Both detectives and suspects share fundamental properties (`name`, `id`), but diverge in responsibilities: Detectives accumulate investigation scores, while Suspects maintain statement histories and hidden roles.

### B. Polymorphism
* Polymorphism is implemented via virtual functions in `Character`:
  - `virtual void displayProfile() const = 0;`
  - `virtual std::string getRoleDescription() const = 0;`
* `Detective` and `Suspect` override these virtual methods to render their respective profiles dynamically at runtime.

### C. Composition & Ownership
* `GameEngine` **owns** a collection of `Detective` instances and `Suspect` instances (`std::vector<Detective>`, `std::vector<Suspect>`).
* `Suspect` **owns** a collection of past statements (`std::vector<Statement>`) to detect inconsistencies and contradictions across rounds.
* `GameEngine` uses `GambleEngine` and `CaseFile` as helper services.

---

## 6. Exception Handling

The system defines custom exceptions derived from `std::exception` under namespace `ProxyMystery`:
* **`ProxyGameException`**: Base exception class for all domain-specific errors.
* **`InvalidInputException`**: Thrown when a player supplies an out-of-range option, malformed integer, or invalid string.
* **`FileNotFoundException`**: Thrown if `data/case_config.txt` cannot be read or opened.
* **`SuspectUnavailableException`**: Thrown if attempting to interrogate an already-exposed or silenced suspect.
* **`GameOverException`**: Raised during unexpected state termination.

All exceptions are caught gracefully inside `GameEngine` and `main.cpp` using hierarchical `try-catch` blocks, preventing raw program crashes.

---

## 7. Memory & Coding Standards Compliance
* **Memory Management:** Fully utilizes modern C++ RAII and standard library containers (`std::vector`, `std::string`, `std::ifstream`, `std::ofstream`). No raw dynamic pointers or memory leaks.
* **Const Correctness:** All non-mutating member functions are designated `const` (e.g., `displayProfile() const`, `getName() const`). Heavy objects are passed via `const &`.
* **Zero Global Variables:** All game state is encapsulated within `GameEngine`.
* **File Separation:** Declarations reside in `.h` headers and implementations in `.cpp` source files with `#pragma once`.

---

## 8. Authors & Contributions

* **Md. Shifat Reza**: Core Game Concept, Gamble Engine (Russian Roulette & Narrator's Gamble), Scoring and Risk-Reward Balance.
* **Abrar Faiyaz**: Project Conceptualization, Character Hierarchy (`Character`, `Detective`, `Suspect`), Polymorphic Methods.
* **Saraf**: Dialogue & Personality System (`Personality`, `Statement`), File I/O & Case Configuration (`CaseFile`).
* **Ariyan**: Game Loop & Round State Machine (`GameEngine`), Menu Navigation, Custom Exception Hierarchy (`Exceptions`).
