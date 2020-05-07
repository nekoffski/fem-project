#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>
#include <fem/grid/MatrixAggregator.hpp>
#include <fem/math/IntegralSolver.hpp>
#include <fem/math/JacobianSolver.h>
#include <fem/math/MatrixSolver.hpp>

using namespace fem;

int main() {
    // grid::GridConfig config{ 0.100f, 0.100f, 4, 4 };
    // grid::Grid grid{ config };
    // grid.build();

    // grid.runSimulation();
    // std::cout << grid.getAggregatedC() << '\n';
    // std::cout << grid.getAggregatedH();

    math::UniversalElement ue;
    math::JacobianSolver js(ue);
    std::cout << ue.boundaryShapeFunctions << '\n';

    std::vector<math::Point> p = {
        { 0.0f, 0.0f },
        { 0.025f, 0.0f },
        { 0.025f, 0.025f },
        { 0.0f, 0.025f }
    };

    auto j = js.calculateBoundaryJacobian(p);

    // TODO: this function should take vector of boundaries/jacobians and calculate aggregated P vector!!
    auto ff = math::calculatePVector({ math::Boundary::LEFT }, ue.boundaryShapeFunctions, j);
    std::cout << ff;

    return 0;
}
