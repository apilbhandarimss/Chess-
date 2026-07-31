#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>
#include "Board.h"
#include "Engine.h"
#include "Evaluator.h"
#include "RuleChecker.h"

const int SCREEN_WIDTH  = 1000;
const int SCREEN_HEIGHT = 1000;

enum GameMode
{
    MODE_NONE,
    MODE_PVP,
    MODE_VS_BLACK_BOT,
    MODE_VS_WHITE_BOT,
};

GameMode drawMenu()
{
    const Rectangle pvpBtn      = { 250, 350, 500, 80 };
    const Rectangle vsBotBlkBtn = { 250, 460, 500, 80 };
    const Rectangle vsBotWhtBtn = { 250, 570, 500, 80 };

    BeginDrawing();
    ClearBackground({ 30, 31, 34, 255 });
    DrawText("Chess Engine", 330, 200, 48, WHITE);

    DrawRectangleRec(pvpBtn,      { 60, 60, 60, 255 });
    DrawText("1)  Player vs Player",  275, 378, 26, WHITE);
    DrawRectangleRec(vsBotBlkBtn, { 60, 60, 60, 255 });
    DrawText("2)  Play vs Black Bot", 275, 488, 26, WHITE);
    DrawRectangleRec(vsBotWhtBtn, { 60, 60, 60, 255 });
    DrawText("3)  Play vs White Bot", 275, 598, 26, WHITE);

    EndDrawing();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 m = GetMousePosition();
        if (CheckCollisionPointRec(m, pvpBtn))      return MODE_PVP;
        if (CheckCollisionPointRec(m, vsBotBlkBtn)) return MODE_VS_BLACK_BOT;
        if (CheckCollisionPointRec(m, vsBotWhtBtn)) return MODE_VS_WHITE_BOT;
    }
    return MODE_NONE;
}

void LoadPieceTextures()
{
    const std::vector<std::pair<std::string, std::string>> paths = {
        {"white_pawn",   "3d_wood/wp.png"}, {"white_knight", "3d_wood/wn.png"},
        {"white_bishop", "3d_wood/wb.png"}, {"white_rook",   "3d_wood/wr.png"},
        {"white_queen",  "3d_wood/wq.png"}, {"white_king",   "3d_wood/wk.png"},
        {"black_pawn",   "3d_wood/bp.png"}, {"black_knight", "3d_wood/bn.png"},
        {"black_bishop", "3d_wood/bb.png"}, {"black_rook",   "3d_wood/br.png"},
        {"black_queen",  "3d_wood/bq.png"}, {"black_king",   "3d_wood/bk.png"},
    };
    for (const auto& [key, path] : paths)
        peiceTexture[key] = LoadTexture(path.c_str());
}

bool hasAnyLegalMove(const Board& board, bool whiteToMove)
{
    for (int fromRow = 0; fromRow < 8; fromRow++)
    for (int fromCol = 0; fromCol < 8; fromCol++)
    {
        char piece = board.squares[fromRow][fromCol];
        if (piece == ' ') continue;
        if ( whiteToMove && !isWhitePiece(piece)) continue;
        if (!whiteToMove &&  isWhitePiece(piece)) continue;

        for (int toRow = 0; toRow < 8; toRow++)
        for (int toCol = 0; toCol < 8; toCol++)
        {
            Board next = board;
            next.squares[toRow][toCol]     = piece;
            next.squares[fromRow][fromCol] = ' ';
            if (isValidMove(board, next))
                return true;
        }
    }
    return false;
}

bool isCheckmate(const Board& board, bool whiteToMove)
{
    return isKingInCheck(board, whiteToMove) && !hasAnyLegalMove(board, whiteToMove);
}

bool isStalemate(const Board& board, bool whiteToMove)
{
    return !isKingInCheck(board, whiteToMove) && !hasAnyLegalMove(board, whiteToMove);
}

char handlePromotionDialog(bool promotingWhite)
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.55f));
    DrawRectangle(200, 300, 600, 350, DARKGRAY);
    DrawRectangleLines(200, 300, 600, 350, WHITE);
    DrawText("Promote Pawn", 360, 320, 30, WHITE);

    const Rectangle queenBtn  = { 230, 390, 180, 100 };
    const Rectangle rookBtn   = { 490, 390, 180, 100 };
    const Rectangle bishopBtn = { 230, 510, 180, 100 };
    const Rectangle knightBtn = { 490, 510, 180, 100 };

    DrawRectangleRec(queenBtn,  LIGHTGRAY); DrawText("Queen",  275, 430, 25, BLACK);
    DrawRectangleRec(rookBtn,   LIGHTGRAY); DrawText("Rook",   545, 430, 25, BLACK);
    DrawRectangleRec(bishopBtn, LIGHTGRAY); DrawText("Bishop", 260, 550, 25, BLACK);
    DrawRectangleRec(knightBtn, LIGHTGRAY); DrawText("Knight", 530, 550, 25, BLACK);

    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return '\0';

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, queenBtn))  return promotingWhite ? 'Q' : 'q';
    if (CheckCollisionPointRec(mouse, rookBtn))   return promotingWhite ? 'R' : 'r';
    if (CheckCollisionPointRec(mouse, bishopBtn)) return promotingWhite ? 'B' : 'b';
    if (CheckCollisionPointRec(mouse, knightBtn)) return promotingWhite ? 'N' : 'n';
    return '\0';
}

void drawOverlayMessage(const Board& board, const char* msg)

{
    BeginDrawing();
    drawBoard(board);
    DrawRectangle(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 50, 500, 100, { 0, 0, 0, 200 });
    DrawText(msg, SCREEN_WIDTH / 2 - MeasureText(msg, 28) / 2, SCREEN_HEIGHT / 2 - 14, 28, WHITE);
    EndDrawing();
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess Engine");
    SetTargetFPS(60);
    LoadPieceTextures();

    GameMode mode = MODE_NONE;
    while (!WindowShouldClose() && mode == MODE_NONE)
        mode = drawMenu();

    Board board;

    while (!WindowShouldClose())
    {
        if (isCheckmate(board, board.whiteturn))
        {
            const char* msg = board.whiteturn ? "Black wins by checkmate!"
                                              : "White wins by checkmate!";
            drawOverlayMessage(board, msg);
            continue;
        }
        if (isStalemate(board, board.whiteturn))
        {
            drawOverlayMessage(board, "Stalemate - Draw!");
            continue;
        }

        bool botShouldMove =
            (mode == MODE_VS_BLACK_BOT && !board.whiteturn) ||
            (mode == MODE_VS_WHITE_BOT &&  board.whiteturn);

        if (botShouldMove && !board.isPromoting)
        {
            Board newBoard     = engineMove(board);
            newBoard.whiteturn = !board.whiteturn;
            board              = newBoard;
            goto render;
        }

        {
            bool humanShouldMove =
                (mode == MODE_PVP) ||
                (mode == MODE_VS_BLACK_BOT &&  board.whiteturn) ||
                (mode == MODE_VS_WHITE_BOT && !board.whiteturn);

            if (humanShouldMove && !board.isPromoting)
                move(board);
        }

        render:
        BeginDrawing();
        ClearBackground(BLACK);
        drawBoard(board);

        if (board.isPromoting)
        {
            char chosen = handlePromotionDialog(board.whiteturn);
            if (chosen != '\0')
            {
                board.squares[board.promotionRow][board.promotionCol] = chosen;
                board.isPromoting  = false;
                board.promotionRow = -1;
                board.promotionCol = -1;
                board.whiteturn    = !board.whiteturn;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}