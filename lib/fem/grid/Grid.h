#pragma once

#include <memory>
#include <vector>

#include <fem/grid/Element.h>
#include <fem/grid/GridConfig.h>
#include <fem/grid/MatrixAggregator.hpp>
#include <fem/grid/Node.h>
#include <fem/math/JacobianSolver.h>
#include <fem/math/UniversalElement.h>

#include <Eigen/Dense>

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

    const UndefinedSizeMat& getAggregatedC() {
        return m_aggregatedC;
    }

    const UndefinedSizeMat& getAggregatedH() {
        return m_aggregatedH;
    }

    const UndefinedSizeVec& getAggregatedP() {
        return m_aggregatedP;
    }

    void solveEquations() {
        Eigen::Matrix<float, 16, 16> A;

        const float dt = 50.0f;

        auto C = m_aggregatedC;
        auto P = m_aggregatedP;
        auto H = m_aggregatedH;

        grid::UndefinedSizeVec t0(16, 100.0f);

        auto Cdt = C / dt;
        auto Hc = H + Cdt;

        std::cout << Hc;

        auto C2 = Cdt * t0;
        auto B = C2 + P;

        std::cout << "\n\n"
                  << B;

        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                A(i, j) = Hc[i][j];
        A = A.inverse();

        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                Hc[i][j] = A(i, j);

        std::cout << "\n\n"
                  << Hc;
        auto t1 = Hc * B;
        std::cout << "\n\n"
                  << t1;

        t0 = t1;
    }

    void aggregate() {
        auto m = aggregateMatrices(m_elements, m_nodes.size());
        m_aggregatedC = m.C;
        m_aggregatedH = m.H;
        m_aggregatedP = m.P;
    }

    void runSimulation();

    void print() const;

private:
    std::vector<Node> m_nodes;
    std::vector<Element> m_elements;

    GridConfig m_gridConfig;

    float m_dx;
    float m_dy;

    int m_elementsX;
    int m_elementsY;

    UndefinedSizeMat m_aggregatedC;
    UndefinedSizeMat m_aggregatedH;
    UndefinedSizeVec m_aggregatedP;

    math::UniversalElement m_ue;
    math::JacobianSolver m_jacobianSolver;
};
}
