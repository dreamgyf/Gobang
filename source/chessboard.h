#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include "record.h"

namespace Ui {
class Chessboard;
}

class Chessboard;

class Judge
{
public:
    enum Winner{null,black,white};
    Judge();
    Winner winner(const Chessboard &game);
};

class AI {
public:
    AI();
    void choose();
    int getx() const {return x;}
    int gety() const {return y;}
private:
    int x = -1;
    int y = -1;
    int point[15][15];
    void initialization(const Chessboard &game);
    void get_point(const Chessboard &game);
};

class Chessboard : public QMainWindow
{
    Q_OBJECT

public:
    enum class Chess{empty,black,white};
    enum Mode{man_machine,man_man};
    enum class Colour{black,white};
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();
    void set_mode(Mode m) {mode = m;}
    Chess get_info(int x,int y) const {return chess[y][x];}
    bool isfull() const;
private slots:
    void new_composition();
    void retract();
    void on_action_about_triggered();
    void on_action_man_machine_triggered();
    void on_action_man_man_triggered();
    void on_action_blackfirst_triggered();
    void on_action_whitefirst_triggered();
private:
    Ui::Chessboard *ui;
    int unitx;
    int unity;
    unsigned num = 0;
    Mode mode = man_man;
    Chess chess[15][15];
    int last_place[2] = {-1,-1};
    Colour firstcolour = Colour::black;
    Colour colour = firstcolour;
    Judge judge;
    bool end = false;
    Record record;
    QMessageBox black_win;
    QMessageBox white_win;
    QMessageBox full;
    QMessageBox about;
    QTextEdit *record_text = new QTextEdit(this);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

};



#endif // CHESSBOARD_H
