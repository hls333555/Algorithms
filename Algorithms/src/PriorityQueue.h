#pragma once

#include <iostream>

namespace HAlgorithm {

	template <typename T>
	class MaxPriorityQueue
	{
	public:
		virtual ~MaxPriorityQueue() {}

		virtual bool Empty() const = 0;
		virtual int Size() const = 0;
		virtual T& Top() const = 0;
		virtual void Pop() = 0;
		virtual void Push(const T& element) = 0;
	};

	template <typename T>
	class MaxHeap : public MaxPriorityQueue<T>
	{
	public:
		MaxHeap(int initialCapacity = 10);
		MaxHeap(T a[], int n);
		virtual ~MaxHeap() { delete m_Heap; }

		virtual bool Empty() const override { return m_HeapSize == 0; }
		virtual int Size() const override { return m_HeapSize; }
		virtual T& Top() const override;
		virtual void Pop() override;
		virtual void Push(const T& element) override;

	private:
		/** �������ѡ� */
		void Construct();

	private:
		T* m_Heap;
		int m_ArraySize;
		int m_HeapSize;

	};

	template<typename T>
	MaxHeap<T>::MaxHeap(int initialCapacity)
	{
		m_ArraySize = initialCapacity;
		m_HeapSize = 0;
		m_Heap = new T[m_ArraySize];
	}

	template<typename T>
	MaxHeap<T>::MaxHeap(T a[], int n)
	{
		m_HeapSize = n;
		m_ArraySize = m_HeapSize + 1;
		m_Heap = new T[m_ArraySize];
		std::copy(a, a + n, m_Heap + 1);

		Construct();
	}

	template<typename T>
	T& MaxHeap<T>::Top() const
	{
		if (m_HeapSize == 0)
		{
			throw std::exception("Trying to get the top of an empty heap!");
		}

		return m_Heap[1];
	}

	template<typename T>
	void MaxHeap<T>::Pop()
	{
		if (m_HeapSize == 0)
		{
			throw std::exception("Trying to pop an element of an empty heap!");
		}

		// ɾ�����Ԫ��
		m_Heap[1].~T();

		// ɾ�����һ��Ԫ��
		T lastElement = m_Heap[m_HeapSize--];

		// �Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ�Ҳ���λ��
		int currentNode = 1, childNode = 2;
		while (childNode <= m_HeapSize)
		{
			if (m_Heap[childNode] < m_Heap[childNode + 1])
			{
				// childNode��ǽϴ����Ԫ��
				childNode++;
			}

			// lastElement��С����������Ԫ�أ����Է������ǵĸ�Ԫ��λ��
			if (lastElement >= m_Heap[childNode])
				break;

			// ��Ԫ������
			m_Heap[currentNode] = m_Heap[childNode];
			// �����ƶ�һ��
			currentNode = childNode;
			childNode *= 2;

		}

		m_Heap[currentNode] = lastElement;
	}

	template<typename T>
	void MaxHeap<T>::Push(const T& element)
	{
		// �ӱ�������ע������0������m_HeapSize��
		if (m_HeapSize == m_ArraySize - 1)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Heap, m_Heap + m_ArraySize, temp);
			// ɾ��������
			delete[] m_Heap;
			m_Heap = temp;
			m_ArraySize *= 2;
		}

		// currentNode����Ҷ�������ƶ�
		int currentNode = ++m_HeapSize;
		while (currentNode != 1 && element > m_Heap[currentNode / 2])
		{
			// Ԫ��������
			m_Heap[currentNode] = m_Heap[currentNode / 2];
			// currentNode������
			currentNode /= 2;
		}

		m_Heap[currentNode] = element;
	}

	template<typename T>
	void MaxHeap<T>::Construct()
	{
		// �����һ�����к���Ԫ�صĽڵ㿪ʼ��ʹÿ����rootNodeΪ���ڵ��������Ϊ�����
		for (int rootNode = m_HeapSize / 2; rootNode >= 1; --rootNode)
		{
			const T currentElement = m_Heap[rootNode];

			int childNode = rootNode * 2;
			while (childNode <= m_HeapSize)
			{
				// ��ֹchildNode + 1Խ��
				if (childNode < m_HeapSize
					&& m_Heap[childNode] < m_Heap[childNode + 1])
				{
					// childNode��ǽϴ����Ԫ��
					childNode++;
				}

				// currentElement��С����������Ԫ�أ����Է������ǵĸ�Ԫ��λ��
				if (currentElement >= m_Heap[childNode])
					break;

				// ��Ԫ������
				m_Heap[childNode / 2] = m_Heap[childNode];
				// �����ƶ�һ��
				childNode *= 2;
			}

			m_Heap[childNode / 2] = currentElement;
		}
	}

	template <typename T>
	class MinHeap : public MaxPriorityQueue<T>
	{
	public:
		MinHeap(int initialCapacity = 10);
		MinHeap(T a[], int n);
		virtual ~MinHeap() { delete m_Heap; }

		virtual bool Empty() const override { return m_HeapSize == 0; }
		virtual int Size() const override { return m_HeapSize; }
		virtual T& Top() const override;
		virtual void Pop() override;
		virtual void Push(const T& element) override;

	private:
		/** �������ѡ� */
		void Construct();

	private:
		T* m_Heap;
		int m_ArraySize;
		int m_HeapSize;

	};

	template<typename T>
	MinHeap<T>::MinHeap(int initialCapacity)
	{
		m_ArraySize = initialCapacity;
		m_HeapSize = 0;
		m_Heap = new T[m_ArraySize];
	}

	template<typename T>
	MinHeap<T>::MinHeap(T a[], int n)
	{
		m_HeapSize = n;
		m_ArraySize = m_HeapSize + 1;
		m_Heap = new T[m_ArraySize];
		std::copy(a, a + n, m_Heap + 1);

		Construct();
	}

	template<typename T>
	T& MinHeap<T>::Top() const
	{
		if (m_HeapSize == 0)
		{
			throw std::exception("Trying to get the top of an empty heap!");
		}

		return m_Heap[1];
	}

	template<typename T>
	void MinHeap<T>::Pop()
	{
		if (m_HeapSize == 0)
		{
			throw std::exception("Trying to pop an element of an empty heap!");
		}

		// ɾ����СԪ��
		m_Heap[1].~T();

		// ɾ�����һ��Ԫ��
		T lastElement = m_Heap[m_HeapSize--];

		// �Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ�Ҳ���λ��
		int currentNode = 1, childNode = 2;
		while (childNode <= m_HeapSize)
		{
			if (m_Heap[childNode] > m_Heap[childNode + 1])
			{
				// childNode��ǽ�С����Ԫ��
				childNode++;
			}

			// lastElement��������������Ԫ�أ����Է������ǵĸ�Ԫ��λ��
			if (lastElement <= m_Heap[childNode])
				break;

			// ��Ԫ������
			m_Heap[currentNode] = m_Heap[childNode];
			// �����ƶ�һ��
			currentNode = childNode;
			childNode *= 2;

		}

		m_Heap[currentNode] = lastElement;
	}

	template<typename T>
	void MinHeap<T>::Push(const T& element)
	{
		// �ӱ�������ע������0������m_HeapSize��
		if (m_HeapSize == m_ArraySize - 1)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Heap, m_Heap + m_ArraySize, temp);
			// ɾ��������
			delete[] m_Heap;
			m_Heap = temp;
			m_ArraySize *= 2;
		}

		// currentNode����Ҷ�������ƶ�
		int currentNode = ++m_HeapSize;
		while (currentNode != 1 && element < m_Heap[currentNode / 2])
		{
			// Ԫ��������
			m_Heap[currentNode] = m_Heap[currentNode / 2];
			// currentNode������
			currentNode /= 2;
		}

		m_Heap[currentNode] = element;
	}

	template<typename T>
	void MinHeap<T>::Construct()
	{
		// �����һ�����к���Ԫ�صĽڵ㿪ʼ��ʹÿ����rootNodeΪ���ڵ��������ΪС����
		for (int rootNode = m_HeapSize / 2; rootNode >= 1; --rootNode)
		{
			const T currentElement = m_Heap[rootNode];

			int childNode = rootNode * 2;
			while (childNode <= m_HeapSize)
			{
				// ��ֹchildNode + 1Խ��
				if (childNode < m_HeapSize
					&& m_Heap[childNode] > m_Heap[childNode + 1])
				{
					// childNode��ǽ�С����Ԫ��
					childNode++;
				}

				// currentElement��������������Ԫ�أ����Է������ǵĸ�Ԫ��λ��
				if (currentElement <= m_Heap[childNode])
					break;

				// ��Ԫ������
				m_Heap[childNode / 2] = m_Heap[childNode];
				// �����ƶ�һ��
				childNode *= 2;
			}

			m_Heap[childNode / 2] = currentElement;
		}
	}

}
