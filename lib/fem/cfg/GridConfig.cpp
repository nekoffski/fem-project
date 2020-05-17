#include <fem/cfg/GridConfig.h>

#include <json/json.h>

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

    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!Json::parseFromStream(builder, configFile, &root, &errs)) {
        throw GridError();
    }

    try {
        auto& grid = root["grid"];

        width = grid["width"].asDouble();
        height = grid["height"].asDouble();
        nodesX = grid["nodes_x"].asInt();
        nodesY = grid["nodes_y"].asInt();
    } catch (Json::Exception& e) {
        throw GridError();
    }
}
}