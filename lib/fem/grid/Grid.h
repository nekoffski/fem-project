#pragma once

#include <memory>
#include <vector>

#include <fem/cfg/GridConfig.h>
#include <fem/grid/Element.h>
#include <fem/grid/Node.h>

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

    void print() const;

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
