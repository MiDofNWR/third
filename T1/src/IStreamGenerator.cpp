#include "../include/IStreamGenerator.h"
#include <stdexcept>

namespace miit::algebra
{
	IStreamGenerator::IStreamGenerator(std::istream& in) : in(in)
	{
	}

	int IStreamGenerator::generate() const
	{
		int value = 0;
		if (!(this->in >> value))
            throw std::runtime_error("Ошибка ввода элементов матрицы из потока.");
		return value;
	}
}
