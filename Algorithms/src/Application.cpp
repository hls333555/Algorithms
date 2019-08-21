#include "Algorithms.h"
#include "LinearList.h"
#include "Matrix.h"

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
		HAlgorithm::Matrix<int> m1(3, 4);
		m1(1, 1) = 1;
		m1(1, 2) = 2;
		m1(1, 3) = 30;
		m1(1, 4) = 24;
		m1(2, 1) = 5;
		m1(2, 2) = 0;
		m1(2, 3) = 7;
		m1(2, 4) = 18;
		m1(3, 1) = 9;
		m1(3, 2) = 70;
		m1(3, 3) = 0;
		m1(3, 4) = 12;
		HAlgorithm::Matrix<int> m2(4, 3);
		m2(1, 1) = 0;
		m2(1, 2) = 2;
		m2(1, 3) = 13;
		m2(2, 1) = 4;
		m2(2, 2) = 25;
		m2(2, 3) = 63;
		m2(3, 1) = 27;
		m2(3, 2) = 8;
		m2(3, 3) = 9;
		m2(4, 1) = 10;
		m2(4, 2) = 32;
		m2(4, 3) = 0;

		std::cout << m1 << "\t*" << std::endl << m2 << "\t=" << std::endl << m1 * m2 << std::endl;
		std::cout << m2 << "\t*" << std::endl << m1 << "\t=" << std::endl << m2 * m1 << std::endl;
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
