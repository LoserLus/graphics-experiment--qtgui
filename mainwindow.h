#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QMouseEvent>
#include <QTimer>
#include <QStack>
#include <QScreen>
#include "cline.h"
#include "clock.h"
#include "paint3dwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QMenuBar* menuBar;
    QMenu* paintMenu;
    QMenu* opreateMenu;
    QAction* drawDiamond;
    QAction* drawLine;
    QAction* drawClock;
    QAction* drawPoly;
    QAction* draw3DCube;
    QAction* drawBezier;
    QAction* drawLightCube;
    QAction* repaint;
    QAction* refresh;
    QPainter* painter;
    enum PAINTER_STATE
    {
        NOT_DRAWING,
        DRAW_LINE,
        DRAW_DIAMOND,
        DRAW_CLOCK,
        DRAW_POLYGON,
        DRAW_3DCUBE,
        DRAW_BEZIER,
        DRAW_LIGHTCUBE
    };
    PAINTER_STATE state = NOT_DRAWING;




    int windowWidth=0,windowHeight=0;
    int lineX1=0,lineX2=0,lineY1=0,lineY2=0;
    int diamondR = 0, diamondN=0;
    Clock * clock=nullptr;
    QTimer *timer=nullptr;

    QVector<QPointF> pointList;                          //存储所有绘制的点
    bool polyFinish=false;
    QPointF fillCenter;
    bool fillPoly=false;
    bool getImage=false;
    QPixmap pixmap;
    QImage image ;

    Paint3DWindow * paint3DWindow=nullptr;

    bool bezierFinish=false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onDrawDiamondAction();
    void onDrawLineAction();
    void onDrawClockAction();
    void onDrawPolyAction();
    void onDraw3DCubeAction();
    void onDrawBezierAction();
    void onDrawLightCubeAction();
    void drawDiamondAlg(QPainter*);
    void drawLineAlg(QPainter*);
    void drawPolyAlg(QPainter*);
    void fillPolyAlg(QPainter*,QStack<QPointF>& ,QPointF,QColor,QColor);
    void scanNextLine(QStack<QPointF>& ,int right,int left,int y,QColor,QColor);
    void drawBezierAlg(QPainter*);
    long getDeCasteliauPoint(double t, long* p,int controlNum);
    void stateChange(PAINTER_STATE newState);
    QString getRGB(QColor &color);
protected:
    void paintEvent(QPaintEvent *);



    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
