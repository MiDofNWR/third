#include "../include/Task1.h"
#include "../include/MatrixMagnitude.h"

namespace miit::algebra
{
    Task1::Task1(Matrix& matrix) : Exercise(matrix), result(matrix) {}

    Matrix& Task1::Solve()
    {
        result = OurMatrix;
        if (result.rowsCount() == 0) return result;
        const int maximum = maxMagnitudeElement(result);
        for (size_t i = 0; i < result.rowsCount(); ++i)
            for (size_t j = 0; j < result.columnsCount(); ++j)
                if (result[static_cast<int>(i)][j] == 0)
                    result[static_cast<int>(i)][j] = maximum;
        return result;
    }
}
