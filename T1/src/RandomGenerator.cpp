#include "../include/RandomGenerator.h"
#include <stdexcept>

namespace miit::algebra
{
	RandomGenerator::RandomGenerator(const int min, const int max) : distribution(min, min > max ? min : max), generator(std::random_device{}())
	{
		if (min > max)
		{
			throw std::invalid_argument("Минимальная граница больше максимальной.");
		}
	}

	int RandomGenerator::generate() const
	{
		return this->distribution(this->generator);
	}
}
