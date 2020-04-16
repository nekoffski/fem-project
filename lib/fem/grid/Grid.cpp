#include <fem/grid/Grid.h>
#include <fem/math/MatrixSolver.hpp>

#include <iostream>

constexpr float DELTA = 0.001f;

namespace fem::grid {

Grid::Grid(GridConfig cfg)
    : m_gridConfig(std::move(cfg))
    , m_ue()
    , m_jacobianSolver(m_ue) {
}

void Grid::runSimulation() {
    for (auto& element : m_elements) {
        // auto& element = m_elements[0];
        std::vector<math::Point> points;
        for (const auto& nodeId : element.nodesIds) {
            auto& node = m_nodes[nodeId];
            points.emplace_back(math::Point{
                node.coords.first, node.coords.second });
        }
        auto [dx, dy, jacobians] = m_jacobianSolver.calculateDerivatives(points);
        element.H = math::calculateHMatrix(dx, dy, jacobians);
        element.C = math::calculateCMatrix(m_ue.shapeFunctions, jacobians);
    }
    aggregate();
}

void Grid::build() {
    m_elementsX = m_gridConfig.nodesX - 1;
    m_elementsY = m_gridConfig.nodesY - 1;
    m_dx = m_gridConfig.width / m_elementsX;
    m_dy = m_gridConfig.height / m_elementsY;

    int i = 0;
    for (float x = 0.0f; x <= m_gridConfig.width + DELTA; x += m_dx) {
        for (float y = 0.0f; y <= m_gridConfig.height + DELTA; y += m_dy) {
            m_nodes.push_back(Node{ { x, y } });
        }
    }

    int wbias = m_elementsY - 2;
    int bias = 0;
    for (int i = 0; i < m_elementsX * m_elementsY; ++i) {
        int biasedI = i + bias;
        m_elements.push_back(Element{ {
            biasedI,
            biasedI + 3 + wbias,
            biasedI + 4 + wbias,
            biasedI + 1,
        } });

        if ((i + 1) % m_elementsY == 0)
            ++bias;
    }
}

void Grid::print() const {
    for (unsigned i = 0; i < m_elementsX + 1; ++i) {
        for (unsigned j = 0; j < m_elementsY + 1; ++j) {
            auto& c = m_nodes[i * (m_elementsX + 1) + j].coords;
            std::cout << c.first << '-' << c.second << ' ';
        }
        std::cout << '\n';
    }
}
}
