

#include <fem/grid/Grid.h>
#include <fem/math/MatrixSolver.hpp>

#include <iostream>

constexpr float DELTA = 0.001f;

static inline bool floatCmp(float x, float y) {
    return std::abs(x - y) < DELTA;
}

namespace fem::grid {

Grid::Grid(cfg::GridConfig cfg)
    : m_gridConfig(std::move(cfg)) {
}

void Grid::build() {
    m_elementsX = m_gridConfig.nodesX - 1;
    m_elementsY = m_gridConfig.nodesY - 1;
    m_dx = m_gridConfig.width / m_elementsX;
    m_dy = m_gridConfig.height / m_elementsY;

    auto isBoundary = [this](float x, float y) -> bool {
        return floatCmp(x, 0.0f) || floatCmp(y, 0.0f) || floatCmp(x, m_gridConfig.width) || floatCmp(y, m_gridConfig.height);
    };

    int i = 0;
    for (float x = 0.0f; x <= m_gridConfig.width + DELTA; x += m_dx)
        for (float y = 0.0f; y <= m_gridConfig.height + DELTA; y += m_dy)
            m_nodes.push_back(Node{ { x, y }, isBoundary(x, y) });

    int wbias = m_elementsY - 2;
    int bias = 0;

    for (int i = 0; i < m_elementsX * m_elementsY; ++i) {
        int biasedI = i + bias;

        auto element = Element{ {
            biasedI,
            biasedI + 3 + wbias,
            biasedI + 4 + wbias,
            biasedI + 1,
        } };

        determineElementBoundaryConditions(element, m_nodes);
        m_elements.push_back(std::move(element));

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
