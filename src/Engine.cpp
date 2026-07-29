#include "Engine.h"
#include "RuleChecker.h"
#include "Evaluator.h"
#include <vector>
#include <limits>
std::vector<Board> generateMoves(const Board& board, bool forWhite)
{
    std::vector<Board> moves;

    for (int fromRow = 0; fromRow < 8; fromRow++)
    for (int fromCol = 0; fromCol < 8; fromCol++)
    {
        char piece = board.squares[fromRow][fromCol];

        if (piece == ' ') continue;
        if ( forWhite && !isWhitePiece(piece)) continue;
        if (!forWhite &&  isWhitePiece(piece)) continue;

        for (int toRow = 0; toRow < 8; toRow++)
        for (int toCol = 0; toCol < 8; toCol++)
        {
            if (toRow == fromRow && toCol == fromCol) continue;

            Board candidate = board;
            candidate.squares[toRow][toCol]     = piece;
            candidate.squares[fromRow][fromCol] = ' ';

            if (!isValidMove(board, candidate)) continue;

            // auto-promote to queen
            if (piece == 'P' && toRow == 0) candidate.squares[toRow][toCol] = 'Q';
            if (piece == 'p' && toRow == 7) candidate.squares[toRow][toCol] = 'q';

            moves.push_back(candidate);
        }
    }

    return moves;
}

int minimax(const Board& board, int depth, bool isWhite)
{
    if (depth == 0)
        return evaluate(board);

    std::vector<Board> moves = generateMoves(board, isWhite);

    if (moves.empty())
    {
        if (isKingInCheck(board, isWhite))
            return isWhite ? -9999 : 9999;  
        return 0;                            
    }

    if (isWhite)
    {
        int best = std::numeric_limits<int>::min();
        for (const Board& next : moves)
        {
            int score = minimax(next, depth - 1, false); // opponent's turn
            if (score > best)
                best = score;
        }
        return best;
    }
    else
    {
        int best = std::numeric_limits<int>::max();
        for (const Board& next : moves)
        {
            int score = minimax(next, depth - 1, true);  // opponent's turn
            if (score < best)
                best = score;
        }
        return best;
    }
}

Board engineMove(const Board& board)
{
    const int DEPTH = 4;

    bool botIsWhite = board.whiteturn;

    std::vector<Board> moves = generateMoves(board, botIsWhite);

    if (moves.empty())
        return board;

    Board bestMove  = moves[0];
    int   bestScore = botIsWhite
                        ? std::numeric_limits<int>::min()
                        : std::numeric_limits<int>::max();

    for (const Board& candidate : moves)
    {
        int score = minimax(candidate, DEPTH - 1, !botIsWhite);

        if (botIsWhite && score > bestScore) { bestScore = score; bestMove = candidate; }
        if (!botIsWhite && score < bestScore) { bestScore = score; bestMove = candidate; }
    }

    return bestMove;
}