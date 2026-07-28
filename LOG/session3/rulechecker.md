# Session 3 - RuleChecker

## Overview

This session significantly expanded the move validation system. The RuleChecker now supports complete movement validation for every standard chess piece, check detection, castling validation, en passant, self-check prevention, and helper functions for board traversal.

---

# Helper Functions

## Piece Identification

Implemented helper functions:

```cpp
bool isWhitePiece(char piece);
bool isBlackPiece(char piece);
```

These determine ownership using ASCII ranges.

* White pieces: `A-Z`
* Black pieces: `a-z`

These helpers are reused throughout the engine for move validation and check detection.

---

## Straight Path Validation

Implemented

```cpp
bool isPathClearStraight(...)
```

Purpose:

* Rook movement
* Queen horizontal movement
* Queen vertical movement

The function walks square-by-square between the source and destination.

If any square is occupied, the path is blocked.

---

## Diagonal Path Validation

Implemented

```cpp
bool isPathClearDiagonal(...)
```

Purpose:

* Bishop movement
* Queen diagonal movement

The function advances one row and one column at a time until reaching the destination.

---

# King Check Detection

Implemented

```cpp
bool isKingInCheck(...)
```

Process:

1. Locate the king.
2. Iterate through every enemy piece.
3. Test whether that piece attacks the king.
4. Return immediately if an attack exists.

Supported attacks:

* Pawn
* Knight
* Bishop
* Rook
* Queen
* King

Sliding pieces use the path checking helper functions to ensure no blocking pieces exist.

---

# Move Validation

Implemented

```cpp
bool isValidMove(const Board& oldBoard,
                 const Board& newBoard);
```

The validator determines:

* Which piece moved
* Source square
* Destination square
* Captured piece
* Whether the move follows chess rules
* Whether the move leaves the king in check

If any requirement fails, the move is rejected.

---

# Pawn Rules

Implemented:

* Single forward move
* Initial double move
* Diagonal capture
* En passant capture

Supported for both white and black pawns.

En passant validation uses:

```cpp
enPassantRow
enPassantCol
```

stored inside the Board class.

---

# Bishop Rules

Implemented:

* Diagonal movement
* Path obstruction checking
* Friendly piece collision prevention
* Enemy captures

---

# Knight Rules

Implemented:

* Standard L-shaped movement
* Jumping over pieces
* Friendly collision prevention
* Enemy captures

Since knights jump, no path checking is required.

---

# Rook Rules

Implemented:

* Horizontal movement
* Vertical movement
* Path obstruction checking
* Friendly collision prevention
* Enemy captures

---

# Queen Rules

Implemented by combining:

* Bishop movement
* Rook movement

Supports:

* Horizontal
* Vertical
* Diagonal movement

Uses both path-checking helper functions.

---

# King Rules

Implemented:

* One-square movement
* Captures
* Friendly collision prevention

The king may move to any adjacent square provided it does not move into check.

---

# Castling

Implemented validation for all four castling moves.

White:

* Kingside
* Queenside

Black:

* Kingside
* Queenside

Validation checks:

* King has never moved.
* Correct rook has never moved.
* Squares between king and rook are empty.
* King is not currently in check.
* Intermediate square is not under attack.

Movement flags:

```cpp
whiteKingMoved
whiteRookAMoved
whiteRookHMoved

blackKingMoved
blackRookAMoved
blackRookHMoved
```

---

# Self-Check Prevention

After validating movement rules, the engine performs a final safety check.

```cpp
if(isKingInCheck(newBoard, whiteMoving))
    return false;
```

This prevents moves that would leave the moving side's own king in check.

---

# Debug Output

Temporary debugging output was added:

```cpp
Trying move:
Piece
Start Square
Destination Square
```

This helps verify move detection while testing.

---

# Validation Pipeline

Every attempted move now passes through the following stages:

```text
Detect moved piece
        │
        ▼
Determine source/destination
        │
        ▼
Validate piece movement
        │
        ▼
Validate captures
        │
        ▼
Validate special rules
    (castling / en passant)
        │
        ▼
Check own king safety
        │
        ▼
Move accepted
```

---

# Features Completed

* White/black piece detection
* Straight path validation
* Diagonal path validation
* Full pawn rules
* Full bishop rules
* Full knight rules
* Full rook rules
* Full queen rules
* Full king rules
* En passant validation
* Castling validation
* King check detection
* Self-check prevention
* Debug move logging

---

# Remaining Improvements

Future work includes:

* Checking that the castling destination square is not attacked.
* Automatic rook movement during castling.
* Automatic pawn promotion.
* Threefold repetition detection.
* Fifty-move rule.
* Draw by insufficient material.
* Move generation optimizations for the chess engine.
