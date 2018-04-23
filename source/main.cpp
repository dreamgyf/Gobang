#include "chessboard.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chessboard main;
    main.show();

    return a.exec();
}
