#ifndef RECORD_H
#define RECORD_H

#include <QVector>
#include <QString>

class Record
{
public:
    enum Colour{black,white};
    Record();
    void add(unsigned num,unsigned x,unsigned y,Colour colour);
    void del();
    unsigned num(unsigned num) const;
    unsigned x(unsigned num) const;
    unsigned y(unsigned num) const;
    QString text(unsigned num) const;
    void clear();
private:
    struct RECORD
    {
        unsigned num;
        unsigned x;
        unsigned y;
        Colour colour;
        QString text;
    };
    QVector<RECORD> record;
};

#endif // RECORD_H
