#ifndef PAINT3DWINDOW_H
#define PAINT3DWINDOW_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QGLWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QOpenGLFunctions>
#include <GL/glu.h>
#include <GL/glut.h>
class Paint3DWindow : public QGLWidget
{
    Q_OBJECT

private:
    GLfloat roate;
    GLfloat scale;
    GLfloat xroate;
    GLfloat yroate;
    GLfloat test;
    bool perspective=false;
    bool light=false;
    /* 观察坐标系参数设置*/
    GLfloat x0 = 0.0, y0= 0.0, z0 =5.0; // 设置观察坐标系原点
    GLfloat xref = 0.0, yref =0.0, zref = 0.0; //设置观察坐标系参考点（视点）
    GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // 设置观察坐标系向上向量（y轴）
    /*观察体（视见体）参数设置 */
    GLfloat xwMin = -1.0, ywMin = -1.0, xwMax = 1.0, ywMax = 1.0;//设置裁剪窗口坐标范围

    GLfloat dnear = 1.0, dfar = 20.0;//设置远、近裁剪面深度范围

    GLuint texture;


    // QOpenGLWidget interface
public:
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
    PAINTER_STATE state = DRAW_3DCUBE;
    Paint3DWindow(QWidget *parent = nullptr);
    void draw3Dcube();
    void drawLightCube();
    void setState(PAINTER_STATE newState);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();



    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};
// 将立方体的八个顶点保存到一个数组里面
static const float vertex_list[][3] =
{
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
};
static const GLint index_list[][2] =
{
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7},
    {0, 2},
    {1, 3},
    {4, 6},
    {5, 7},
    {0, 4},
    {1, 5},
    {7, 3},
    {2, 6}
};
static const GLfloat cube_vertex_list[][3] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
};
static const GLint cube_index_list[][4] = {
    0, 1, 2, 3,//bottem
    0, 3, 7, 4,//left
    2, 3, 7, 6,//front
    1, 2, 6, 5,//right
    0, 1, 5, 4,//back
    4, 5, 6, 7//top
};
#endif // PAINT3DWINDOW_H
