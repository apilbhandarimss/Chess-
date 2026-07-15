# Board.cpp Documentation

## Overview

`Board.cpp` implements the chess board representation and the basic interaction between the player and the board. It is responsible for initializing the chessboard, rendering the board and pieces using Raylib, handling mouse input, and executing valid piece movements. It acts as the visual and gameplay layer between the user and the chess rules.

---

# Included Header Files

| Header          | Purpose                                                                   |
| --------------- | ------------------------------------------------------------------------- |
| `Board.h`       | Defines the `Board` class and board data structure.                       |
| `raylib.h`      | Provides graphics rendering, textures, mouse input, and window functions. |
| `RuleChecker.h` | Validates whether a move follows chess rules.                             |
| `<map>`         | Stores textures using key-value pairs.                                    |
| `<string>`      | Stores texture names.                                                     |

---

# Global Variables

```cpp
int selectedRow = -1;
int selectedCol = -1;
bool pieceSelected = false;
```

These variables store the currently selected chess piece.

* `selectedRow` – Row of the selected piece.
* `selectedCol` – Column of the selected piece.
* `pieceSelected` – Indicates whether a piece has been selected.

---

# Board Configuration

Several constants define the appearance of the board.

* Screen width and height.
* Chessboard size.
* Board position on the screen.
* Size of each square.
* Color palette for:

  * Light squares
  * Dark squares
  * Background
  * Sidebar
  * Highlights
  * Check indicator

Using constants makes the interface easier to modify without changing the rendering code.

---

# Texture Map

```cpp
std::map<std::string, Texture2D> peiceTexture;
```

A global map stores every chess piece texture.

Each texture is accessed using a string key such as:

* `"white_pawn"`
* `"white_king"`
* `"black_queen"`

This avoids repeatedly loading textures during rendering.

---

# Board Constructor

```cpp
Board::Board()
{
    initl();
}
```

The constructor automatically initializes the chessboard whenever a new `Board` object is created.

---

# initl()

## Purpose

Initializes the chessboard with the standard starting position.

## Working

1. Creates an 8×8 character array.
2. Places all white pieces on the last two ranks.
3. Places all black pieces on the first two ranks.
4. Leaves the middle four ranks empty.
5. Copies this arrangement into the board's `squares` array.

Uppercase letters represent white pieces, while lowercase letters represent black pieces.

---

# drawBoard()

## Purpose

Draws the complete chessboard and all chess pieces.

## Working

### 1. Clear Background

The previous frame is cleared using the board background color.

### 2. Draw Chess Squares

The function loops through all 64 board positions.

Each square alternates between:

* Light wood color
* Dark wood color

to create the traditional chessboard pattern.

### 3. Draw Chess Pieces

For every square:

* Reads the character stored in the board.
* Determines which chess piece it represents.
* Draws the corresponding texture.

Example:

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

The switch statement maps each character to its corresponding texture.

### 4. Draw Sidebar

A dark rectangle is drawn beside the chessboard.

The sidebar can later be used for:

* Engine statistics
* Move history
* Evaluation score
* Player information

---

# move()

## Purpose

Handles all mouse interactions and performs chess moves.

## Working

### Step 1: Detect Mouse Click

The function waits until the left mouse button is pressed.

### Step 2: Convert Mouse Position

The mouse coordinates are converted into board coordinates.

```
Mouse Position
      ↓
Board Column
Board Row
```

### Step 3: Verify Click

The function checks whether the click occurred inside the chessboard.

---

## Piece Selection

If no piece has been selected:

* Read the clicked square.
* Ignore empty squares.
* Verify that the piece belongs to the current player.
* Store its row and column.
* Mark the piece as selected.

This prevents players from selecting the opponent's pieces.

---

## Cancelling Selection

If the player clicks the same square again:

* The selection is cleared.
* No move is performed.

This allows players to deselect a piece.

---

## Temporary Board

When moving a piece:

```text
Original Board
        │
        ▼
 Temporary Copy
        │
Attempt Move
        │
        ▼
Validate Move
```

A temporary copy of the board is created.

The move is first applied to this copy instead of directly modifying the original board.

---

## Move Validation

The temporary board is passed to:

```cpp
isValidMove(b, temp);
```

This function checks whether the move satisfies the chess rules.

If the move is legal:

* The temporary board replaces the original board.
* The player's turn changes.

If the move is illegal:

* The original board remains unchanged.

---

## Turn Management

After every successful move:

```text
White
  ↓
Black
  ↓
White
  ↓
Black
```

The `whiteturn` flag is toggled to alternate turns between players.

---

# Program Flow

```text
Mouse Click
      │
      ▼
Inside Board?
      │
      ▼
Select Piece
      │
      ▼
Choose Destination
      │
      ▼
Create Temporary Board
      │
      ▼
Validate Move
      │
 ┌────┴────┐
 │         │
Valid    Invalid
 │         │
 ▼         ▼
Update   Ignore
Board     Move
 │
 ▼
Switch Turn
```

---

# Summary

`Board.cpp` manages the visual representation of the chessboard and basic gameplay interaction. It initializes the starting position, renders the chessboard and pieces, processes mouse selections, validates moves through the `RuleChecker` module, updates the board after legal moves, and alternates turns between players. It serves as the core interaction layer connecting the graphical interface with the chess rule engine.
