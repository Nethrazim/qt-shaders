#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shaderwidget.h"

#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QTabWidget* tabWidget = new QTabWidget(this);

    // Create Shader Widgets
    ShaderWidget* shader1 = new ShaderWidget(nullptr, "rainbow_triangle_vertex_shader.shader","rainbow_triangle_fragment_shader.shader");


    // Ensure they expand within the tabs
    shader1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    // Wrap ShaderWidget in layouts
    QWidget* tab1 = new QWidget();
    QVBoxLayout* layout1 = new QVBoxLayout();
    layout1->addWidget(shader1);
    tab1->setLayout(layout1);

    // Add tabs with proper layouts
    tabWidget->addTab(tab1, "Shader 1");

    setCentralWidget(tabWidget);
    resize(800, 600);


}

MainWindow::~MainWindow()
{
    delete ui;
}
