#include <iostream>

#include <fem/Errors.h>
#include <fem/Simulation.h>
#include <fem/grid/Grid.h>

using namespace fem;

int main() {
    grid::GridConfig config{ 0.100f, 0.100f, 31, 31, 1.0f, 100.0f };
    // grid::GridConfig config{ 0.100f, 0.100f, 4, 4, 50.0f, 500.0f };

    grid::Grid grid{ config };
    grid.build();

    fem::Simulation(grid).run();

    return 0;
}
