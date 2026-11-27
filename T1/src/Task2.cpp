#include "../include/Task2.h"
#include "../include/MatrixMagnitude.h"
#include <vector>

namespace miit::algebra
{
    Task2::Task2(Matrix& matrix) : Exercise(matrix), result(matrix) {}

    Matrix& Task2::Solve()
    {
        result = OurMatrix;
        const size_t rows = result.rowsCount();
        const size_t cols = result.columnsCount();
        if (rows == 0) return result;
        const auto maximum = magnitude(maxMagnitudeElement(result));
        std::vector<bool> insertAfter(cols, false);
        for (size_t j = 0; j < cols; ++j)
            for (size_t i = 0; i < rows; ++i)
                if (magnitude(result[static_cast<int>(i)][j]) == maximum)
                {
                    insertAfter[j] = true;
                    break;
                }

        std::vector<std::vector<int>> expanded(rows);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
            {
                expanded[i].push_back(result[static_cast<int>(i)][j]);
                if (insertAfter[j]) expanded[i].push_back(0);
            }
        result = Matrix(std::move(expanded));
        return result;
    }
}
