#pragma once

#include <memory>
#include <vector>

#include <fem/grid/Element.h>
#include <fem/grid/GridConfig.h>
#include <fem/grid/MatrixAggregator.hpp>
#include <fem/grid/Node.h>
#include <fem/math/JacobianSolver.h>
#include <fem/math/UniversalElement.h>

#include <Eigen/Dense>

namespace fem::grid {

class Grid {
public:
    explicit Grid(GridConfig cfg);
    void build();

    std::vector<Node>& getNodes() {
        return m_nodes;
    }

    std::vector<Element>& getElements() {
        return m_elements;
    }

    float getDx() {
        return m_dx;
    }

    float getDy() {
        return m_dy;
    }

    const UndefinedSizeMat& getAggregatedC() {
        return m_aggregatedC;
    }

    const UndefinedSizeMat& getAggregatedH() {
        return m_aggregatedH;
    }

    const UndefinedSizeVec& getAggregatedP() {
        return m_aggregatedP;
    }

    void solveEquations() {
        const float dt = 50.0f;

        auto Cdt = m_aggregatedC / dt;
        auto Hc = m_aggregatedH + Cdt;

        auto C2 = Cdt * m_temperature;
        auto B = C2 + m_aggregatedP;

        auto t1 = inverseMatrix(Hc) * B;
        m_temperature = t1;
    }

    void aggregate() {
        auto m = aggregateMatrices(m_elements, m_nodes.size());
        m_aggregatedC = m.C;
        m_aggregatedH = m.H;
        m_aggregatedP = m.P;
    }

    void printMinMaxTemperature(float time) {
        auto [min, max] = std::minmax_element(m_temperature.begin(), m_temperature.end());
        std::cout << "Time: " << time << " // min: " << *min << " - "
                  << "max: " << *max << "\n";
    }

    void runSimulation();

    void print() const;

private:
    UndefinedSizeVec m_temperature;

    std::vector<Node> m_nodes;
    std::vector<Element> m_elements;

    GridConfig m_gridConfig;

    float m_dx;
    float m_dy;

    int m_elementsX;
    int m_elementsY;

    UndefinedSizeMat m_aggregatedC;
    UndefinedSizeMat m_aggregatedH;
    UndefinedSizeVec m_aggregatedP;

    math::UniversalElement m_ue;
    math::JacobianSolver m_jacobianSolver;
};
}
