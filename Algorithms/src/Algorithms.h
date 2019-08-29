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
			// 不断从小根堆中取出两课树合并，直到剩下一棵树
			for (int i = 0; i < n - 1; ++i)
			{
				x = heap.Top();
				heap.Pop();
				y = heap.Top();
				heap.Pop();

				z.weight = x.weight + y.weight;
				z.tree = new LinkedBinaryTree<T>(0, *x.tree, *y.tree);
				heap.Push(z);

				// 删除树但不删除子节点，子节点的所有权已转移给z.tree
				delete x.tree;
				delete y.tree;
			}

			delete[] hNode;
			return heap.Top().tree;
		}

		/** 构建霍夫曼树用于压缩和解压。 */
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
			// 不断从小根堆中取出两课树合并，直到剩下一棵树
			for (int i = 0; i < n - 1; ++i)
			{
				x = heap.Top();
				heap.Pop();
				y = heap.Top();
				heap.Pop();

				z.weight = x.weight + y.weight;
				z.tree = new LinkedBinaryTree<char>('0', *x.tree, *y.tree);
				heap.Push(z);

				// 删除树但不删除子节点，子节点的所有权已转移给z.tree
				delete x.tree;
				delete y.tree;
			}

			delete[] hNode;
			return heap.Top().tree;
		}

		/** 读取文件内容，返回所有出现字符及其出现频率的键值对。*/
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
			// 不跳过空白符
			in >> std::noskipws;
			// 读入文件内容
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

		/** 将霍夫曼编码长度，字符-权重字典，字典长度，编码后内容写入文件。 */
		void EncodeWrite(const std::string& filePath, int huffmanSize, SortedChain<char, int>* charWeights, int charNum, const std::string& fileContent)
		{
			// 必须用二进制写入，否则编码里可能会有文件结束符，导致读取时提前结束
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
			// 读取霍夫曼编码长度
			std::getline(in, str);
			huffmanSize = std::stoi(str);

			// 读取字符-权重字典长度
			std::getline(in, str);
			int charNum = std::stoi(str);
			charWeights = new SortedChain<char, int>;
			// 读取字符-权重字典数据
			for (int i = 0; i < charNum; ++i)
			{
				// 读取字符
				char c = in.get();
				// 读取权重
				std::getline(in, str);
				charWeights->Insert({ c, std::stoi(str) });
			}
			
			char c;
			in >> std::noskipws;
			// 读取编码内容
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

		/** 中序遍历得出每个字符（叶节点）的编码（字符串形式）。 */
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
					// 打印编码表
					//std::cout << startTreeNode->element << ": " << code << std::endl;
				}
				// 回到上一层，需删除最后一个字符
				code.pop_back();

				if (startTreeNode->rightChild)
				{
					code += '1';
					InOrderLeaves(startTreeNode->rightChild, hCodes, code);
				}
			}
		}

		/** 根据0、1编码遍历哈夫曼树，取出对应字符。 */
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

		/** 将0、1表示的字符串编码转换为二进制位存储进unsigned char。 */
		unsigned char Encode(std::string& code)
		{
			// 不够8位用0补位
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

		/** 将二进制位转换为0、1表示的字符串编码。 */
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
			std::cout << "读取文件......" << std::endl;
			std::string fileContent;
			SortedChain<char, int>* charWeights = EncodeRead(inFilePath, fileContent);

			std::cout << "构建霍夫曼树......" << std::endl;
			LinkedBinaryTree<char>* hTree = HuffmanTree(charWeights);

			// 生成由0、1构成的字符串霍夫曼编码表
			SortedChain<char, std::string> hCodes;
			InOrderLeaves(hTree->Root(), hCodes);

			std::cout << "生成霍夫曼编码......" << std::endl;
			// 将文件内容转换成由0、1构成的字符串霍夫曼编码
			std::string hStr;
			for (const auto& c : fileContent)
			{
				hStr += *hCodes.Find(c);
			}
			
			std::cout << "转码中......" << std::endl;
			// 霍夫曼编码总长度
			int hSize = hStr.size();
			std::string str, outStr;
			for (int i = 0; i < hSize; i += 8)
			{
				// 循环提取8个位进行转码，不够的补0
				str = hStr.substr(i, 8);
				outStr += Encode(str);
			}
			std::cout << "写入" << outFilePath << "......" << std::endl;
			EncodeWrite(outFilePath, hSize, charWeights, charWeights->Size(), outStr);
			int prevSize = fileContent.size();
			int currentSize = outStr.size();
			std::cout << "压缩完成!\n-----------------------------------" << std::endl;
			std::cout <<"压缩前大小：" << prevSize << "字节\n压缩后大小（不包括元数据）：" << currentSize << "字节\n压缩比：" << (float)currentSize / prevSize * 100 << "%" << std::endl;

			delete charWeights;
		}

		void Decompress(const std::string& inFilePath, const std::string& outFilePath)
		{
			std::cout << "读取文件......" << std::endl;
			int huffmanSize = 0;
			SortedChain<char, int>* charWeights = nullptr;
			std::string fileContent;
			DecodeRead(inFilePath, huffmanSize, charWeights, fileContent);

			std::cout << "构建霍夫曼树......" << std::endl;
			LinkedBinaryTree<char>* hTree = HuffmanTree(charWeights);

			// 生成由0、1构成的字符串霍夫曼编码表
			SortedChain<char, std::string> hCodes;
			InOrderLeaves(hTree->Root(), hCodes);

			std::cout << "生成霍夫曼编码......" << std::endl;
			// 将文件内容转换成由0、1构成的字符串霍夫曼编码
			std::string hStr;
			for (const auto& c : fileContent)
			{
				hStr += Decode(c);
			}
			// 剔除末尾补位的0
			while (hStr.size() > huffmanSize)
			{
				hStr.pop_back();
			}

			std::cout << "转码中......" << std::endl;
			std::string outStr;
			TraverseByCode(hTree->Root(), hStr, outStr);

			std::cout << "写入" << outFilePath << "......" << std::endl;
			DecodeWrite(outFilePath, outStr);
			std::cout << "解压完成!" << std::endl;
			
			delete charWeights;
		}
	}

}
