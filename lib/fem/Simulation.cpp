#include <fem/Simulation.h>

#include <fem/Timer.hpp>
#include <fem/math/MatrixSolver.hpp>

namespace fem {

Simulation::Simulation(grid::Grid& grid, cfg::SimulationConfig cfg)
    : m_grid(grid)
    , m_cfg(std::move(cfg))
    , m_ue()
    , m_jacobianSolver(m_ue)
    , m_temperature(m_cfg.nodesCount, m_cfg.initialTemperature)
    , m_C(m_cfg.nodesCount)
    , m_H(m_cfg.nodesCount)
    , m_P(m_cfg.nodesCount) {
}

void Simulation::run() {
    Timer timer("Total simulation time: ");

    float timestep = m_cfg.timestep;
    auto& nodes = m_grid.getNodes();
    auto& elements = m_grid.getElements();

    for (auto& element : elements)
        updateElement(element, nodes);
    aggregateMatrices();

    for (float t = 0.0f; t < m_cfg.simulationTime; t += m_cfg.timestep) {
        solveEquations();
        printMinMaxTemperature(t + m_cfg.timestep);
    }
}

void Simulation::updateElement(grid::Element& element, std::vector<grid::Node>& nodes) {
    std::vector<math::Point> points;
    for (const auto& nodeId : element.nodesIds) {
        auto& node = nodes[nodeId];
        points.emplace_back(math::Point{
            node.coords.first, node.coords.second });
    }
    auto [dx, dy, jacobians] = m_jacobianSolver.calculateDerivatives(points);

    element.C = math::calculateCMatrix(m_ue.shapeFunctions, jacobians, m_cfg.specificHeat, m_cfg.density);

    auto boundaryJacobian = m_jacobianSolver.calculateBoundaryJacobian(points);

    auto H = math::calculateHMatrix(dx, dy, jacobians, m_cfg.conductivity);
    auto HBC = math::calculateHBCMatrix(element.boundariesWithBC,
        m_ue.boundaryShapeFunctions, boundaryJacobian, m_cfg.alfa);
    element.H = std::move(H) + std::move(HBC);

    auto P = math::calculatePVector(element.boundariesWithBC, m_ue.boundaryShapeFunctions,
        boundaryJacobian, m_cfg.alfa, m_cfg.ambientTemperature);
    element.P = std::move(P);
}

void Simulation::solveEquations() {
    const float dt = m_cfg.timestep;

    auto Cdt = m_C / dt;
    auto Hc = m_H + Cdt;
    auto C2 = Cdt * m_temperature;
    auto B = C2 + m_P;

    m_temperature = Hc.solve(std::move(B));
}

void Simulation::aggregateMatrices() {
    resetMatrices();
    for (const auto& element : m_grid.getElements()) {
        const auto& nodes = element.nodesIds;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m_H.data[nodes[i]][nodes[j]] += element.H[i][j];
                m_C.data[nodes[i]][nodes[j]] += element.C[i][j];
            }
            m_P.data[nodes[i]] += element.P[i];
        }
    }
}

void Simulation::resetMatrices() {
    m_H.reset();
    m_C.reset();
    m_P.reset();
}

void Simulation::printMinMaxTemperature(float time) {
    auto [min, max] = std::minmax_element(m_temperature.begin(), m_temperature.end());
    std::cout << "Time: " << time << " // min: " << *min << " - "
              << "max: " << *max << "\n";
}
}