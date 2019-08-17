#include "Algorithms.h"
#include "Timer.h"

template <typename T>
void Print(T a[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout << a[i] << std::endl;
	}
}

template <typename T>
void SortingTest(void (*func)(T a[], int n), int scale = 1000)
{
	int step = 10;
	T* a = new T[scale];

	std::cout << "最坏运行时间：" << std::endl;

	for (int n = 0; n <= scale; n += step)
	{
		for (int i = 0; i < n; ++i)
		{
			a[i] = n - i;
		}

		{
			HUtil::Timer timer;
			func(a, n);
			std::cout << "n: " << n << "\t";
		}
		
		if (n == 100)
		{
			step = 100;
		}
	}
	delete[] a;
}

int main()
{
	int a[] = { 2,4,6,8,9 };
	char b[] = { 'e','b','d','f','c','a','g' };

	SortingTest<int>(InsertionSort);
	
	//InsertionSort(b, 7);
	//Print(b, 7);
	//std::cout << BinarySeach(a, 5, 6) << std::endl;

	return 0;
}
