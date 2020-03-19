#include <iostream>

#include <fem/Errors.h>
#include <fem/grid/Grid.h>
#include <fem/math/IntegralSolver.hpp>

using namespace fem;

int main() {
    // std::unique_ptr<grid::Grid> grid;

    // try {
    //     grid = std::make_unique<grid::Grid>(grid::GridConfig(1, 1, 5, 5));
    //     grid->build();
    // } catch (GridError& e) {
    //     std::cout << "Error while creating grid.\n";
    //     return -1;
    // }

    // grid->print();

    auto fun1 = [](float x) {
        return 5 * x * x + 3 * x + 6;
    };

    auto fun2 = [](float x, float y) {
        return 5 * x * x * y * y + 3 * x * y + 6;
    };

    
    std::cout << math::solveIntegral<float>(fun1) << '\n';
    std::cout << math::solveIntegral<float>(fun2) << '\n';

    return 0;
}
