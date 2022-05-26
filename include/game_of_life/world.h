#pragma once
#include <memory>

namespace GoL {
    class World {
       private:
        const static int _width{10};
        const static int _height{5};
        bool grid[_width][_height];
        bool initial_grid[_width][_height];

       public:
        World();

        bool checkInput(std::string input);
        void displayWorld();
        bool nextIteration();
        int neighbours(int c, int r);
        void restartWorld();
    };
}  // namespace GoL