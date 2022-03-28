#include "cline.h"

CLine::CLine(QPoint *start, QPoint *end, QObject *parent):QObject(parent)
{
    this->start = start;
    this->end = end;
}

CLine::~CLine()
{

}

void CLine::drawLine()
{
    qDebug()<<"CLine draw Line ";
    qDebug()<<"start:"<<"("<<start->x()<<","<<start->y()<<")";
    qDebug()<<"end:"<<"("<<end->x()<<","<<end->y()<<")";
    int deltaX = start->x()-end->x();
    int deltaY = start->y()-end->y();
    if(deltaX==0&&deltaY==0) qDebug()<<"same point";
    else if(deltaX==0) qDebug()<<"k is oo";
    else if(deltaY==0) qDebug()<<"k is 0";
    else
    {
        float k = 1.0*deltaY/deltaX;
        qDebug()<<"k is "<<k;
    }
}

void CLine::setStart(int x, int y)
{
    start=new QPoint(x,y);
}

void CLine::setEnd(int x, int y)
{
    end=new QPoint(x,y);
}
