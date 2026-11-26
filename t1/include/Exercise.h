#pragma once
#include "Generator.h"
#include "Matrix.h"
namespace miit::algebra {
/**
 * @brief Базовый класс заданий, выполняемых над матрицей.
 */
class Exercise {
protected:
    /** @brief Копия матрицы, над которой выполняется задание. */
    Matrix<int> matrix_;
public:
    /**
     * @brief Создаёт задание для указанной матрицы.
     * @param matrix Исходная матрица.
     */
    explicit Exercise(Matrix<int> matrix);
    /** @brief Создаёт задание и заполняет матрицу генератором. */
    explicit Exercise(Matrix<int> matrix, const Generator& generator);
    /** @brief Уничтожает объект задания. */
    virtual ~Exercise();
    /** @brief Выполняет преобразование матрицы. */
    virtual void solve() = 0;
    /**
     * @brief Возвращает текущую матрицу задания.
     * @return Копия матрицы с результатом преобразования.
     */
    Matrix<int> getMatrix() const;
};
}
