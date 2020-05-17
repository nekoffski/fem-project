#pragma once

#include <cstdint>
#include <vector>

#include <Eigen/Dense>

namespace fem::math::containers {

template <typename T>
class VectorX {
public:
    std::vector<T> data;

    explicit VectorX() = default;

    explicit VectorX(Eigen::VectorX<T> eigen)
        : m_size(eigen.rows()) {
        data.resize(m_size);
        for (int i = 0; i < m_size; ++i)
            data[i] = eigen(i);
    }

    explicit VectorX(std::size_t size, T defaultValue = static_cast<T>(0))
        : m_size(size) {
        data.resize(m_size, defaultValue);
    }

    std::size_t size() const {
        return m_size;
    }

    void reset() {
        for (int i = 0; i < m_size; ++i)
            data[i] = static_cast<T>(0);
    }

    Eigen::VectorX<T> toEigen() {
        Eigen::VectorX<T> res(m_size);
        for (int i = 0; i < m_size; ++i)
            res(i) = data[i];
        return res;
    }

    VectorX operator+(const VectorX& rhs) {
        VectorX<T> res = *this;
        for (int i = 0; i < m_size; ++i)
            res.data[i] += rhs.data[i];
        return res;
    }

    auto begin() {
        return data.begin();
    }

    auto end() {
        return data.end();
    }

private:
    std::size_t m_size;
};
}
