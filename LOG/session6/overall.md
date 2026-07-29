# Overall Development Log

## Session Summary

This session focused on moving the engine from a simple material-search chess program into a more complete chess engine with a stronger evaluation function and improved game flow.

---

# Engine

## Minimax Search
- Implemented recursive Minimax search.
- Added configurable search depth (currently 4 plies).
- Search alternates between maximizing (White) and minimizing (Black).
- Detects terminal positions:
  - Checkmate
  - Stalemate
- Returns large positive/negative values for checkmate.

---

## Move Generation

Implemented `generateMoves()`.

Features:
- Generates all legal moves for the side to move.
- Filters illegal moves through `isValidMove()`.
- Automatically promotes pawns to queens during engine search.
- Produces candidate board states directly for Minimax.

---

## Engine Move Selection

Implemented `engineMove()`.

Features:
- Generates all legal moves.
- Evaluates each move using Minimax.
- Chooses the highest evaluation for White.
- Chooses the lowest evaluation for Black.

---

# Evaluation

## Initial Material Evaluation

Connected the evaluator to the engine.

Added material scoring:

| Piece | Value |
|-------|------:|
| Pawn | 82 |
| Knight | 337 |
| Bishop | 365 |
| Rook | 477 |
| Queen | 1025 |

(Kings excluded from material score.)

---

## PeSTO Evaluation

Replaced the simple evaluator with a PeSTO-inspired tapered evaluation.

Added:

- Midgame piece values
- Endgame piece values
- Piece-square tables for:
  - Pawn
  - Knight
  - Bishop
  - Rook
  - Queen
  - King
- Game phase interpolation
- Midgame/endgame score blending

Evaluation now considers:

- Material
- Piece placement
- Opening vs endgame differences
- Automatic transition between game phases

---

## Evaluation Infrastructure

Implemented helper functions:

- `pieceIndex()`
- `mgTableValue()`
- `egTableValue()`

Added:

- Phase weights
- Total phase calculation
- Board mirroring for black pieces
- Midgame/endgame interpolation

---

# GUI

## Main Menu

Added a graphical menu.

Modes:

- Player vs Player
- Player vs Black Bot
- Player vs White Bot

---

## AI Integration

Connected the engine to the GUI.

The bot now:

- Detects when it is its turn.
- Calls `engineMove()`.
- Updates the board.
- Skips human input during AI turns.

---

## Promotion

Implemented promotion dialog for human players.

Features:

- Queen
- Rook
- Bishop
- Knight

Bot promotions automatically become queens.

---

## Game End Detection

Implemented:

- Checkmate detection
- Stalemate detection

Added overlay messages displaying the game result.

---

# Rule Support

Current supported rules:

- Legal move validation
- Check detection
- Checkmate
- Stalemate
- Pawn promotion
- Castling support (flag-based implementation)
- Automatic queen promotion for engine search

---

# Internal Improvements

Improved overall engine structure.

Separated responsibilities into:

- Engine
- Evaluator
- RuleChecker
- Board
- Main

The engine now performs:

Generate Moves
→ Evaluate
→ Minimax Search
→ Best Move Selection

instead of relying only on raw material comparisons.

---

# Next Goals

- Alpha-Beta Pruning
- Move Ordering
- Transposition Table (Zobrist Hashing)
- Quiescence Search
- Mobility Evaluation
- Passed Pawn Evaluation
- Doubled/Isolated Pawn Penalties
- Bishop Pair Bonus
- Rook Open File Bonus
- King Safety Evaluation
- Killer Move Heuristic
- History Heuristic
- Iterative Deepening
- Opening Book