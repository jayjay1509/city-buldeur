#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "gameplay/game.h"

int main(int argc, char* argv[]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // moyen de supprimer la console 
    // Appel de la fonction main standard
    return main(__argc, __argv);
}

int main(int argc, char* argv[]) {
    Game game;
    game.Run();
    return 0;
}


