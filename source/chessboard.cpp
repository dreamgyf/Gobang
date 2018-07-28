#include "chessboard.h"
#include "ui_chessboard.h"




Chessboard::Chessboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chessboard)
{
    for(int i = 0;i < 15;++i)
        for(int j = 0;j < 15;++j)
            chess[i][j] = Chess::empty;
    unitx = width()/4.0*3.0/16.0;
    unity = (height()-23)/16;
    ui->setupUi(this);
    QPushButton *newgame = new QPushButton(u8"开始新游戏",this);
    QPushButton *retract = new QPushButton(u8"悔棋",this);
    QPushButton *about = new QPushButton(u8"关于",this);
    QPushButton *exit = new QPushButton(u8"退出",this);
    newgame->setGeometry(width()/4*3+12,height()/9*8,100,30);
    retract->setGeometry(width()/4*3+12+110,height()/9*8,100,30);
    about->setGeometry(width()/4*3+12,height()/9*8+30+10,100,30);
    exit->setGeometry(width()/4*3+12+110,height()/9*8+30+10,100,30);
    record_text->setGeometry(width()/4*3+12,height()/10,width()/4.45,height()/10*7.3);
    record_text->setReadOnly(true);
    record_text->setPlainText(u8"这里是棋局记录：");
    setWindowTitle(u8"五子棋");
    ui->action_man_machine->setChecked(false);
    ui->action_man_man->setChecked(true);
    ui->action_blackfirst->setChecked(true);
    ui->action_whitefirst->setChecked(false);
    connect(ui->action_new,&QAction::triggered,this,&Chessboard::new_composition);
    connect(newgame,&QPushButton::clicked,this,&Chessboard::new_composition);
    connect(retract,&QPushButton::clicked,this,&Chessboard::retract);
    connect(about,&QPushButton::clicked,this,&Chessboard::on_action_about_triggered);
    connect(exit,&QPushButton::clicked,this,&Chessboard::close);
}

Chessboard::~Chessboard()
{
    delete ui;
}

bool Chessboard::isfull() const
{
    for(int y = 0;y < 15;++y)
        for(int x = 0;x < 15;++x)
            if(chess[y][x] == Chess::empty)
                return false;
    return true;
}

void Chessboard::paintEvent(QPaintEvent *event)
{
    unitx = width()/4.0*3.0/16.0;
    unity = (height()-23)/16;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawPixmap(0,23,width()/4*3,height()-23,QPixmap("Chessboard.jpg"));
    for(int i = 1;i <= 15;++i)  //绘制棋盘
    {
        painter.drawLine(unitx,23 + unity * i,unitx * 15,23 + unity * i);
        painter.drawLine(unitx * i,23 + unity,unitx * i,23 + unity * 15);
    }
    for(int y = 0;y < 15;++y)   //绘制棋子
        for(int x = 0;x < 15;++x)
        {
            if(chess[y][x] == Chess::black)
                painter.drawPixmap((x+1)*unitx-unitx/3,23+(y+1)*unity-unity/3,unitx/3*2,unity/3*2,QPixmap("black.png"));
            else if(chess[y][x] == Chess::white)
                painter.drawPixmap((x+1)*unitx-unitx/3,23+(y+1)*unity-unity/3,unitx/3*2,unity/3*2,QPixmap("white.png"));
        }
    if(last_place[0] >= 0 && last_place[1] >= 0)
    {
        painter.drawPixmap((last_place[0]+1)*unitx-unitx/3,23+(last_place[1]+1)*unity-unity/3,unitx/3*2,unity/3*2,QPixmap("record.png"));
    }
    record_text->setPlainText(record.text(num));
}

void Chessboard::mousePressEvent(QMouseEvent *event)
{
    if(!end)    //判断游戏是否进行，如果游戏结束，则对鼠标事件不响应
    {
        int x = -1;
        int y = -1;
        if(event->x()-event->x()/unitx*unitx <= unitx/4 && event->x() >= unitx/4*3 && event->x() <= unitx*15+unitx/4)    //确定鼠标点击位置附近的棋盘网格坐标
        {
            x = event->x()/unitx-1;
        }
        else if(event->x()-event->x()/unitx*unitx >= unitx/4*3 && event->x() >= unitx/4*3 && event->x() <= unitx*15+unitx/4)
        {
            x = event->x()/unitx;
        }
        if(event->y()-23-(event->y()-23)/unity*unity <= unity/4 && (event->y()-23) >= unity/4*3 && (event->y()-23) <= unity*15+unity/4)
        {
            y = (event->y()-23)/unity-1;
        }
        else if(event->y()-23-(event->y()-23)/unity*unity >= unity/4*3 && (event->y()-23) >= unity/4*3 && (event->y()-23) <= unity*15+unity/4)
        {
            y = (event->y()-23)/unity;
        }
        if(x >= 0 && y >= 0 && chess[y][x] == Chess::empty)    //确定鼠标点击的位置附近有可落子的网格
        {
            last_place[0] = x;
            last_place[1] = y;
            if(colour == Colour::black)
            {
                record.add(++num,x,y,Record::Colour::black);    //增加记录
                chess[y][x] = Chess::black;
                colour = Colour::white;    //更改颜色
            }
            else
            {
                record.add(++num,x,y,Record::Colour::white);
                chess[y][x] = Chess::white;
                colour = Colour::black;
            }
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
        if(isfull())
        {
            full.information(this,u8"平局",u8"棋盘已满\n   平局",QMessageBox::Ok);
            end = true;
        }
    }
}

void Chessboard::new_composition()
{
    for(int i = 0;i < 15;++i)
        for(int j = 0;j < 15;++j)
            chess[i][j] = Chess::empty;
    colour = firstcolour;
    end = false;
    last_place[0] = -1;
    last_place[1] = -1;
    num = 0;
    record.clear();
    update();
}

void Chessboard::retract()
{
    if(num>0 && !end)
    {
        chess[record.y(num)][record.x(num)] = Chess::empty;
        if(colour == Colour::black)
            colour = Colour::white;    //更改颜色
        else
            colour = Colour::black;
        last_place[0] = record.x(num-1);
        last_place[1] = record.y(num-1);
        --num;
        record.del();
        update();
    }
}

void Chessboard::on_action_about_triggered()
{
    about.about(this,u8"关于",u8"AI尚未开发完毕\n目前仅支持人人对战");
}

void Chessboard::on_action_man_machine_triggered()
{
//    ui->action_man_man->setChecked(false);
//    ui->action_man_machine->setChecked(true);
//    mode = man_machine;
    on_action_about_triggered();
    ui->action_man_machine->setChecked(false);  //暂时不开启
}

void Chessboard::on_action_man_man_triggered()
{
    ui->action_man_machine->setChecked(false);
    ui->action_man_man->setChecked(true);
    mode = man_man;
}

void Chessboard::on_action_blackfirst_triggered()
{
    ui->action_whitefirst->setChecked(false);
    ui->action_blackfirst->setChecked(true);
    firstcolour = Colour::black;
}

void Chessboard::on_action_whitefirst_triggered()
{
    ui->action_blackfirst->setChecked(false);
    ui->action_whitefirst->setChecked(true);
    firstcolour = Colour::white;
}
