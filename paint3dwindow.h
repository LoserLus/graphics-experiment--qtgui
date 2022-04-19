#ifndef PAINT3DWINDOW_H
#define PAINT3DWINDOW_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QGLWidget>
#include <QKeyEvent>
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
