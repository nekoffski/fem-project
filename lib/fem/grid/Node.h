#pragma once

#include <tuple>

namespace fem::grid {

struct Node {
    Node(std::pair<float, float> coords)
        : coords(coords)
        , temp(0)
        , boundaryCase(false) {}

    std::pair<float, float> coords;
    int temp;
    bool boundaryCase;
};
}
