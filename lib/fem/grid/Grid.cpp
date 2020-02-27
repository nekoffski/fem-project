#include <fem/grid/Grid.h>

namespace fem::grid {

Grid::Grid(GridConfig cfg)
    : m_gridConfig(std::move(cfg)) {
}
}