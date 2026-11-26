#include "Exercise.h"
#include <utility>
namespace miit::algebra {
Exercise::Exercise(Matrix<int> matrix) : matrix_(std::move(matrix)) {}
Exercise::Exercise(Matrix<int> matrix, const Generator& generator) : matrix_(std::move(matrix)) { matrix_.fill(generator); }
Exercise::~Exercise() = default;
Matrix<int> Exercise::getMatrix() const { return matrix_; }
}
