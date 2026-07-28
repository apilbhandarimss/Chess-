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
        int enPassantCol = -1;  
        int enPassantRow = -1; 
        bool whiteKingMoved = false;
        bool blackKingMoved = false;
        bool whiteRookAMoved = false; 
        bool whiteRookHMoved = false; 
        bool blackRookAMoved = false;
        bool isPromoting = false;
        int promotionRow = -1;
        int promotionCol = -1;
bool blackRookHMoved = false;
};
void drawBoard(const Board& board );
void move(Board &b);
extern std::map<std::string,Texture2D> peiceTexture;
