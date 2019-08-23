#include "Algorithms.h"
#include "LinearList.h"
#include "Matrix.h"
#include "Stack.h"
#include "Queue.h"

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

	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
