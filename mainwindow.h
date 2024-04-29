#pragma once

#include <QDockWidget>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);

  private:
    void initGlDock();

  private:
    QDockWidget *editorDock;
    QDockWidget *previewDock;
};