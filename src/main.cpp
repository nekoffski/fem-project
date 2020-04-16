#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>
#include <fem/grid/MatrixAggregator.hpp>
#include <fem/math/IntegralSolver.hpp>
#include <fem/math/JacobianSolver.h>
#include <fem/math/MatrixSolver.hpp>

using namespace fem;

int main() {
    grid::GridConfig config{ 0.100f, 0.100f, 4, 4 };
    grid::Grid grid{ config };
    grid.build();

    grid.runSimulation();
    std::cout << grid.getAggregatedC() << '\n';
    std::cout << grid.getAggregatedH();

    return 0;
}
