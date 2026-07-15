#include "RuleChecker.h"
#include <iostream>


bool isValidMove(const Board& oldBoard, const Board& newBoard)
{
    int fromRow = -1;
    int fromCol = -1;

    int toRow = -1;
    int toCol = -1;


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
                }

                else if(oldBoard.squares[row][col] == ' ' &&
                        newBoard.squares[row][col] != ' ')
                {
                    toRow = row;
                    toCol = col;
                }
            }
        }
    }


    if(fromRow == -1 || toRow == -1)
        return false;


    char piece = oldBoard.squares[fromRow][fromCol];


    std::cout << "Trying move: "
              << piece << " "
              << fromRow << "," << fromCol
              << " -> "
              << toRow << "," << toCol
              << "\n";


    
    if(piece != 'P' && piece != 'p')
        return false;



   
    if(piece == 'P')
    {
        
        if(toCol == fromCol &&
           toRow == fromRow - 1)
        {
            return true;
        }


        
        if(fromRow == 6 &&
           toCol == fromCol &&
           toRow == fromRow - 2 &&
           oldBoard.squares[fromRow - 1][fromCol] == ' ')
        {
            return true;
        }
    }



    // BLACK PAWN
    if(piece == 'p')
    {
        // one step forward
        if(toCol == fromCol &&
           toRow == fromRow + 1)
        {
            return true;
        }


        // two steps from starting position
        if(fromRow == 1 &&
           toCol == fromCol &&
           toRow == fromRow + 2 &&
           oldBoard.squares[fromRow + 1][fromCol] == ' ')
        {
            return true;
        }
    }


    return false;
}