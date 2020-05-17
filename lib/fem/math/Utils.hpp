#pragma once

#include <array>
#include <cmath>
#include <sstream>

#include <fem/math/containers/Vector.hpp>

#include <Eigen/Dense>

namespace fem::math {

const float SQRT3 = std::sqrt(3.0f);

struct Point {
    float x;
    float y;
};

enum class Boundary : unsigned char {
    LEFT = 0,
    BOTTOM = 1,
    RIGHT = 2,
    TOP = 3
};

using UndefinedSizeMat = std::vector<std::vector<float>>;
using UndefinedSizeVec = std::vector<float>;

using Mat4 = std::array<std::array<float, 4>, 4>;
using Mat8x4 = std::array<std::array<float, 4>, 8>;
using Mat2 = std::array<std::array<float, 2>, 2>;
using Vec4 = std::array<float, 4>;
}

inline fem::math::UndefinedSizeVec operator+(const fem::math::UndefinedSizeVec& lhs, const fem::math::UndefinedSizeVec& rhs) {
    fem::math::UndefinedSizeVec res = lhs;
    for (int i = 0; i < lhs.size(); ++i)
        res[i] += rhs[i];
    return res;
}

inline fem::math::UndefinedSizeMat operator+(const fem::math::UndefinedSizeMat& lhs, const fem::math::UndefinedSizeMat& rhs) {
    fem::math::UndefinedSizeMat res = lhs;
    int n = lhs.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] += rhs[i][j];
    return res;
}

template <typename T>
inline fem::math::containers::VectorX<T> operator*(const fem::math::UndefinedSizeMat& lhs, const fem::math::containers::VectorX<T>& rhs) {
    int n = lhs.size();
    fem::math::containers::VectorX<T> res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res.data[i] += lhs[i][j] * rhs.data[j];
    return res;
}

inline fem::math::UndefinedSizeMat operator/(const fem::math::UndefinedSizeMat& lhs, float rhs) {
    fem::math::UndefinedSizeMat res = lhs;
    int n = lhs.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] = lhs[i][j] / rhs;
    return res;
}

inline std::ostream& operator<<(std::ostream& ss, const fem::math::UndefinedSizeMat& mat) {
    for (auto& x : mat) {
        for (auto& y : x)
            ss << y << " ";
        ss << "\n";
    }
    return ss;
}

inline std::ostream& operator<<(std::ostream& ss, const fem::math::UndefinedSizeVec& vec) {
    for (auto& x : vec) {
        ss << x << ' ';
    }
    return ss;
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

inline std::ostream& operator<<(std::ostream& s, const fem::math::Vec4& v) {
    for (int i = 0; i < 4; ++i)
        s << v[i] << ' ';
    return s;
}

inline std::ostream& operator<<(std::ostream& s, const fem::math::Mat8x4& m) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j)
            s << m[i][j] << " ";
        s << "\n";
    }
    return s;
}

inline fem::math::Mat4 operator+(const fem::math::Mat4& lhs, const fem::math::Mat4& rhs) {
    fem::math::Mat4 res{};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = lhs[i][j] + rhs[i][j];
    return res;
}
