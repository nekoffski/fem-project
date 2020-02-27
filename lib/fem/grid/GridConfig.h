#pragma once

#include <string>

namespace fem::grid {

struct GridConfig {
    explicit GridConfig(const std::string& configPath);

    float width;
    float height;
    int nodesX;
    int nodesY;
};
}