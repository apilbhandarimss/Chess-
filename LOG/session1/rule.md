# RuleChecker.cpp Documentation

## Overview

`RuleChecker.cpp` is responsible for validating whether a proposed chess move is legal according to the implemented chess rules. In the current version of the project, it only validates **pawn movement** for both white and black pieces. Other chess pieces are not yet supported.

The file compares the board before and after a move, determines which piece moved, and checks whether the movement follows the rules of chess.

---

# Included Header Files

| Header          | Purpose                                      |
| --------------- | -------------------------------------------- |
| `RuleChecker.h` | Declares the move validation functions.      |
| `<iostream>`    | Prints debugging information to the console. |

---

# Function

## `isValidMove()`

### Purpose

Determines whether a move made by the player is legal.

```cpp id="m1t6sv"
bool isValidMove(const Board& oldBoard, const Board& newBoard)
```

The function receives two board states:

* `oldBoard` – Board before the move.
* `newBoard` – Board after the move.

It compares both boards to determine what changed.

---

# Step 1: Locate the Move

The function scans every square on the board.

```text id="l4t2de"
Old Board
      │
      ▼
Compare Every Square
      │
      ▼
Find Starting Position
Find Destination Position
```

During comparison:

* The square that changed from a piece to an empty square is the **starting position**.
* The square that changed from empty to a piece is the **destination**.

The coordinates are stored in:

* `fromRow`
* `fromCol`
* `toRow`
* `toCol`

---

# Step 2: Validate Move Detection

```cpp id="tbgrna"
if(fromRow == -1 || toRow == -1)
    return false;
```

If the function cannot determine both the starting and destination squares, the move is considered invalid.

---

# Step 3: Identify the Moving Piece

```cpp id="0jkbci"
char piece = oldBoard.squares[fromRow][fromCol];
```

The piece located at the starting position is retrieved for validation.

---

# Step 4: Debug Output

```cpp id="64kxhy"
std::cout << "Trying move..."
```

The program prints:

* Piece type
* Starting position
* Destination position

Example:

```text id="p7n8ua"
Trying move: P 6,4 -> 4,4
```

This helps during debugging by showing which move the program is attempting to validate.

---

# Step 5: Supported Pieces

```cpp id="2m5xg8"
if(piece != 'P' && piece != 'p')
    return false;
```

At the current stage, only pawns are supported.

If the selected piece is not:

* White Pawn (`P`)
* Black Pawn (`p`)

the move is immediately rejected.

---

# White Pawn Movement

The function implements two legal moves.

## One Square Forward

```text id="cg9w9s"
Start
  │
  ▼
One Square Forward
```

Conditions:

* Same column.
* One row upward.
* No sideways movement.

---

## Two Squares Forward

Allowed only if:

* Pawn is on its initial row.
* Destination is two squares ahead.
* The square between the start and destination is empty.

```text id="g8i5cl"
Initial Position
      │
      ▼
Advance Two Squares
```

---

# Black Pawn Movement

Black pawns move in the opposite direction.

## One Square Forward

Conditions:

* Same column.
* One row downward.

---

## Two Squares Forward

Allowed only when:

* Pawn is on its starting row.
* Destination is two squares ahead.
* The square between both positions is empty.

---

# Invalid Moves

If none of the legal pawn movement conditions are satisfied, the function returns:

```cpp id="oaqj3z"
return false;
```

The move is rejected, and the board remains unchanged.

---

# Current Limitations

The current implementation does **not** support:

* Pawn captures
* En passant
* Pawn promotion
* Rook movement
* Knight movement
* Bishop movement
* Queen movement
* King movement
* Castling
* Check detection
* Checkmate detection

Only forward pawn movement has been implemented.

---

# Algorithm Flow

```text id="o2tkm6"
Receive Old Board
        │
        ▼
Receive New Board
        │
        ▼
Compare Both Boards
        │
        ▼
Find Start Square
Find Destination Square
        │
        ▼
Identify Moving Piece
        │
        ▼
Is Pawn?
   │
 ┌─┴─────┐
 │        │
No       Yes
 │        │
 ▼        ▼
Reject  Check Pawn Rules
            │
      ┌─────┴─────┐
      │           │
   Legal      Illegal
      │           │
      ▼           ▼
 Return True   Return False
```

---

# Summary

`RuleChecker.cpp` provides the first stage of move validation for the chess engine. It compares the previous and updated board states, identifies the moved piece, verifies that the movement follows the implemented pawn movement rules, and returns whether the move is legal. This module forms the foundation upon which future support for additional chess pieces and advanced chess rules can be added.
