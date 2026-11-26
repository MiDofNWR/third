#include "RandomGenerator.h"
#include <stdexcept>
namespace miit::algebra {
RandomGenerator::RandomGenerator(int minimum, int maximum)
    : engine_(std::random_device{}()), distribution_(minimum, maximum) {
    if (minimum > maximum) throw std::invalid_argument("Минимальное значение не должно превышать максимальное");
}
int RandomGenerator::generate() const { return distribution_(engine_); }
}
