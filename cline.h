#ifndef CLINE_H
#define CLINE_H

#include <QObject>
#include <QPoint>
#include <QDebug>
#include <QPainter>
class CLine : public QObject
{
    Q_OBJECT
public:
    CLine(QPoint* start=nullptr,QPoint* end=nullptr,QObject *parent = nullptr);
    ~CLine();
    void drawLine();
    void setStart(int x,int y);
    void setEnd(int x,int y);
private:
    QPoint* start;
    QPoint* end;


};

#endif // CLINE_H
