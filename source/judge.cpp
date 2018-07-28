#include "chessboard.h"

Judge::Judge()
{
}


Judge::Winner Judge::winner(const Chessboard &game)
{
    for(int x = 0;x < 15;++x)
        for(int y = 0;y < 15;++y)
        {
            //判断黑子
            if(game.get_info(x,y)==Chessboard::Chess::black)
            {
                //判断右侧横向
                int tempx=x;
                int tempy=y;
                int num=1;
                while(++tempx<15 && game.get_info(tempx,tempy)==Chessboard::Chess::black)
                    ++num;
                if(num==5)
                    return black;
                //判断下侧纵向
                tempx=x;
                tempy=y;
                num=1;
                while(++tempy<15 && game.get_info(tempx,tempy)==Chessboard::Chess::black)
                    ++num;
                if(num==5)
                    return black;
                //判断右下斜向
                tempx=x;
                tempy=y;
                num=1;
                while(++tempx<15 && ++tempy<15 && game.get_info(tempx,tempy)==Chessboard::Chess::black)
                    ++num;
                if(num==5)
                    return black;
                //判断左下斜向
                tempx=x;
                tempy=y;
                num=1;
                while(--tempx>=0 && ++tempy<15 && game.get_info(tempx,tempy)==Chessboard::Chess::black)
                    ++num;
                if(num==5)
                    return black;

            }
            //判断白子
            if(game.get_info(x,y)==Chessboard::Chess::white)
            {
                //判断右侧横向
                int tempx=x;
                int tempy=y;
                int num=1;
                while(++tempx<15 && game.get_info(tempx,tempy)==Chessboard::Chess::white)
                    ++num;
                if(num==5)
                    return white;
                //判断下侧纵向
                tempx=x;
                tempy=y;
                num=1;
                while(++tempy<15 && game.get_info(tempx,tempy)==Chessboard::Chess::white)
                    ++num;
                if(num==5)
                    return white;
                //判断右下斜向
                tempx=x;
                tempy=y;
                num=1;
                while(++tempx<15 && ++tempy<15 && game.get_info(tempx,tempy)==Chessboard::Chess::white)
                    ++num;
                if(num==5)
                    return white;
                //判断左下斜向
                tempx=x;
                tempy=y;
                num=1;
                while(--tempx>=0 && ++tempy<15 && game.get_info(tempx,tempy)==Chessboard::Chess::white)
                    ++num;
                if(num==5)
                    return white;
            }
        }
    return null;
}
