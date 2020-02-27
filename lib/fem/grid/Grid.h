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

private:
    std::vector<Node> m_nodes;
    std::vector<Element> m_elements;

    GridConfig m_gridConfig;
};
}