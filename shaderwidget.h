#ifndef SHADERWIDGET_H
#define SHADERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class ShaderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
        ShaderWidget(QWidget* parent = nullptr, std::string vertexShaderSource = "", std::string fragmentShaderSource = "");
        ~ShaderWidget();

    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int w, int h) override;

    private:
        QOpenGLShaderProgram* shaderProgram;
        QOpenGLBuffer vbo;
        QOpenGLVertexArrayObject vao;
        std::string vertexShaderSource;
        std::string fragmentShaderSource;
};

#endif // SHADERWIDGET_H
