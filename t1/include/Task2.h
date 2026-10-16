#pragma once
#include "Exercise.h"
namespace miit::algebra {
/**
 * @brief Второе преобразование матрицы из варианта задания.
 */
class Task2 final : public Exercise {
public:
    using Exercise::Exercise;
    /**
     * @brief Вставляет нулевой столбец после каждого столбца с максимальным по модулю элементом.
     */
    void solve() override;
};
}
