# Chess Engine in C++ using Raylib

# Overview

This project is an object-oriented chess engine written in **C++** using the **Raylib** graphics library. The project implements a complete graphical chess game together with the foundation of a real chess engine.

The application supports human vs human and human vs AI gameplay, validates legal chess moves, detects checkmate and stalemate, performs pawn promotion, and includes a Minimax search engine with a tapered positional evaluation based on PeSTO piece-square tables.

The project is designed with modularity in mind, making it easy to extend with stronger search algorithms and more advanced evaluation techniques.

---

# Objectives

- Build a modular chess engine using Object-Oriented Programming.
- Implement complete chess rules.
- Develop a graphical interface using Raylib.
- Implement a working AI using Minimax.
- Create a strong positional evaluation function.
- Provide a clean architecture for future engine improvements.

---

# Features

## Graphical Interface

- Raylib-based GUI
- Wooden chess piece textures
- Mouse-based piece movement
- Interactive promotion dialog
- Main menu
- Endgame overlay messages

---

## Game Modes

- Player vs Player
- Player vs Black AI
- Player vs White AI

---

## Chess Rules

Implemented:

- Pawn movement
- Pawn captures
- Knight movement
- Bishop movement
- Rook movement
- Queen movement
- King movement
- Castling
- Pawn promotion
- Check detection
- Checkmate detection
- Stalemate detection
- Turn management
- Illegal move prevention

Engine search automatically promotes pawns to queens.

---

## Chess Engine

Implemented:

- Legal move generation
- Recursive Minimax search
- Depth-limited search
- Automatic move selection
- Checkmate scoring
- Stalemate evaluation

---

## Evaluation Function

Current evaluator includes:

- Material evaluation
- Midgame piece values
- Endgame piece values
- Piece-Square Tables (PeSTO)
- Positional scoring
- Game phase calculation
- Midgame / Endgame interpolation

Evaluation considers:

- Material advantage
- Piece placement
- Opening vs endgame differences
- Automatic transition between game phases

---

# Project Structure

```
ChessEngine/
│
├── include/
│   ├── Board.h
│   ├── Engine.h
│   ├── Evaluator.h
│   └── RuleChecker.h
│
├── src/
│   ├── main.cpp
│   ├── Board.cpp
│   ├── Engine.cpp
│   ├── Evaluator.cpp
│   └── RuleChecker.cpp
│
├── 3d_wood/
│
├── CMakeLists.txt
└── README.md
```

---

# Program Flow

```
Start Program
      │
      ▼
Create Window
      │
      ▼
Load Piece Textures
      │
      ▼
Display Main Menu
      │
      ▼
Select Game Mode
      │
      ▼
Initialize Board
      │
      ▼
Main Game Loop
      │
      ├── Check Game State
      │       │
      │       ├── Checkmate?
      │       └── Stalemate?
      │
      ├── AI Turn?
      │       │
      │       └── Engine Search
      │
      ├── Human Input
      │
      ├── Validate Move
      │
      ├── Update Board
      │
      ├── Promotion
      │
      └── Render Board
      │
      ▼
Close Window
```

---

# File Description

## main.cpp

Responsible for:

- Window creation
- Texture loading
- Main menu
- Game loop
- AI integration
- Promotion dialog
- Rendering
- Game-over detection

---

## Board.cpp

Responsible for:

- Board representation
- Piece rendering
- Mouse interaction
- Piece movement
- Turn switching
- Promotion state

---

## RuleChecker.cpp

Responsible for all chess rules.

Includes:

- Piece movement validation
- Check detection
- Castling validation
- Promotion handling
- Legal move verification

---

## Engine.cpp

Contains the chess engine.

Implements:

- Move generation
- Minimax search
- Engine move selection
- Automatic queen promotion during search

---

## Evaluator.cpp

Responsible for board evaluation.

Implements:

- Material evaluation
- Piece-square tables
- Midgame evaluation
- Endgame evaluation
- Phase interpolation
- Final positional score

---

# Board Representation

The chess board is stored as an 8×8 character array.

```
r n b q k b n r
p p p p p p p p
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
P P P P P P P P
R N B Q K B N R
```

Uppercase letters represent White pieces.

Lowercase letters represent Black pieces.

| Character | Piece |
|-----------|-------|
| P | White Pawn |
| N | White Knight |
| B | White Bishop |
| R | White Rook |
| Q | White Queen |
| K | White King |
| p | Black Pawn |
| n | Black Knight |
| b | Black Bishop |
| r | Black Rook |
| q | Black Queen |
| k | Black King |

---

# Engine Search

Current search algorithm:

```
Current Position
       │
       ▼
Generate Legal Moves
       │
       ▼
For Each Move
       │
       ▼
Minimax Search
       │
       ▼
Evaluate Position
       │
       ▼
Choose Best Move
```

Current search depth:

```
4 plies
```

---

# Evaluation Pipeline

```
Board
   │
   ▼
Material Score
   │
   ▼
Piece-Square Tables
   │
   ▼
Midgame Score
   │
   ▼
Endgame Score
   │
   ▼
Game Phase Calculation
   │
   ▼
Tapered Evaluation
   │
   ▼
Final Score
```

---

# Current Evaluation Components

✔ Material values

✔ Piece-square tables

✔ Midgame evaluation

✔ Endgame evaluation

✔ Tapered evaluation

✔ Positional bonuses

---

# Technologies Used

- C++
- Raylib
- CMake
- Object-Oriented Programming

---

# Future Improvements

## Search

- Alpha-Beta Pruning
- Iterative Deepening
- Quiescence Search
- Transposition Tables
- Zobrist Hashing
- Killer Move Heuristic
- History Heuristic

## Evaluation

- Mobility evaluation
- Passed pawns
- Isolated pawns
- Doubled pawns
- Backward pawns
- Bishop pair bonus
- Connected rooks
- Open files
- Semi-open files
- King safety
- Pawn shield
- Piece mobility
- Hanging piece detection
- Static Exchange Evaluation (SEE)

## Features

- Undo/Redo
- Move history
- PGN support
- FEN support
- UCI protocol
- Opening book
- Endgame tablebases

---

# How to Build

## Prerequisites

- CMake 3.11 or newer
- A C++17 compatible compiler
- Git (optional, for cloning)

---

## Windows (MSYS2 + MinGW)

Install:
- MSYS2
- `mingw-w64-x86_64-gcc`
- `mingw-w64-x86_64-cmake`

Build:

```bash
cmake -B build -G "MinGW Makefiles"
cmake --build build
```

Run:

```bash
./build/ChessEngineOOP.exe
```

---

## Windows (Visual Studio 2022)

Open a **Developer Command Prompt for Visual Studio**.

Build:

```powershell
cmake -B build
cmake --build build --config Release
```

Run:

```powershell
.\build\Release\ChessEngineOOP.exe
```

---

## Linux

### Install dependencies

Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake
```

Arch Linux:

```bash
sudo pacman -S base-devel cmake
```

Fedora:

```bash
sudo dnf install gcc-c++ cmake
```

Build:

```bash
cmake -B build
cmake --build build
```

Run:

```bash
./build/ChessEngineOOP
```

---

## macOS

Install prerequisites using Homebrew:

```bash
brew install cmake
```

Build:

```bash
cmake -B build
cmake --build build
```

Run:

```bash
./build/ChessEngineOOP
```

Ensure the **3d_wood** directory is copied beside the executable before running.

---

# Conclusion

This project has evolved from a simple chess GUI into a functional chess engine capable of playing complete games. It combines legal move generation, graphical interaction, and a Minimax-based AI with a tapered positional evaluation using PeSTO piece-square tables. The modular architecture provides a solid foundation for implementing stronger search algorithms, advanced evaluation heuristics, and competitive engine features in future development.