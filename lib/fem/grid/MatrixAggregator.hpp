#pragma once

#include <iostream>
#include <ostream>
#include <vector>

#include <fem/grid/Element.h>

namespace fem::grid {

using UndefinedSizeMat = std::vector<std::vector<float>>;
using UndefinedSizeVec = std::vector<float>;

struct AggregatedMatrices {
    AggregatedMatrices(std::size_t n) {
        C.resize(n);
        for (auto& v : C)
            v.resize(n);
        H = C;
        P.resize(n);
    }

    UndefinedSizeMat C;
    UndefinedSizeMat H;
    UndefinedSizeVec P;
};

inline AggregatedMatrices aggregateMatrices(const std::vector<Element>& elements, const std::size_t N) {
    AggregatedMatrices aggregatedMatrices{ N };
    for (const auto& element : elements) {
        const auto& nodes = element.nodesIds;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                aggregatedMatrices.H[nodes[i]][nodes[j]] += element.H[i][j];
                aggregatedMatrices.C[nodes[i]][nodes[j]] += element.C[i][j];
            }
            aggregatedMatrices.P[nodes[i]] += element.P[i];
        }
    }
    return aggregatedMatrices;
}
}

inline fem::grid::UndefinedSizeVec operator+(const fem::grid::UndefinedSizeVec& lhs, const fem::grid::UndefinedSizeVec& rhs) {
    fem::grid::UndefinedSizeVec res = lhs;
    for (int i = 0; i < lhs.size(); ++i)
        res[i] += rhs[i];
    return res;
}

inline fem::grid::UndefinedSizeMat operator+(const fem::grid::UndefinedSizeMat& lhs, const fem::grid::UndefinedSizeMat& rhs) {
    fem::grid::UndefinedSizeMat res = lhs;
    int n = lhs.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] += rhs[i][j];
    return res;
}

inline fem::grid::UndefinedSizeVec operator*(const fem::grid::UndefinedSizeMat& lhs, const fem::grid::UndefinedSizeVec& rhs) {
    int n = lhs.size();
    fem::grid::UndefinedSizeVec res(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i] += lhs[i][j] * rhs[j];
    return res;
}

inline fem::grid::UndefinedSizeMat operator/(const fem::grid::UndefinedSizeMat& lhs, float rhs) {
    fem::grid::UndefinedSizeMat res = lhs;
    int n = lhs.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] = lhs[i][j] / rhs;
    return res;
}

inline std::ostream& operator<<(std::ostream& ss, const fem::grid::UndefinedSizeMat& mat) {
    for (auto& x : mat) {
        for (auto& y : x)
            ss << y << " ";
        ss << "\n";
    }
    return ss;
}

inline std::ostream& operator<<(std::ostream& ss, const fem::grid::UndefinedSizeVec& vec) {
    for (auto& x : vec) {
        ss << x << ' ';
    }
    return ss;
}
