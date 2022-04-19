#include "paint3dwindow.h"

Paint3DWindow::Paint3DWindow(QWidget *parent):QGLWidget(parent)
{
    roate=0.0f;
    xroate=0.0f;
    yroate=0.0f;
    scale=0.5f;
    //QTimer *timer = new QTimer(this);                   //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    //connect(timer, &QTimer::timeout, this, &Paint3DWindow::updateGL);
    //timer->start(10);
}

void Paint3DWindow::draw3Dcube()
{
    int i,j;
    glColor3f( 1.0, 0.0, 0.0 );
    glBegin(GL_LINES);
    for(i=0; i<12; ++i) // 12 条线段

    {
        for(j=0; j<2; ++j) // 每条线段 2个顶点

        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

void Paint3DWindow::drawLightCube()
{
    GLfloat colors[][3] = {
        { 1.0, 0.0, 0.0 },
        { 1.0, 1.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 1.0, 1.0 },
        { 1.0, 0.0, 1.0 },
        { 0.0, 0.0, 1.0 }
    };
    //    glEnable(GL_LIGHT0); //使用第0号光照
    //    glEnable(GL_LIGHTING); //在后面的渲染中使用光照
    //    GLfloat sun_light_position[] = { -2.0f, 2.0f, 0.0f, 1.0f };

    //定义  的漫反射特性
    GLfloat mat_diffuse[]={
        1.0, 0.0, 0.0,1.0,
        1.0, 1.0, 0.0,1.0,
        0.0, 1.0, 0.0,1.0,
        0.0, 1.0, 1.0,1.0,
        1.0, 0.0, 1.0,1.0,
        0.0, 0.0, 1.0,1.0,
    };
    //    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //指定第0号光源的位置

    //    for (int i = 0; i < 6; ++i)      // 有六个面，循环六次
    //    {
    //        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*i);
    //        glColor3fv(colors[i]);
    //        glBegin(GL_POLYGON);
    //        for (int j = 0; j < 4; ++j)     // 每个面有四个顶点，循环四次
    //            glVertex3fv(cube_vertex_list[cube_index_list[i][j]]);
    //        glEnd();
    //    }


    glBegin( GL_QUADS );
    glColor3f( 0.0, 1.0, 0.0 );
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*0);
    glVertex3f(  1.0,  1.0, -1.0 );
    glVertex3f( -1.0,  1.0, -1.0 );
    glVertex3f( -1.0,  1.0,  1.0 );
    glVertex3f(  1.0,  1.0,  1.0 );

    glColor3f( 1.0, 0.5, 0.0 );
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*1);
    glVertex3f(  1.0, -1.0,  1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f(  1.0, -1.0, -1.0 );

    glColor3f( 1.0, 0.0, 0.0 );
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*2);
    glVertex3f(  1.0,  1.0,  1.0 );
    glVertex3f( -1.0,  1.0,  1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );

    glColor3f( 1.0, 1.0, 0.0 );
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*3);
    glVertex3f(  1.0, -1.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( -1.0,  1.0, -1.0 );
    glVertex3f(  1.0,  1.0, -1.0 );

    glColor3f( 0.0, 0.0, 1.0 );
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*4);
    glVertex3f( -1.0,  1.0,  1.0 );
    glVertex3f( -1.0,  1.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );

    glColor3f( 1.0, 0.0, 1.0 );
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse+4*5);
    glVertex3f(  1.0,  1.0, -1.0 );
    glVertex3f(  1.0,  1.0,  1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );
    glVertex3f(  1.0, -1.0, -1.0 );
    glEnd();
}

void Paint3DWindow::setState(PAINTER_STATE newState)
{
    state = newState;
}


void Paint3DWindow::initializeGL()
{

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0); //使用第0号光照
    glEnable(GL_LIGHTING); //在后面的渲染中使用光照
    GLfloat sun_light_position[] = { -1.0f, 1.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //指定第0号光源的位置
}

void Paint3DWindow::resizeGL(int w, int h)
{
    glViewport( 0, 0, (GLint)w, (GLint)h);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //     if (w <= h)
    //             glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
    //                 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    //         else
    //             glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
    //                 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    gluPerspective( 0.0, (GLfloat)w/(GLfloat)h, 1.0, 500.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


}

void Paint3DWindow::paintGL()
{

    glMatrixMode( GL_MODELVIEW );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScalef(scale,scale,scale);
    glRotatef(roate,1,1,1);
    glRotatef(xroate,1,0,0);
    glRotatef(yroate,0,1,0);
    switch (state) {
    case DRAW_3DCUBE:
        draw3Dcube();
        break;
    case DRAW_LIGHTCUBE:
        drawLightCube();
        break;
    default:
        break;
    }

    //    glBegin( GL_TRIANGLES );
    //    glColor3f( 1.0, 0.0, 0.0 );
    //    glVertex3f(  0.0,  1.0,  0.0 );
    //    glColor3f( 0.0, 1.0, 0.0 );
    //    glVertex3f( -1.0, -1.0,  1.0 );
    //    glColor3f( 0.0, 0.0, 1.0 );
    //    glVertex3f(  1.0, -1.0,  1.0 );
    //    glColor3f( 1.0, 0.0, 0.0 );
    //    glVertex3f(  0.0,  1.0,  0.0 );
    //    glColor3f( 0.0, 0.0, 1.0 );
    //    glVertex3f(  1.0, -1.0,  1.0 );
    //    glColor3f( 0.0, 1.0, 0.0 );
    //    glVertex3f(  1.0, -1.0, -1.0 );
    //    glColor3f( 1.0, 0.0, 0.0 );
    //    glVertex3f(  0.0,  1.0,  0.0 );
    //    glColor3f( 0.0, 1.0, 0.0 );
    //    glVertex3f(  1.0, -1.0, -1.0 );
    //    glColor3f( 0.0, 0.0, 1.0 );
    //    glVertex3f( -1.0, -1.0, -1.0 );
    //    glColor3f( 1.0, 0.0, 0.0 );
    //    glVertex3f(  0.0,  1.0,  0.0 );
    //    glColor3f( 0.0, 0.0, 1.0 );
    //    glVertex3f( -1.0, -1.0, -1.0 );
    //    glColor3f( 0.0, 1.0, 0.0 );
    //    glVertex3f( -1.0, -1.0,  1.0 );
    //    glEnd();


    // glEnd();
    // roate+=1;

}

void Paint3DWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        roate-=1;
        break;
    case Qt::Key_Right:
        roate+=1;
        break;
    case Qt::Key_W:
        xroate+=1;
        break;
    case Qt::Key_S:
        xroate-=1;
        break;
    case Qt::Key_A:
        yroate-=1;
        break;
    case Qt::Key_D:
        yroate+=1;
        break;
    case Qt::Key_Space:
        roate=0;
        xroate=0;
        yroate=0;
        break;
    default:
        break;
    }
    updateGL();
}

void Paint3DWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        scale+=0.1;
    }
    else if(event->button()==Qt::RightButton)
    {
        scale-=0.1;
    }
    updateGL();
}



