#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QPoint>
#include <QTime>
#include <QColor>
#include <QPainter>
class Clock : public QObject
{
    Q_OBJECT
public:
    Clock(QObject *parent = nullptr);
    ~Clock();
    void drawCurrentTime(QPainter* p,int w,int h);
private:
    // 时针、分针、秒针位置 - 多边形
    const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -30)
    };
    const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -65)
    };

    const QPoint secondHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -80)
    };

    // 时针、分针、秒针颜色
//    QColor hourColor(200,100,0,100);
//    QColor minuteColor(0, 127, 127, 150);
//    QColor secondColor(0, 160, 230, 150);
    QColor *hourColor;
    QColor *minuteColor;
    QColor *secondColor;
    QTime time;

};

#endif // CLOCK_H
