#include "JacobianSolver.h"

#include <array>
#include <functional>
#include <vector>

#include <cmath>

namespace {
float dN1_dksi(float eta) {
    return -0.25 * (1.0f - eta);
}

float dN2_dksi(float eta) {
    return 0.25 * (1.0f - eta);
}

float dN3_dksi(float eta) {
    return 0.25 * (1.0f + eta);
}

float dN4_dksi(float eta) {
    return -0.25 * (1.0f + eta);
}

float dN1_deta(float ksi) {
    return -0.25 * (1.0f - ksi);
}

float dN2_deta(float ksi) {
    return -0.25 * (1.0f + ksi);
}

float dN3_deta(float ksi) {
    return 0.25 * (1.0f + ksi);
}

float dN4_deta(float ksi) {
    return 0.25 * (1.0f - ksi);
}

std::vector<fem::math::Point> localPoints{
    { -1.0f / fem::math::SQRT3, -1.0f / fem::math::SQRT3 }, // p1
    { 1.0f / fem::math::SQRT3, -1.0f / fem::math::SQRT3 }, // p2
    { 1.0f / fem::math::SQRT3, 1.0f / fem::math::SQRT3 }, // p3
    { -1.0f / fem::math::SQRT3, 1.0f / fem::math::SQRT3 } // p4
};

std::vector<std::function<float(float)>> dksis{
    dN1_dksi, dN2_dksi, dN3_dksi, dN4_dksi
};

std::vector<std::function<float(float)>> detas{
    dN1_deta, dN2_deta, dN3_deta, dN4_deta
};
}

namespace fem::math {

JacobianSolver::JacobianSolver() {
    for (int i = 0; i < 4; ++i) {
        const auto& p = localPoints[i];
        for (int j = 0; j < 4; ++j)
            dksi[i][j] = dksis[j](p.y);
    }
    for (int i = 0; i < 4; ++i) {
        const auto& p = localPoints[i];
        for (int j = 0; j < 4; ++j)
            deta[i][j] = detas[j](p.x);
    }
}

Jacobians JacobianSolver::calculateJacobians(std::vector<Point> points) {
    Jacobians res;
    for (int i = 0; i < 4; ++i) {
        res.matrices[i][0][0] = dksi[i][0] * points[0].x + dksi[i][1] * points[1].x + dksi[i][2] * points[2].x + dksi[i][3] * points[3].x;
        res.matrices[i][0][1] = dksi[i][0] * points[0].y + dksi[i][1] * points[1].y + dksi[i][2] * points[2].y + dksi[i][3] * points[3].y;
        res.matrices[i][1][0] = deta[i][0] * points[0].x + deta[i][1] * points[1].x + deta[i][2] * points[2].x + deta[i][3] * points[3].x;
        res.matrices[i][1][1] = deta[i][0] * points[0].y + deta[i][1] * points[1].y + deta[i][2] * points[2].y + deta[i][3] * points[3].y;

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
            xDerivatives[i][z] = j[0][0] * dksi[i][z] + j[0][1] * deta[i][z];
            yDerivatives[i][z] = j[1][0] * dksi[i][z] + j[1][1] * deta[i][z];
        }
    }
    return { xDerivatives, yDerivatives, dets };
}
}
