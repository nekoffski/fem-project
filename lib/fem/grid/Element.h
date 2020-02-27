#pragma

#include <vector>

#include <fem/grid/Node.h>

namespace fem::grid {

struct Element {
    std::vector<int> nodesIds;
};
}