#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"
#include <gtest/gtest.h>
#include <climits>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace miit::algebra;

TEST(GeneratorTests, ZeroGeneratorFillsWithZeros)
{
    ZeroGenerator gen;
    Matrix m(2, 3);
    m.fill(gen);

    for (size_t i = 0; i < m.rowsCount(); ++i)
    {
        for (size_t j = 0; j < m.columnsCount(); ++j)
        {
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

TEST(GeneratorTests, ConstantGeneratorFillsWithConstant)
{
    ConstantGenerator gen(7);
    Matrix m(2, 2);
    m.fill(gen);

    for (size_t i = 0; i < m.rowsCount(); ++i)
    {
        for (size_t j = 0; j < m.columnsCount(); ++j)
        {
            EXPECT_EQ(m[i][j], 7);
        }
    }
}

TEST(GeneratorTests, RandomGeneratorRespectsRange)
{
    EXPECT_THROW(RandomGenerator(10, 5), std::invalid_argument);

    RandomGenerator gen(-10, 10);
    for (int i = 0; i < 50; ++i)
    {
        const int val = gen.generate();
        EXPECT_GE(val, -10);
        EXPECT_LE(val, 10);
    }
}

TEST(GeneratorTests, IStreamGeneratorReadsStream)
{
    std::istringstream iss("1 2 3 4");
    IStreamGenerator gen(iss);
    Matrix m(2, 2);
    m.fill(gen);

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTests, ThrowsOnInvalidSizeOrIndex)
{
    EXPECT_THROW(Matrix(0, 3), std::runtime_error);
    EXPECT_THROW(Matrix(3, 0), std::runtime_error);

    Matrix m(2, 2);
    EXPECT_THROW(m[5][5], std::runtime_error);
}

TEST(MatrixTests, CopyAndMoveConstructorsWork)
{
    std::istringstream iss("1 2 3 4");
    IStreamGenerator gen(iss);
    Matrix original(2, 2);
    original.fill(gen);

    Matrix copy(original);
    EXPECT_EQ(copy, original);

    Matrix moved(std::move(copy));
    EXPECT_EQ(moved, original);
}

TEST(MatrixTests, StreamOperatorsWork)
{
    std::istringstream iss("5 6 7 8");
    Matrix m(2, 2);
    iss >> m;

    Matrix expected(2, 2);
    expected[0][0] = 5;
    expected[0][1] = 6;
    expected[1][0] = 7;
    expected[1][1] = 8;

    EXPECT_EQ(m, expected);

    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), m.toString());
}


TEST(MatrixTests, ConstructsFromVectorsAndRejectsInvalidShapes)
{
    Matrix matrix(std::vector<std::vector<int>>{{1, 2}, {3, 4}});
    EXPECT_EQ(matrix.rowsCount(), 2);
    EXPECT_EQ(matrix.columnsCount(), 2);
    EXPECT_EQ(matrix[1][0], 3);
    EXPECT_THROW((Matrix(std::vector<std::vector<int>>{{1}, {2, 3}})), std::runtime_error);
    EXPECT_THROW((Matrix(std::vector<std::vector<int>>{})), std::runtime_error);
    EXPECT_THROW(matrix[-1], std::runtime_error);
}

TEST(Task1Tests, ReplacesAllZerosWithSignedMaximumMagnitude)
{
    Matrix input(std::vector<std::vector<int>>{{0, -9, 0}, {7, 0, 9}});
    Task1 task(input);
    Matrix expected(std::vector<std::vector<int>>{{-9, -9, -9}, {7, -9, 9}});
    EXPECT_EQ(task.Solve(), expected);
    EXPECT_EQ(input[0][0], 0);
    EXPECT_EQ(task.Solve(), expected);
}

TEST(Task1Tests, HandlesNoZerosAndAllZeros)
{
    Matrix noZeros(std::vector<std::vector<int>>{{1, -2}, {3, 4}});
    Task1 first(noZeros);
    EXPECT_EQ(first.Solve(), noZeros);
    Matrix allZeros(std::vector<std::vector<int>>{{0, 0}});
    Task1 second(allZeros);
    EXPECT_EQ(second.Solve(), allZeros);
}

TEST(Task2Tests, InsertsZeroAfterEveryColumnWithMaximumAbsoluteValue)
{
    Matrix input(std::vector<std::vector<int>>{{-8, 2, 8}, {1, 8, 3}});
    Task2 task(input);
    Matrix expected(std::vector<std::vector<int>>{{-8, 0, 2, 0, 8, 0}, {1, 0, 8, 0, 3, 0}});
    EXPECT_EQ(task.Solve(), expected);
    EXPECT_EQ(task.Solve(), expected);
}

TEST(Task2Tests, AllZeroMatrixInsertsAfterEveryColumn)
{
    Matrix input(std::vector<std::vector<int>>{{0, 0}, {0, 0}});
    Task2 task(input);
    Matrix expected(std::vector<std::vector<int>>{{0, 0, 0, 0}, {0, 0, 0, 0}});
    EXPECT_EQ(task.Solve(), expected);
}

TEST(TaskTests, HandlesMinimumIntWithoutAbsoluteValueOverflow)
{
    Matrix input(std::vector<std::vector<int>>{{0, INT_MIN, INT_MAX}});
    Task1 first(input);
    Matrix expectedFirst(std::vector<std::vector<int>>{{INT_MIN, INT_MIN, INT_MAX}});
    EXPECT_EQ(first.Solve(), expectedFirst);
    Task2 second(input);
    Matrix expectedSecond(std::vector<std::vector<int>>{{0, INT_MIN, 0, INT_MAX}});
    EXPECT_EQ(second.Solve(), expectedSecond);
}
