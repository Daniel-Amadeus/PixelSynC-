#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}