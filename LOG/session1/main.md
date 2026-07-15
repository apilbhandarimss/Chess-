# main.cpp Documentation

## Overview

`main.cpp` is the entry point of the Chess Engine application. Its primary responsibility is to initialize the graphical window, load all chess piece textures, create the chess board, execute the main game loop, and properly release resources before the application closes.

Unlike other files that implement chess logic or AI, this file mainly coordinates the overall execution of the program.

---

# Libraries Used

| Library         | Purpose                                                           |
| --------------- | ----------------------------------------------------------------- |
| `<iostream>`    | Standard input/output operations.                                 |
| `<map>`         | Stores chess piece textures using a key-value structure.          |
| `<vector>`      | Stores the list of texture file paths.                            |
| `<string>`      | Handles texture names and file paths.                             |
| `<memory>`      | Supports smart pointers used throughout the project.              |
| `<algorithm>`   | Provides common STL algorithms.                                   |
| `<chrono>`      | Used for timing and performance measurements.                     |
| `raylib.h`      | Provides graphics, textures, window creation, and input handling. |
| `Board.h`       | Contains the chess board representation.                          |
| `Engine.h`      | Contains the chess engine and AI functions.                       |
| `Evaluator.h`   | Evaluates chess positions.                                        |
| `RuleChecker.h` | Implements legal move generation and chess rules.                 |

---

# Screen Configuration

```cpp
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1080;
```

These constants define the dimensions of the application window.

---

# LoadPieceTextures()

## Purpose

This function loads all chess piece images from disk into GPU memory before the game starts.

## Working

1. Creates a vector containing every chess piece name and its corresponding image path.
2. Loops through the vector.
3. Loads each image using Raylib's `LoadTexture()`.
4. Stores each texture inside the global texture map (`peiceTexture`).

Example entries:

* White Pawn → `3d_wood/wp.png`
* White King → `3d_wood/wk.png`
* Black Queen → `3d_wood/bq.png`

Using a map allows textures to be accessed easily by their names.

---

# main() Function

The `main()` function controls the complete execution of the application.

## Step 1: Create Chess Board

```cpp
Board b;
```

Creates a `Board` object containing the current game state.

---

## Step 2: Initialize Window

```cpp
InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess Engine");
```

Creates the graphical window where the chess game is displayed.

---

## Step 3: Load Assets

```cpp
LoadPieceTextures();
```

Loads all chess piece images before rendering begins.

---

## Step 4: Main Game Loop

```cpp
while (!WindowShouldClose())
```

This loop continues until the player closes the application window.

Inside the loop:

### Move Handling

```cpp
move(b);
```

Processes user input and updates the chess board according to the selected move.

### Begin Drawing

```cpp
BeginDrawing();
```

Starts rendering the current frame.

### Draw Chess Board

```cpp
drawBoard(b);
```

Draws the board, pieces, and current game state.

### End Drawing

```cpp
EndDrawing();
```

Displays the completed frame on the screen.

This sequence repeats every frame, creating a continuously updated graphical interface.

---

## Step 5: Release Resources

```cpp
for (auto& texture : peiceTexture)
{
    UnloadTexture(texture.second);
}
```

Frees all loaded textures from memory to prevent memory leaks.

---

## Step 6: Close Window

```cpp
CloseWindow();
```

Closes the graphical window and terminates Raylib properly.

---

# Execution Flow

```
Program Starts
       │
       ▼
Create Board Object
       │
       ▼
Initialize Window
       │
       ▼
Load Chess Piece Textures
       │
       ▼
Enter Main Game Loop
       │
       ├── Process Player Move
       ├── Begin Drawing
       ├── Draw Chess Board
       ├── End Drawing
       │
       └── Repeat Until Window Closes
       │
       ▼
Unload Textures
       │
       ▼
Close Window
       │
       ▼
Program Ends
```

---

# Summary

`main.cpp` serves as the controller of the Chess Engine application. It initializes the graphical environment, loads game assets, creates the chess board, continuously updates and renders the game through the main loop, and performs proper cleanup before exiting. The actual chess logic, move validation, evaluation, and AI search are delegated to other modules, making `main.cpp` responsible only for coordinating the application's execution.
