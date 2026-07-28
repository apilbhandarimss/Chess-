# Session 3 - Main Loop, Turn Management, and Game End Detection

## Overview

This session focused on building the main game loop and implementing complete game state detection. The engine can now determine whether the current position is checkmate or stalemate and display the appropriate result on screen.

---

## Features Added

### Piece Texture Loading

Implemented `LoadPieceTextures()` to load all chess piece textures from the `3d_wood` directory.

Supported textures:

* White Pawn
* White Knight
* White Bishop
* White Rook
* White Queen
* White King
* Black Pawn
* Black Knight
* Black Bishop
* Black Rook
* Black Queen
* Black King

All textures are stored inside the global `pieceTexture` map for easy lookup during rendering.

---

### Legal Move Detection

Implemented:

```cpp
bool hasAnyLegalMove(const Board& board, bool whiteToMove);
```

This function:

* Iterates through every square on the board.
* Finds every piece belonging to the side to move.
* Generates every possible destination square.
* Creates a temporary board.
* Uses `isValidMove()` to verify legality.
* Returns immediately when a legal move is found.

If no legal moves exist, the function returns `false`.

---

### Checkmate Detection

Implemented:

```cpp
bool isCheckmate(const Board& board, bool whiteToMove);
```

Logic:

* King must currently be in check.
* Side to move must have no legal moves.

Formula:

```
Checkmate =
King In Check
AND
No Legal Moves
```

---

### Stalemate Detection

Implemented:

```cpp
bool isStalemate(const Board& board, bool whiteToMove);
```

Logic:

* King is **not** in check.
* Side to move has no legal moves.

Formula:

```
Stalemate =
King NOT In Check
AND
No Legal Moves
```

---

## Turn Management

Added

```cpp
bool whiteToMove = true;
```

The turn switches only after a successful move.

Current implementation:

```cpp
Board before = b;
move(b);

if (b.squares != before.squares)
    whiteToMove = !whiteToMove;
```

This prevents changing turns if the player attempts an illegal move.

---

## Main Game Loop

The game loop now performs the following steps:

1. Check for checkmate.
2. Check for stalemate.
3. Allow the current player to move.
4. Switch turns if the board changed.
5. Draw the updated board.

This creates a complete playable gameplay loop.

---

## End Game Display

When checkmate occurs:

* A semi-transparent overlay is drawn.
* The winning side is displayed.

Example:

```
Black wins by checkmate!
```

or

```
White wins by checkmate!
```

When stalemate occurs:

```
Stalemate - Draw!
```

The board remains visible beneath the message.

---

## Resource Cleanup

Before closing the application:

```cpp
for(auto& texture : pieceTexture)
    UnloadTexture(texture.second);
```

All loaded textures are released to prevent memory leaks.

Finally:

```cpp
CloseWindow();
```

closes the Raylib window safely.

---

## Current Architecture

```
main.cpp
│
├── Initialize Window
├── Load Textures
├── Main Loop
│   ├── Checkmate Detection
│   ├── Stalemate Detection
│   ├── Handle Player Move
│   ├── Switch Turns
│   └── Draw Board
│
├── Cleanup Textures
└── Close Window
```

---

## Current Progress

Completed:

* Board representation
* Piece movement
* Move validation
* Turn management
* Check detection
* Checkmate detection
* Stalemate detection
* Texture loading
* Rendering loop
* End-game overlays
* Resource cleanup

---

## Next Goals (Session 4)

Planned improvements:

* Castling
* En passant
* Pawn promotion
* Undo move
* Move history
* FEN import/export
* AI integration using the Engine and Evaluator classes
* Minimax with alpha-beta pruning
* Legal move highlighting
* Check highlighting
* Game restart functionality
