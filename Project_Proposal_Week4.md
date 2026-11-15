# CSE 4302: Object Oriented Programming Lab
## Term Project Proposal (Week 4 Submission)

---

### Project Title:
**PROXY DILO KE? — The IUT Attendance Mystery**

### Team Members:
1. **Md. Shifat Reza** (Student ID: 210041001)
2. **Abrar Faiyaz** (Student ID: 210041002)
3. **Saraf** (Student ID: 210041003)
4. **Ariyan** (Student ID: 210041004)

---

### 1. Project Motivation & Problem Statement
Attendance manipulation through illicit proxies is an age-old phenomenon across academic institutions. In our university setting, keeping attendance transparent and fair is critical. 

*Proxy Dilo Ke?* takes inspiration from classic social deduction games (such as Mafia and Werewolf) and transforms the premise into a university-themed, text-based interactive investigation game built purely in modern C++ (C++20). 

A detective squad consisting of up to 4 human students must work collaboratively on a terminal console to expose a hidden "Proxy Syndicate" operating within a classroom, uncover the mastermind **"Proxy King"**, and interrogate AI-controlled student suspects before the semester ends.

---

### 2. Core Gameplay Mechanics

1. **Investigation Rounds:** 
   The investigation spans a maximum of 4 rounds. Each round provides the detective squad with a limited number of action points to spend.
2. **Interrogation & Statement Tracking:**
   Detectives can question different classroom archetypes (e.g., The CR, The Backbencher, The Topper, The Sleeper, The Latecomer, The Gossip Master) regarding their whereabouts, observations, and alibis during roll call.
3. **Contradiction Detection:**
   Honest students provide factual, consistent accounts. Members of the Proxy Syndicate fabricate stories. If a suspect contradicts their earlier statement across rounds, detectives can formally challenge them to earn investigation bonus points.
4. **High-Stakes Interrogation (Russian Roulette & Narrator's Gamble):**
   To break tight-lipped suspects, detectives can initiate a high-stakes confrontation inspired by Russian Roulette (1-in-6 chance of backfiring vs. 5-in-6 chance of extracting critical letter clues), or guess the Narrator's secret number (1 to 4) for forensic alibi confirmations.
5. **Classroom Trial & Expulsion Vote:**
   At the end of each round, detectives cast a collective vote to expose a suspect. Exposing the Proxy King triggers immediate victory. Wrongly accusing an innocent student incurs a disciplinary penalty.

---

### 3. Object-Oriented Design & Course Concept Mapping

This project strictly adheres to all core OOP principles mandated in the CSE 4302 lab syllabus:

1. **Classes & Encapsulation:**
   - Every class is cleanly segregated into `.h` (declarations) and `.cpp` (definitions).
   - Strict data hiding with `private` and `protected` fields.
   - Const-correctness implemented across all non-mutating member functions and object references.
   - Zero global variables; state is encapsulated within instances.
2. **Inheritance:**
   - Abstract Base Class: `Character` (encapsulating general attributes: `name`, `id`).
   - Derived Classes: `Detective` (accumulates scores and actions) and `Suspect` (maintains statement logs and hidden roles).
3. **Polymorphism:**
   - Virtual functions declared in `Character`: `virtual void displayProfile() const = 0` and `virtual std::string getRoleDescription() const = 0`.
   - Overridden dynamically by `Detective` and `Suspect` at runtime.
4. **Exception Handling:**
   - Custom exception hierarchy rooted at `ProxyGameException` (derived from `std::exception`).
   - Handles `InvalidInputException`, `FileNotFoundException`, and `SuspectUnavailableException` through structured `try-catch` blocks.
5. **File I/O & Persistence:**
   - `CaseFile::loadSuspectsFromFile()` reads suspect templates and alibis from `data/case_config.txt` via `std::ifstream`.
   - `CaseFile::saveCaseArchive()` records investigation verdicts, final scores, and rosters to `data/case_archive.txt` via `std::ofstream`.
6. **Modern C++ & Memory Safety:**
   - Built under the C++20 standard using RAII principles and Standard Template Library (STL) containers (`std::vector`, `std::string`, `std::mt19937`). No naked memory leaks or unmanaged raw pointers.

---

### 4. Work Breakdown & Team Responsibility

| Member | Designated Role | Specific Class Deliverables |
| :--- | :--- | :--- |
| **Md. Shifat Reza** | Game Mechanics & Risk Systems | `GambleEngine.h/.cpp`, `GambleResult`, Point scoring algorithms |
| **Abrar Faiyaz** | Character Domain & OOP Hierarchy | `Character.h/.cpp`, `Detective.h/.cpp`, `Suspect.h/.cpp` |
| **Saraf** | Narrative, Dialogue & File I/O | `Personality.h/.cpp`, `Statement.h/.cpp`, `CaseFile.h/.cpp` |
| **Ariyan** | Engine Orchestration & Exceptions | `GameEngine.h/.cpp`, `Exceptions.h/.cpp`, `main.cpp`, `Makefile` |

---

### 5. Project Roadmap (Week 4 to Week 15)
* **Week 4:** Proposal submission & architecture approval.
* **Week 6 - 8:** Baseline game loop and character classes unit integration.
* **Week 9 - 11:** Polish contradiction detection, Russian Roulette probability balancing, and custom file I/O scenarios.
* **Week 12 - 14:** Edge case testing, input validation hardening, and documentation.
* **Week 15:** Final presentation and interactive live demo.
