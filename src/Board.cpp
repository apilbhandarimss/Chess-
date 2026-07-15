#include "Board.h"
#include "raylib.h"
#include "RuleChecker.h"
#include<map>
#include<string>
int selectedRow = -1;
int selectedCol = -1;
bool pieceSelected = false;
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 1080;
const int BOARD_SIZE = 120*8;
const int BOARD_OFFSET_X = 40;
const int BOARD_OFFSET_Y = 10;
const int SQUARE_SIZE = BOARD_SIZE / 8;
const Color COLOR_LIGHT_SQ = { 240, 217, 181, 255 }; 
const Color COLOR_DARK_SQ  = { 181, 136, 99, 255 };  
const Color COLOR_BOARD_BG = { 30, 31, 34, 255 };     
const Color COLOR_SIDEBAR  = { 43, 45, 49, 255 };     
const Color COLOR_ACCENT_BLUE = { 88, 101, 242, 255 }; 
const Color COLOR_HIGHLIGHT_LEGAL = { 100, 200, 100, 140 };
const Color COLOR_HIGHLIGHT_CAPTURE = { 230, 80, 80, 160 };
const Color COLOR_HIGHLIGHT_LAST = { 245, 230, 120, 90 };
const Color COLOR_HIGHLIGHT_SELECTED = { 88, 101, 242, 110 };
const Color COLOR_CHECK = { 240, 80, 80, 180 };
#include "Board.h"
std::map<std::string, Texture2D> peiceTexture;
Board::Board()
{
    initl();
}

void Board::initl(){
    char initialBoard[8][8] =
    {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    };

    for(int row = 0; row < 8; row++)
        for(int col = 0; col < 8; col++)
            squares[row][col] = initialBoard[row][col];
}
void drawBoard(const Board& board)
{
    ClearBackground(COLOR_BOARD_BG);

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Color squareColor = ((row + col) % 2 == 0)
                ? COLOR_LIGHT_SQ
                : COLOR_DARK_SQ;

            DrawRectangle(
                BOARD_OFFSET_X + col * SQUARE_SIZE,
                BOARD_OFFSET_Y + row * SQUARE_SIZE,
                SQUARE_SIZE,
                SQUARE_SIZE,
                squareColor
            );
            char piece = board.squares[row][col];

switch (piece)
{
case 'P':
    DrawTexture(peiceTexture["white_pawn"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'R':
    DrawTexture(peiceTexture["white_rook"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'N':
    DrawTexture(peiceTexture["white_knight"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'B':
    DrawTexture(peiceTexture["white_bishop"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'Q':
    DrawTexture(peiceTexture["white_queen"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'K':
    DrawTexture(peiceTexture["white_king"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'p':
    DrawTexture(peiceTexture["black_pawn"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'r':
    DrawTexture(peiceTexture["black_rook"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'n':
    DrawTexture(peiceTexture["black_knight"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'b':
    DrawTexture(peiceTexture["black_bishop"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'q':
    DrawTexture(peiceTexture["black_queen"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;

case 'k':
    DrawTexture(peiceTexture["black_king"],
        BOARD_OFFSET_X + col * SQUARE_SIZE,
        BOARD_OFFSET_Y + row * SQUARE_SIZE,
        WHITE);
    break;
}

            
        }
    }

    DrawRectangle(
        BOARD_OFFSET_X + BOARD_SIZE + 20,
        0,
        SCREEN_WIDTH - (BOARD_OFFSET_X + BOARD_SIZE + 20),
        SCREEN_HEIGHT,
        COLOR_SIDEBAR
    );
}
void move(Board& b)
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        int col = (mouse.x - BOARD_OFFSET_X) / SQUARE_SIZE;
        int row = (mouse.y - BOARD_OFFSET_Y) / SQUARE_SIZE;


        if(row >= 0 && row < 8 && col >= 0 && col < 8)
        {

            if(!pieceSelected)
            {
                char piece = b.squares[row][col];

                if(piece != ' ')
                {
                    // white turn
                    if(b.whiteturn && piece >= 'A' && piece <= 'Z')
                    {
                        selectedRow = row;
                        selectedCol = col;
                        pieceSelected = true;
                    }

                    // black turn
                    else if(!b.whiteturn && piece >= 'a' && piece <= 'z')
                    {
                        selectedRow = row;
                        selectedCol = col;
                        pieceSelected = true;
                    }
                }
            }


            // Moving piece
            else
            {
                // clicking same square cancels
                if(row == selectedRow && col == selectedCol)
                {
                    pieceSelected = false;
                    selectedRow = -1;
                    selectedCol = -1;
                    return;
                }


                Board temp = b;


                temp.squares[row][col] =
                    temp.squares[selectedRow][selectedCol];


                temp.squares[selectedRow][selectedCol] = ' ';


                if(isValidMove(b,temp))
                {
                    b = temp;
                    b.whiteturn = !b.whiteturn;
                }


                pieceSelected = false;
                selectedRow = -1;
                selectedCol = -1;
            }
        }
    }
}