#include "Algorithms.h"
#include "LinearList.h"
#include "Matrix.h"
#include "Stack.h"
#include "Queue.h"
#include "Dictionary.h"

#include "Test.h"

template <typename T>
void Print(T a[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout << a[i] << std::endl;
	}
}

int main()
{
	int a[] = { 2,4,6,8,9 };
	char b[] = { 'e','b','d','f','c','a','g' };

	try
	{
		HAlgorithm::SortedChain<int, int> d;
		for (int i = 10; i > 0; --i)
		{
			d.Insert({ i, 2 * i });
		}
		d.Output(std::cout);
		d.Erase(7);
		d.Erase(4);
		d.Erase(1);
		std::cout << std::endl << "---------------" << std::endl;
		d.Output(std::cout);
		std::cout << std::endl;
		auto x = d.Find(1);
		if (x)
		{
			std::cout << "x: " << *x << std::endl;
		}
		auto y = d.Find(2);
		if (y)
		{
			std::cout << "y: " << *y << std::endl;
		}
		auto z = d.Find(9);
		if (z)
		{
			std::cout << "z: " << *z << std::endl;
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
