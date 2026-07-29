# Overall Progress Log

## Date
2026-07-29

---

# Chess Engine Progress

## Engine

### Implemented Minimax Search
- Added recursive Minimax algorithm.
- White acts as maximizing player.
- Black acts as minimizing player.
- Uses board evaluation at search depth limit.
- Detects terminal positions:
  - Checkmate
  - Stalemate

---

### Move Generation

Implemented full move generation.

- Iterates over every board square.
- Finds all legal moves using `isValidMove()`.
- Generates a new `Board` object for each legal move.
- Automatically promotes pawns to queens during engine search.

Function added:

```cpp
generateMoves(...)
```

---

### Engine Move Selection

Implemented AI move selection.

- Generates all legal moves.
- Searches each move using Minimax.
- Chooses:
  - Highest evaluation for White
  - Lowest evaluation for Black

Function:

```cpp
engineMove(...)
```

Current search depth:

```
Depth = 4
```

---

### Evaluator Integration

Connected the evaluation system with the engine.

Search flow:

```
Generate Moves
      ↓
 Minimax Search
      ↓
 evaluate(board)
      ↓
 Best Move
```

The engine now makes decisions based on board evaluation instead of random legal moves.

---

# Main Game Loop

Reworked game loop to support multiple game modes.

Added:

- Player vs Player
- Player vs Black Bot
- Player vs White Bot

Created:

```cpp
enum GameMode
```

and menu selection UI.

---

# Bot Integration

Integrated engine into gameplay.

Features:

- Detects when it is the bot's turn.
- Calls:

```cpp
engineMove(board)
```

- Updates board automatically.
- Prevents human move during bot turn.
- Uses `goto render` to immediately redraw after engine move.

---

# Checkmate & Stalemate Detection

Added helper functions.

Implemented:

```cpp
hasAnyLegalMove()
```

Built:

```cpp
isCheckmate()
isStalemate()
```

Game now ends correctly when:

- Checkmate occurs
- Stalemate occurs

Overlay message displayed for game result.

---

# Promotion Handling

Separated promotion into its own dialog.

Added:

```cpp
handlePromotionDialog()
```

Features:

- Queen
- Rook
- Bishop
- Knight

Human promotion uses GUI.

Engine promotion automatically promotes to Queen.

---

# Rendering Improvements

Added overlay message rendering.

Function:

```cpp
drawOverlayMessage()
```

Displays:

- Checkmate
- Stalemate

without closing the game.

---

# Texture Loading

Improved texture loading.

Created:

```cpp
LoadPieceTextures()
```

Loads every piece texture using a loop instead of repeated code.

---

# Overall Architecture

Current engine flow:

```
Menu
    ↓
Game Loop
    ↓
Player/Bot Turn
    ↓
Generate Legal Moves
    ↓
Minimax Search
    ↓
Board Evaluation
    ↓
Best Move Selected
    ↓
Render Board
```

---

# Current Features

- ✅ PvP Mode
- ✅ Play vs Black AI
- ✅ Play vs White AI
- ✅ Minimax Search
- ✅ Static Evaluation
- ✅ Legal Move Generation
- ✅ Checkmate Detection
- ✅ Stalemate Detection
- ✅ Pawn Promotion
- ✅ Promotion GUI
- ✅ Automatic AI Queen Promotion
- ✅ Endgame Overlay Messages
- ✅ Engine integrated into main game loop

---

# Next Goals

- Alpha-Beta Pruning
- Piece-Square Tables
- Move Ordering
- Castling
- En Passant
- Opening Book
- Transposition Table (Zobrist Hashing)
- Quiescence Search
- Iterative Deepening
- Time-controlled Search
- Stronger Evaluation Function