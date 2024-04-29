#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader.c_str());
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader.c_str());
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

void GLWidget::cleanup()
{
    if (program == nullptr)
        return;
    makeCurrent();
    delete program;
    program = nullptr;
    doneCurrent();
    QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
}