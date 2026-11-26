#include "Task2.h"
#include <algorithm>
#include <vector>
namespace miit::algebra {
namespace {
long long magnitude(int value) {
    return value < 0 ? -static_cast<long long>(value) : static_cast<long long>(value);
}

template<typename T>
T valueWithMaximumMagnitude(const Matrix<T>& matrix) {
    T result = matrix[0][0];
    for (std::size_t r = 0; r < matrix.rows(); ++r) {
        for (const auto& value : matrix[r]) if (magnitude(value) > magnitude(result)) result = value;
    }
    return result;
}
}
void Task2::solve() {
    if (matrix_.empty()) return;
    const long long maximum = magnitude(valueWithMaximumMagnitude(matrix_));
    std::vector<Matrix<int>::value_type> zeros(matrix_.rows(), Matrix<int>::value_type{});
    const std::size_t originalColumns = matrix_.columns();
    for (std::size_t c = originalColumns; c-- > 0U;) {
        bool contains = false;
        for (std::size_t r = 0; r < matrix_.rows(); ++r) contains = contains || magnitude(matrix_[r][c]) == maximum;
        if (contains) matrix_.insertColumn(c + 1U, zeros);
    }
}
}
