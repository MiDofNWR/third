#pragma once

#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Реализация первого задания (Вариант 10)
	 */
	class Task1 : public Exercise
	{
	private:
		/**
		 * @brief Матрица с результатом первого задания
		 */
		Matrix result;

	public:
		/**
		 * @brief Создать объект первого задания
		 * @param matrix Матрица, над которой будет выполняться задание
		 */
		Task1(Matrix& matrix);

		/**
		 * @brief Заменить нулевые элементы максимальным по модулю элементом матрицы
		 * @return Матрица после выполнения задания
		 */
		Matrix& Solve() override;
	};
}
