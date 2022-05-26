#pragma once
#include "world.h"

namespace GoL {
    class WorldHandler {
       private:
        int iteration{0};
        World world;

       public:
        WorldHandler();
        void iterationLoop();
        char waitForCharInput(int seconds);
    };
}  // namespace GoL