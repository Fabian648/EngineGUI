//
// Created by fabia on 23.11.2024.
//

#include "MainWindow.h"
#include <QVBoxLayout>
#include <thread>

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), sdlWidget(new SDLWidget(this)), console(new QTextEdit(this)) {
    setWindowTitle("Game Engine mit Qt und SDL");
    setMinimumSize(1000, 1000);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    layout->addWidget(sdlWidget, 2);
    layout->addWidget(console, 1);

    console->setReadOnly(true);
    setCentralWidget(centralWidget);

    sdlWidget->initializeSDL();

    std::thread([this]() { sdlWidget->runGameLoop(console); }).detach();
}

MainWindow::~MainWindow() {
    sdlWidget->~SDLWidget();
}
