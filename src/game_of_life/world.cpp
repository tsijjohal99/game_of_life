#include "game_of_life/world.h"

#include <algorithm>
#include <iostream>

namespace GoL {
    World::World() {
        for (int r = 0; r < _height; r++) {
            std::string line;
            std::cout << "Input line " << r << " (. = dead, * = alive):" << '\n';
            std::cin >> line;
            if (checkInput(line)) {
                for (int c = 0; c < _width; c++) {
                    grid[c][r] = line[c] == '.' ? false : true;
                }
            } else {
                std::cout << "Try again\n";
                r--;
            }
        }
        memcpy(initial_grid, grid, sizeof(initial_grid));
    }

    bool World::checkInput(std::string input) {
        if (input.size() != _width ||
            !std::all_of(input.begin(), input.end(), [](char c) { return c == '.' || c == '*'; }))
            return false;
        return true;
    }

    void World::displayWorld() {
        for (int r = 0; r < _height; r++) {
            for (int c = 0; c < _width; c++) {
                std::cout << (grid[c][r] ? '*' : '.');
                std::cout << ' ';
            }
            std::cout << '\n';
        }
    }

    bool World::nextIteration() {
        bool new_grid[_width][_height];
        bool empty = true;
        for (int r = 0; r < _height; r++) {
            for (int c = 0; c < _width; c++) {
                int neighbours_count = neighbours(c, r);
                if (grid[c][r]) {
                    if (neighbours_count < 2 || neighbours_count > 3) {
                        new_grid[c][r] = false;
                    } else {
                        new_grid[c][r] = true;
                        empty = false;
                    }
                } else {
                    if (neighbours_count == 3) {
                        new_grid[c][r] = true;
                        empty = false;
                    } else {
                        new_grid[c][r] = false;
                    }
                }
            }
        }
        memcpy(grid, new_grid, sizeof(grid));
        return empty;
    }

    int World::neighbours(int c, int r) {
        int count = 0;
        for (int i = c - 1; i < c + 2; i++) {
            for (int j = r - 1; j < r + 2; j++) {
                if (!(i == c && j == r) && grid[i % _width][j % _height])
                    count++;
            }
        }
        return count;
    }

    void World::restartWorld() {
        memcpy(grid, initial_grid, sizeof(grid));
    }
}  // namespace GoL