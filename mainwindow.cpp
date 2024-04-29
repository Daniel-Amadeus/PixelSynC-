#include "mainwindow.h"
#include "glwidget.h"

#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("PixelSynC++");
    setGeometry(100, 100, 1200, 800);

    setCentralWidget(new QTextEdit(this));

    setDockNestingEnabled(true);
    initGlDock();
}

void MainWindow::initGlDock()
{
    previewDock = new QDockWidget("Preview", this);
    previewDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::RightDockWidgetArea, previewDock);

    auto glWidget = new GLWidget(previewDock);
    previewDock->setWidget(glWidget);
}