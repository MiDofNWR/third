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
    /** @brief Необязательный генератор для заполнения матрицы. */
    Generator* generator_;
public:
    /**
     * @brief Создаёт задание для указанной матрицы.
     * @param matrix Исходная матрица.
     * @param generator Генератор для заполнения матрицы или nullptr.
     */
    explicit Exercise(Matrix<int> matrix, Generator* generator = nullptr);
    /** @brief Уничтожает объект задания. */
    virtual ~Exercise();
    /**
     * @brief Заполняет матрицу значениями выбранного генератора.
     * @throw std::logic_error Если генератор не задан.
     */
    void fill();
    /** @brief Выполняет преобразование матрицы. */
    virtual void solve() = 0;
    /**
     * @brief Возвращает текущую матрицу задания.
     * @return Копия матрицы с результатом преобразования.
     */
    Matrix<int> getMatrix() const;
};
}
