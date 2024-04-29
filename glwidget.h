#pragma once

#include <QEvent>
#include <QExposeEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

  public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

  protected:
    void initializeGL() override;
    void paintGL() override;

  private:
    GLint posAttr = 0;
    GLint uvAttribute = 0;
    GLint matrixUniform = 0;

    QOpenGLShaderProgram *program = nullptr;
};
