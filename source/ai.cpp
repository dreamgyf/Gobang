#include "chessboard.h"

AI::AI()
{
}


void AI::initialization(const Chessboard &game)
{
    for(int y = 0;y < 15;++y)
        for(int x = 0;x < 15;++x)
        {
            if(game.get_info(x,y) == Chessboard::Chess::empty)
                point[y][x] = 0;
            else
                point[y][x] = -1;
        }
}

void get_point(const Chessboard &game)
{
    for(int y = 0;y < 15;++y)
        for(int x = 0;x < 15;++x)
        {
            if(game.get_info(x,y) != Chessboard::Chess::empty)
                continue;

        }
}
