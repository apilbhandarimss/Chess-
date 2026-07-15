# Chess Engine in C++ using Raylib

## Overview

This project is a simple object-oriented chess engine developed in **C++** using the **Raylib** graphics library. The project demonstrates the implementation of a graphical chessboard, piece rendering, user interaction, and basic chess move validation.

The engine currently focuses on building the core architecture of a chess engine. Players can move pieces using the mouse, and the program validates moves before updating the board. At the current stage, pawn movement has been implemented as the first legal piece movement, providing a foundation for adding the remaining chess rules.

---

# Objectives

* Implement a chess board using Object-Oriented Programming.
* Display chess pieces using Raylib textures.
* Allow users to move pieces using the mouse.
* Validate legal moves before updating the board.
* Build a modular architecture that can easily be expanded into a complete chess engine.

---

# Features

* Graphical chess board using Raylib
* Mouse-based piece selection
* Piece movement
* Turn management
* Legal move validation
* Pawn movement implementation
* Texture-based chess pieces
* Object-oriented code structure
* Easy to extend with additional chess rules

---

# Project Structure

```
ChessEngine/
│
├── main.cpp
├── Board.cpp
├── Board.h
├── RuleChecker.cpp
├── RuleChecker.h
│
├── 3d_wood/
│   ├── wp.png
│   ├── wr.png
│   ├── wn.png
│   ├── wb.png
│   ├── wq.png
│   ├── wk.png
│   ├── bp.png
│   ├── br.png
│   ├── bn.png
│   ├── bb.png
│   ├── bq.png
│   └── bk.png
│
└── README.md
```

---

# Program Flow

The application follows the following execution sequence:

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
Initialize Chess Board
      │
      ▼
Game Loop
      │
      ├── Detect Mouse Click
      │
      ├── Select Piece
      │
      ├── Attempt Move
      │
      ├── Validate Move
      │
      ├── Update Board
      │
      └── Draw Board
      │
      ▼
Close Window
```

---

# File Description

## main.cpp

This file contains the entry point of the application.

Responsibilities include:

* Creating the game window
* Loading textures
* Creating the Board object
* Running the game loop
* Calling movement logic
* Rendering the chess board
* Releasing textures before closing

---

## Board.h

Defines the Board class.

Contains:

* Chess board representation
* Current player's turn
* Function declarations

---

## Board.cpp

Responsible for all board-related operations.

Functions include:

### Board Constructor

Initializes the board.

### initl()

Places every chess piece in its standard starting position.

### drawBoard()

Draws:

* Chess board
* Chess pieces
* Sidebar

### move()

Handles player interaction.

Its responsibilities include:

* Detecting mouse clicks
* Selecting pieces
* Deselecting pieces
* Moving pieces
* Calling the move validator
* Switching turns

---

## RuleChecker.h

Contains function declarations related to move validation.

---

## RuleChecker.cpp

Implements the chess rules.

Currently implemented:

* White pawn one-square movement
* White pawn two-square opening move
* Black pawn one-square movement
* Black pawn two-square opening move

The file compares two board states to determine:

* Source square
* Destination square
* Piece being moved

After identifying the move, the function checks whether it follows the implemented chess rules.

---

# Board Representation

The chess board is stored as an 8×8 character array.

Example:

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

Uppercase letters represent white pieces.

Lowercase letters represent black pieces.

| Character | Piece        |
| --------- | ------------ |
| P         | White Pawn   |
| R         | White Rook   |
| N         | White Knight |
| B         | White Bishop |
| Q         | White Queen  |
| K         | White King   |
| p         | Black Pawn   |
| r         | Black Rook   |
| n         | Black Knight |
| b         | Black Bishop |
| q         | Black Queen  |
| k         | Black King   |
| Space     | Empty Square |

---

# Piece Textures

Each chess piece uses a PNG texture stored inside the **3d_wood** folder.

Example mapping:

```
white_pawn   -> wp.png
white_rook   -> wr.png
white_knight -> wn.png
white_bishop -> wb.png
white_queen  -> wq.png
white_king   -> wk.png

black_pawn   -> bp.png
black_rook   -> br.png
black_knight -> bn.png
black_bishop -> bb.png
black_queen  -> bq.png
black_king   -> bk.png
```

Textures are loaded once at startup and unloaded before the application exits.

---

# Mouse Interaction

The movement system follows these steps:

1. Player clicks a piece.
2. The piece becomes selected.
3. Player clicks the destination square.
4. A temporary board is created.
5. The move is applied to the temporary board.
6. The move is validated.
7. If valid, the actual board is updated.
8. The turn switches to the opposite player.

---

# Implemented Rules

Current implementation supports:

* White pawn single move
* White pawn double opening move
* Black pawn single move
* Black pawn double opening move
* Turn-based movement
* Piece selection
* Move cancellation by clicking the selected piece again

---

# Future Improvements

Planned features include:

* Rook movement
* Knight movement
* Bishop movement
* Queen movement
* King movement
* Pawn captures
* En passant
* Pawn promotion
* Castling
* Check detection
* Checkmate detection
* Stalemate detection
* Undo move
* Move history
* Board evaluation
* Minimax search
* Alpha-Beta pruning
* FEN support
* PGN support

---

# Technologies Used

* C++
* Raylib
* Object-Oriented Programming (OOP)

---

# How to Run

1. Install Raylib.
2. Clone the repository.
3. Build the project using your preferred compiler or CMake.
4. Ensure the **3d_wood** folder is located beside the executable.
5. Run the program.

---

# Conclusion

This project serves as the foundation of a complete chess engine developed using C++ and Raylib. It demonstrates object-oriented design, graphical rendering, user interaction, and move validation while maintaining a modular structure that can be extended with additional chess rules, search algorithms, and engine features.
