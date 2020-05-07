#pragma once

#include <tuple>

namespace fem::grid {

struct Node {
    Node(std::pair<float, float> coords, bool bc = false)
        : coords(coords)
        , temp(0)
        , boundaryCondition(bc) {}

    std::pair<float, float> coords;
    int temp;
    bool boundaryCondition;
};
}
