#include <fem/grid/Grid.h>

#include <iostream>

namespace fem::grid {

Grid::Grid(GridConfig cfg)
    : m_gridConfig(std::move(cfg)) {
}

void Grid::build() {
    m_elementsX = m_gridConfig.nodesX - 1;
    m_elementsY = m_gridConfig.nodesY - 1;
    m_dx = m_gridConfig.width / m_elementsX;
    m_dy = m_gridConfig.height / m_elementsY;

    for (float x = 0.0f; x <= m_gridConfig.width; x += m_dx) {
        for (float y = 0.0f; y <= m_gridConfig.height; y += m_dy) {
            m_nodes.push_back(Node{ { x, y } });
        }
    }

    int bias = 0;
    for (int i = 0; i < m_elementsX * m_elementsY; ++i) {
        int biasedI = i + bias;
        m_elements.push_back(Element{ { biasedI, biasedI + 1, biasedI + 3, biasedI + 4 } });

        if ((i + 1) % m_elementsY == 0) {
            ++bias;
        }
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
