#include "record.h"

Record::Record()
{
    RECORD temp;
    temp.num = 0;
    temp.x = -1;
    temp.y = -1;
    temp.colour = black;
    temp.text = QString(u8"这里是棋局记录：");
    record.push_back(temp);
}

void Record::add(unsigned num,unsigned x,unsigned y,Colour colour)
{
    RECORD temp;
    temp.num = num;
    temp.x = x;
    temp.y = y;
    temp.colour = colour;
    if(colour == black)
        temp.text = QString(u8"\n黑棋落子")+char(65+x)+QString::number(15-y);
    else if(colour == white)
        temp.text = QString(u8"\n白棋落子")+char(65+x)+QString::number(15-y);
    record.push_back(temp);
}

void Record::del()
{
    record.pop_back();
}

unsigned Record::num(unsigned num) const
{
    return record[num].num;
}

unsigned Record::x(unsigned num) const
{
    return record[num].x;
}

unsigned Record::y(unsigned num) const
{
    return record[num].y;
}

QString Record::text(unsigned num) const
{
    QString text;
    for(unsigned i=0;i<=num;i++)
    {
        text += record[i].text;
    }
    return text;
}

void Record::clear()
{
    QVector<RECORD> newrecord;
    record.swap(newrecord);
    RECORD temp;
    temp.num = 0;
    temp.x = -1;
    temp.y = -1;
    temp.colour = black;
    temp.text = QString(u8"这里是棋局记录：");
    record.push_back(temp);
}
