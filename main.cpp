#include "Game.h"

int main() {
    while (true) {
        int status = Game::start();
        if (status != Game::RELOAD_STATUS) break;
    }
}