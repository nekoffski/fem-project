#pragma once

#include <cstdint>
#include <exception>
#include <vector>

#include <fem/math/containers/Vector.hpp>

#include <Eigen/Dense>

namespace fem::math::containers {

template <typename T>
class MatrixX {
public:
    std::vector<std::vector<T>> data;

    explicit MatrixX() = default;

    explicit MatrixX(std::size_t size, T defaultValue = static_cast<T>(0))
        : m_size(size) {
        data.resize(m_size);
        for (int i = 0; i < m_size; ++i)
            data[i].resize(m_size, defaultValue);
    }

    void reset() {
        for (int i = 0; i < m_size; ++i)
            for (int j = 0; j < m_size; ++j)
                data[i][j] = static_cast<T>(0);
    }

    std::size_t size() const {
        return m_size;
    }

    VectorX<T> solve(VectorX<T> B) {
        Eigen::MatrixXf A(m_size, m_size);

        for (int i = 0; i < m_size; ++i)
            for (int j = 0; j < m_size; ++j)
                A(i, j) = data[i][j];

        // temp = A.lu().solve(B.toEigen());
        return VectorX<T>{ A.llt().solve(B.toEigen()) };
    }

    MatrixX operator+(const MatrixX& rhs) {
        MatrixX<T> res = *this;
        for (int i = 0; i < m_size; ++i)
            for (int j = 0; j < m_size; ++j)
                res.data[i][j] += rhs.data[i][j];
        return res;
    }

    template <typename C>
    MatrixX operator/(const C value) {
        MatrixX<T> res = *this;
        for (int i = 0; i < m_size; ++i)
            for (int j = 0; j < m_size; ++j)
                res.data[i][j] /= value;
        return res;
    }

    VectorX<T> operator*(const VectorX<T>& rhs) {
        int n = rhs.size();
        if (n != m_size)
            throw std::logic_error("Size does not match");
        VectorX<T> res(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res.data[i] += data[i][j] * rhs.data[j];
        return res;
    }

private:
    std::size_t m_size;
};
}
