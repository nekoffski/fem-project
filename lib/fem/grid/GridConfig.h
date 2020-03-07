#pragma once

#include <string>

namespace fem::grid {

struct GridConfig {
    GridConfig() = default;
    GridConfig(float width, float height, int nodesX, int nodesY)
        : width(width)
        , height(height)
        , nodesX(nodesX)
        , nodesY(nodesY) {
    }
    explicit GridConfig(const std::string& configPath);

    float width;
    float height;
    int nodesX;
    int nodesY;
};
}