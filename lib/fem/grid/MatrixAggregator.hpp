#pragma once

#include <iostream>
#include <ostream>
#include <vector>

#include <fem/grid/Element.h>

namespace fem::grid {

using UndefinedSizeMat = std::vector<std::vector<float>>;

struct AggregatedMatrices {
    AggregatedMatrices(std::size_t n) {
        C.resize(n);
        for (auto& v : C)
            v.resize(n);
        H = C;
    }

    UndefinedSizeMat C;
    UndefinedSizeMat H;
};

inline AggregatedMatrices aggregateMatrices(const std::vector<Element>& elements, const std::size_t N) {
    AggregatedMatrices aggregatedMatrices{ N };

    for (const auto& element : elements) {
        const auto& nodes = element.nodesIds;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                aggregatedMatrices.H[nodes[i]][nodes[j]] += element.H[i][j];
                aggregatedMatrices.C[nodes[i]][nodes[j]] += element.C[i][j];
            }
    }
    return aggregatedMatrices;
}
}

inline std::ostream& operator<<(std::ostream& ss, const fem::grid::UndefinedSizeMat& mat) {
    for (auto& x : mat) {
        for (auto& y : x) {
            ss << y << " ";
        }
        ss << "\n";
    }
    return ss;
}
