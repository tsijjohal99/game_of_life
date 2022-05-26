#include "game_of_life/worldHandler.h"

#include <conio.h>
#include <stdio.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace GoL {
    WorldHandler::WorldHandler() {
        world.displayWorld();
        iterationLoop();
    }

    void WorldHandler::iterationLoop() {
        bool looping = true;
        while (looping) {
            system("cls");
            std::cout << "Iteration " << ++iteration << '\n';
            looping = !world.nextIteration();
            world.displayWorld();
            std::cout << "Press p to pause for 5 seconds\n";
            std::cout << "Press r to restart\n";
            std::cout << "Press 0 to exit\n";
            char input = waitForCharInput(1);
            switch (input) {
                case 'p': {
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    break;
                }
                case 'r': {
                    world.restartWorld();
                    break;
                }
                case '0': {
                    looping = false;
                    break;
                }
            }
        }
    }

    char WorldHandler::waitForCharInput(int seconds) {
        char c = '1';
        while (seconds != 0) {
            if (_kbhit()) {
                c = getch();
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            --seconds;
        }
        return c;
    }
}  // namespace GoL