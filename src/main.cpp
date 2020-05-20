#include <iostream>

#include <fem/Errors.h>
#include <fem/Simulation.h>
#include <fem/cfg/Config.h>
#include <fem/grid/Grid.h>

using namespace fem;

int main(int argc, char** argv) {
    if (argc != 2)
        throw std::logic_error("usage: ./fem `config.json`");

    try {
        cfg::Config config(argv[1]);

        grid::Grid grid{ config };
        grid.build();

        fem::Simulation(grid, config).run();

    } catch (ConfigError& e) {
        std::cout << "Error during loading config file\n";
        return -1;
    }

    return 0;
}
