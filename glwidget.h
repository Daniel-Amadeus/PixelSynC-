#pragma once

#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

  public:
    GLWidget(QWidget *parent);
};
