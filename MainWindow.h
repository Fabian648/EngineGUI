#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SDLWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT

    SDLWidget* sdlWidget;
    QTextEdit* console;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
};

#endif // MAINWINDOW_H
