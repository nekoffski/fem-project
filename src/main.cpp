#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>
#include <fem/math/IntegralSolver.hpp>
#include <fem/math/JacobianSolver.h>
#include <fem/math/MatrixSolver.hpp>

using namespace fem;

int main() {
    math::UniversalElement ue;
    math::JacobianSolver jacobianSolver(ue);

    std::vector<math::Point> points{
        { 0.0f, 0.0f },
        { 0.025f, 0.0f },
        { 0.025f, 0.025f },
        { 0.0f, 0.025f }
    };

    auto [dx, dy, jacobians] = jacobianSolver.calculateDerivatives(points);
    auto h = fem::math::calculateHMatrix(dx, dy, jacobians);
    auto c = fem::math::calculateCMatrix(ue.shapeFunctions, jacobians);

    std::cout << c;

    return 0;
}
