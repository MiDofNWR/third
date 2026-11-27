#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
	/**
	 * @brief Базовый класс для заданий, выполняемых над матрицей
	 */
	class Exercise
	{
	public:
		/**
		 * @brief Матрица, над которой выполняются задания
		 */
		Matrix& OurMatrix;

		/**
		 * @brief Создать объект задания для указанной матрицы
		 * @param matrix Матрица, над которой будет выполняться задание
		 */
		Exercise(Matrix& matrix);

		/**
		 * @brief Уничтожить объект задания
		 */
		virtual ~Exercise() = default;

		/**
		 * @brief Выполнить задание
		 * @return Матрица с результатом задания
		 */
		virtual Matrix& Solve() = 0;
	};
}
