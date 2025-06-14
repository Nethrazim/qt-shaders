#include "shaderwidget.h"
#include <QWindow>

ShaderWidget::ShaderWidget(QWidget* parent, std::string vertexShaderSource, std::string fragmentShaderSource)
    : QOpenGLWidget(parent), shaderProgram(nullptr), vertexShaderSource(vertexShaderSource), fragmentShaderSource(fragmentShaderSource) {}

ShaderWidget::~ShaderWidget() {
    makeCurrent();
    vbo.destroy();
    vao.destroy();
    delete shaderProgram;
    doneCurrent();
}

void ShaderWidget::initializeGL() {
    makeCurrent();
    initializeOpenGLFunctions();

    QWidget* native = nativeParentWidget();
    if(native && native->windowHandle()) {
        native->windowHandle()->setSurfaceType(QSurface::OpenGLSurface);
    }
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    shaderProgram = new QOpenGLShaderProgram(this);
    if(this->vertexShaderSource.empty())
    {
        shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                               "#version  330 core\n"
                                               "layout(location = 0) in vec3 position;\n"
                                               "void main() {"
                                               "   gl_Position = vec4(position, 1.0);"
                                               "}");
    }else
    {
        shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(this->vertexShaderSource));
    }

    if(this->fragmentShaderSource.empty())
    {
        shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                               "#version 330 core\n"
                                               "out vec4 FragColor;\n"
                                               "void main() { FragColor = vec4(1.0, 0.0, 0.0, 1.0); }");
    }
    else
    {
        shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(this->fragmentShaderSource));
    }



    if(!shaderProgram->link())
    {
        qDebug() << "Shader linking failed:" << shaderProgram->log();
    }

    /*GLfloat vertices[] = {
        -0.5, -0.5f, 0.0f,  //Bottom-left
        0.5f, -0.5f, 0.0f, //Bottom-right
        0.0f, 0.5f, 0.0f //Top-center
    };*/

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.8f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.1f, 0.0f, 1.0f
    };

    // Create VAO
    vao.create();
    vao.bind();

    // Create VBO
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    //Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vbo.release();
    vao.release();
}

void ShaderWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram->bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.release();
    shaderProgram->release();
}

void ShaderWidget::resizeGL(int w, int h){
    glViewport(0,0, w, h);
}
