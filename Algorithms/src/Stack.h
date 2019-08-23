#pragma once

#include "LinearList.h"

namespace HAlgorithm {

	template <typename T>
	class Stack
	{
	public:
		virtual ~Stack() {}

		virtual bool Empty() const = 0;
		virtual int Size() const = 0;
		virtual T& Top() const = 0;
		virtual void Pop() = 0;
		virtual void Push(const T& element) = 0;
	};

	template <typename T>
	class DerivedArrayStack : private ArrayList<T>, public Stack<T>
	{
	public:
		DerivedArrayStack(int initialCapacity = 10)
			: ArrayList<T>(initialCapacity) {}

		virtual bool Empty() const override { return ArrayList<T>::Empty(); }
		virtual int Size() const override { return ArrayList<T>::Size(); }
		virtual T& Top() const override;
		virtual void Pop() override;
		virtual void Push(const T& element);
		
	};

	template<typename T>
	T& DerivedArrayStack<T>::Top() const
	{
		if (ArrayList<T>::Empty())
		{
			throw std::exception("Trying to get the top of an empty stack!");
		}

		return ArrayList<T>::Get(ArrayList<T>::Size() - 1);
	}

	template<typename T>
	void DerivedArrayStack<T>::Pop()
	{
		if (ArrayList<T>::Empty())
		{
			throw std::exception("Trying to pop an element of an empty stack!");
		}

		ArrayList<T>::Erase(ArrayList<T>::Size() - 1);
	}

	template<typename T>
	void DerivedArrayStack<T>::Push(const T& element)
	{
		ArrayList<T>::Insert(ArrayList<T>::Size(), element);
	}

	template <typename T>
	class ArrayStack : public Stack<T>
	{
	public:
		ArrayStack(int initialCapacity = 10);
		virtual ~ArrayStack() { delete[] m_Element; }

		virtual bool Empty() const override { return m_StackTop == -1; }
		virtual int Size() const override { return m_StackTop + 1; }
		virtual T& Top() const override;
		virtual void Pop() override;
		virtual void Push(const T& element) override;
		virtual void Output(std::ostream& out, const char* deli = " ") const;

	private:
		T* m_Element;
		int m_StackTop;
		int m_ArraySize;
	};

	template<typename T>
	ArrayStack<T>::ArrayStack(int initialCapacity)
	{
		if (initialCapacity < 1)
		{
			std::stringstream ss;
			ss << "Initial capacity (= " << initialCapacity << ") must be > 0!";
			throw std::invalid_argument(ss.str());
		}

		m_StackTop = -1;
		m_ArraySize = initialCapacity;
		m_Element = new T[m_ArraySize];
	}

	template<typename T>
	T& ArrayStack<T>::Top() const
	{
		if (m_StackTop == -1)
		{
			throw std::exception("Trying to get the top of an empty stack!");
		}

		return m_Element[m_StackTop];
	}

	template<typename T>
	void ArrayStack<T>::Pop()
	{
		if (m_StackTop == -1)
		{
			throw std::exception("Trying to pop an element of an empty stack!");
		}

		// 手动调用析构函数
		m_Element[m_StackTop--].~T();
	}

	template<typename T>
	void ArrayStack<T>::Push(const T& element)
	{
		// 加倍容量
		if (m_StackTop == m_ArraySize - 1)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Element, m_Element + m_ArraySize, temp);
			delete[] m_Element;
			m_Element = temp;
			m_ArraySize *= 2;
		}

		m_Element[++m_StackTop] = element;
	}

	template<typename T>
	void ArrayStack<T>::Output(std::ostream& out, const char* deli) const
	{
		std::copy(m_Element, m_Element + m_StackTop + 1, std::ostream_iterator<T>(out, deli));
	}

	template <typename T>
	class DerivedLinkedStack : private Chain<T>, public Stack<T>
	{
	public:
		DerivedLinkedStack(int initialCapacity = 10)
			: Chain<T>() {}

		virtual bool Empty() const override { return Chain<T>::Empty(); }
		virtual int Size() const override { return Chain<T>::Size(); }
		virtual T& Top() const override;
		virtual void Pop() override;
		virtual void Push(const T& element);

	};

	template<typename T>
	T& DerivedLinkedStack<T>::Top() const
	{
		if (Chain<T>::Empty())
		{
			throw std::exception("Trying to get the top of an empty stack!");
		}

		return Chain<T>::Get(0);
	}

	template<typename T>
	void DerivedLinkedStack<T>::Pop()
	{
		if (Chain<T>::Empty())
		{
			throw std::exception("Trying to pop an element of an empty stack!");
		}

		Chain<T>::Erase(0);
	}

	template<typename T>
	void DerivedLinkedStack<T>::Push(const T& element)
	{
		Chain<T>::Insert(0, element);
	}

	template <typename T>
	class LinkedStack : public Stack<T>
	{
	public:
		LinkedStack()
			: m_StackTop(nullptr)
			, m_StackSize(0) {}
		virtual ~LinkedStack();

		virtual bool Empty() const override { return m_StackSize == 0; }
		virtual int Size() const override { return m_StackSize; }
		virtual T& Top() const override;
		virtual void Pop() override;
		virtual void Push(const T& element) override;

	private:
		/** 链表的左端作为栈顶 */
		ChainNode<T>* m_StackTop;
		int m_StackSize;
	};

	template<typename T>
	LinkedStack<T>::~LinkedStack()
	{
		while (m_StackTop)
		{
			ChainNode<T>* nextNode = m_StackTop->next;
			delete m_StackTop;
			m_StackTop = nextNode;
		}
	}

	template<typename T>
	T& LinkedStack<T>::Top() const
	{
		if (m_StackSize == 0)
		{
			throw std::exception("Trying to get the top of an empty stack!");
		}

		return m_StackTop->element;
	}

	template<typename T>
	void LinkedStack<T>::Pop()
	{
		if (m_StackSize == 0)
		{
			throw std::exception("Trying to pop an element of an empty stack!");
		}

		ChainNode<T>* nextNode = m_StackTop->next;
		delete m_StackTop;
		m_StackTop = nextNode;
		m_StackSize--;
	}

	template<typename T>
	void LinkedStack<T>::Push(const T& element)
	{
		m_StackTop = new ChainNode<T>(element, m_StackTop);
		m_StackSize++;
	}

}
