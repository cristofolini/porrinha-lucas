#include <chrono>
#include <cstdlib>
#include <iostream>
#include "dezero.h"
#include "ai.h"

namespace lucas {


    Player * generateDezero( cmdline::args&& /*args*/ ) {
            bool keep = false;
            unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::string name = "Dezero";
            return new DezeroPlayer(seed, name, keep);
        }
    } // namespace lucas
