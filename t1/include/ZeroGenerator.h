#pragma once
#include "Generator.h"
namespace miit::algebra {
/**
 * @brief Генератор нулевых значений.
 */
class ZeroGenerator final : public Generator {
public:
    /**
     * @brief Возвращает ноль.
     * @return Нулевое значение.
     */
    int generate() override;
};
}
