#include "JacobianSolver.h"

#include <array>
#include <functional>
#include <vector>

#include <cmath>

namespace {
}

namespace fem::math {

JacobianSolver::JacobianSolver(UniversalElement universalElement)
    : ue(std::move(universalElement)) {
}

Jacobians JacobianSolver::calculateJacobians(std::vector<Point> points) {
    Jacobians res;
    for (int i = 0; i < 4; ++i) {
        res.matrices[i][0][0] = ue.dksi[i][0] * points[0].x + ue.dksi[i][1] * points[1].x + ue.dksi[i][2] * points[2].x + ue.dksi[i][3] * points[3].x;
        res.matrices[i][0][1] = ue.dksi[i][0] * points[0].y + ue.dksi[i][1] * points[1].y + ue.dksi[i][2] * points[2].y + ue.dksi[i][3] * points[3].y;
        res.matrices[i][1][0] = ue.deta[i][0] * points[0].x + ue.deta[i][1] * points[1].x + ue.deta[i][2] * points[2].x + ue.deta[i][3] * points[3].x;
        res.matrices[i][1][1] = ue.deta[i][0] * points[0].y + ue.deta[i][1] * points[1].y + ue.deta[i][2] * points[2].y + ue.deta[i][3] * points[3].y;

        float det = res.matrices[i][0][0] * res.matrices[i][1][1] - res.matrices[i][1][0] * res.matrices[i][0][1];

        res.matrices[i][0][0] /= det;
        res.matrices[i][0][1] /= det;
        res.matrices[i][1][0] /= det;
        res.matrices[i][1][1] /= det;

        res.dets[i] = det;
    }
    return res;
}

DerivativesTables JacobianSolver::calculateDerivatives(std::vector<Point> points) {
    Mat4 xDerivatives;
    Mat4 yDerivatives;
    auto [jac, dets] = calculateJacobians(points);

    for (int i = 0; i < 4; ++i) {
        auto& j = jac[0];
        for (int z = 0; z < 4; ++z) {
            xDerivatives[i][z] = j[0][0] * ue.dksi[i][z] + j[0][1] * ue.deta[i][z];
            yDerivatives[i][z] = j[1][0] * ue.dksi[i][z] + j[1][1] * ue.deta[i][z];
        }
    }
    return { xDerivatives, yDerivatives, dets };
}

std::vector<float> JacobianSolver::calculateBoundaryJacobian(std::vector<Point> points) {
    const auto n = points.size();
    std::vector<float> res(n - 1);

    for (int i = 0; i < n - 1; ++i) {
        const auto [xb, yb] = points[i];
        const auto [xe, ye] = points[i + 1];
        res[i] = (std::abs(xe - xb) + std::abs(ye - yb)) / 2.0f;
    }
    return res;
}
}
