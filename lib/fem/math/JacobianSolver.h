#pragma once

#include <array>
#include <functional>
#include <vector>

#include <fem/math/UniversalElement.h>
#include <fem/math/Utils.hpp>
#include <fem/grid/Node.h>

namespace fem::math {

struct DerivativesTables {
    Mat4 dx;
    Mat4 dy;
    std::array<float, 4> jacobians;
};

struct Jacobians {
    std::array<Mat2, 4> matrices;
    std::array<float, 4> dets;
};

class JacobianSolver {
public:
    explicit JacobianSolver(UniversalElement);
    Jacobians calculateJacobians(std::vector<Point> points);
    
    std::vector<float> calculateBoundaryJacobian(std::vector<Point>);

    DerivativesTables calculateDerivatives(std::vector<Point> points);

private:
    UniversalElement ue;
};
}
