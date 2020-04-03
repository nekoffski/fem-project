#include <fem/math/IntegralSolver.hpp>

#include <gtest/gtest.h>

using namespace fem::math;

class IntergralSolverTests : public testing::Test {
protected:
    static constexpr float DELTA = 0.1f;
};


struct IntegralSolver1DTestCase {
    std::function<float(float)> function;
    float result;
};

struct IntegralSolver2DTestCase {
    std::function<float(float, float)> function;
    float result;
};


class IntegralSolver1DTests : public IntergralSolverTests, public testing::WithParamInterface<IntegralSolver1DTestCase> {
};

class IntegralSolver2DTests : public IntergralSolverTests, public testing::WithParamInterface<IntegralSolver2DTestCase> {
};


TEST_P(IntegralSolver1DTests, test_givenFunction_whenIntegrating_expectCorrectResult) {
    auto p = GetParam();
    auto result = solveIntegral(p.function);

    EXPECT_TRUE(std::fabs(result - p.result) < DELTA);
}

TEST_P(IntegralSolver2DTests, test_givenFunction_whenIntegrating_expectCorrectResult) {
    auto p = GetParam();
    auto result = solveIntegral(p.function);

    EXPECT_TRUE(std::fabs(result - p.result) < DELTA);
}

// test cases

static IntegralSolver1DTestCase testCases1D[] {
    [](float x) { return x + 1; }, 2.0f
};

static IntegralSolver2DTestCase testCases2D[] {
    [](float x, float y) { return x + y; }, 0.0f
};

INSTANTIATE_TEST_CASE_P(_, IntegralSolver1DTests, ::testing::ValuesIn(testCases1D));
INSTANTIATE_TEST_CASE_P(_, IntegralSolver2DTests, ::testing::ValuesIn(testCases2D));
