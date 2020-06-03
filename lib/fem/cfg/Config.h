#pragma once

#include <string>

#include <fem/cfg/GridConfig.h>
#include <fem/cfg/SimulationConfig.h>

namespace fem::cfg {

class Config {
public:
    explicit Config(std::string);

    operator GridConfig() const {
        return m_gridConfig;
    }

    operator SimulationConfig() const {
        return m_simulationConfig;
    }

private:
    GridConfig m_gridConfig;
    SimulationConfig m_simulationConfig;
};
}
