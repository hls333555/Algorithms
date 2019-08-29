#include "Algorithms.h"
#include "LinearList.h"
#include "Matrix.h"
#include "Stack.h"
#include "Queue.h"
#include "Dictionary.h"
#include "PriorityQueue.h"

#include "Test.h"

template <typename T>
void Print(T a[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	int a[] = { 20,12,35,15,10,80,30,17,2,1 };
	char b[] = { 'e','b','d','f','c','a','g' };

	try
	{
		//Print(a, 10);
		//HAlgorithm::HeapSort(a, 10);
		//Print(a, 10);

		//int a[10];
		//int n = 10;
		//for (int i = 0; i < n; i++)
		//	a[i] = 2 * i;
		//HAlgorithm::LinkedBinaryTree<int>* x = HAlgorithm::HHuffmanCoding::HuffmanTree<int>(a, n);
		//x->PostOrder();

		HuffmanCompressionTest();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
