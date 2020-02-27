#include <fem/grid/GridConfig.h>

#include <fstream>
#include <sstream>
#include <vector>

#include <fem/Errors.h>

constexpr int CONFIG_LINES = 4;

namespace fem::grid {

GridConfig::GridConfig(const std::string& configPath) {
    std::ifstream configFile(std::string(CONFIG_DIR) + configPath);

    if (!configFile.is_open()) {
        throw GridError();
    }

    std::vector<std::string> lines;
    std::string tmp;

    while (std::getline(configFile, tmp)) {
        lines.push_back(tmp);
    }

    if (lines.size() != CONFIG_LINES) {
        throw GridError();
    }

    width = std::atof(lines[0].c_str());
    height = std::atof(lines[1].c_str());
    nodesX = std::atoi(lines[2].c_str());
    nodesY = std::atoi(lines[3].c_str());
}
}