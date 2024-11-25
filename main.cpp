#define SDL_MAIN_HANDLED
#include <QApplication>
#include <iostream>
#include "MainWindow.h"
#include "windows.h"

int main(int argc, char* argv[]) {
    AllocConsole(); // Erstellt eine Konsole
    freopen("CONOUT$", "w", stdout); // Umleitet std::cout zur Konsole
    freopen("CONOUT$", "w", stderr); // Umleitet std::cerr zur Konsole
    freopen("CONIN$", "r", stdin);  // Umleitet std::cin zur Konsole

    std::cout << "Konsole erfolgreich eingerichtet!" << std::endl;

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
