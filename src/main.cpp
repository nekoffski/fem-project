#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>
#include <fem/math/IntegralSolver.hpp>
#include <fem/math/JacobianSolver.h>
#include <fem/math/MatrixHSolver.hpp>

using namespace fem;

int main() {
    math::JacobianSolver jacobianSolver;

    std::vector<math::Point> points{
        { 0.0f, 0.0f },
        { 0.025f, 0.0f },
        { 0.025f, 0.025f },
        { 0.0f, 0.025f }
    };

    constexpr float K = 30.0f;
    auto [dx, dy, jacobians] = jacobianSolver.calculateDerivatives(points);
    auto h = fem::math::calculateHMatrix(dx, dy, jacobians, K);

    std::cout << h;

    return 0;
}
