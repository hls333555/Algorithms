#pragma once

#include <sstream>

#include "LinearList.h"

namespace HAlgorithm {

	template <typename T>
	class Queue
	{
	public:
		virtual ~Queue() {}

		virtual bool Empty() const = 0;
		virtual int Size() const = 0;
		virtual T& Front() const = 0;
		virtual T& Back() const = 0;
		virtual void Pop() = 0;
		virtual void Push(const T& element) = 0;
	};

	/** 环形队列 */
	template <typename T>
	class ArrayQueue : public Queue<T>
	{
	public:
		ArrayQueue(int initialCapacity = 10);
		virtual ~ArrayQueue() { delete[] m_element; }

		virtual bool Empty() const override { return m_Front == m_Back; }
		virtual int Size() const override { return m_Back > m_Front ? m_Back - m_Front : m_Back + m_ArraySize - m_Front; }
		virtual T& Front() const override;
		virtual T& Back() const override;
		virtual void Pop() override;
		virtual void Push(const T& element) override;

	private:
		/** m_Front指向首元素的前一个位置，m_Back指向尾元素，这样当二者相等时表示队列为空 */
		int m_Front, m_Back;
		int m_ArraySize;
		T* m_element;
	};

	template<typename T>
	ArrayQueue<T>::ArrayQueue(int initialCapacity)
	{
		if (initialCapacity < 1)
		{
			std::stringstream ss;
			ss << "Initial capacity (= " << initialCapacity << ") must be > 0!";
			throw std::invalid_argument(ss.str());
		}

		m_ArraySize = initialCapacity;
		m_element = new T[m_ArraySize];
		m_Front = m_Back = 0;
	}

	template<typename T>
	T& ArrayQueue<T>::Front() const
	{
		if (m_Front == m_Back)
		{
			throw std::exception("Trying to get the front of an empty queue!");
		}

		int start = (m_Front + 1) % m_ArraySize;
		return m_element[start];
	}

	template<typename T>
	T& ArrayQueue<T>::Back() const
	{
		if (m_Front == m_Back)
		{
			throw std::exception("Trying to get the back of an empty queue!");
		}

		return m_element[m_Back];
	}

	template<typename T>
	void ArrayQueue<T>::Pop()
	{
		if (m_Front == m_Back)
		{
			throw std::exception("Trying to pop an element of an empty queue!");
		}

		m_Front = (m_Front + 1) % m_ArraySize;
		// 手动调用析构函数
		m_element[m_Front].~T();
	}

	template<typename T>
	void ArrayQueue<T>::Push(const T& element)
	{
		// 当还剩一个空位置时加倍容量防止m_Front==m_Back，因为此时意思是队列为空
		if ((m_Back + 1) % m_ArraySize == m_Front)
		{
			T* temp = new T[m_ArraySize * 2];
			int start = (m_Front + 1) % m_ArraySize;
			// 队列未形成环
			if (m_Back > m_Front)
			{
				std::copy(m_element + start, m_element + m_ArraySize, temp);
			}
			// 队列形成环
			else
			{
				std::copy(m_element + start, m_element + m_ArraySize, temp);
				std::copy(m_element, m_element + m_Back + 1, temp + m_ArraySize - start);
			}
			// 复制完后首元素在数组头，m_Front在数组尾
			m_Front = m_ArraySize * 2 - 1;
			// 队列长度为m_ArraySize-1
			m_Back = m_ArraySize - 2;
			delete[] m_element;
			m_element = temp;
			m_ArraySize *= 2;
		}

		m_Back = (m_Back + 1) % m_ArraySize;
		m_element[m_Back] = element;
	}

	template <typename T>
	class LinkedQueue : public Queue<T>
	{
	public:
		LinkedQueue()
			: m_Front(nullptr), m_Back(nullptr)
			, m_QueueSize(0) {}
		virtual ~LinkedQueue();

		virtual bool Empty() const override { return m_Front == nullptr; }
		virtual int Size() const override { return m_QueueSize; }
		virtual T& Front() const override;
		virtual T& Back() const override;
		virtual void Pop() override;
		virtual void Push(const T& element) override;

	private:
		ChainNode<T>* m_Front, *m_Back;
		int m_QueueSize;

	};

	template<typename T>
	LinkedQueue<T>::~LinkedQueue()
	{
		while (m_Front)
		{
			ChainNode<T>* nextNode = m_Front->next;
			delete m_Front;
			m_Front = nextNode;
		}
	}

	template<typename T>
	T& LinkedQueue<T>::Front() const
	{
		if (m_QueueSize == 0)
		{
			throw std::exception("Trying to get the front of an empty queue!");
		}

		return m_Front->element;
	}

	template<typename T>
	T& LinkedQueue<T>::Back() const
	{
		if (m_QueueSize == 0)
		{
			throw std::exception("Trying to get the back of an empty queue!");
		}

		return m_Back->element;
	}

	template<typename T>
	void LinkedQueue<T>::Pop()
	{
		if (m_QueueSize == 0)
		{
			throw std::exception("Trying to pop the front of an empty queue!");
		}

		ChainNode<T>* nextNode = m_Front->next;
		delete m_Front;
		m_Front = nextNode;
		m_QueueSize--;
	}

	template<typename T>
	void LinkedQueue<T>::Push(const T& element)
	{
		ChainNode<T>* nextNode = new ChainNode<T>(element);

		if (m_QueueSize == 0)
		{
			m_Front = nextNode;
		}
		else
		{
			m_Back->next = nextNode;
		}
		m_Back = nextNode;
		m_QueueSize++;
	}

}
