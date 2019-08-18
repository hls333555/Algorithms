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

		// Double the capacity
		if (m_ListSize == m_ArraySize)
		{
			T* temp = new T[m_ArraySize * 2];
			std::copy(m_Element, m_Element + m_ArraySize, temp);
			// Release the old array
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
		// Call the destructor
		m_Element[--m_ListSize].~T();

		// Shrink the capacity
		if (m_ListSize < m_ArraySize / 4)
		{
			int newSize = std::max(m_InitialCapacity, m_ArraySize / 2);
			T* temp = new T[newSize];
			std::copy(m_Element, m_Element + newSize, temp);
			// Release the old array
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

}
