#include "cline.h"

CLine::CLine(QPoint *start, QPoint *end, QObject *parent):QObject(parent)
{
    this->start = start;
    this->end = end;
}

CLine::~CLine()
{

}

void CLine::drawLine(QPainter* p,int width,int height)
{
    qDebug()<<"CLine draw Line ";
    qDebug()<<"start:"<<"("<<start->x()<<","<<start->y()<<")";
    qDebug()<<"end:"<<"("<<end->x()<<","<<end->y()<<")";
    int deltaX = start->x()-end->x();
    int deltaY = start->y()-end->y();
    float k;
//    p->translate(width/2,height/2);
//    p->scale(1,-1);
    if(deltaX==0&&deltaY==0)
    {
        qDebug()<<"same point";
        p->drawPoint(*end);
    }
    else if(deltaX==0)
    {
        qDebug()<<"k is oo";
        int x = start->x();
        int to=end->y();
        int from=start->y();
        if(start->y()>end->y())
        {
            to = start->y();
            from = end->y();
        }
        qDebug()<<"from:"<<from<<" to: "<<to;
        for(int i=from;i<=to;i++)
            p->drawPoint(x,i);
    }
    else if(deltaY==0)
    {
        qDebug()<<"k is 0";
        int y = start->y();
        int to=end->x();
        int from=start->x();
        if(start->x()>end->x())
        {
            from = end->x();
            to = start->x();
        }
        qDebug()<<"from:"<<from<<" to: "<<to;
        for(int i = from;i<=to;i++)
            p->drawPoint(i,y);
    }
    else if(deltaX*deltaY<0) //k<0
    {
        k=1.0*deltaY/deltaX;
        int a = deltaY, b = -deltaX;
        int toX=0,toY=0,fromY=0,fromX=0;

        if(deltaY/deltaX<-1) //|k| >=1 k<0
        {
            int d = a-2*b;
            int delta1 = -2*b,delta2=2*(a-b);
            if(start->y()<=end->y())
            {
                fromX = end->x();
                fromY = end->y();
                toX = start->x();
                toY = start->y();
                d=-d;
                delta1=-delta1;
                delta2=-delta2;
            }
            else
            {
                fromX = start->x();
                fromY = start->y();
                toX=end->x();
                toY=end->y();
            }

            p->drawPoint(fromX,fromY);
            while(fromY>=toY)
            {
                if(d<0)
                {
                    fromX++;
                    d+=delta2;
                }
                else d+=delta1;
                fromY--;
                p->drawPoint(fromX,fromY);
            }
        }
        else                  //|k|<1 k<0
        {
            int d = 2*a-b;
            int delta1 = 2*a,delta2=2*(a-b);
            if(start->x()>end->x())
            {
                fromX = end->x();
                fromY = end->y();
                toX = start->x();
                toY = start->y();
                d=-d;
                delta1=-delta1;
                delta2=-delta2;
            }
            else
            {
                fromX = start->x();
                fromY = start->y();
                toX=end->x();
                toY=end->y();
            }

            p->drawPoint(fromX,fromY);
            while(fromX<=toX)
            {
                if(d>=0)
                {
                    fromY--;
                    d+=delta2;
                }
                else d+=delta1;
                fromX++;
                p->drawPoint(fromX,fromY);
            }
        }
    }
    else                        //k>0
    {
        k=1.0*deltaY/deltaX;
        int a = deltaY, b = -deltaX;
        int toX=0,toY=0,fromY=0,fromX=0;

        if(deltaY/deltaX>=1) //k>=1
        {
            int d = 2*b+a;
            int delta1 = 2*b,delta2=2*(a+b);
            if(start->y()>end->y())
            {
                fromX = end->x();
                fromY = end->y();
                toX = start->x();
                toY = start->y();
                d=-d;
                delta1=-delta1;
                delta2=-delta2;
            }
            else
            {
                fromX = start->x();
                fromY = start->y();
                toX=end->x();
                toY=end->y();
            }

            p->drawPoint(fromX,fromY);
            while(fromY<=toY)
            {
                if(d>=0)
                {
                    fromX++;
                    d+=delta2;
                }
                else d+=delta1;
                fromY++;
                p->drawPoint(fromX,fromY);
            }

        }
        else                    //k<1
        {
            int d = 2*a+b;
            int delta1 = 2*a,delta2=2*(a+b);
            if(start->x()>end->x())
            {
                fromX = end->x();
                fromY = end->y();
                toX = start->x();
                toY = start->y();
                d=-d;
                delta1=-delta1;
                delta2=-delta2;
            }
            else
            {
                fromX = start->x();
                fromY = start->y();
                toX=end->x();
                toY=end->y();
            }
            p->drawPoint(fromX,fromY);
            while(fromX<=toX)
            {
                if(d<0)
                {
                    fromY++;
                    d+=delta2;
                }
                else d+=delta1;
                fromX++;
                p->drawPoint(fromX,fromY);
            }

        }
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
