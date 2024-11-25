#ifndef SDLWIDGET_H
#define SDLWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <SDL.h>
#include <vector>

class SDLWidget : public QWidget {
Q_OBJECT

    SDL_Window* sdlWindow;
    SDL_Renderer* renderer;
    bool running;

public:
    SDLWidget(QWidget* parent = nullptr);
    ~SDLWidget() override;

    void initializeSDL();
    void runGameLoop(QTextEdit* console);

private:
    void handleEvents(SDL_Event& e, QTextEdit* console);
    void renderScene();
};

#endif // SDLWIDGET_H
