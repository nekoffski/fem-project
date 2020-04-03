#pragma once

#include <array>
#include <cmath>
#include <sstream>

namespace fem::math {

const float SQRT3 = std::sqrt(3.0f);

struct Point {
    float x;
    float y;
};

using Mat4 = std::array<std::array<float, 4>, 4>;
using Mat2 = std::array<std::array<float, 2>, 2>;
}

inline std::ostream& operator<<(std::ostream& s, const fem::math::Mat2& m) {
    s << m[0][0] << " " << m[0][1] << '\n'
      << m[1][0] << " " << m[1][1] << '\n';
    return s;
}

inline std::ostream& operator<<(std::ostream& s, const fem::math::Mat4& m) {
    s << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << '\n'
      << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << '\n'
      << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << '\n'
      << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << '\n';
    return s;
}