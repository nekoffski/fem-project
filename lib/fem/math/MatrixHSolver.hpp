#pragma once

#include <iostream>

#include <fem/math/Utils.hpp>

namespace fem::math {

inline Mat4 calculateHMatrix(const Mat4& dx, const Mat4& dy, std::array<float, 4> jac, const float k) {
    Mat4 h{};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int z = 0; z < 4; ++z) {
                h[j][z] += dx[i][j] * dx[i][z] * jac[i] * k;
                h[j][z] += dy[i][j] * dy[i][z] * jac[i] * k;
            }
        }
    }
    return h;
}
}
