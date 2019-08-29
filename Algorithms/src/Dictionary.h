#pragma once

#include <map>

namespace HAlgorithm {

	template <typename T1, typename T2>
	class Dictionary
	{
	public:
		virtual ~Dictionary() {}

		virtual bool Empty() const = 0;
		virtual int Size() const = 0;
		virtual T2* Find(const T1& key) const = 0;
		virtual void Insert(const std::pair<const T1, T2>& pair) = 0;
		virtual void Erase(const T1& key) = 0;
		virtual void Output(std::ostream& out) const = 0;
	};

	template <typename T1, typename T2>
	struct PairNode
	{
		std::pair<const T1, T2> element;
		PairNode<T1, T2>* next;

		PairNode() {}
		PairNode(const std::pair<T1, T2>& _element, PairNode<T1, T2>* _next = nullptr)
			: element(_element), next(_next) {}
	};

	template <typename T1, typename T2>
	class SortedChain : public Dictionary<T1, T2>
	{
		class Iterator
		{
		public:
			typedef struct forward_iterator_tag iterator_category;
			typedef PairNode<T1, T2> value_type;
			typedef ptrdiff_t difference_type;
			typedef PairNode<T1, T2>* pointer;
			typedef PairNode<T1, T2>& reference;

			Iterator(PairNode<T1, T2>* position = 0)
				: m_Position(position) {}

			PairNode<T1, T2>& operator*() const { return *m_Position; }
			PairNode<T1, T2>* operator->() const { return &*m_Position; }

			Iterator& operator++()
			{
				m_Position = m_Position->next;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator temp = *this;
				m_Position = m_Position->next;
				return temp;
			}

			bool operator==(const Iterator& other) const { return m_Position == other.m_Position; }
			bool operator!=(const Iterator& other) const { return m_Position != other.m_Position; }

		private:
			PairNode<T1, T2>* m_Position;
		};

	public:
		SortedChain()
			: m_FirstNode(nullptr)
			, m_DictionarySize(0) {}
		virtual ~SortedChain();

		virtual bool Empty() const override { return m_DictionarySize == 0; }
		virtual int Size() const override { return m_DictionarySize; }
		virtual T2* Find(const T1& key) const override;
		virtual void Insert(const std::pair<const T1, T2>& pair) override;
		virtual void Erase(const T1& key) override;
		virtual void Output(std::ostream& out) const override;

		Iterator Begin() { return Iterator(m_FirstNode); }

	private:
		PairNode<T1, T2>* m_FirstNode;
		int m_DictionarySize;
	};

	template<typename T1, typename T2>
	SortedChain<T1, T2>::~SortedChain()
	{
		while (m_FirstNode)
		{
			PairNode<T1, T2>* nextNode = m_FirstNode->next;
			delete m_FirstNode;
			m_FirstNode = nextNode;
		}
	}

	template<typename T1, typename T2>
	T2* SortedChain<T1, T2>::Find(const T1& key) const
	{
		PairNode<T1, T2>* currentNode = m_FirstNode;
		while (currentNode && currentNode->element.first != key)
		{
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			return nullptr;
		}
		return &currentNode->element.second;
	}

	template<typename T1, typename T2>
	void SortedChain<T1, T2>::Insert(const std::pair<const T1, T2>& pair)
	{
		PairNode<T1, T2>* currentNode = m_FirstNode,
			*lastNode = nullptr; // 用于定位插入位置
		// 寻找插入位置（按字典顺序排列）
		while (currentNode && currentNode->element.first < pair.first)
		{
			lastNode = currentNode;
			currentNode = currentNode->next;
		}

		// 找到匹配，更新值
		if (currentNode && currentNode->element.first == pair.first)
		{
			currentNode->element.second = pair.second;
		}
		// 无匹配键值对
		else
		{
			PairNode<T1, T2>* newNode = new PairNode<T1, T2>(pair, currentNode);
			if (lastNode)
			{
				// 插入新节点
				lastNode->next = newNode;
			}
			else
			{
				// 插入头结点
				m_FirstNode = newNode;
			}
			m_DictionarySize++;
		}
	}

	template<typename T1, typename T2>
	void SortedChain<T1, T2>::Erase(const T1& key)
	{
		PairNode<T1, T2>* currentNode = m_FirstNode,
			*lastNode = nullptr; // 用于定位删除位置
		while (currentNode && currentNode->element.first < key)
		{
			lastNode = currentNode;
			currentNode = currentNode->next;
		}
		
		// 找到了匹配的键值对
		if (currentNode && currentNode->element.first == key)
		{
			if (lastNode)
			{
				// 删除节点
				lastNode->next = currentNode->next;
			}
			else
			{
				// 删除头结点
				m_FirstNode = currentNode->next;
			}
			delete currentNode;
			m_DictionarySize--;
		}
	}

	template<typename T1, typename T2>
	void SortedChain<T1, T2>::Output(std::ostream& out) const
	{
		for (PairNode<T1, T2>* currentNode = m_FirstNode; currentNode != nullptr; currentNode = currentNode->next)
		{
			out << "(" << currentNode->element.first << ", " << currentNode->element.second << ") ";
		}
	}

	/** 线性探查，每个桶只能存储一个键值对 */
	template <typename T1, typename T2>
	class HashTable
	{
	public:
		HashTable(int divisor);
		~HashTable() { delete[] m_Table; }

		bool Empty() const { return m_TableSize == 0; }
		int Size() const { return m_TableSize; }
		/**
		 * 查找关键字为key的键值对。
		 * 若匹配的键值对存在，返回它的位置；否则，若列表不满，返回关键字为key的键值对可插入的位置。
		 */
		int Search(const T1& key) const;
		T2* Find(const T1& key) const;
		void Insert(const std::pair<const T1, T2>& pair);
		void Erase(const T1& key);

	private:
		std::pair<const T1, T2>** m_Table;
		int m_Divisor;
		int m_TableSize;

	};

	template<typename T1, typename T2>
	HashTable<T1, T2>::HashTable(int divisor)
		: m_Divisor(divisor)
		, m_TableSize(0)
	{
		m_Table = new std::pair<const T1, T2>* [m_Divisor];
		for (int i = 0; i < m_Divisor; ++i)
		{
			m_Table[i] = nullptr;
		}
	}

	template<typename T1, typename T2>
	int HashTable<T1, T2>::Search(const T1& key) const
	{
		// 起始桶
		int i = std::hash<T1>(key) % m_Divisor;
		// 从起始桶开始
		int j = i;
		do
		{
			if (m_Table[j] == nullptr || m_Table[j]->first == key)
			{
				return j;
			}
			// 下一个桶
			j = (j + 1) % m_Divisor;
		} while (j != i);
		// 表满
		return j;
	}

	template<typename T1, typename T2>
	T2* HashTable<T1, T2>::Find(const T1& key) const
	{
		int i = Search(key);

		if (m_Table[i] && m_Table[i]->first == key)
		{
			return m_Table[i]->second;
		}

		return nullptr;
	}

	template<typename T1, typename T2>
	void HashTable<T1, T2>::Insert(const std::pair<const T1, T2>& pair)
	{
		int i = Search(pair.first);

		if (m_Table[i])
		{
			// 找到匹配的键值对， 更新值
			if (m_Table[i]->first == pair.first)
			{
				m_Table[i]->second = pair.second;
			}
			// 表满
			else
			{
				throw std::exception("Failed to insert the pair to a full hash table!");
			}
		}
		else
		{
			// 没有匹配的键值对，将键值对插入合适的位置
			m_Table[i] = new std::pair<const T1, T2>(pair);
			m_TableSize++;
		}
	}

	template<typename T1, typename T2>
	void HashTable<T1, T2>::Erase(const T1& key)
	{
		int i = Search(key);

		if (m_Table[i])
		{
			// 找到匹配的键值对，删除
			if (m_Table[i]->first == key)
			{
				delete m_Table[i];
				return;
			}
		}

		throw std::exception("Failed to delete the pair containing the key!");
	}

	/** 链式散列，每个桶可存储无数个键值对 */
	template <typename T1, typename T2>
	class HashChain
	{
	public:
		HashChain(int divisor);
		~HashChain() { delete[] m_Table; }

		bool Empty() const { return m_TableSize == 0; }
		int Size() const { return m_TableSize; }
		T2* Find(const T1& key) const;
		void Insert(const std::pair<const T1, T2>& pair);
		void Erase(const T1& key);

	private:
		SortedChain<T1, T2>* m_Table;
		int m_Divisor;
		int m_TableSize;

	};

	template<typename T1, typename T2>
	HashChain<T1, T2>::HashChain(int divisor)
		: m_Divisor(divisor)
		, m_TableSize(0)
	{
		m_Table = new SortedChain<T1, T2> [m_Divisor];
	}

	template<typename T1, typename T2>
	T2* HashChain<T1, T2>::Find(const T1& key) const
	{
		return m_Table[std::hash<T1>(key) % m_Divisor].Find(key);
	}

	template<typename T1, typename T2>
	void HashChain<T1, T2>::Insert(const std::pair<const T1, T2>& pair)
	{
		int i = std::hash<T1>(pair.first) % m_Divisor;
		int lastSize = m_Table[i].Size();
		m_Table[i].Insert(pair);
		if (m_Table[i].Size() > lastSize)
		{
			m_TableSize++;
		}
	}

	template<typename T1, typename T2>
	void HashChain<T1, T2>::Erase(const T1& key)
	{
		int i = std::hash<T1>(key) % m_Divisor;
		int lastSize = m_Table[i].Size();
		m_Table[i].Erase(key);
		if (m_Table[i].Size() < lastSize)
		{
			m_TableSize--;
		}
	}

}
