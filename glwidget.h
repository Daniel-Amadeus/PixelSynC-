#pragma once

#include <QEvent>
#include <QExposeEvent>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <string>

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

    std::string vertexShader = "attribute highp vec4 posAttr;\n"
                               "attribute lowp vec2 uvAttr;\n"
                               "varying lowp vec2 uv;\n"
                               "void main() {\n"
                               "   uv = uvAttr;\n"
                               "   gl_Position = posAttr;\n"
                               "}\n";

    std::string fragmentShader = "varying lowp vec2 uv;\n"
                                 "void main() {\n"
                                 "   gl_FragColor = vec4(step(0.5, uv), 0.0, 1.0);\n"
                                 "}\n";

    QOpenGLShaderProgram *program = nullptr;
};
