#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <cmath>

namespace fem::math {

using NodeWeightVector = std::vector<std::pair<float, float>>;

NodeWeightVector n1 {
    { -1.0f / sqrt(3.0f), 1.0f },
    {  1.0f / sqrt(3.0f), 1.0f }
};

NodeWeightVector n2 {
    { -sqrt(3.0f/5.0f),  5.0f/9.0f},
    {  0.0f,             8.0f/9.0f },
    {  sqrt(3.0f/5.0f),  5.0f/9.0f}
};

std::unordered_map<int, NodeWeightVector> nodeWeightMap {
    { 1, n1 },
    { 2, n2 }
};

template<typename T>
T solveIntegral(std::function<T(T)> fun, int N = 2) {
    T res = 0;
    for (const auto &[node, weight] : nodeWeightMap.at(N)) {
        res += fun(node) * weight;
    }
    return res;
}

template<typename T>
T solveIntegral(std::function<T(T, T)> fun, int N = 2) {
    T res = 0;
    const auto& nn = nodeWeightMap.at(N);
    for (const auto &[nodeX, weightX] : nn) {
        for (const auto&[nodeY, weightY] : nn) {
            res += fun(nodeX, nodeY) * weightX * weightY;
        }
    } 
    return res; 
}

}
