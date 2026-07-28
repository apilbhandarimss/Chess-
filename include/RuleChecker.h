#pragma once

#include "Board.h"
bool isBlackPiece(char piece);
bool isWhitePiece(char piece);
bool isValidMove(const Board& oldBoard, const Board& newBoard);
bool isKingInCheck(const Board &a, bool b);
bool isStaleMate(const Board &a);
bool cheakMate(Board oldBoard);
void endGame();
