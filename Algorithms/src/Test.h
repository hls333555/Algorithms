#pragma once

#include "Timer.h"

#include "Algorithms.h"
#include "LinearList.h"
#include "Stack.h"

void LinearListTest(int scale = 50000)
{
	srand(time(nullptr));

	std::cout << "-ArrayList---------------------" << std::endl;
	{
		HAlgorithm::ArrayList<int> AL(scale);
		std::cout << scale << "次Get()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			AL.Insert(AL.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			AL.Get(i);
		}
	}
	{
		HAlgorithm::ArrayList<int> AL(scale);
		std::cout << scale << "次Find()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			AL.Insert(AL.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			AL.Find(AL.Get(i));
		}
	}
	{
		HAlgorithm::ArrayList<int> AL;
		std::cout << scale << "次Insert()-最好情况（扩容）：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			AL.Insert(AL.Size(), i);
		}
	}
	{
		HAlgorithm::ArrayList<int> AL(scale);
		std::cout << scale << "次Insert()-最好情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			AL.Insert(AL.Size(), i);
		}
	}
	{
		HAlgorithm::ArrayList<int> AL;
		std::cout << scale << "次Insert()-平均（随机）情况（扩容）：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = AL.Size() ? AL.Size() : 1;
			AL.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::ArrayList<int> AL(scale);
		std::cout << scale << "次Insert()-平均（随机）情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = AL.Size() ? AL.Size() : 1;
			AL.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::ArrayList<int> AL;
		std::cout << scale << "次Insert()-最坏情况（扩容）：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			AL.Insert(0, i);
		}
	}
	{
		HAlgorithm::ArrayList<int> AL(scale);
		std::cout << scale << "次Insert()-最坏情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			AL.Insert(0, i);
		}
	}
	std::cout << "-VectorList---------------------" << std::endl;
	{
		HAlgorithm::VectorList<int> VL(scale);
		std::cout << scale << "次Get()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			VL.Insert(VL.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			VL.Get(i);
		}
	}
	{
		HAlgorithm::VectorList<int> VL(scale);
		std::cout << scale << "次Find()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			VL.Insert(VL.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			VL.Find(VL.Get(i));
		}
	}
	{
		HAlgorithm::VectorList<int> VL;
		std::cout << scale << "次Insert()-最好情况（扩容）：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			VL.Insert(VL.Size(), i);
		}
	}
	{
		HAlgorithm::VectorList<int> VL(scale);
		std::cout << scale << "次Insert()-最好情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			VL.Insert(VL.Size(), i);
		}
	}
	{
		HAlgorithm::VectorList<int> VL;
		std::cout << scale << "次Insert()-平均（随机）情况（扩容）：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = VL.Size() ? VL.Size() : 1;
			VL.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::VectorList<int> VL(scale);
		std::cout << scale << "次Insert()-平均（随机）情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = VL.Size() ? VL.Size() : 1;
			VL.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::VectorList<int> VL;
		std::cout << scale << "次Insert()-最坏情况（扩容）：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			VL.Insert(0, i);
		}
	}
	{
		HAlgorithm::VectorList<int> VL(scale);
		std::cout << scale << "次Insert()-最坏情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			VL.Insert(0, i);
		}
	}
	std::cout << "-Chain---------------------" << std::endl;
	{
		HAlgorithm::Chain<int> C;
		std::cout << scale << "次Get()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			C.Insert(0, i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			C.Get(i);
		}
	}
	{
		HAlgorithm::Chain<int> C;
		std::cout << scale << "次Find()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			C.Insert(0, i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			C.Find(C.Get(i));
		}
	}
	{
		HAlgorithm::Chain<int> C;
		std::cout << scale << "次Insert()-最好情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			C.Insert(0, i);
		}
	}
	{
		HAlgorithm::Chain<int> C;
		std::cout << scale << "次Insert()-平均（随机）情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = C.Size() ? C.Size() : 1;
			C.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::Chain<int> C;
		std::cout << scale << "次Insert()-最坏情况：" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			C.Insert(C.Size(), i);
		}
	}
}

void StackTest(int scale = 50000000)
{
	std::cout << "-DerivedArrayStack---------------------" << std::endl;
	{
		HAlgorithm::DerivedArrayStack<int> DAS;
		HUtil::Timer timer;
		std::cout << scale << "次Push()（扩容），";
		for (int i = 0; i < scale; ++i)
		{
			DAS.Push(i);
		}
		std::cout << scale << "次Top()，Pop()（扩容）：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			DAS.Top();
			DAS.Pop();
		}
	}
	{
		HAlgorithm::DerivedArrayStack<int> DAS(scale);
		HUtil::Timer timer;
		std::cout << scale << "次Push()，";
		for (int i = 0; i < scale; ++i)
		{
			DAS.Push(i);
		}
		std::cout << scale << "次Top()，Pop()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			DAS.Top();
			DAS.Pop();
		}
	}
	std::cout << "-ArrayStack---------------------" << std::endl;
	{
		HAlgorithm::ArrayStack<int> AS;
		HUtil::Timer timer;
		std::cout << scale << "次Push()（扩容），";
		for (int i = 0; i < scale; ++i)
		{
			AS.Push(i);
		}
		std::cout << scale << "次Top()，Pop()（扩容）：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			AS.Top();
			AS.Pop();
		}
	}
	{
		HAlgorithm::ArrayStack<int> AS(scale);
		HUtil::Timer timer;
		std::cout << scale << "次Push()，";
		for (int i = 0; i < scale; ++i)
		{
			AS.Push(i);
		}
		std::cout << scale << "次Top()，Pop()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			AS.Top();
			AS.Pop();
		}
	}
	std::cout << "-DerivedLinkedStack---------------------" << std::endl;
	{
		HAlgorithm::DerivedLinkedStack<int> DLS;
		HUtil::Timer timer;
		std::cout << scale << "次Push()，";
		for (int i = 0; i < scale; ++i)
		{
			DLS.Push(i);
		}
		std::cout << scale << "次Top()，Pop()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			DLS.Top();
			DLS.Pop();
		}
	}
	std::cout << "-LinkedStack---------------------" << std::endl;
	{
		HAlgorithm::LinkedStack<int> LS;
		HUtil::Timer timer;
		std::cout << scale << "次Push()，";
		for (int i = 0; i < scale; ++i)
		{
			LS.Push(i);
		}
		std::cout << scale << "次Top()，Pop()：" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			LS.Top();
			LS.Pop();
		}
	}
}

void MazeTest()
{
	// 全开放的迷宫
	bool maze1[10][10];
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			maze1[i][j] = 0;
		}
	}
	// 全封闭的迷宫
	bool maze2[10][10];
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			maze2[i][j] = 1;
		}
	}
	// 不含回退的迷宫
	bool maze3[][10] = {
		{0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,1,0,0},
		{0,0,0,1,0,1,0,0,0,0},
		{0,1,0,1,0,1,0,1,1,0},
		{0,1,0,1,0,1,0,1,0,0},
		{0,1,1,1,0,1,0,1,0,1},
		{0,1,0,0,0,1,0,1,0,1},
		{0,1,0,1,1,1,0,1,0,0},
		{1,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,1,1,1,1,0,0},
	};
	// 含回退的迷宫
	bool maze4[][10] = {
		{0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,1,0,0},
		{0,0,0,1,1,1,0,0,0,0},
		{0,1,0,1,0,1,0,1,1,0},
		{0,1,0,1,0,1,0,1,0,0},
		{0,1,0,1,0,1,0,1,0,1},
		{0,1,0,0,0,1,0,1,0,1},
		{0,1,0,1,1,1,0,1,0,0},
		{1,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,1,1,1,1,0,0},
	};

	HAlgorithm::HMaze::SolveMaze(maze1, 10);
	HAlgorithm::HMaze::SolveMaze(maze2, 10);
	HAlgorithm::HMaze::SolveMaze(maze3, 10);
	HAlgorithm::HMaze::SolveMaze(maze4, 10);
}

void HuffmanCompressionTest()
{
	std::cout << "文本压缩工具 v0.1\n" << std::endl;
	char compress;
	std::cout << "压缩or解压？(y/n)" << std::endl;
	std::cin >> compress;
	std::cin.get();
	
	std::string inFilePath, outFilePath;
	if (compress == 'y')
	{
		std::cout << "请输入要压缩的文件路径：" << std::endl;
		std::getline(std::cin, inFilePath);
		std::cout << "请输入压缩完的文件路径(内容为空则默认使用上个路径)：" << std::endl;
		std::getline(std::cin, outFilePath);
		if (outFilePath == "")
		{
			outFilePath = inFilePath;
		}

		std::cout << "开始压缩......" << std::endl;
		HAlgorithm::HHuffmanCoding::Compress(inFilePath, outFilePath);
	}
	else
	{
		std::cout << "请输入要解压的文件路径：" << std::endl;
		std::getline(std::cin, inFilePath);
		std::cout << "请输入解压完的文件路径(内容为空则默认使用上个路径)：" << std::endl;
		std::getline(std::cin, outFilePath);
		if (outFilePath == "")
		{
			outFilePath = inFilePath;
		}

		std::cout << "开始解压......" << std::endl;
		HAlgorithm::HHuffmanCoding::Decompress(inFilePath, outFilePath);
	}
}
