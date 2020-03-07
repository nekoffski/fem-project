#include <fem/grid/Grid.h>
#include <fem/grid/GridConfig.h>

#include <gtest/gtest.h>

using namespace fem::grid;

class GridTests : public testing::Test {
protected:
    void SetUp() {
        m_gridConfig = GridConfig{ m_width, m_height, m_nodesX, m_nodesY };
        m_grid = std::make_unique<Grid>(m_gridConfig);
        m_grid->build();
    }

    GridConfig m_gridConfig;
    std::unique_ptr<Grid> m_grid;

    float m_width{ 200.0f };
    float m_height{ 100.0f };
    int m_nodesX{ 5 };
    int m_nodesY{ 10 };
};

TEST_F(GridTests, test_givenGridConfig_whenCreatingGrid_expectCorrectNodeCount) {
    const auto& nodes = m_grid->getNodes();

    EXPECT_EQ(nodes.size(), m_nodesX * m_nodesY);
}

TEST_F(GridTests, test_givenGridConfig_whenCreatingGrid_expectCorrectElementsCount) {
    const auto& elements = m_grid->getElements();
    auto elementsCount = (m_nodesX - 1) * (m_nodesY - 1);

    EXPECT_EQ(elements.size(), elementsCount);
}

TEST_F(GridTests, test_givenGridConfig_whenCreatingGrid_expectCorrectDx) {
    auto dx = m_width / (m_nodesX - 1);

    EXPECT_EQ(m_grid->getDx(), dx);
}

TEST_F(GridTests, test_givenGridConfig_whenCreatingGrid_expectCorrectDy) {
    auto dy = m_height / (m_nodesY - 1);

    EXPECT_EQ(m_grid->getDy(), dy);
}

TEST_F(GridTests, test_givenGridConfig_whenCreatingGrid_expectCorrectCoordinatesInNodes) {
    const auto& nodes = m_grid->getNodes();
    auto begin = std::pair<float, float>(0.0f, 0.0f);
    auto end = std::pair<float, float>(m_width, m_height);

    EXPECT_EQ(nodes[0].coords, begin);
    EXPECT_EQ(nodes.back().coords, end);
}

struct TestParam {
    int id;
    std::array<int, 4> nodes;
};

class GridParamTests : public GridTests, public testing::WithParamInterface<TestParam> {
};

auto testCase1 = TestParam{ 0, { 0, 1, 3, 4 } };
auto testCase2 = TestParam{ 1, { 1, 2, 4, 5 } };
auto testCase3 = TestParam{ 3, { 3, 4, 6, 7 } };
auto testCase4 = TestParam{ 11, { 12, 13, 15, 16 } };
auto testCase5 = TestParam{ 22, { 24, 25, 27, 28 } };

TEST_P(GridParamTests, test_givenGrid_expectCorrectNodesInElement) {
    auto p = GetParam();
    const auto& element = m_grid->getElements().at(p.id);

    auto& nodes = element.nodesIds;
    for (auto node : p.nodes) {
        if (auto it = std::find(nodes.begin(), nodes.end(), node); it == element.nodesIds.end()) {
            FAIL();
        }
    }
}

INSTANTIATE_TEST_CASE_P(_, GridParamTests, ::testing::Values(testCase1, testCase2, testCase3, testCase4, testCase5));
