#include "mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("PixelSynC++");
    setGeometry(100, 100, 1200, 800);

    setDockNestingEnabled(true);

    editorDock = new QDockWidget("Editor", this);
    editorDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, editorDock);

    previewDock = new QDockWidget("Preview", this);
    previewDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::RightDockWidgetArea, previewDock);

    auto glWidget = new GLWidget(previewDock);
    previewDock->setWidget(glWidget);
}