#pragma once
#include "Exercise.h"
namespace miit::algebra {
/**
 * @brief Первое преобразование матрицы из варианта задания.
 */
class Task1 final : public Exercise {
public:
    using Exercise::Exercise;
    /**
     * @brief Заменяет первый нуль в каждом столбце элементом с максимальным модулем.
     */
    void solve() override;
};
}
