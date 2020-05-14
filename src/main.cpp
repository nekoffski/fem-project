#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>
#include <fem/grid/MatrixAggregator.hpp>
#include <fem/math/IntegralSolver.hpp>
#include <fem/math/JacobianSolver.h>
#include <fem/math/MatrixSolver.hpp>

using namespace fem;

int main() {
    grid::GridConfig config{ 0.100f, 0.100f, 4, 4, 0.1f, 10.0f };
    grid::Grid grid{ config };
    grid.build();
    // grid::GridConfig config{ 0.100f, 0.100f, 4, 4 };
    // grid::Grid grid{ config };
    // grid.build();

    grid.runSimulation();

    // auto C = grid.getAggregatedC();
    // auto P = grid.getAggregatedP();
    // auto H = grid.getAggregatedH();
    // grid::UndefinedSizeVec t0(16, 100.0f);
    // float step = 50.0f;

    // auto Cdt = C / step;

    // auto C2 = Cdt * t0;

    // auto Hc = H + Cdt;
    // std::cout << H << "\n\n"
    //           << C << "\n\n"
    //           << Cdt << "\n\n";
    // std::cout << Hc << "\n\n";
    // std::cout << P;
    // std::cout << C2 << "\n\n";
    // std::cout << P + C2 << '\n';

    // std::cout << '\n'
    //           << '\n'
    //           << C << "\n\n"
    //           << C / 2.0f;
    // std::cout << grid.getAggregatedH() << "\n\n";
    // std::cout << grid.getAggregatedP() << '\n';

    //math::UniversalElement ue;
    //math::JacobianSolver js(ue);
    //std::cout << ue.boundaryShapeFunctions << '\n';

    std::vector<math::Point>
        p = {
            { 0.0f, 0.0f },
            { 0.025f, 0.0f },
            { 0.025f, 0.025f },
            { 0.0f, 0.025f }
        };

    //auto j = js.calculateBoundaryJacobian(p);

    // TODO: this function should take vector of boundaries/jacobians and calculate aggregated P vector!!
    //auto ff = math::calculatePVector({ math::Boundary::LEFT }, ue.boundaryShapeFunctions, j);
    //std::cout << ff;

    return 0;
}
