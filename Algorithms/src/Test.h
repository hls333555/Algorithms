#pragma once

#include "Timer.h"

#include "LinearList.h"

void LinearListTest(int scale = 50000)
{
	srand(time(nullptr));

	std::cout << "-ArrayList---------------------" << std::endl;
	{
		HAlgorithm::ArrayList<int> a(scale);
		std::cout << scale << "��Get()��" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			a.Insert(a.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			a.Get(i);
		}
	}
	{
		HAlgorithm::ArrayList<int> a(scale);
		std::cout << scale << "��Find()��" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			a.Insert(a.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			a.Find(a.Get(i));
		}
	}
	{
		HAlgorithm::ArrayList<int> a;
		std::cout << scale << "��Insert()-�����������ݣ���" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			a.Insert(a.Size(), i);
		}
	}
	{
		HAlgorithm::ArrayList<int> a(scale);
		std::cout << scale << "��Insert()-��������" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			a.Insert(a.Size(), i);
		}
	}
	{
		HAlgorithm::ArrayList<int> a;
		std::cout << scale << "��Insert()-ƽ�����������������ݣ���" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = a.Size() ? a.Size() : 1;
			a.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::ArrayList<int> a(scale);
		std::cout << scale << "��Insert()-ƽ��������������" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = a.Size() ? a.Size() : 1;
			a.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::ArrayList<int> a;
		std::cout << scale << "��Insert()-���������ݣ���" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			a.Insert(0, i);
		}
	}
	{
		HAlgorithm::ArrayList<int> a(scale);
		std::cout << scale << "��Insert()-������" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			a.Insert(0, i);
		}
	}
	std::cout << "-VectorList---------------------" << std::endl;
	{
		HAlgorithm::VectorList<int> b(scale);
		std::cout << scale << "��Get()��" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			b.Insert(b.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			b.Get(i);
		}
	}
	{
		HAlgorithm::VectorList<int> b(scale);
		std::cout << scale << "��Find()��" << std::endl;
		for (int i = 0; i < scale; ++i)
		{
			b.Insert(b.Size(), i);
		}
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			b.Find(b.Get(i));
		}
	}
	{
		HAlgorithm::VectorList<int> b;
		std::cout << scale << "��Insert()-�����������ݣ���" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			b.Insert(b.Size(), i);
		}
	}
	{
		HAlgorithm::VectorList<int> b(scale);
		std::cout << scale << "��Insert()-��������" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			b.Insert(b.Size(), i);
		}
	}
	{
		HAlgorithm::VectorList<int> b;
		std::cout << scale << "��Insert()-ƽ�����������������ݣ���" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = b.Size() ? b.Size() : 1;
			b.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::VectorList<int> b(scale);
		std::cout << scale << "��Insert()-ƽ��������������" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			int size = b.Size() ? b.Size() : 1;
			b.Insert(rand() % size, i);
		}
	}
	{
		HAlgorithm::VectorList<int> b;
		std::cout << scale << "��Insert()-���������ݣ���" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			b.Insert(0, i);
		}
	}
	{
		HAlgorithm::VectorList<int> b(scale);
		std::cout << scale << "��Insert()-������" << std::endl;
		HUtil::Timer timer;
		for (int i = 0; i < scale; ++i)
		{
			b.Insert(0, i);
		}
	}
}
