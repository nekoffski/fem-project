#pragma once

namespace fem::cfg {

struct SimulationConfig {
    float initialTemperature;
    float simulationTime;
    float timestep;
    float ambientTemperature;
    float alfa;
    float specificHeat;
    float conductivity;
    float density;
    int nodesCount;
};
}
