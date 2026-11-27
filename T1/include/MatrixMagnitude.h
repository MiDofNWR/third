#pragma once

#include "Matrix.h"
#include <cstdint>

namespace miit::algebra
{
    // Расширение до int64_t позволяет корректно обработать INT_MIN.
    inline std::int64_t magnitude(int value)
    {
        const std::int64_t wide = value;
        return wide < 0 ? -wide : wide;
    }

    // При равенстве модулей выбирается первый элемент при обходе по строкам.
    inline int maxMagnitudeElement(const Matrix& matrix)
    {
        int result = matrix[0][0];
        for (size_t i = 0; i < matrix.rowsCount(); ++i)
            for (size_t j = 0; j < matrix.columnsCount(); ++j)
                if (magnitude(matrix[static_cast<int>(i)][j]) > magnitude(result))
                    result = matrix[static_cast<int>(i)][j];
        return result;
    }
}
