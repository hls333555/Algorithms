#pragma once

#include <iostream>
#include <sstream>

namespace HAlgorithm {

	template <typename T>
	class Matrix
	{
	public:
		Matrix(int rows = 0, int cols = 0);
		Matrix(const Matrix<T>& other);
		~Matrix() { delete[] m_Element; }

		int GetRows() const { return m_Rows; }
		int GetColumns() const { return m_Cols; }
		int Size() const { return m_Rows * m_Cols; }

		T& operator()(int row, int col) const;
		Matrix<T>& operator=(const Matrix<T>& other);
		Matrix<T> operator+(const Matrix<T>& other) const;
		Matrix<T> operator-(const Matrix<T>& other) const;
		Matrix<T> operator*(const Matrix<T>& other) const;

		bool IsValidIndex(int row, int col) const { return row >= 1 && row <= m_Rows && col >= 1 && col <= m_Cols; }
		void Output(std::ostream& out) const;

	private:
		int m_Rows, m_Cols;
		/** ���������򽲾���ӳ�䵽һά������ */
		T* m_Element;
	};

	template <typename T>
	Matrix<T>::Matrix(int rows, int cols)
	{
		if (rows < 0 || cols < 0)
		{
			throw std::invalid_argument("Rows and columns must be >= 0!");
		}
		if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
		{
			throw std::invalid_argument("Either both or neither rows and columns should be 0!");
		}
		m_Rows = rows;
		m_Cols = cols;
		m_Element = new T[rows * cols];
	}

	template<typename T>
	Matrix<T>::Matrix(const Matrix<T>& other)
	{
		m_Rows = other.m_Rows;
		m_Cols = other.m_Cols;
		m_Element = new T[Size()];
		std::copy(other.m_Element, other.m_Element + Size(), m_Element);
	}

	template<typename T>
	T& Matrix<T>::operator()(int row, int col) const
	{
		if (!IsValidIndex(row, col))
		{
			throw std::invalid_argument("Row or col out of range!");
		}

		return m_Element[(row - 1) * m_Cols + (col - 1)];
	}

	template<typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
	{
		// �����Լ������Լ�
		if (&other != this)
		{
			delete[] m_Element;
			m_Rows = other.m_Rows;
			m_Cols = other.m_Cols;
			m_Element = new T[Size()];
			std::copy(other.m_Element, other.m_Element + Size(), m_Element);
		}
		return *this;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
	{
		if (m_Rows != other.m_Rows || m_Cols != other.m_Cols)
		{
			throw std::invalid_argument("Rows or cols mismatch!");
		}

		Matrix<T> result(m_Rows, m_Cols);
		for (int i = 0; i < Size(); ++i)
		{
			result.m_Element[i] = m_Element[i] + other.m_Element[i];
		}
		return result;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
	{
		if (m_Rows != other.m_Rows || m_Cols != other.m_Cols)
		{
			throw std::invalid_argument("Rows or cols mismatch!");
		}

		Matrix<T> result(m_Rows, m_Cols);
		for (int i = 0; i < Size(); ++i)
		{
			result.m_Element[i] = m_Element[i] - other.m_Element[i];
		}
		return result;
	}

	template<typename T>
	Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
	{
		if (m_Cols != other.m_Rows)
		{
			throw std::invalid_argument("Columns and rows mismatch!");
		}

		Matrix<T> result(m_Rows, other.m_Cols);
		int sum = 0, m1 = 0, m2 = 0;
		// �����������ÿi+1��
		for (int i = 0; i < m_Rows; ++i)
		{
			// �����������(i+1, j+1)
			for (int j = 0; j < other.m_Cols; ++j)
			{
				for (int k = 0; k < m_Cols; ++k)
				{
					sum += m_Element[m1] * other.m_Element[m2];
					// *this�е�i+1�е���һ��
					m1++;
					// other�е�j+1�е���һ��
					m2 += other.m_Cols;
				}
				result.m_Element[i * other.m_Cols + j] = sum;
				sum = 0;
				// ���е�������һ�����¿�ʼ
				m1 -= m_Cols;
				m2 = j + 1;
			}
			// ����һ�к͵�һ�����¿�ʼ
			m1 = (i + 1) * m_Cols;
			m2 = 0;
		}
		return result;
	}

	template<typename T>
	void Matrix<T>::Output(std::ostream& out) const
	{
		out.setf(std::ios::left);
		for (int i = 1; i <= m_Rows; ++i)
		{
			for (int j = 1; j <= m_Cols; ++j)
			{
				out.width(5);
				out << (*this)(i, j) << " ";
			}
			out << std::endl;
		}
		//out << std::endl;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Matrix<T>& x)
	{
		x.Output(out);
		return out;
	}

}
