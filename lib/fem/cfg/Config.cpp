#include <fem/cfg/Config.h>

#include <fstream>
#include <sstream>
#include <vector>

#include <json/json.h>

#include <fem/Errors.h>

#ifndef CONFIG_DIR
#define CONFIG_DIR "./cfg"
#endif

namespace fem::cfg {

Config::Config(std::string path) {
    std::ifstream configFile(std::string(CONFIG_DIR) + path);

    if (!configFile.is_open()) {
        throw ConfigError();
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!Json::parseFromStream(builder, configFile, &root, &errs))
        throw ConfigError();

    try {
        auto& grid = root["grid"];

        m_gridConfig = GridConfig{
            grid["width"].asFloat(),
            grid["height"].asFloat(),
            grid["nodes_x"].asInt(),
            grid["nodes_y"].asInt()
        };

        auto& simulation = root["simulation"];

        m_simulationConfig = SimulationConfig{
            simulation["initial_temperature"].asFloat(),
            simulation["simulation_time"].asFloat(),
            simulation["timestep"].asFloat(),
            simulation["ambient_temperature"].asFloat(),
            simulation["alfa"].asFloat(),
            simulation["specific_heat"].asFloat(),
            simulation["conductivity"].asFloat(),
            simulation["density"].asFloat(),
            m_gridConfig.nodesX * m_gridConfig.nodesY
        };
    } catch (Json::Exception& e) {
        throw ConfigError();
    }
}
}