#include "chessboard.h"
#include "ui_chessboard.h"




Chessboard::Chessboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chessboard)
{
    for(int i = 0;i < 15;++i)
        for(int j = 0;j < 15;++j)
            chess[i][j] = empty;
    unitx = width()/16.0;
    unity = height()/16.0;
    ui->setupUi(this);
    setWindowTitle(u8"五子棋");
    //connect(ui->action_about,&QAction::triggered,&about,&About::show);
    connect(ui->action_new,&QAction::triggered,this,&Chessboard::new_composition);

}

Chessboard::~Chessboard()
{
    delete ui;
}

void Chessboard::paintEvent(QPaintEvent *event)
{
    unitx = width()/16;
    unity = (height()-23)/16;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawPixmap(0,23,width(),height()-23,QPixmap("Chessboard.jpg"));
    for(int i = 1;i <= 15;++i)
    {
        painter.drawLine(unitx,23 + unity * i,unitx * 15,23 + unity * i);
        painter.drawLine(unitx * i,23 + unity,unitx * i,23 + unity * 15);
    }
    for(int y = 0;y < 15;++y)
        for(int x = 0;x < 15;++x)
        {
            if(chess[y][x] == black)
                painter.drawPixmap((x+1)*unitx-unitx/3,23+(y+1)*unity-unity/3,unitx/3*2,unity/3*2,QPixmap("black.png"));
            else if(chess[y][x] == white)
                painter.drawPixmap((x+1)*unitx-unitx/3,23+(y+1)*unity-unity/3,unitx/3*2,unity/3*2,QPixmap("white.png"));
        }
}

void Chessboard::mousePressEvent(QMouseEvent *event)
{
    if(!end)
    {
        int x = -1;
        int y = -1;
        if(event->x()-event->x()/unitx*unitx <= unitx/4)
        {
            x = event->x()/unitx-1;
        }
        else if(event->x()-event->x()/unitx*unitx >= unitx/4*3)
        {
            x = event->x()/unitx;
        }
        if(event->y()-23-(event->y()-23)/unity*unity <= unity/4)
        {
            y = (event->y()-23)/unity-1;
        }
        else if(event->y()-23-(event->y()-23)/unity*unity >= unity/4*3)
        {
            y = (event->y()-23)/unity;
        }
        if(x >= 0 && y >= 0 && chess[y][x] == empty)
        {
            if(colour)
                chess[y][x] = black;
            else
                chess[y][x] = white;
            colour = !colour;
            update();
        }
        if(judge.winner(*this)==Judge::Winner::black)
        {
            black_win.information(this,u8"黑方胜",u8"黑方胜",QMessageBox::Ok);
            end = true;
        }
        if(judge.winner(*this)==Judge::Winner::white)
        {
            white_win.information(this,u8"白方胜",u8"白方胜",QMessageBox::Ok);
            end = true;
        }
    }
}

void Chessboard::new_composition()
{
    for(int i = 0;i < 15;++i)
        for(int j = 0;j < 15;++j)
            chess[i][j] = empty;
    end = false;
    update();
}

void Chessboard::on_action_about_triggered()
{
    about.about(this,u8"关于",u8"AI尚未开发完毕\n目前仅支持人人对战");
}
