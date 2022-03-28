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
#include "cline.h"
#include "clock.h"
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
    QAction* repaint;
    QAction* refresh;
    QPainter* painter;
    enum PAINTER_STATE
    {
        NOT_DRAWING,
        DRAW_LINE,
        DRAW_DIAMOND,
        DRAW_CLOCK
    };
    PAINTER_STATE state = NOT_DRAWING;
    int windowWidth=0,windowHeight=0;
    bool flag = true;
    bool enableUptade =false;
    int pointIndex=0;
    int lineX1=0,lineX2=0,lineY1=0,lineY2=0;
    int diamondR = 0, diamondN=0;
    Clock * clock=nullptr;
    QTimer *timer=nullptr;
    //QVector<QPoint> pointList;
    // QWidget interface
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void onDrawDiamondAction();
    void onDrawLineAction();
    void onDrawClockAction();
    void drawDiamondAlg(QPainter*);
    void drawLineAlg(QPainter*);
    void stateChange(PAINTER_STATE newState);
protected:
    void paintEvent(QPaintEvent *);


};
#endif // MAINWINDOW_H
