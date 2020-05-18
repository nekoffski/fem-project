#pragma once

#include <fem/Timer.hpp>
#include <fem/grid/Element.h>
#include <fem/grid/Grid.h>
#include <fem/grid/Node.h>
#include <fem/math/JacobianSolver.h>
#include <fem/math/MatrixSolver.hpp>
#include <fem/math/UniversalElement.h>
#include <fem/math/containers/Matrix.hpp>
#include <fem/math/containers/Vector.hpp>

namespace fem {

class Simulation {
public:
    explicit Simulation(grid::Grid& grid);

    void run();
    void aggregateMatrices();
    void solveEquations();
    void printMinMaxTemperature(float time);
    void updateElement(grid::Element& element, std::vector<grid::Node>& nodes);
    void resetMatrices();

private:
    grid::Grid& m_grid;

    math::containers::MatrixX<float> m_C;
    math::containers::MatrixX<float> m_H;
    math::containers::VectorX<float> m_P;
    math::containers::VectorX<float> m_temperature;

    math::UniversalElement m_ue;
    math::JacobianSolver m_jacobianSolver;
};
}