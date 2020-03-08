#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>

using namespace fem;

int main() {
    std::unique_ptr<grid::Grid> grid;

    try {
        grid = std::make_unique<grid::Grid>(grid::GridConfig("cfg.json"));
        grid->build();
    } catch (GridError& e) {
        std::cout << "Error while creating grid.\n";
        return -1;
    }

    return 0;
}
