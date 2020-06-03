#pragma once

#include <tuple>

namespace fem::grid {

struct Node {
    Node(std::pair<float, float> coords, bool bc = false)
        : coords(coords)
        , temp(0.0f)
        , boundaryCondition(bc) {}

    std::pair<float, float> coords;
    float temp;
    bool boundaryCondition;
};
}
