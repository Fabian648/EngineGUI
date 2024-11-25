#include "SDLWidget.h"
#include "utils.h"
#include <iostream>
#include <thread>

SDLWidget::SDLWidget(QWidget* parent)
        : QWidget(parent), sdlWindow(nullptr), renderer(nullptr), running(true) {
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NativeWindow);
    setFocusPolicy(Qt::StrongFocus);
}

SDLWidget::~SDLWidget() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (sdlWindow) SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

void SDLWidget::initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL konnte nicht initialisiert werden! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    sdlWindow = SDL_CreateWindowFrom((void*)winId());
    if (!sdlWindow) {
        std::cerr << "Fenster konnte nicht erstellt werden! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer konnte nicht erstellt werden! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return;
    }
}

void SDLWidget::runGameLoop(QTextEdit* console) {
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            handleEvents(e, console);
        }
        renderScene();
    }
}

void SDLWidget::handleEvents(SDL_Event& e, QTextEdit* console) {
    if (e.type == SDL_QUIT) {
        running = false;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (e.button.button == SDL_BUTTON_LEFT) {
            console->append(QString("Linker Mausklick bei X: %1, Y: %2").arg(mouseX).arg(mouseY));
            createRectangle(100, 100, mouseX, mouseY);
        } else if (e.button.button == SDL_BUTTON_RIGHT) {
            for (int i = 0; i < list_rect.size(); i++) {
                if (isPointInRect(mouseX, mouseY, list_rect[i])) {
                    console->append(QString("Rechteck %1 ausgewaehlt.").arg(i));
                }
            }
        }
    }
}

void SDLWidget::renderScene() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Schwarz
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rot
    for (const auto& rect : list_rect) {
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}
