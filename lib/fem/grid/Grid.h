#pragma once

#include <memory>
#include <vector>

#include <fem/grid/Element.h>
#include <fem/grid/GridConfig.h>
#include <fem/grid/Node.h>

namespace fem::grid {

class Grid {
public:
    explicit Grid(GridConfig cfg);
    void build();

    const std::vector<Node>& getNodes() const {
        return m_nodes;
    }

    const std::vector<Element>& getElements() const {
        return m_elements;
    }

    float getDx() {
        return m_dx;
    }

    float getDy() {
        return m_dy;
    }

private:
    std::vector<Node> m_nodes;
    std::vector<Element> m_elements;

    GridConfig m_gridConfig;

    float m_dx;
    float m_dy;

    int m_elementsX;
    int m_elementsY;
};
}
