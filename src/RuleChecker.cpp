#include "RuleChecker.h"
#include <iostream>
#include <cstdlib>
bool isPathClearStraight(const Board& board, int fromRow, int fromCol, int toRow, int toCol)
{
    if(fromRow == toRow)
    {
        int step = (toCol > fromCol) ? 1 : -1;

        for(int col = fromCol + step; col != toCol; col += step)
        {
            if(board.squares[fromRow][col] != ' ')
                return false;
        }
    }
    else if(fromCol == toCol)
    {
        int step = (toRow > fromRow) ? 1 : -1;

        for(int row = fromRow + step; row != toRow; row += step)
        {
            if(board.squares[row][fromCol] != ' ')
                return false;
        }
    }

    return true;
}
bool isPathClearDiagonal(const Board& board, int fromRow, int fromCol, int toRow, int toCol)
{
    int rowStep = (toRow > fromRow) ? 1 : -1;
    int colStep = (toCol > fromCol) ? 1 : -1;

    int row = fromRow + rowStep;
    int col = fromCol + colStep;

    while(row != toRow && col != toCol)
    {
        if(board.squares[row][col] != ' ')
            return false;

        row += rowStep;
        col += colStep;
    }

    return true;
}

bool isWhitePiece(char piece)
{
    return piece >= 'A' && piece <= 'Z';
}

bool isBlackPiece(char piece)
{
    return piece >= 'a' && piece <= 'z';
}

bool isValidMove(const Board& oldBoard, const Board& newBoard)
{
    int fromRow = -1;
    int fromCol = -1;
    int toRow = -1;
    int toCol = -1;

    char movingPiece = ' ';

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(oldBoard.squares[row][col] != newBoard.squares[row][col])
            {
                if(oldBoard.squares[row][col] != ' ' &&
                   newBoard.squares[row][col] == ' ')
                {
                    fromRow = row;
                    fromCol = col;
                    movingPiece = oldBoard.squares[row][col];
                }
            }
        }
    }

    if(fromRow == -1)
        return false;

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(oldBoard.squares[row][col] != newBoard.squares[row][col])
            {
                if(newBoard.squares[row][col] == movingPiece)
                {
                    toRow = row;
                    toCol = col;
                }
            }
        }
    }

    if(toRow == -1)
        return false;

    char piece = movingPiece;
    char targetPiece = oldBoard.squares[toRow][toCol];

    std::cout << "Trying move: "
              << piece << " "
              << fromRow << "," << fromCol
              << " -> "
              << toRow << "," << toCol
              << "\n";


    if(piece == 'P')
    {
        if(toCol == fromCol &&
           toRow == fromRow - 1 &&
           targetPiece == ' ')
        {
            return true;
        }

        if(fromRow == 6 &&
           toCol == fromCol &&
           toRow == fromRow - 2 &&
           targetPiece == ' ' &&
           oldBoard.squares[fromRow - 1][fromCol] == ' ')
        {
            return true;
        }

        if(toRow == fromRow - 1 &&
           abs(toCol - fromCol) == 1 &&
           isBlackPiece(targetPiece))
        {
            return true;
        }
    }

    if(piece == 'p')
    {
        if(toCol == fromCol &&
           toRow == fromRow + 1 &&
           targetPiece == ' ')
        {
            return true;
        }

        if(fromRow == 1 &&
           toCol == fromCol &&
           toRow == fromRow + 2 &&
           targetPiece == ' ' &&
           oldBoard.squares[fromRow + 1][fromCol] == ' ')
        {
            return true;
        }

        if(toRow == fromRow + 1 &&
           abs(toCol - fromCol) == 1 &&
           isWhitePiece(targetPiece))
        {
            return true;
        }
    }
    if(piece == 'B')
{
    if(abs(toRow - fromRow) == abs(toCol - fromCol))
    {
        if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol))
        {
            if(targetPiece == ' ' || isBlackPiece(targetPiece))
                return true;
        }
    }
}

if(piece == 'b')
{
    if(abs(toRow - fromRow) == abs(toCol - fromCol))
    {
        if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol))
        {
            if(targetPiece == ' ' || isWhitePiece(targetPiece))
                return true;
        }
    }
}
if(piece == 'N')
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if((rowDiff == 2 && colDiff == 1) ||
       (rowDiff == 1 && colDiff == 2))
    {
        if(targetPiece == ' ' || isBlackPiece(targetPiece))
            return true;
    }
}

if(piece == 'n')
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if((rowDiff == 2 && colDiff == 1) ||
       (rowDiff == 1 && colDiff == 2))
    {
        if(targetPiece == ' ' || isWhitePiece(targetPiece))
            return true;
    }
}
if(piece == 'Q')
{
    bool diagonal = abs(toRow - fromRow) == abs(toCol - fromCol);
    bool straight = (fromRow == toRow || fromCol == toCol);

    if(diagonal)
    {
        if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol) &&
           (targetPiece == ' ' || isBlackPiece(targetPiece)))
        {
            return true;
        }
    }

    if(straight)
    {
        if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol) &&
           (targetPiece == ' ' || isBlackPiece(targetPiece)))
        {
            return true;
        }
    }
}

if(piece == 'q')
{
    bool diagonal = abs(toRow - fromRow) == abs(toCol - fromCol);
    bool straight = (fromRow == toRow || fromCol == toCol);

    if(diagonal)
    {
        if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol) &&
           (targetPiece == ' ' || isWhitePiece(targetPiece)))
        {
            return true;
        }
    }

    if(straight)
    {
        if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol) &&
           (targetPiece == ' ' || isWhitePiece(targetPiece)))
        {
            return true;
        }
    }
}
if(piece == 'R')
{
    if(fromRow == toRow || fromCol == toCol)
    {
        if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol))
        {
            if(targetPiece == ' ' || isBlackPiece(targetPiece))
            {
                return true;
            }
        }
    }
}

if(piece == 'r')
{
    if(fromRow == toRow || fromCol == toCol)
    {
        if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol))
        {
            if(targetPiece == ' ' || isWhitePiece(targetPiece))
            {
                return true;
            }
        }
    }
}
if(piece == 'K')
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if(rowDiff <= 1 && colDiff <= 1)
    {
        if(targetPiece == ' ' || isBlackPiece(targetPiece))
            return true;
    }
}

if(piece == 'k')
{
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if(rowDiff <= 1 && colDiff <= 1)
    {
        if(targetPiece == ' ' || isWhitePiece(targetPiece))
            return true;
    }
}
    return false;
}