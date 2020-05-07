#pragma once

#include <vector>

#include <fem/grid/Node.h>
#include <fem/math/Utils.hpp>

namespace fem::grid {

struct Element {
    std::vector<int> nodesIds;
    math::Mat4 H;
    math::Mat4 C;
    math::Mat4 P;
};
}
