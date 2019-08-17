#pragma once

#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>

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
