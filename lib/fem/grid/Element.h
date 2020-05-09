#pragma once

#include <vector>

#include <fem/grid/Node.h>
#include <fem/math/Utils.hpp>

namespace fem::grid {

struct Element {
    explicit Element(std::vector<int> nodesIds)
        : nodesIds(std::move(nodesIds)) {
    }

    std::vector<int> nodesIds;
    std::vector<math::Boundary> boundariesWithBC;
    math::Mat4 H;
    math::Mat4 C;
    math::Mat4 P;
};

inline void determineElementBoundaryConditions(Element& element, const std::vector<Node>& nodes) {
    const auto& ids = element.nodesIds;
    std::vector<math::Boundary> boundaries;

    if (nodes[ids[0]].boundaryCondition && nodes[ids[1]].boundaryCondition)
        boundaries.push_back(math::Boundary::BOTTOM);
    if (nodes[ids[1]].boundaryCondition && nodes[ids[2]].boundaryCondition)
        boundaries.push_back(math::Boundary::RIGHT);
    if (nodes[ids[2]].boundaryCondition && nodes[ids[3]].boundaryCondition)
        boundaries.push_back(math::Boundary::TOP);
    if (nodes[ids[3]].boundaryCondition && nodes[ids[0]].boundaryCondition)
        boundaries.push_back(math::Boundary::LEFT);

    element.boundariesWithBC = std::move(boundaries);
}
}
