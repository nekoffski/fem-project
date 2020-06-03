#pragma once

#include <fem/cfg/SimulationConfig.h>
#include <fem/grid/Element.h>
#include <fem/grid/Grid.h>
#include <fem/grid/Node.h>
#include <fem/math/JacobianSolver.h>
#include <fem/math/UniversalElement.h>
#include <fem/math/containers/Matrix.hpp>
#include <fem/math/containers/Vector.hpp>

#include <iostream>

namespace fem {

class Simulation {
public:
    explicit Simulation(grid::Grid& grid, cfg::SimulationConfig cfg);

    void run();

private:
    void aggregateMatrices();
    void solveEquations();
    void printMinMaxTemperature(float time);
    void updateElement(grid::Element& element, std::vector<grid::Node>& nodes);
    void resetMatrices();
    void updateTemperatureInNodes();

    void printTemperatures() {
        std::cout << "\n";
        int ff = std::sqrt(m_cfg.nodesCount);
        for (int i = 0; i < ff; ++i) {
            std::cout << m_grid.getNodes()[i + i * ff].temp << "\n";
        }
        std::cout << "\n";
    }

    grid::Grid& m_grid;
    cfg::SimulationConfig m_cfg;

    math::containers::MatrixX<float> m_C;
    math::containers::MatrixX<float> m_H;
    math::containers::VectorX<float> m_P;
    math::containers::VectorX<float> m_temperature;

    math::UniversalElement m_ue;
    math::JacobianSolver m_jacobianSolver;
};
}