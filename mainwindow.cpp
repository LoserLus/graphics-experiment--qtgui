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
    repaint = new QAction("重绘");
    refresh = new QAction("刷新");
    paintMenu->addAction(drawDiamond);
    opreateMenu->addAction(repaint);
    opreateMenu->addAction(refresh);
    menuBar->addMenu(paintMenu);
    menuBar->addMenu(opreateMenu);
    this->setMenuBar(menuBar);
    connect(drawDiamond,&QAction::triggered,this,&MainWindow::onDrawDiamondAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDrawDiamondAction()
{
    qDebug() << "click!";
    state = DRAW_DIAMOND;
    flag = true;
    update();

}

void MainWindow::drawDiamondAlg(QPainter *p)
{
    if(!flag) return;
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
        int r = box1->value();
        int n = box2->value();
        int w = this->width();
        int h = this->height();
        QPointF center(0,0);
        p->translate(w/2,h/2);
        p->drawEllipse(center,r,r);
        QVector<QPointF> points;
        //QVector<QPointF> y;
        qreal perAngle = M_PI*2/n;
        for(int i=0;i<n;i++)
        {
            qreal x = r*cos(i * perAngle);
            qreal y = r*sin(i * perAngle);
            QPointF point(x,y);
            points.append(point);
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j)
                    p->drawLine(points[i],points[j]);
            }
        }

    }
    flag =false;

}

void MainWindow::paintEvent(QPaintEvent *)
{
    //painter->translate(this->width()/2,this->height()/2);



    painter->begin(this);
    switch (state)
    {

        case NOT_DRAWING:
            break;
        case DRAW_DIAMOND:
            drawDiamondAlg(painter);
            break;
        default:
            break;
    }
    painter->end();
}

