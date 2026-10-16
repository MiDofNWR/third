#include "Task1.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace miit::algebra {
namespace {
long long magnitude(int value) {
    return value < 0 ? -static_cast<long long>(value) : static_cast<long long>(value);
}

int valueWithMaximumMagnitude(const Matrix<int>& matrix) {
    int result = matrix[0][0];
    for (std::size_t r = 0; r < matrix.rows(); ++r) {
        for (int value : matrix[r]) if (magnitude(value) > magnitude(result)) result = value;
    }
    return result;
}
}
void Task1::solve() {
    if (matrix_.empty()) return;
    const int maximum = valueWithMaximumMagnitude(matrix_);
    for (std::size_t c = 0; c < matrix_.columns(); ++c) {
        for (std::size_t r = 0; r < matrix_.rows(); ++r) if (matrix_[r][c] == 0) { matrix_[r][c] = maximum; break; }
    }
}
}
