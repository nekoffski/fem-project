#pragma once

#include <memory>
#include <vector>

#include <fem/grid/Element.h>
#include <fem/grid/GridConfig.h>
#include <fem/grid/MatrixAggregator.hpp>
#include <fem/grid/Node.h>
#include <fem/math/JacobianSolver.h>
#include <fem/math/UniversalElement.h>

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

    void aggregate() {
        auto m = aggregateMatrices(m_elements, m_nodes.size());
        m_aggregatedC = m.C;
        m_aggregatedH = m.H;
    }

    void runSimulation();

    void print() const;

private:
    std::vector<Node> m_nodes;
    std::vector<Element> m_elements;

    GridConfig m_gridConfig;

    float m_dx;
    float m_dy;

    int m_elementsX;
    int m_elementsY;

    UndefinedSizeMat m_aggregatedC;
    UndefinedSizeMat m_aggregatedH;

    math::UniversalElement m_ue;
    math::JacobianSolver m_jacobianSolver;
};
}
