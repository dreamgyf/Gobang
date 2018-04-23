#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>


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

class Chessboard : public QMainWindow
{
    Q_OBJECT

public:
    enum Chess{empty,black,white};
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();
    Chess get_info(int x,int y) const {return chess[y][x];}
private slots:


    void new_composition();

    void on_action_about_triggered();

private:
    Ui::Chessboard *ui;
    //About about;
    int unitx;
    int unity;
    Chess chess[15][15];
    bool colour = true;
    Judge judge;
    bool end = false;
    QMessageBox black_win;
    QMessageBox white_win;
    QMessageBox about;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

};



#endif // CHESSBOARD_H
