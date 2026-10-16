#pragma once
#include "Generator.h"
namespace miit::algebra {
/**
 * @brief Генератор, всегда возвращающий одно и то же число.
 */
class ConstantGenerator final : public Generator {
private:
    /** @brief Значение, возвращаемое при каждом вызове generate. */
    int value_;
public:
    /**
     * @brief Создаёт генератор постоянного значения.
     * @param value Значение для генерации.
     */
    explicit ConstantGenerator(int value);
    /**
     * @brief Возвращает сохранённое значение.
     * @return Постоянное целое число.
     */
    int generate() override;
};
}
