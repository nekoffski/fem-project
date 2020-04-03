#pragma once

#include <array>
#include <functional>
#include <vector>

#include <fem/math/Utils.hpp>

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
    explicit JacobianSolver();
    Jacobians calculateJacobians(std::vector<Point> points);

    DerivativesTables calculateDerivatives(std::vector<Point> points);

private:
    Mat4 dksi;
    Mat4 deta;
};
}