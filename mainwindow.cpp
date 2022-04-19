#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setMinimumSize(640,480);
    ui->setupUi(this);
    painter = new QPainter(this);

    menuBar = new QMenuBar(this);
    paintMenu=new QMenu("绘图",menuBar);
    opreateMenu=new QMenu("操作",menuBar);
    drawDiamond = new QAction("金刚石");
    drawLine = new QAction("直线");
    drawClock = new QAction("时钟");
    drawPoly = new QAction("多边形");
    draw3DCube = new QAction("立体正方形");
    drawBezier = new QAction("Bezier曲线");
    drawLightCube = new QAction("光照立方体");
    repaint = new QAction("重绘");
    refresh = new QAction("刷新");
    paintMenu->addAction(drawDiamond);
    paintMenu->addAction(drawLine);
    paintMenu->addAction(drawClock);
    paintMenu->addAction(drawPoly);
    paintMenu->addAction(draw3DCube);
    paintMenu->addAction(drawBezier);
    paintMenu->addAction(drawLightCube);
    opreateMenu->addAction(repaint);
    opreateMenu->addAction(refresh);
    menuBar->addMenu(paintMenu);
    menuBar->addMenu(opreateMenu);
    this->setMenuBar(menuBar);
    connect(drawDiamond,&QAction::triggered,this,&MainWindow::onDrawDiamondAction);
    connect(drawLine,&QAction::triggered,this,&MainWindow::onDrawLineAction);
    connect(drawClock,&QAction::triggered,this,&MainWindow::onDrawClockAction);
    connect(drawPoly,&QAction::triggered,this,&MainWindow::onDrawPolyAction);
    connect(draw3DCube,&QAction::triggered,this,&MainWindow::onDraw3DCubeAction);
    connect(drawBezier,&QAction::triggered,this,&MainWindow::onDrawBezierAction);
    connect(drawLightCube,&QAction::triggered,this,&MainWindow::onDrawLightCubeAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onDrawDiamondAction()
{
    qDebug() << "click!";
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("请输入参数："));
    QString rString = QString("半径：");
    QString nString = QString("等分数：");
    QSpinBox *box1 = new QSpinBox(&dialog);
    box1->setMaximum(500);
    QSpinBox *box2 = new QSpinBox(&dialog);
    form.addRow(rString,box1);
    form.addRow(nString,box2);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    connect(&buttonBox,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    if(dialog.exec()==QDialog::Accepted)
    {
        diamondR = box1->value();
        diamondN = box2->value();
        stateChange(DRAW_DIAMOND);
    }
    update();

}
void MainWindow::onDrawLineAction()
{
    stateChange(DRAW_LINE);
    //flag = true;

    update();
}

void MainWindow::onDrawClockAction()
{
    if(timer == nullptr)
    {
        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    }
    if(clock == nullptr)
    {
        clock = new Clock(this);
    }
    stateChange(DRAW_CLOCK);
    update();
    timer->start(1000);
}

void MainWindow::onDrawPolyAction()
{
    stateChange(DRAW_POLYGON);
    update();
}
void drawLightCubeAlg(QPainter*);
void MainWindow::onDraw3DCubeAction()
{
    stateChange(DRAW_3DCUBE);
    if(paint3DWindow==nullptr)
    {
        paint3DWindow = new Paint3DWindow();
    }
    else
    {
        if(!paint3DWindow->isHidden())
            paint3DWindow->hide();

    }
    paint3DWindow->setState((Paint3DWindow::PAINTER_STATE)DRAW_3DCUBE);
    paint3DWindow->show();
}

void MainWindow::onDrawBezierAction()
{
    stateChange(DRAW_BEZIER);
    update();
}

void MainWindow::onDrawLightCubeAction()
{
    stateChange(DRAW_LIGHTCUBE);
    if(paint3DWindow==nullptr)
    {
        paint3DWindow = new Paint3DWindow();
    }
    else
    {
        if(!paint3DWindow->isHidden())
            paint3DWindow->hide();
    }
    paint3DWindow->setState((Paint3DWindow::PAINTER_STATE)DRAW_LIGHTCUBE);
    paint3DWindow->show();
}
void MainWindow::drawDiamondAlg(QPainter *p)
{
    p->translate(windowWidth/2,windowHeight/2);
    p->scale(1,-1);
    QPointF center(0,0);
    p->drawEllipse(center,diamondR,diamondR);
    QVector<QPointF> points;
    //QVector<QPointF> y;
    qreal perAngle = M_PI*2/diamondN;
    for(int i=0;i<diamondN;i++)
    {
        qreal x = diamondR*cos(i * perAngle);
        qreal y = diamondR*sin(i * perAngle);
        QPointF point(x,y);
        points.append(point);
    }
    for(int i=0;i<diamondN;i++)
    {
        for(int j=0;j<diamondN;j++)
        {
            if(i!=j)
                p->drawLine(points[i],points[j]);
        }
    }

}


void MainWindow::drawLineAlg(QPainter * p)
{
    CLine l;
    l.setStart(lineX1,lineY1);
    l.setEnd(lineX2,lineY2);
    l.drawLine(p,windowWidth,windowHeight);

}

void MainWindow::drawPolyAlg(QPainter *p)
{

    QVector<QLineF> lineList;
    QColor bColor(Qt::red);
    p->setPen(bColor);
    //存储前面的线段   线段的个数：pointList.size() - 1
    for(int i = 0; i < pointList.size() - 1; i++ )
    {
        QLineF line(QPointF(pointList[i].x(), pointList[i].y()), QPointF(pointList[i + 1].x(), pointList[i + 1].y()));
        lineList.push_back(line);
    }
    //双击后封闭多边形
    if(polyFinish)
    {
        QLineF line(QPointF(pointList[0].x(), pointList[0].y()), QPointF(pointList[pointList.size()-1].x(), pointList[pointList.size()-1].y()));
        lineList.push_back(line);
    }
    //绘制所有线段
    p->drawLines(lineList);
    if(fillPoly)
    {
        QStack<QPointF> s;
        QColor fColor(Qt::black);
        fillPolyAlg(painter,s,fillCenter,bColor,fColor);
        fillPoly=false;
    }
}

void MainWindow::fillPolyAlg(QPainter *painter, QStack<QPointF> &s, QPointF point, QColor bColor, QColor fColor)
{
    qDebug()<<"fill Poly alg"<<"("<<point.x()<<","<<point.y()<<")";
    //    if(!flag)
    //    {
    //        stateChange(NOT_DRAWING);
    //        pixmap= grab();
    //        stateChange(DRAW_POLYGON);
    //        image = pixmap.toImage();
    //        flag=true;
    //        update();
    //    }
    QString bc = getRGB(bColor);
    QString fc = getRGB(fColor);
    qDebug()<<"bc:"<<bc<<"fc"<<fc;
    pixmap = QPixmap::grabWindow(this->winId());
    image = pixmap.toImage();
    image.save("/home/luyilong/Pictures/widget.jpg",nullptr,100);

    s.push(fillCenter);
    while(!s.empty())
    {
        QPointF p = s.pop();
        int left = 0;
        int right = 0;
        //        QColor test = ;
        painter->setPen(fColor);
        painter->setBrush(QBrush(fColor));
        for (left = p.x(); image.pixelColor(left, p.y()) != bColor; left--)
        {
            painter->drawPoint(left,p.y());
            image.setPixelColor(left,p.y(),fColor);
        }
        for (right = p.x()+1; image.pixelColor(right, p.y()) != bColor; right++)
        {
            painter->drawPoint(right,p.y());
            image.setPixelColor(right,p.y(),fColor);
        }
        scanNextLine(s,right,left,p.y()-1,bColor,fColor);
        scanNextLine(s,right,left,p.y()+1,bColor,fColor);
    }
}

void MainWindow::scanNextLine(QStack<QPointF> &s, int right, int left, int y, QColor bColor, QColor fColor)
{if(!bezierFinish)
        for (int i = left+1;i<right ;i++ )
        {
            if(image.pixelColor(i,y)!=bColor&&image.pixelColor(i,y)!=fColor)
            {
                int j =i+1;
                while(image.pixelColor(j,y)!=bColor)
                    j++;
                i=j--;
                QPointF P(j,y);
                s.push(P);
            }
        }
}

void MainWindow::drawBezierAlg(QPainter *p)
{
    QVector<QLineF> lineList;
    //QColor bColor(Qt::blue);
    //存储前面的线段   线段的个数：pointList.size() - 1
    for(int i = 0; i < pointList.size() - 1; i++ )
    {
        QLineF line(QPointF(pointList[i].x(), pointList[i].y()), QPointF(pointList[i + 1].x(), pointList[i + 1].y()));
        lineList.push_back(line);
    }
    p->drawLines(lineList);
    if(bezierFinish)
    {
        painter->setPen(QColor(Qt::blue));
        double delta = 1.0/5000;
        QPointF temp;
        long px[10],py[10];
        for(int k=0;k<pointList.size();k++)
        {
            px[k]=pointList.at(k).x();
            py[k]=pointList.at(k).y();
        }
        for(double t=0;t<=1;t+=delta)
        {
            temp.setX(getDeCasteliauPoint(t,px,pointList.size()));
            temp.setY(getDeCasteliauPoint(t,py,pointList.size()));
            painter->drawPoint(temp);
        }
    }
}

long MainWindow::getDeCasteliauPoint(double t, long *p, int controlNum)
{
    double P[10][10];
    for(int k=0;k<controlNum;k++)
    {
        P[0][k]=p[k];
    }
    for(int r=1;r<controlNum;r++)
    {
        for(int i=0;i<controlNum-r;i++)
        {
            P[r][i]=(1-t)*P[r-1][i]+t*P[r-1][i+1];
        }
    }
    return (long)P[controlNum-1][0];
}




void MainWindow::stateChange(PAINTER_STATE newState)
{
    if(state == DRAW_CLOCK)
    {
        if(timer!=nullptr&&timer->isActive())
            timer->stop();
    }
    switch (state)
    {
    case DRAW_CLOCK:
        if(timer!=nullptr&&timer->isActive())
            timer->stop();
        break;
    case DRAW_POLYGON:
        if(!fillPoly)
        {
            polyFinish=false;
            pointList.clear();
        }
        break;
    case DRAW_BEZIER:
        pointList.clear();
        bezierFinish=false;
    default:
        break;
    }
    state = newState;
    switch (state)
    {
    case DRAW_BEZIER:
        pointList.clear();
    default:
        break;
    }
}

QString MainWindow::getRGB(QColor &color)
{
    return QString("rgba(%1, %2, %3)")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        switch (state)
        {
        case DRAW_LINE:
            lineX1=event->x();
            lineY1=event->y();
            break;
        default:
            break;

        }
    }

    //qDebug()<<"press"<<":"<<event->button()<<"("<<lineX1<<","<<lineY1<<")";

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
            switch (state) {
            case DRAW_LINE:
                lineX2=event->x();
                lineY2=event->y();
                break;
            case DRAW_POLYGON:
            case DRAW_BEZIER:
                pointList.push_back(event->pos());
            default:
                break;

            }
            update();
    }
    else if (event->button() == Qt::RightButton) {
        switch (state)
        {
        case DRAW_POLYGON:
            if(polyFinish)
            {
                fillCenter.setX(event->x());
                fillCenter.setY(event->y());
                fillPoly=true;
                update();
            }
            break;
        case DRAW_BEZIER:
            bezierFinish=true;
            update();
            break;
        default:
            break;
        }

        qDebug()<<"release"<<":"<<event->button()<<"("<<lineX2<<","<<lineY2<<")";
    }
}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        switch (state) {
        case DRAW_POLYGON:
            pointList.push_back(event->pos());
            polyFinish=true;
        default:
            break;
        }
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    windowWidth = this->width();
    windowHeight = this->height();
    painter->begin(this);
    switch (state)
    {

    case NOT_DRAWING:
        break;
    case DRAW_DIAMOND:
        drawDiamondAlg(painter);
        break;
    case DRAW_LINE:
        drawLineAlg(painter);
        break;
    case DRAW_CLOCK:
        clock->drawCurrentTime(painter,windowWidth,windowHeight);
        break;
    case DRAW_POLYGON:
        drawPolyAlg(painter);
    case DRAW_BEZIER:
        drawBezierAlg(painter);
    default:
        break;
    }
    painter->end();
}


