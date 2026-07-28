#include "RuleChecker.h"
#include <iostream>
#include <cstdlib>

bool isWhitePiece(char piece)
{
    return piece >= 'A' && piece <= 'Z';
}

bool isBlackPiece(char piece)
{
    return piece >= 'a' && piece <= 'z';
}

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

bool isKingInCheck(const Board& board, bool whiteKing)
{
    int kingRow = -1;
    int kingCol = -1;

    char king = whiteKing ? 'K' : 'k';

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(board.squares[row][col] == king)
            {
                kingRow = row;
                kingCol = col;
            }
        }
    }

    if(kingRow == -1)
        return false;

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            char piece = board.squares[row][col];

            if(piece == ' ')
                continue;

            if(whiteKing && !isBlackPiece(piece))
                continue;

            if(!whiteKing && !isWhitePiece(piece))
                continue;

            int dr = kingRow - row;
            int dc = kingCol - col;

            switch(piece)
            {
            case 'p':
                if(dr == 1 && abs(dc) == 1)
                    return true;
                break;

            case 'P':
                if(dr == -1 && abs(dc) == 1)
                    return true;
                break;

            case 'n':
            case 'N':
                if((abs(dr) == 2 && abs(dc) == 1) ||
                   (abs(dr) == 1 && abs(dc) == 2))
                    return true;
                break;

            case 'b':
            case 'B':
                if(abs(dr) == abs(dc) &&
                   isPathClearDiagonal(board, row, col, kingRow, kingCol))
                    return true;
                break;

            case 'r':
            case 'R':
                if((row == kingRow || col == kingCol) &&
                   isPathClearStraight(board, row, col, kingRow, kingCol))
                    return true;
                break;

            case 'q':
            case 'Q':
                if(abs(dr) == abs(dc))
                {
                    if(isPathClearDiagonal(board, row, col, kingRow, kingCol))
                        return true;
                }

                if(row == kingRow || col == kingCol)
                {
                    if(isPathClearStraight(board, row, col, kingRow, kingCol))
                        return true;
                }
                break;

            case 'k':
            case 'K':
                if(abs(dr) <= 1 && abs(dc) <= 1)
                    return true;
                break;
            }
        }
    }

    return false;
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

    bool moveIsLegal = false;

    if(piece == 'P')
    {
        if(toCol == fromCol &&
           toRow == fromRow - 1 &&
           targetPiece == ' ')
            moveIsLegal = true;

        if(fromRow == 6 &&
           toCol == fromCol &&
           toRow == fromRow - 2 &&
           targetPiece == ' ' &&
           oldBoard.squares[fromRow - 1][fromCol] == ' ')
            moveIsLegal = true;

        if(toRow == fromRow - 1 &&
           abs(toCol - fromCol) == 1 &&
           isBlackPiece(targetPiece))
            moveIsLegal = true;

        if(toRow == fromRow - 1 &&
           abs(toCol - fromCol) == 1 &&
           targetPiece == ' ' &&
           toCol == oldBoard.enPassantCol &&
           fromRow == oldBoard.enPassantRow)
            moveIsLegal = true;
    }

    if(piece == 'p')
    {
        if(toCol == fromCol &&
           toRow == fromRow + 1 &&
           targetPiece == ' ')
            moveIsLegal = true;

        if(fromRow == 1 &&
           toCol == fromCol &&
           toRow == fromRow + 2 &&
           targetPiece == ' ' &&
           oldBoard.squares[fromRow + 1][fromCol] == ' ')
            moveIsLegal = true;

        if(toRow == fromRow + 1 &&
           abs(toCol - fromCol) == 1 &&
           isWhitePiece(targetPiece))
            moveIsLegal = true;

        if(toRow == fromRow + 1 &&
           abs(toCol - fromCol) == 1 &&
           targetPiece == ' ' &&
           toCol == oldBoard.enPassantCol &&
           fromRow == oldBoard.enPassantRow)
            moveIsLegal = true;
    }

    if(piece == 'B')
    {
        if(abs(toRow - fromRow) == abs(toCol - fromCol))
            if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol))
                if(targetPiece == ' ' || isBlackPiece(targetPiece))
                    moveIsLegal = true;
    }

    if(piece == 'b')
    {
        if(abs(toRow - fromRow) == abs(toCol - fromCol))
            if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol))
                if(targetPiece == ' ' || isWhitePiece(targetPiece))
                    moveIsLegal = true;
    }

    if(piece == 'N')
    {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
            if(targetPiece == ' ' || isBlackPiece(targetPiece))
                moveIsLegal = true;
    }

    if(piece == 'n')
    {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
            if(targetPiece == ' ' || isWhitePiece(targetPiece))
                moveIsLegal = true;
    }

    if(piece == 'Q')
    {
        bool diagonal = abs(toRow - fromRow) == abs(toCol - fromCol);
        bool straight = (fromRow == toRow || fromCol == toCol);

        if(diagonal)
            if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol) &&
               (targetPiece == ' ' || isBlackPiece(targetPiece)))
                moveIsLegal = true;

        if(straight)
            if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol) &&
               (targetPiece == ' ' || isBlackPiece(targetPiece)))
                moveIsLegal = true;
    }

    if(piece == 'q')
    {
        bool diagonal = abs(toRow - fromRow) == abs(toCol - fromCol);
        bool straight = (fromRow == toRow || fromCol == toCol);

        if(diagonal)
            if(isPathClearDiagonal(oldBoard, fromRow, fromCol, toRow, toCol) &&
               (targetPiece == ' ' || isWhitePiece(targetPiece)))
                moveIsLegal = true;

        if(straight)
            if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol) &&
               (targetPiece == ' ' || isWhitePiece(targetPiece)))
                moveIsLegal = true;
    }

    if(piece == 'R')
    {
        if(fromRow == toRow || fromCol == toCol)
            if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol))
                if(targetPiece == ' ' || isBlackPiece(targetPiece))
                    moveIsLegal = true;
    }

    if(piece == 'r')
    {
        if(fromRow == toRow || fromCol == toCol)
            if(isPathClearStraight(oldBoard, fromRow, fromCol, toRow, toCol))
                if(targetPiece == ' ' || isWhitePiece(targetPiece))
                    moveIsLegal = true;
    }

    if(piece == 'K')
    {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if(rowDiff <= 1 && colDiff <= 1)
            if(targetPiece == ' ' || isBlackPiece(targetPiece))
                moveIsLegal = true;

        // white kingside castling (king e1->g1)
        if(!oldBoard.whiteKingMoved && !oldBoard.whiteRookHMoved &&
           fromRow == 7 && fromCol == 4 && toRow == 7 && toCol == 6 &&
           oldBoard.squares[7][5] == ' ' && oldBoard.squares[7][6] == ' ' &&
           !isKingInCheck(oldBoard, true))
        {
            Board middle = oldBoard;
            middle.squares[7][5] = 'K';
            middle.squares[7][4] = ' ';
            if(!isKingInCheck(middle, true))
                moveIsLegal = true;
        }

        // white queenside castling (king e1->c1)
        if(!oldBoard.whiteKingMoved && !oldBoard.whiteRookAMoved &&
           fromRow == 7 && fromCol == 4 && toRow == 7 && toCol == 2 &&
           oldBoard.squares[7][3] == ' ' && oldBoard.squares[7][2] == ' ' && oldBoard.squares[7][1] == ' ' &&
           !isKingInCheck(oldBoard, true))
        {
            Board middle = oldBoard;
            middle.squares[7][3] = 'K';
            middle.squares[7][4] = ' ';
            if(!isKingInCheck(middle, true))
                moveIsLegal = true;
        }
    }

    if(piece == 'k')
    {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if(rowDiff <= 1 && colDiff <= 1)
            if(targetPiece == ' ' || isWhitePiece(targetPiece))
                moveIsLegal = true;

        // black kingside castling (king e8->g8)
        if(!oldBoard.blackKingMoved && !oldBoard.blackRookHMoved &&
           fromRow == 0 && fromCol == 4 && toRow == 0 && toCol == 6 &&
           oldBoard.squares[0][5] == ' ' && oldBoard.squares[0][6] == ' ' &&
           !isKingInCheck(oldBoard, false))
        {
            Board middle = oldBoard;
            middle.squares[0][5] = 'k';
            middle.squares[0][4] = ' ';
            if(!isKingInCheck(middle, false))
                moveIsLegal = true;
        }

        // black queenside castling (king e8->c8)
        if(!oldBoard.blackKingMoved && !oldBoard.blackRookAMoved &&
           fromRow == 0 && fromCol == 4 && toRow == 0 && toCol == 2 &&
           oldBoard.squares[0][3] == ' ' && oldBoard.squares[0][2] == ' ' && oldBoard.squares[0][1] == ' ' &&
           !isKingInCheck(oldBoard, false))
        {
            Board middle = oldBoard;
            middle.squares[0][3] = 'k';
            middle.squares[0][4] = ' ';
            if(!isKingInCheck(middle, false))
                moveIsLegal = true;
        }
    }

    if(!moveIsLegal)
        return false;

    bool whiteMoving = isWhitePiece(piece);

    if(isKingInCheck(newBoard, whiteMoving))
        return false;

    return true;
}