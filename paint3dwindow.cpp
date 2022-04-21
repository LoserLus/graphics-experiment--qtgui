#include "paint3dwindow.h"

Paint3DWindow::Paint3DWindow(QWidget *parent):QGLWidget(parent)
{
    roate=0.0f;
    xroate=0.0f;
    yroate=0.0f;
    scale=0.5f;
    test=0.0f;
}

void Paint3DWindow::draw3Dcube()
{
    int i,j;
    glColor3f (0.0, 0.0, 0.0); // 设置前景色为黑色
    glLineWidth (2.0); //设置线宽
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

    // glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);                                  //开始绘制立方体
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)

    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)

    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右面)
    glEnd();                                            //立方体绘制结束

}

void Paint3DWindow::setState(PAINTER_STATE newState)
{
    state = newState;
}


void Paint3DWindow::initializeGL()
{



    gluLookAt (x0, y0, z0, xref, yref, zref, Vx, Vy, Vz); //指定三维观察参数
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    texture = bindTexture(QPixmap("/home/luyilong/QTCode/CGExpGUI/NeHe.bmp").toImage());       //载入位图并转换成纹理
    glEnable(GL_DEPTH_TEST);
    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};  //环境光参数
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  //漫散光参数
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
    glEnable(GL_LIGHT1);                                //启动一号光源
}

void Paint3DWindow::resizeGL(int w, int h)
{
    glViewport( 0, 0, (GLint)w, (GLint)h);

    //    glMatrixMode( GL_PROJECTION );
    //    glLoadIdentity();
    //    glFrustum (-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, 2.0f);//透视投影，设置透视视景体
    //    //     if (w <= h)
    //    //             glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
    //    //                 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    //    //         else
    //    //             glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
    //    //                 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    //    //gluPerspective( 45.0, (GLfloat)w/(GLfloat)h, 0.8, 500.0 );
    //    glMatrixMode( GL_MODELVIEW );
    //    glLoadIdentity();
    //    gluLookAt (x0, y0, z0, xref, yref, zref, Vx, Vy, Vz); //指定三维观察参数

}

void Paint3DWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if(perspective)
        glFrustum (xwMin, xwMax, ywMin, ywMax, dnear, dfar);//透视投影，设置透视视景体
    //    gluPerspective( 45.0, (GLfloat)this->width()/(GLfloat)this->height(), 3.0, 50.0 );
    //glFrustum (-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, 2.0f);//透视投影，设置透视视景体
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef(0,0,test);
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
        roate=0.0f;
        xroate=0.0f;
        yroate=0.0f;
        scale=0.5f;
        test=0.0f;
        light = false;
        perspective=false;
        break;
    case Qt::Key_Up:
        test+=0.1;
        qDebug()<<"test value :"<<test;
        break;
    case Qt::Key_Down:
        test-=0.1;
        qDebug()<<"test value :"<<test;
    case Qt::Key_P:
        perspective=!perspective;
    case Qt::Key_L:
        light = !light;
        if(light)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
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



