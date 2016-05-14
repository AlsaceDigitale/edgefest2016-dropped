#include "GameLoop.hpp"

int main(int, char const**) {
    GameLoop::Instance().init();
    GameLoop::Instance().run();

    return EXIT_SUCCESS;
}
