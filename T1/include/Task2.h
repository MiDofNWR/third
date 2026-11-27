#pragma once

#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Реализация второго задания (Вариант 10)
	 */
	class Task2 : public Exercise
	{
	private:
		/**
		 * @brief Матрица с результатом второго задания
		 */
		Matrix result;

	public:
		/**
		 * @brief Создать объект второго задания
		 * @param matrix Матрица, над которой будет выполняться задание
		 */
		Task2(Matrix& matrix);

		/**
		 * @brief Вставить нулевой столбец после каждого столбца с максимальным по модулю элементом
		 * @return Матрица после выполнения задания
		 */
		Matrix& Solve() override;
	};
}
