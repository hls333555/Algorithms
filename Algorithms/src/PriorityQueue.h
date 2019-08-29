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
		/** 构建最大堆。 */
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

		// 删除最大元素
		m_Heap[1].~T();

		// 删除最后一个元素
		T lastElement = m_Heap[m_HeapSize--];

		// 从根开始，为最后一个元素寻找插入位置
		int currentNode = 1, childNode = 2;
		while (childNode <= m_HeapSize)
		{
			if (m_Heap[childNode] < m_Heap[childNode + 1])
			{
				// childNode标记较大的子元素
				childNode++;
			}

			// lastElement不小于这两个子元素，可以放在它们的父元素位置
			if (lastElement >= m_Heap[childNode])
				break;

			// 子元素上移
			m_Heap[currentNode] = m_Heap[childNode];
			// 向下移动一层
			currentNode = childNode;
			childNode *= 2;

		}

		m_Heap[currentNode] = lastElement;
	}

	template<typename T>
	void MaxHeap<T>::Push(const T& element)
	{
		// 加倍容量，注意索引0不算在m_HeapSize里
		if (m_HeapSize == m_ArraySize - 1)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Heap, m_Heap + m_ArraySize, temp);
			// 删除旧数组
			delete[] m_Heap;
			m_Heap = temp;
			m_ArraySize *= 2;
		}

		// currentNode从新叶子向上移动
		int currentNode = ++m_HeapSize;
		while (currentNode != 1 && element > m_Heap[currentNode / 2])
		{
			// 元素向下移
			m_Heap[currentNode] = m_Heap[currentNode / 2];
			// currentNode向上移
			currentNode /= 2;
		}

		m_Heap[currentNode] = element;
	}

	template<typename T>
	void MaxHeap<T>::Construct()
	{
		// 从最后一个具有孩子元素的节点开始，使每个以rootNode为根节点的子树成为大根堆
		for (int rootNode = m_HeapSize / 2; rootNode >= 1; --rootNode)
		{
			const T currentElement = m_Heap[rootNode];

			int childNode = rootNode * 2;
			while (childNode <= m_HeapSize)
			{
				// 防止childNode + 1越界
				if (childNode < m_HeapSize
					&& m_Heap[childNode] < m_Heap[childNode + 1])
				{
					// childNode标记较大的子元素
					childNode++;
				}

				// currentElement不小于这两个子元素，可以放在它们的父元素位置
				if (currentElement >= m_Heap[childNode])
					break;

				// 子元素上移
				m_Heap[childNode / 2] = m_Heap[childNode];
				// 向下移动一层
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
		/** 构建最大堆。 */
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

		// 删除最小元素
		m_Heap[1].~T();

		// 删除最后一个元素
		T lastElement = m_Heap[m_HeapSize--];

		// 从根开始，为最后一个元素寻找插入位置
		int currentNode = 1, childNode = 2;
		while (childNode <= m_HeapSize)
		{
			if (m_Heap[childNode] > m_Heap[childNode + 1])
			{
				// childNode标记较小的子元素
				childNode++;
			}

			// lastElement不大于这两个子元素，可以放在它们的父元素位置
			if (lastElement <= m_Heap[childNode])
				break;

			// 子元素上移
			m_Heap[currentNode] = m_Heap[childNode];
			// 向下移动一层
			currentNode = childNode;
			childNode *= 2;

		}

		m_Heap[currentNode] = lastElement;
	}

	template<typename T>
	void MinHeap<T>::Push(const T& element)
	{
		// 加倍容量，注意索引0不算在m_HeapSize里
		if (m_HeapSize == m_ArraySize - 1)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Heap, m_Heap + m_ArraySize, temp);
			// 删除旧数组
			delete[] m_Heap;
			m_Heap = temp;
			m_ArraySize *= 2;
		}

		// currentNode从新叶子向上移动
		int currentNode = ++m_HeapSize;
		while (currentNode != 1 && element < m_Heap[currentNode / 2])
		{
			// 元素向下移
			m_Heap[currentNode] = m_Heap[currentNode / 2];
			// currentNode向上移
			currentNode /= 2;
		}

		m_Heap[currentNode] = element;
	}

	template<typename T>
	void MinHeap<T>::Construct()
	{
		// 从最后一个具有孩子元素的节点开始，使每个以rootNode为根节点的子树成为小根堆
		for (int rootNode = m_HeapSize / 2; rootNode >= 1; --rootNode)
		{
			const T currentElement = m_Heap[rootNode];

			int childNode = rootNode * 2;
			while (childNode <= m_HeapSize)
			{
				// 防止childNode + 1越界
				if (childNode < m_HeapSize
					&& m_Heap[childNode] > m_Heap[childNode + 1])
				{
					// childNode标记较小的子元素
					childNode++;
				}

				// currentElement不大于这两个子元素，可以放在它们的父元素位置
				if (currentElement <= m_Heap[childNode])
					break;

				// 子元素上移
				m_Heap[childNode / 2] = m_Heap[childNode];
				// 向下移动一层
				childNode *= 2;
			}

			m_Heap[childNode / 2] = currentElement;
		}
	}

}
