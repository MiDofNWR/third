#include "ConstantGenerator.h"
namespace miit::algebra {
ConstantGenerator::ConstantGenerator(int value) : value_(value) {}
int ConstantGenerator::generate() const { return value_; }
}
