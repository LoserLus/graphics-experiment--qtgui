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
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onDrawDiamondAction();
    void drawDiamondAlg(QPainter*);
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    QMenuBar* menuBar;
    QMenu* paintMenu;
    QMenu* opreateMenu;
    QAction* drawDiamond;
    QAction* repaint;
    QAction* refresh;
    QPainter* painter;
    enum PAINTER_STATE
        {
            NOT_DRAWING,
            DRAW_LINE,
            DRAW_DIAMOND
        };
        PAINTER_STATE state = NOT_DRAWING;
    bool flag = true;
};
#endif // MAINWINDOW_H
