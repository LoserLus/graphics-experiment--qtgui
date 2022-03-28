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
    repaint = new QAction("重绘");
    refresh = new QAction("刷新");
    paintMenu->addAction(drawDiamond);
    paintMenu->addAction(drawLine);
    paintMenu->addAction(drawClock);
    opreateMenu->addAction(repaint);
    opreateMenu->addAction(refresh);
    menuBar->addMenu(paintMenu);
    menuBar->addMenu(opreateMenu);
    this->setMenuBar(menuBar);
    connect(drawDiamond,&QAction::triggered,this,&MainWindow::onDrawDiamondAction);
    connect(drawLine,&QAction::triggered,this,&MainWindow::onDrawLineAction);
    connect(drawClock,&QAction::triggered,this,&MainWindow::onDrawClockAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        switch (state) {
        case DRAW_LINE:
            lineX1=event->x();
            lineY1=event->y();
            break;
        default:
            break;

        }
    }
    qDebug()<<"press"<<":"<<event->button()<<"("<<lineX1<<","<<lineY1<<")";
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
        default:
            break;

        }
    }
    update();
    qDebug()<<"release"<<":"<<event->button()<<"("<<lineX2<<","<<lineY2<<")";
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
    l.drawLine();

}

void MainWindow::stateChange(PAINTER_STATE newState)
{
    if(state == DRAW_CLOCK)
    {
        if(timer!=nullptr&&timer->isActive())
            timer->stop();
    }
    state = newState;
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
        //drawLineAlg(painter);
        painter->drawLine(lineX1,lineY1,lineX2,lineY2);
        drawLineAlg(painter);
        break;
    case DRAW_CLOCK:
        clock->drawCurrentTime(painter,windowWidth,windowHeight);
        break;
    default:
        break;
    }
    painter->end();
}

