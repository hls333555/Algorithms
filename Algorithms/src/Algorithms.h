#pragma once

#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>

#include "Stack.h"

namespace HAlgorithm {

	/** 交换两元素 */
	template <typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	/** 累加数组元素 */
	template <typename T>
	T Sum(T a[], int n)
	{
		return std::accumulate(a, a + n, 0);
	}

	/** 累乘数组元素 */
	template <typename T>
	T Product(T a[], int n)
	{
		return std::accumulate(a, a + n, 1, std::multiplies<T>());
	}

	/** 求所有排列 */
	template <typename T>
	int Permutations(T a[], int n)
	{
		std::sort(a, a + n);
		int count = 0;
		do
		{
			std::copy(a, a + n, std::ostream_iterator<T>(std::cout, " "));
			std::cout << std::endl;
			count++;
		} while (std::next_permutation(a, a + n));
		return count;
	}

	/**
	 * 多项式计算
	 * @param coeff - 系数数组，由低次到高次
	 * @param n - 项数
	 * @param x - 自变量的值
	 */
	template <typename T>
	T PolyEval(T coeff[], int n, const T& x)
	{
		T result = coeff[0], y = 1;
		for (int i = 1; i < n; ++i)
		{
			y *= x;
			result += coeff[i] * y;
		}
		return result;
	}

	/** 利用Horner法则的多项式计算 */
	template <typename T>
	T PolyEval_Horner(T coeff[], int n, const T& x)
	{
		T result = coeff[n - 1];
		for (int i = n - 2; i >= 0; --i)
		{
			result = result * x + coeff[i];
		}
		return result;
	}

	/** 名次计算 */
	template <typename T>
	void Rank(T a[], int n, T r[])
	{
		for (int i = 0; i < n; ++i)
		{
			r[i] = 0;
		}

		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (a[j] <= a[i])
				{
					r[i]++;
				}
				else
				{
					r[j]++;
				}
			}
		}
	}

	/** 利用附加数组的计数排序 */
	template <typename T>
	void RankSort(T a[], int n, T r[])
	{
		T* temp = new T[n];
		for (int i = 0; i < n; ++i)
		{
			temp[r[i]] = a[i];
		}
		for (int i = 0; i < n; ++i)
		{
			a[i] = temp[i];
		}
		delete[] temp;
	}

	/** 原地重排的计数排序 */
	template <typename T>
	void RankSort_InPlace(T a[], int n, T r[])
	{
		for (int i = 0; i < n; ++i)
		{
			while (r[i] != i)
			{
				Swap(a[i], a[r[i]]);
				Swap(r[i], r[r[i]]);
			}
		}
	}

	/** 寻找数组最大元素位置 */
	template <typename T>
	int IndexOfMax(T a[], int n)
	{
		int max = 0;
		for (int i = 1; i < n; ++i)
		{
			if (a[max] < a[i])
			{
				max = i;
			}
		}
		return max;
	}

	/** 选择排序 */
	template <typename T>
	void SelectionSort(T a[], int n)
	{
		for (int i = n; i > 1; --i)
		{
			int max = IndexOfMax(a, i);
			Swap(a[max], a[i - 1]);
		}
	}

	/** 及时终止的选择排序 */
	template <typename T>
	void SelectionSort2(T a[], int n)
	{
		bool bSorted = false;
		for (int i = n; !bSorted && i > 1; --i)
		{
			bSorted = true;
			int max = 0;
			for (int j = 1; j < i; ++j)
			{
				if (a[max] <= a[j])
				{
					max = j;
				}
				else
				{
					bSorted = false;
				}
			}
			Swap(a[max], a[i - 1]);
		}
	}

	/** 一次冒泡过程 */
	template <typename T>
	void Bubble(T a[], int n)
	{
		for (int i = 1; i < n; ++i)
		{
			if (a[i - 1] > a[i])
			{
				Swap(a[i - 1], a[i]);
			}
		}
	}

	/** 冒泡排序 */
	template <typename T>
	void BubbleSort(T a[], int n)
	{
		for (int i = n; i > 1; --i)
		{
			Bubble(a, i);
		}
	}

	/** 及时终止的冒泡排序 */
	template <typename T>
	void BubbleSort2(T a[], int n)
	{
		bool bSwapped = true;
		for (int i = n; bSwapped && i > 1; --i)
		{
			bSwapped = false;
			for (int j = 1; j < n; ++j)
			{
				if (a[j - 1] > a[j])
				{
					Swap(a[j - 1], a[j]);
					bSwapped = true;
				}
			}
		}
	}

	/** 在有序数组中插入一个元素 */
	template <typename T>
	void Insert(T a[], int n, const T& val)
	{
		int i;
		for (i = n - 1; i >= 0 && val < a[i]; --i)
		{
			a[i + 1] = a[i];
		}
		a[i + 1] = val;
	}

	/** 插入排序 */
	template <typename T>
	void InsertionSort(T a[], int n)
	{
		for (int i = 1; i < n; ++i)
		{
			T val = a[i];
			Insert(a, i, val);
		}
	}

	/** 二分查找（有序数组） */
	template <typename T>
	int BinarySeach(T a[], int n, const T& val)
	{
		int left = 0, right = n - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (val == a[mid])
			{
				return mid;
			}
			if (val < a[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return -1;
	}

	bool CheckMatchedPairs(const std::string& str, char c1 = '{', char c2 = '}')
	{
		bool bResult = true;
		ArrayStack<int> stack;
		for (int i = 0; i < str.size(); ++i)
		{
			if (str[i] == c1)
			{
				stack.Push(i);
			}
			else
			{
				if (str[i] == c2)
				{
					try
					{
						stack.Pop();
					}
					catch (std::exception e)
					{
						std::cout << "No match for " << c2 << " at " << i << std::endl;
						bResult = false;
					}
				}
			}
		}

		while (!stack.Empty())
		{
			std::cout << "No match for " << c1 << " at " << stack.Top() << std::endl;
			bResult = false;
			stack.Pop();
		}

		if (bResult)
		{
			std::cout << "No issues found!" << std::endl;
		}
		return bResult;
	}

	/** 汉诺塔问题-将n个碟子从1塔移动到3塔 */
	void TowersOfHanoi(int n, int x = 1, int y = 2, int z = 3)
	{
		if (n > 0)
		{
			// 将n-1个碟子递归地从1塔经3塔中转移动到2塔
			TowersOfHanoi(n - 1, x, z, y);
			// 将1塔的1个碟子移动到3塔
			std::cout << x << "->" << z << std::endl;
			// 将n-1个碟子递归地从2塔经1塔中转移动到3塔
			TowersOfHanoi(n - 1, y, x, z);
		}
	}

	namespace HMaze {

		struct Position
		{
			int row, column;
		};

		std::ostream& operator<<(std::ostream& out, const Position& x)
		{
			out << "(" << x.row << ", " << x.column << ")";
			return out;
		}

		enum Direction
		{
			right = 0, down, left, up
		};

		bool SolveMaze(bool mazeData[][10], int size)
		{
			Position offset[4];
			// 向右
			offset[right].row = 0; offset[right].column = 1;
			// 向下
			offset[down].row = 1; offset[down].column = 0;
			// 向左
			offset[left].row = 0; offset[left].column = -1;
			// 向上
			offset[up].row = -1; offset[up].column = 0;

			// 为包括外围障碍墙的新迷宫分配空间
			bool** maze = new bool* [size + 2];
			for (int i = 0; i < size + 2; ++i)
			{
				maze[i] = new bool[size + 2];
			}

			// 复制迷宫数据
			for (int i = 1; i <= size; ++i)
			{
				for (int j = 1; j <= size; ++j)
				{
					maze[i][j] = mazeData[i - 1][j - 1];
				}
			}
			// 初始化迷宫外围的障碍墙
			for (int i = 0; i <= size + 1; ++i)
			{
				// 顶部
				maze[0][i] = 1;
				// 底部
				maze[size + 1][i] = 1;
				// 左部
				maze[i][0] = 1;
				// 右部
				maze[i][size + 1] = 1;
			}

			Position currentPos{ 1,1 };
			maze[1][1] = 1; // 建一堵墙，防止回到出口
			int currentDir = right;
			ArrayStack<Position> stackPath;

			// 没有到达出口
			while (currentPos.row != size || currentPos.column != size)
			{
				int nextRow, nextColumn;
				// 顺时针方向搜索可以移动的方向
				while (currentDir <= up)
				{
					nextRow = currentPos.row + offset[currentDir].row;
					nextColumn = currentPos.column + offset[currentDir].column;
					// 找到可以移动的方向
					if (!maze[nextRow][nextColumn])
						break;
					currentDir++;
				}
				// 下一个移动位置已经找到
				if (currentDir <= up)
				{
					// 记录移动路径
					stackPath.Push(currentPos);
					// 移动到下一个位置
					currentPos.row = nextRow;
					currentPos.column = nextColumn;
					// 防止回到刚才的位置
					maze[currentPos.row][currentPos.column] = 1;
					// 重置搜索方向
					currentDir = right;
				}
				// 没有相邻的位置可移动，返回
				else
				{
					// 无路可退
					if (stackPath.Empty())
					{
						std::cout << "No path exist!" << std::endl;
						return false;
					}
					Position lastPos = stackPath.Top();
					stackPath.Pop();
					// 判断退回后再进行搜索的方向
					if (currentPos.row == lastPos.row)
					{
						// 若上一步是向右移动，则回退后向下搜索
						// 若上一步是向左移动，则回退后向上搜索
						currentDir = 2 + lastPos.column - currentPos.column;
					}
					else
					{
						// 若上一步是向下移动，则回退后向左搜索
						// 若上一步是向上移动，则回退后无方向可移动，需继续回退
						currentDir = 3 + lastPos.row - currentPos.row;
					}
					// 退回上一个记录的位置
					currentPos = lastPos;
				}
			}
			// 打印路径
			stackPath.Output(std::cout, "->");
			// 打印终点
			std::cout << "(" << currentPos.row << ", " << currentPos.column << ")" << std::endl;

			for (int i = 0; i < size + 2; ++i)
			{
				delete[] maze[i];
			}
			delete[] maze;
			return true;
		}
	}

	
}
