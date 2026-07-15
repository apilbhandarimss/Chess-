#pragma once
#include<map>
#include<raylib.h>
#include<string>
class Board
{
    public:
        Board();
        void initl();
        char squares[8][8];
        bool whiteturn=true;
};
void drawBoard(const Board& board );
void move(Board &b);
extern std::map<std::string,Texture2D> peiceTexture;
