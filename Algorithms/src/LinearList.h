#pragma once

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

namespace HAlgorithm {

	template <typename T>
	class LinearList
	{
	public:
		virtual ~LinearList() {}

		virtual bool Empty() const = 0;
		virtual int Size() const = 0;
		virtual T& Get(int index) const = 0;
		virtual int Find(const T& element) const = 0;
		virtual void Insert(int index, const T& element) = 0;
		virtual void Erase(int index) = 0;
		virtual void Output(std::ostream& out) const = 0;
	};

	template <typename T>
	class ArrayList : public LinearList<T>
	{
		class Iterator
		{
		public:
			typedef struct bidirectional_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

			Iterator(T* position = 0)
				: m_Position(position) {}

			T& operator*() const { return *m_Position; }
			T* operator->() const { return &*m_Position; }

			Iterator& operator++()
			{
				++m_Position;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator temp = *this;
				++m_Position;
				return temp;
			}
			Iterator& operator--()
			{
				--m_Position;
				return *this;
			}
			Iterator operator--(int)
			{
				Iterator temp = *this;
				--m_Position;
				return temp;
			}

			bool operator==(const Iterator& other) const { return m_Position == other.m_Position; }
			bool operator!=(const Iterator& other) const { return m_Position != other.m_Position; }

		private:
			T* m_Position;
		};

	public:
		ArrayList(int initialCapacity = 10);
		ArrayList(const ArrayList& other);
		virtual ~ArrayList() { delete[] m_Element; }

		virtual bool Empty() const override { return m_ListSize == 0; }
		virtual int Size() const override { return m_ListSize; }
		virtual T& Get(int index) const override;
		virtual int Find(const T& element) const override;
		virtual void Insert(int index, const T& element) override;
		virtual void Erase(int index) override;
		virtual void Output(std::ostream& out) const override;

		int Capacity() const { return m_ArraySize; }
		bool IsValidIndex(int index) const { return index >= 0 && index < m_ListSize; }

		Iterator Begin() { return Iterator(m_Element); }
		Iterator End() { return Iterator(m_Element + m_ListSize); }

	private:
		void CheckIndex(int index) const;

	protected:
		T* m_Element;
		int m_InitialCapacity;
		int m_ArraySize;
		int m_ListSize;
	};

	template<typename T>
	ArrayList<T>::ArrayList(int initialCapacity)
		: m_InitialCapacity(initialCapacity)
	{
		if (initialCapacity < 1)
		{
			std::stringstream ss;
			ss << "Initial capacity (= " << initialCapacity << ") must be > 0!";
			throw std::invalid_argument(ss.str());
		}

		m_ArraySize = initialCapacity;
		m_Element = new T[m_ArraySize];
		m_ListSize = 0;
	}

	template<typename T>
	ArrayList<T>::ArrayList(const ArrayList& other)
	{
		m_ArraySize = other.m_ArraySize;
		m_ListSize = other.m_ListSize;
		m_Element = new T[m_ArraySize];
		std::copy(other.m_Element, other.m_Element + m_ListSize, m_Element);
	}

	template<typename T>
	T& ArrayList<T>::Get(int index) const
	{
		CheckIndex(index);
		return m_Element[index];
	}

	template<typename T>
	int ArrayList<T>::Find(const T& element) const
	{
		// Be aware here uses a subtraction
		int foundIndex = (int)(std::find(m_Element, m_Element + m_ListSize, element) - m_Element);
		if (foundIndex == m_ListSize)
		{
			return -1;
		}
		return foundIndex;
	}

	template<typename T>
	void ArrayList<T>::Insert(int index, const T& element)
	{
		if (index < 0 || index > m_ListSize)
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << m_ListSize << "]!";
			throw std::invalid_argument(ss.str());
		}

		// 加倍容量
		if (m_ListSize == m_ArraySize)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Element, m_Element + m_ArraySize, temp);
			// 删除旧数组
			delete[] m_Element;
			m_Element = temp;
			m_ArraySize *= 2;
		}

		std::copy_backward(m_Element + index, m_Element + m_ListSize, m_Element + m_ListSize + 1);
		m_Element[index] = element;
		m_ListSize++;
	}

	template<typename T>
	void ArrayList<T>::Erase(int index)
	{
		CheckIndex(index);
		std::copy(m_Element + index + 1, m_Element + m_ListSize, m_Element + index);
		// 手动调用析构函数
		m_Element[--m_ListSize].~T();

		// 缩小容量
		if (m_ListSize < m_ArraySize / 4)
		{
			int newSize = std::max(m_InitialCapacity, m_ArraySize / 2);
			T* temp = new T[newSize];
			std::copy(m_Element, m_Element + newSize, temp);
			// 删除旧数组
			delete[] m_Element;
			m_Element = temp;
			m_ArraySize = newSize;
		}
	}

	template<typename T>
	void ArrayList<T>::Output(std::ostream& out) const
	{
		std::copy(m_Element, m_Element + m_ListSize, std::ostream_iterator<T>(out, " "));
	}

	template<typename T>
	void ArrayList<T>::CheckIndex(int index) const
	{
		if (!IsValidIndex(index))
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << m_ListSize << ")!";
			throw std::invalid_argument(ss.str());
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const ArrayList<T>& x)
	{
		x.Output(out);
		return out;
	}

	template <typename T>
	class VectorList : public LinearList<T>
	{
	public:
		VectorList(int initialCapacity = 10);
		VectorList(const VectorList& other);
		virtual ~VectorList() { delete m_Element; }

		virtual bool Empty() const override { return m_Element->empty(); }
		virtual int Size() const override { return (int)m_Element->size(); }
		virtual T& Get(int index) const override;
		virtual int Find(const T& element) const override;
		virtual void Insert(int index, const T& element) override;
		virtual void Erase(int index) override;
		virtual void Output(std::ostream& out) const override;

		int Capacity() const { return (int)m_Element->capacity(); }
		bool IsValidIndex(int index) const { return index >= 0 && index < Size(); }

		typename std::vector<T>::iterator Begin() { return m_Element->begin(); }
		typename std::vector<T>::iterator End() { return m_Element->end(); }

	private:
		void CheckIndex(int index) const;

	private:
		std::vector<T>* m_Element;
	};

	template<typename T>
	VectorList<T>::VectorList(int initialCapacity)
	{
		if (initialCapacity < 1)
		{
			std::stringstream ss;
			ss << "Initial capacity (= " << initialCapacity << ") must be > 0!";
			throw std::invalid_argument(ss.str());
		}

		m_Element = new std::vector<T>;
		m_Element->reserve(initialCapacity);
	}

	template<typename T>
	VectorList<T>::VectorList(const VectorList& other)
	{
		m_Element = new std::vector<T>(*other.m_Element);
	}

	template<typename T>
	T& VectorList<T>::Get(int index) const
	{
		CheckIndex(index);
		return (*m_Element)[index];
	}

	template<typename T>
	int VectorList<T>::Find(const T& element) const
	{
		auto foundItr = std::find(m_Element->begin(), m_Element->end(), element);
		if (foundItr == m_Element->end())
		{
			return -1;
		}
		return (int)(foundItr - m_Element->begin());
	}

	template<typename T>
	void VectorList<T>::Insert(int index, const T& element)
	{
		if (index < 0 || index > Size())
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << Size() << "]!";
			throw std::invalid_argument(ss.str());
		}

		m_Element->insert(m_Element->begin() + index, element);

	}

	template<typename T>
	void VectorList<T>::Erase(int index)
	{
		CheckIndex(index);
		m_Element->erase(m_Element->begin() + index);
	}

	template<typename T>
	void VectorList<T>::Output(std::ostream& out) const
	{
		std::copy(m_Element->begin(), m_Element->end(), std::ostream_iterator<T>(out, " "));
	}

	template<typename T>
	void VectorList<T>::CheckIndex(int index) const
	{
		if (!IsValidIndex(index))
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << Size() << ")!";
			throw std::invalid_argument(ss.str());
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const VectorList<T>& x)
	{
		x.Output(out);
		return out;
	}

	template <typename T>
	struct ChainNode
	{
		T element;
		ChainNode<T>* next;

		ChainNode() {}
		ChainNode(const T& _element, ChainNode<T>* _next = nullptr)
			: element(_element), next(_next) {}
	};

	template <typename T>
	class Chain : public LinearList<T>
	{
		class Iterator
		{
			typedef struct forward_iterator_type iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

			Iterator(const ChainNode<T>& node = nullptr)
				: m_Node(node) {}

			T& operator*() { return m_Node->element; }
			T* operator->() { return &m_Node->element; }

			Iterator& operator++()
			{
				m_Node = m_Node->next;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator temp = *this;
				m_Node = m_Node->next;
				return temp;
			}

			bool operator==(const Iterator& other) { return m_Node == other.m_Node; }
			bool operator!=(const Iterator& other) { return m_Node != other.m_Node; }

		private:
			ChainNode<T>* m_Node;
		};

	public:
		Chain();
		Chain(const Chain<T>& other);
		~Chain();

		virtual bool Empty() const override { return m_ListSize == 0; }
		virtual int Size() const override { return m_ListSize; }
		virtual T& Get(int index) const override;
		virtual int Find(const T& element) const override;
		virtual void Insert(int index, const T& element) override;
		virtual void Erase(int index) override;
		virtual void Output(std::ostream& out) const override;

		bool IsValidIndex(int index) const { return index >= 0 && index < m_ListSize; }

		Iterator Begin() const { return Iterator(m_FirstNode); }
		Iterator End() const { return Iterator(nullptr); }

		void BinSort(int range);
		void RadixSort(int radix);

	private:
		void CheckIndex(int index) const;

	protected:
		ChainNode<T>* m_FirstNode;
		int m_InitialCapacity;
		int m_ListSize;
	};

	template<typename T>
	Chain<T>::Chain()
	{
		m_FirstNode = nullptr;
		m_ListSize = 0;
	}

	template<typename T>
	Chain<T>::Chain(const Chain<T>& other)
	{
		m_ListSize = other.m_ListSize;

		if (m_ListSize == 0)
		{
			m_FirstNode = nullptr;
			return;
		}

		// 存储当前要复制的节点
		ChainNode<T>* sourceNode = other.m_FirstNode;
		// 复制第一个节点
		m_FirstNode = new ChainNode<T>(sourceNode->element);
		// 更新下一个要复制的节点
		sourceNode = sourceNode->next;
		// 存储当前复制出的节点
		ChainNode<T>* targetNode = m_FirstNode;
		//循环复制余下的节点
		while (sourceNode)
		{
			ChainNode<T>* nextNode = new ChainNode<T>(sourceNode->element);
			targetNode->next = nextNode;
			sourceNode = sourceNode->next;
			targetNode = targetNode->next;
		}
		// 链表结束
		targetNode->next = nullptr;
	}

	template<typename T>
	Chain<T>::~Chain()
	{
		while (m_FirstNode)
		{
			ChainNode<T>* nextNode = m_FirstNode->next;
			delete m_FirstNode;
			m_FirstNode = nextNode;
		}
	}

	template<typename T>
	T& Chain<T>::Get(int index) const
	{
		CheckIndex(index);

		ChainNode<T>* currentNode = m_FirstNode;
		// 循环index次到达目标节点
		for (int i = 0; i < index; ++i)
		{
			currentNode = currentNode->next;
		}
		return currentNode->element;
	}

	template<typename T>
	int Chain<T>::Find(const T& element) const
	{
		ChainNode<T>* currentNode = m_FirstNode;
		int index = 0;
		while (currentNode && currentNode->element != element)
		{
			index++;
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			return -1;
		}
		return index;
	}

	template<typename T>
	void Chain<T>::Insert(int index, const T& element)
	{
		if (index < 0 || index > m_ListSize)
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << Size() << "]!";
			throw std::invalid_argument(ss.str());
		}

		if (index == 0)
		{
			// 在链表头插入
			m_FirstNode = new ChainNode<T>(element, m_FirstNode);
		}
		else
		{
			ChainNode<T>* currentNode = m_FirstNode;
			// 寻找新节点的前驱
			for (int i = 0; i < index - 1; ++i)
			{
				currentNode = currentNode->next;
			}
			// 在currentNode之后插入
			currentNode->next = new ChainNode<T>(element, currentNode->next);
		}
		m_ListSize++;
	}

	template<typename T>
	void Chain<T>::Erase(int index)
	{
		CheckIndex(index);

		ChainNode<T>* deleteNode;
		if (index == 0)
		{
			deleteNode = m_FirstNode;
			m_FirstNode = m_FirstNode->next;
		}
		else
		{
			ChainNode<T>* currentNode = m_FirstNode;
			// 寻找要删除节点的前驱
			for (int i = 0; i < index - 1; ++i)
			{
				currentNode = currentNode->next;
			}
			deleteNode = currentNode->next;
			currentNode->next = currentNode->next->next;
		}
		delete deleteNode;
		m_ListSize--;
	}

	template<typename T>
	void Chain<T>::Output(std::ostream& out) const
	{
		for (ChainNode<T>* currentNode = m_FirstNode; currentNode != nullptr; currentNode = currentNode->next)
		{
			out << currentNode->element << " ";
		}
	}

	/** 通过跟踪每一个箱子的首尾节点， 就可以在“子收集阶段”把箱子链接起来 */
	template<typename T>
	void Chain<T>::BinSort(int range)
	{
		ChainNode<T>** bottom, **top;
		bottom = new ChainNode<T>* [range + 1];
		top = new ChainNode<T>* [range + 1];
		for (int i = 0; i <= range; ++i)
		{
			bottom[i] = nullptr;
		}

		// 链表的节点分配给箱子
		for (; m_FirstNode != nullptr; m_FirstNode = m_FirstNode->next)
		{
			// 元素类型转换微int
			int bin = m_FirstNode->element;
			// 箱子为空
			if (bottom[bin] == nullptr)
			{
				bottom[bin] = top[bin] = m_FirstNode;
			}
			// 箱子不空
			else
			{
				top[bin]->next = m_FirstNode;
				top[bin] = m_FirstNode;
			}
		}

		// 用于连接各个箱子的节点
		ChainNode<T>* startNode = nullptr;
		// 把箱子中的节点收集到有序链表
		for (int bin = 0; bin <= range; ++bin)
		{
			// 箱子不空
			if (bottom[bin] != nullptr)
			{
				// 第一个非空箱子
				if (startNode == nullptr)
				{
					m_FirstNode = bottom[bin];
				}
				// 不是第一个非空箱子
				else
				{
					startNode->next = bottom[bin];
				}
				startNode = top[bin];
			}
		}
		// 链表结束
		if (startNode)
		{
			startNode->next = nullptr;
		}

		delete[] bottom;
		delete[] top;
	}

	template<typename T>
	void Chain<T>::RadixSort(int radix)
	{
		// TODO
	}

	template<typename T>
	void Chain<T>::CheckIndex(int index) const
	{
		if (!IsValidIndex(index))
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << m_ListSize << ")!";
			throw std::invalid_argument(ss.str());
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Chain<T>& x)
	{
		x.Output(out);
		return out;
	}

	template<typename T>
	class ExtendedChain : public Chain<T>
	{
	public:
		ExtendedChain();
		ExtendedChain(const ExtendedChain<T>& other);
		~ExtendedChain();

		virtual void Insert(int index, const T& element) override;
		virtual void Erase(int index) override;

		virtual void Clear();
		virtual void PushBack(const T& element);

	private:
		/** 用于快速在末尾插入 */
		ChainNode<T>* m_LastNode;
	};

	template<typename T>
	ExtendedChain<T>::ExtendedChain()
		: Chain()
	{
		m_LastNode = nullptr;
	}

	template<typename T>
	ExtendedChain<T>::ExtendedChain(const ExtendedChain<T>& other)
	{
		this->m_ListSize = other.m_ListSize;

		if (this->m_ListSize == 0)
		{
			this->m_FirstNode = nullptr;
			m_LastNode = nullptr;
			return;
		}

		// 存储当前要复制的节点
		ChainNode<T>* sourceNode = other.m_FirstNode;
		// 复制第一个节点
		this->m_FirstNode = new ChainNode<T>(sourceNode->element);
		// 更新下一个要复制的节点
		sourceNode = sourceNode->next;
		// 存储当前复制出的节点
		ChainNode<T>* targetNode = this->m_FirstNode;
		//循环复制余下的节点
		while (sourceNode)
		{
			ChainNode<T>* nextNode = new ChainNode<T>(sourceNode->element);
			targetNode->next = nextNode;
			sourceNode = sourceNode->next;
			targetNode = targetNode->next;
		}
		// 链表结束
		targetNode->next = nullptr;
		m_LastNode = targetNode;
	}

	template<typename T>
	ExtendedChain<T>::~ExtendedChain()
	{
		while (this->m_FirstNode)
		{
			ChainNode<T>* nextNode = this->m_FirstNode->next;
			delete this->m_FirstNode;
			this->m_FirstNode = nextNode;
		}
	}

	template<typename T>
	void ExtendedChain<T>::Insert(int index, const T& element)
	{
		if (index < 0 || index > this->m_ListSize)
		{
			std::ostringstream ss;
			ss << "Index (= " << index << ") must be inside the range [0, " << this->Size() << "]!";
			throw std::invalid_argument(ss.str());
		}

		if (index == 0)
		{
			// 在链表头插入
			this->m_FirstNode = new ChainNode<T>(element, this->m_FirstNode);
		}
		else
		{
			ChainNode<T>* currentNode = this->m_FirstNode;
			// 寻找新节点的前驱
			for (int i = 0; i < index - 1; ++i)
			{
				currentNode = currentNode->next;
			}
			// 在currentNode之后插入
			currentNode->next = new ChainNode<T>(element, currentNode->next);
			if (currentNode->next->next == nullptr)
			{
				m_LastNode = currentNode->next;
			}
		}
		this->m_ListSize++;
	}

	template<typename T>
	void ExtendedChain<T>::Erase(int index)
	{
		this->CheckIndex(index);

		ChainNode<T>* deleteNode;
		if (index == 0)
		{
			deleteNode = this->m_FirstNode;
			this->m_FirstNode = this->m_FirstNode->next;
		}
		else
		{
			ChainNode<T>* currentNode = this->m_FirstNode;
			// 寻找要删除节点的前驱
			for (int i = 0; i < index - 1; ++i)
			{
				currentNode = currentNode->next;
			}
			deleteNode = currentNode->next;
			currentNode->next = currentNode->next->next;
			if (currentNode->next == nullptr)
			{
				m_LastNode = currentNode;
			}
		}
		delete deleteNode;
		this->m_ListSize--;
	}

	template<typename T>
	void ExtendedChain<T>::Clear()
	{
		while (this->m_FirstNode)
		{
			ChainNode<T>* nextNode = this->m_FirstNode->next;
			delete this->m_FirstNode;
			this->m_FirstNode = nextNode;
		}
		this->m_ListSize = 0;
	}

	template<typename T>
	void ExtendedChain<T>::PushBack(const T& element)
	{
		ChainNode<T>* newNode = new ChainNode<T>(element);
		if (this->m_ListSize == 0)
		{
			this->m_FirstNode = this->m_LastNode = newNode;
		}
		else
		{
			this->m_LastNode->next = newNode;
			this->m_LastNode = newNode;
		}
		this->m_ListSize++;
	}

}
