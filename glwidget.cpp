#include "glwidget.h"

static const char *vertexShaderSource = "attribute highp vec4 posAttr;\n"
                                        "attribute lowp vec2 uvAttr;\n"
                                        "varying lowp vec2 uv;\n"
                                        "void main() {\n"
                                        "   uv = uvAttr;\n"
                                        "   gl_Position = posAttr;\n"
                                        "}\n";

static const char *fragmentShaderSource = "varying lowp vec2 uv;\n"
                                          "void main() {\n"
                                          "   gl_FragColor = vec4(step(0.5, uv), 0.0, 1.0);\n"
                                          "}\n";

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();

    program->bind();
    posAttr = program->attributeLocation("posAttr");
    Q_ASSERT(posAttr != -1);
    uvAttribute = program->attributeLocation("uvAttr");
    Q_ASSERT(uvAttribute != -1);
    program->release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->bind();

    static const GLfloat vertices[] = {-1.0f, 3.0f, -1.0f, -1.0f, 3.0f, -1.0f};
    static const GLfloat uvs[] = {0.0f, 2.0f, 0.0f, 0.0f, 2.0f, 0.0f};

    glVertexAttribPointer(posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, 0, uvs);

    glEnableVertexAttribArray(posAttr);
    glEnableVertexAttribArray(uvAttribute);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(uvAttribute);
    glDisableVertexAttribArray(posAttr);

    program->release();
}