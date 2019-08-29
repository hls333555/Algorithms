#pragma once

#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <iterator>

#include "Stack.h"
#include "Dictionary.h"
#include "BinaryTree.h"
#include "PriorityQueue.h"

namespace HAlgorithm {

	/** ������Ԫ�� */
	template <typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	/** �ۼ�����Ԫ�� */
	template <typename T>
	T Sum(T a[], int n)
	{
		return std::accumulate(a, a + n, 0);
	}

	/** �۳�����Ԫ�� */
	template <typename T>
	T Product(T a[], int n)
	{
		return std::accumulate(a, a + n, 1, std::multiplies<T>());
	}

	/** ���������� */
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
	 * ����ʽ����
	 * @param coeff - ϵ�����飬�ɵʹε��ߴ�
	 * @param n - ����
	 * @param x - �Ա�����ֵ
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

	/** ����Horner����Ķ���ʽ���� */
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

	/** ���μ��� */
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

	/** ���ø�������ļ������� */
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

	/** ԭ�����ŵļ������� */
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

	/** Ѱ���������Ԫ��λ�� */
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

	/** ѡ������ */
	template <typename T>
	void SelectionSort(T a[], int n)
	{
		for (int i = n; i > 1; --i)
		{
			int max = IndexOfMax(a, i);
			Swap(a[max], a[i - 1]);
		}
	}

	/** ��ʱ��ֹ��ѡ������ */
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

	/** һ��ð�ݹ��� */
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

	/** ð������ */
	template <typename T>
	void BubbleSort(T a[], int n)
	{
		for (int i = n; i > 1; --i)
		{
			Bubble(a, i);
		}
	}

	/** ��ʱ��ֹ��ð������ */
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

	/** �����������в���һ��Ԫ�� */
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

	/** �������� */
	template <typename T>
	void InsertionSort(T a[], int n)
	{
		for (int i = 1; i < n; ++i)
		{
			T val = a[i];
			Insert(a, i, val);
		}
	}

	/** ���ֲ��ң��������飩 */
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

	/** ��ŵ������-��n�����Ӵ�1���ƶ���3�� */
	void TowersOfHanoi(int n, int x = 1, int y = 2, int z = 3)
	{
		if (n > 0)
		{
			// ��n-1�����ӵݹ�ش�1����3����ת�ƶ���2��
			TowersOfHanoi(n - 1, x, z, y);
			// ��1����1�������ƶ���3��
			std::cout << x << "->" << z << std::endl;
			// ��n-1�����ӵݹ�ش�2����1����ת�ƶ���3��
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
			// ����
			offset[right].row = 0; offset[right].column = 1;
			// ����
			offset[down].row = 1; offset[down].column = 0;
			// ����
			offset[left].row = 0; offset[left].column = -1;
			// ����
			offset[up].row = -1; offset[up].column = 0;

			// Ϊ������Χ�ϰ�ǽ�����Թ�����ռ�
			bool** maze = new bool* [size + 2];
			for (int i = 0; i < size + 2; ++i)
			{
				maze[i] = new bool[size + 2];
			}

			// �����Թ�����
			for (int i = 1; i <= size; ++i)
			{
				for (int j = 1; j <= size; ++j)
				{
					maze[i][j] = mazeData[i - 1][j - 1];
				}
			}
			// ��ʼ���Թ���Χ���ϰ�ǽ
			for (int i = 0; i <= size + 1; ++i)
			{
				// ����
				maze[0][i] = 1;
				// �ײ�
				maze[size + 1][i] = 1;
				// ��
				maze[i][0] = 1;
				// �Ҳ�
				maze[i][size + 1] = 1;
			}

			Position currentPos{ 1,1 };
			maze[1][1] = 1; // ��һ��ǽ����ֹ�ص�����
			int currentDir = right;
			ArrayStack<Position> stackPath;

			// û�е������
			while (currentPos.row != size || currentPos.column != size)
			{
				int nextRow, nextColumn;
				// ˳ʱ�뷽�����������ƶ��ķ���
				while (currentDir <= up)
				{
					nextRow = currentPos.row + offset[currentDir].row;
					nextColumn = currentPos.column + offset[currentDir].column;
					// �ҵ������ƶ��ķ���
					if (!maze[nextRow][nextColumn])
						break;
					currentDir++;
				}
				// ��һ���ƶ�λ���Ѿ��ҵ�
				if (currentDir <= up)
				{
					// ��¼�ƶ�·��
					stackPath.Push(currentPos);
					// �ƶ�����һ��λ��
					currentPos.row = nextRow;
					currentPos.column = nextColumn;
					// ��ֹ�ص��ղŵ�λ��
					maze[currentPos.row][currentPos.column] = 1;
					// ������������
					currentDir = right;
				}
				// û�����ڵ�λ�ÿ��ƶ�������
				else
				{
					// ��·����
					if (stackPath.Empty())
					{
						std::cout << "No path exist!" << std::endl;
						return false;
					}
					Position lastPos = stackPath.Top();
					stackPath.Pop();
					// �ж��˻غ��ٽ��������ķ���
					if (currentPos.row == lastPos.row)
					{
						// ����һ���������ƶ�������˺���������
						// ����һ���������ƶ�������˺���������
						currentDir = 2 + lastPos.column - currentPos.column;
					}
					else
					{
						// ����һ���������ƶ�������˺���������
						// ����һ���������ƶ�������˺��޷�����ƶ������������
						currentDir = 3 + lastPos.row - currentPos.row;
					}
					// �˻���һ����¼��λ��
					currentPos = lastPos;
				}
			}
			// ��ӡ·��
			stackPath.Output(std::cout, "->");
			// ��ӡ�յ�
			std::cout << "(" << currentPos.row << ", " << currentPos.column << ")" << std::endl;

			for (int i = 0; i < size + 2; ++i)
			{
				delete[] maze[i];
			}
			delete[] maze;
			return true;
		}
	}

	template <typename T>
	void HeapSort(T a[], int n)
	{
		MaxHeap<T> heap(a, n);

		for (int i = n - 1; i >= 0; --i)
		{
			T max = heap.Top();
			heap.Pop();
			a[i] = max;
		}
	}

	namespace HHuffmanCoding {

		template <typename T>
		struct HuffmanNode
		{
			bool operator<(const HuffmanNode<T>& other) const { return weight < other.weight; }
			bool operator<=(const HuffmanNode<T>& other) const { return weight <= other.weight; }
			bool operator>(const HuffmanNode<T>& other) const { return weight > other.weight; }
			bool operator>=(const HuffmanNode<T>& other) const { return weight >= other.weight; }

			int weight;
			LinkedBinaryTree<T>* tree;
		};

		template <typename T>
		LinkedBinaryTree<T>* HuffmanTree(int weights[], int n)
		{
			HuffmanNode<T>* hNode = new HuffmanNode<T>[n];
			LinkedBinaryTree<T> emptyTree;
			for (int i = 0; i < n; ++i)
			{
				hNode[i].weight = weights[i];
				hNode[i].tree = new LinkedBinaryTree<T>(i + 1, emptyTree, emptyTree);
			}

			MinHeap<HuffmanNode<T>> heap(hNode, n);

			HuffmanNode<T> x, y, z;
			// ���ϴ�С������ȡ���������ϲ���ֱ��ʣ��һ����
			for (int i = 0; i < n - 1; ++i)
			{
				x = heap.Top();
				heap.Pop();
				y = heap.Top();
				heap.Pop();

				z.weight = x.weight + y.weight;
				z.tree = new LinkedBinaryTree<T>(0, *x.tree, *y.tree);
				heap.Push(z);

				// ɾ��������ɾ���ӽڵ㣬�ӽڵ������Ȩ��ת�Ƹ�z.tree
				delete x.tree;
				delete y.tree;
			}

			delete[] hNode;
			return heap.Top().tree;
		}

		/** ����������������ѹ���ͽ�ѹ�� */
		LinkedBinaryTree<char>* HuffmanTree(SortedChain<char, int>* charWeights)
		{
			int n = charWeights->Size();
			HuffmanNode<char>* hNode = new HuffmanNode<char>[n];
			LinkedBinaryTree<char> emptyTree;
			int i = 0;
			for (auto It = charWeights->Begin(); It != nullptr; ++It)
			{
				hNode[i].weight = (*It).element.second;
				hNode[i].tree = new LinkedBinaryTree<char>((*It).element.first, emptyTree, emptyTree);
				i++;
			}

			MinHeap<HuffmanNode<char>> heap(hNode, n);

			HuffmanNode<char> x, y, z;
			// ���ϴ�С������ȡ���������ϲ���ֱ��ʣ��һ����
			for (int i = 0; i < n - 1; ++i)
			{
				x = heap.Top();
				heap.Pop();
				y = heap.Top();
				heap.Pop();

				z.weight = x.weight + y.weight;
				z.tree = new LinkedBinaryTree<char>('0', *x.tree, *y.tree);
				heap.Push(z);

				// ɾ��������ɾ���ӽڵ㣬�ӽڵ������Ȩ��ת�Ƹ�z.tree
				delete x.tree;
				delete y.tree;
			}

			delete[] hNode;
			return heap.Top().tree;
		}

		/** ��ȡ�ļ����ݣ��������г����ַ��������Ƶ�ʵļ�ֵ�ԡ�*/
		SortedChain<char, int>* EncodeRead(const std::string& filePath, std::string& fileContent)
		{
			std::ifstream in(filePath);
			if (!in.is_open())
			{
				std::stringstream ss;
				ss << "Failed to open the file with path = \"" << filePath << "\"!";
				throw std::exception(ss.str().c_str());
			}

			char c;
			SortedChain<char, int>* charWeights = new SortedChain<char, int>;
			// �������հ׷�
			in >> std::noskipws;
			// �����ļ�����
			while (in >> c)
			{
				if (int* result = charWeights->Find(c))
				{
					(*result)++;
				}
				else
				{
					charWeights->Insert({ c, 1 });
				}

				fileContent += c;
			}
			return charWeights;
		}

		/** �����������볤�ȣ��ַ�-Ȩ���ֵ䣬�ֵ䳤�ȣ����������д���ļ��� */
		void EncodeWrite(const std::string& filePath, int huffmanSize, SortedChain<char, int>* charWeights, int charNum, const std::string& fileContent)
		{
			// �����ö�����д�룬�����������ܻ����ļ������������¶�ȡʱ��ǰ����
			std::ofstream out(filePath, std::ios::binary);
			if (!out.is_open())
			{
				std::stringstream ss;
				ss << "Failed to open the file with path = \"" << filePath << "\"!";
				throw std::exception(ss.str().c_str());
			}

			out << huffmanSize << std::endl;
			out << charNum << std::endl;
			for (auto It = charWeights->Begin(); It != nullptr; ++It)
			{
				out << (*It).element.first << (*It).element.second << std::endl;
			}
			out << fileContent;
		}

		void DecodeRead(const std::string& filePath, int& huffmanSize, SortedChain<char, int>*& charWeights, std::string& fileContent)
		{
			std::ifstream in(filePath, std::ios::binary);
			if (!in.is_open())
			{
				std::stringstream ss;
				ss << "Failed to open the file with path = \"" << filePath << "\"!";
				throw std::exception(ss.str().c_str());
			}

			std::string str;
			// ��ȡ���������볤��
			std::getline(in, str);
			huffmanSize = std::stoi(str);

			// ��ȡ�ַ�-Ȩ���ֵ䳤��
			std::getline(in, str);
			int charNum = std::stoi(str);
			charWeights = new SortedChain<char, int>;
			// ��ȡ�ַ�-Ȩ���ֵ�����
			for (int i = 0; i < charNum; ++i)
			{
				// ��ȡ�ַ�
				char c = in.get();
				// ��ȡȨ��
				std::getline(in, str);
				charWeights->Insert({ c, std::stoi(str) });
			}
			
			char c;
			in >> std::noskipws;
			// ��ȡ��������
			while (in >> c)
			{
				fileContent += c;
			}
		}

		void DecodeWrite(const std::string& filePath, const std::string& fileContent)
		{
			std::ofstream out(filePath);
			if (!out.is_open())
			{
				std::stringstream ss;
				ss << "Failed to open the file with path = \"" << filePath << "\"!";
				throw std::exception(ss.str().c_str());
			}

			out << fileContent;
		}

		/** ��������ó�ÿ���ַ���Ҷ�ڵ㣩�ı��루�ַ�����ʽ���� */
		void InOrderLeaves(BinaryTreeNode<char>* startTreeNode, SortedChain<char, std::string>& hCodes, std::string code = "")
		{
			if (startTreeNode)
			{
				if (startTreeNode->leftChild)
				{
					code += '0';
					InOrderLeaves(startTreeNode->leftChild, hCodes, code);
				}

				if (!startTreeNode->leftChild && !startTreeNode->rightChild)
				{
					hCodes.Insert({ startTreeNode->element, code });
					// ��ӡ�����
					//std::cout << startTreeNode->element << ": " << code << std::endl;
				}
				// �ص���һ�㣬��ɾ�����һ���ַ�
				code.pop_back();

				if (startTreeNode->rightChild)
				{
					code += '1';
					InOrderLeaves(startTreeNode->rightChild, hCodes, code);
				}
			}
		}

		/** ����0��1�����������������ȡ����Ӧ�ַ��� */
		void TraverseByCode(BinaryTreeNode<char>* startTreeNode, const std::string& str, std::string& outStr)
		{
			BinaryTreeNode<char>* rootNode = startTreeNode;
			for (int i = 0; i < str.size(); ++i)
			{
				if (startTreeNode)
				{
					if (str[i] == '0')
					{
						startTreeNode = startTreeNode->leftChild;
					}
					else
					{
						startTreeNode = startTreeNode->rightChild;
					}

					if (!startTreeNode->leftChild && !startTreeNode->rightChild)
					{
						outStr += startTreeNode->element;
						startTreeNode = rootNode;
					}
				}
			}
		}

		/** ��0��1��ʾ���ַ�������ת��Ϊ������λ�洢��unsigned char�� */
		unsigned char Encode(std::string& code)
		{
			// ����8λ��0��λ
			while (code.size() < 8)
			{
				code += '0';
			}

			int result = 0x0;
			for (int i = 0; i < 8; ++i)
			{
				result <<= 1;
				if (code[i] == '1')
				{
					++result;
				}
			}
			return result;
		}

		/** ��������λת��Ϊ0��1��ʾ���ַ������롣 */
		std::string Decode(char c)
		{
			std::string s;
			for (int i = 0; i < 8; i++)
			{
				if (c & 0x80)
				{
					s += '1';
				}
				else
				{
					s += '0';
				}
				c <<= 1;
			}
			return s;
		}

		void Compress(const std::string& inFilePath, const std::string& outFilePath)
		{
			std::cout << "��ȡ�ļ�......" << std::endl;
			std::string fileContent;
			SortedChain<char, int>* charWeights = EncodeRead(inFilePath, fileContent);

			std::cout << "������������......" << std::endl;
			LinkedBinaryTree<char>* hTree = HuffmanTree(charWeights);

			// ������0��1���ɵ��ַ��������������
			SortedChain<char, std::string> hCodes;
			InOrderLeaves(hTree->Root(), hCodes);

			std::cout << "���ɻ���������......" << std::endl;
			// ���ļ�����ת������0��1���ɵ��ַ�������������
			std::string hStr;
			for (const auto& c : fileContent)
			{
				hStr += *hCodes.Find(c);
			}
			
			std::cout << "ת����......" << std::endl;
			// �����������ܳ���
			int hSize = hStr.size();
			std::string str, outStr;
			for (int i = 0; i < hSize; i += 8)
			{
				// ѭ����ȡ8��λ����ת�룬�����Ĳ�0
				str = hStr.substr(i, 8);
				outStr += Encode(str);
			}
			std::cout << "д��" << outFilePath << "......" << std::endl;
			EncodeWrite(outFilePath, hSize, charWeights, charWeights->Size(), outStr);
			int prevSize = fileContent.size();
			int currentSize = outStr.size();
			std::cout << "ѹ�����!\n-----------------------------------" << std::endl;
			std::cout <<"ѹ��ǰ��С��" << prevSize << "�ֽ�\nѹ�����С��������Ԫ���ݣ���" << currentSize << "�ֽ�\nѹ���ȣ�" << (float)currentSize / prevSize * 100 << "%" << std::endl;

			delete charWeights;
		}

		void Decompress(const std::string& inFilePath, const std::string& outFilePath)
		{
			std::cout << "��ȡ�ļ�......" << std::endl;
			int huffmanSize = 0;
			SortedChain<char, int>* charWeights = nullptr;
			std::string fileContent;
			DecodeRead(inFilePath, huffmanSize, charWeights, fileContent);

			std::cout << "������������......" << std::endl;
			LinkedBinaryTree<char>* hTree = HuffmanTree(charWeights);

			// ������0��1���ɵ��ַ��������������
			SortedChain<char, std::string> hCodes;
			InOrderLeaves(hTree->Root(), hCodes);

			std::cout << "���ɻ���������......" << std::endl;
			// ���ļ�����ת������0��1���ɵ��ַ�������������
			std::string hStr;
			for (const auto& c : fileContent)
			{
				hStr += Decode(c);
			}
			// �޳�ĩβ��λ��0
			while (hStr.size() > huffmanSize)
			{
				hStr.pop_back();
			}

			std::cout << "ת����......" << std::endl;
			std::string outStr;
			TraverseByCode(hTree->Root(), hStr, outStr);

			std::cout << "д��" << outFilePath << "......" << std::endl;
			DecodeWrite(outFilePath, outStr);
			std::cout << "��ѹ���!" << std::endl;
			
			delete charWeights;
		}
	}

}
