#include "clock.h"

Clock::Clock(QObject *parent) : QObject(parent)
{
    hourColor = new QColor(200,100,0,100);
    minuteColor = new QColor(0,127,127,150);
    secondColor = new QColor(0,160,230,150);
}

Clock::~Clock()
{

}

void Clock::drawCurrentTime(QPainter *p,int w,int h)
{
    time = QTime::currentTime();
    p->translate(w/2,h/2);
    p->scale(2,2);
    p->setPen(Qt::NoPen);
    p->setBrush(*hourColor);

    p->save();
    // 每圈360° = 12h 即：旋转角度 = 小时数 * 30°
    p->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    p->drawConvexPolygon(hourHand, 3);
    p->restore();

    p->setPen(*hourColor);

    // 绘制小时线 （360度 / 12 = 30度）
    for (int i = 0; i < 12; ++i) {
        p->drawLine(88, 0, 96, 0);
        p->rotate(30.0);
    }

//    int radius = 100;
//    QFont font = p->font();
//    font.setBold(true);
//    p->setFont(font);
//    int pointSize = font.pointSize();

//    // 绘制小时文本
//    int nHour = 0;
//    for (int i = 0; i < 12; ++i) {
//        nHour = i + 3;
//        if (nHour > 12)
//            nHour -= 12;
//        p->drawText(textRectF(radius*0.8, pointSize, i * 30), Qt::AlignCenter, QString::number(nHour));
//    }

    // 绘制分针
    p->setPen(Qt::NoPen);
    p->setBrush(*minuteColor);

    p->save();
    // 每圈360° = 60m 即：旋转角度 = 分钟数 * 6°
    p->rotate(6.0 * (time.minute() + time.second() / 60.0));
    p->drawConvexPolygon(minuteHand, 3);
    p->restore();

    p->setPen(*minuteColor);

    // 绘制分钟线 （360度 / 60 = 6度）
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            p->drawLine(92, 0, 96, 0);
        p->rotate(6.0);
    }

    // 绘制秒针
    p->setPen(Qt::NoPen);
    p->setBrush(*secondColor);

    p->save();
    // 每圈360° = 60s 即：旋转角度 = 秒数 * 6°
    p->rotate(6.0 * time.second());
    p->drawConvexPolygon(secondHand, 3);
    p->restore();
}
