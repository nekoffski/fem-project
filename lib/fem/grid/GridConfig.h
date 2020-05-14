#pragma once

#include <string>

namespace fem::grid {

struct GridConfig {
    GridConfig() = default;
    GridConfig(float width, float height, int nodesX, int nodesY, float timestep = 0.1f, float duration = 10.0f)
        : width(width)
        , height(height)
        , nodesX(nodesX)
        , nodesY(nodesY)
        , timestep(timestep)
        , duration(duration) {
    }
    explicit GridConfig(const std::string& configPath);

    float width;
    float height;
    int nodesX;
    int nodesY;
    float timestep;
    float duration;
};
}