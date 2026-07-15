#include<iostream>
#include<map>
#include<chrono>
#include<algorithm>
#include<memory>
#include<vector>
#include<string>
#include<raylib.h>
#include "Board.h"
#include "Engine.h"
#include "Evaluator.h"
#include "RuleChecker.h"
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1080;
void LoadPieceTextures() {
    std::vector<std::pair<std::string, std::string>> texturePaths = {
        {"white_pawn", "3d_wood/wp.png"},   {"white_knight", "3d_wood/wn.png"},
        {"white_bishop", "3d_wood/wb.png"}, {"white_rook", "3d_wood/wr.png"},
        {"white_queen", "3d_wood/wq.png"},  {"white_king", "3d_wood/wk.png"},
        {"black_pawn", "3d_wood/bp.png"},   {"black_knight", "3d_wood/bn.png"},
        {"black_bishop", "3d_wood/bb.png"}, {"black_rook", "3d_wood/br.png"},
        {"black_queen", "3d_wood/bq.png"},  {"black_king", "3d_wood/bk.png"}
    };
        for (const auto& texture : texturePaths)
    {
        peiceTexture[texture.first] = LoadTexture(texture.second.c_str());
    }
}

int main()
{
    Board b;
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Chess Engine");
    LoadPieceTextures();
    while (!WindowShouldClose())
    {   move(b);
        BeginDrawing();
        drawBoard(b);
        EndDrawing();
        
    }
    for (auto& texture : peiceTexture)
    {
        UnloadTexture(texture.second);
    }
    CloseWindow();
    
    
    return 0;
}
