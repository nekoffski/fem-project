#pragma once

#include <iostream>
#include <unordered_map>

#include <fem/math/Utils.hpp>

namespace fem::math {

enum class Boundary : unsigned char {
    LEFT = 0,
    BOTTOM = 1,
    RIGHT = 2,
    TOP = 3
};

inline std::unordered_map<Boundary, std::array<int, 2>> boundaryToPoints = {
    { Boundary::LEFT, { 0, 1 } },
    { Boundary::BOTTOM, { 2, 3 } },
    { Boundary::RIGHT, { 4, 5 } },
    { Boundary::TOP, { 6, 7 } }
};

inline Mat4 calculateHMatrix(const Mat4& dx, const Mat4& dy, std::array<float, 4> jac, const float k = 25.0f) {
    Mat4 h{};

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int z = 0; z < 4; ++z) {
                h[j][z] += dx[i][j] * dx[i][z] * jac[i] * k;
                h[j][z] += dy[i][j] * dy[i][z] * jac[i] * k;
            }
    return h;
}

inline Mat4 calculateCMatrix(const Mat4& shapes, std::array<float, 4> jac, const float C = 700.0f, const float ro = 7800.0f) {
    Mat4 c{};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                c[j][k] += shapes[i][j] * shapes[i][k] * jac[i] * C * ro;
    return c;
}

inline Mat4 calculatePVector(std::vector<Boundary> boundaries, Mat8x4 bs, std::vector<float> jacobians) {
    Mat4 p{};
    for (const auto& boundary : boundaries) {
        const auto& points = boundaryToPoints[boundary];
        const auto jacobian = jacobians[static_cast<int>(boundary)];

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                p[i][j] += (bs[points[0]][i] * bs[points[0]][j] + bs[points[1]][i] * bs[points[1]][j]) * jacobian * 25;
    }
    return p;
}
}
