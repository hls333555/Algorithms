#pragma once

#include <iostream>

#include "Queue.h"

namespace HAlgorithm {

	template <typename T>
	struct BinaryTreeNode
	{
		BinaryTreeNode()
			: leftChild(nullptr), rightChild(nullptr) {}
		BinaryTreeNode(const T& _element)
			: element(_element)
			, leftChild(nullptr), rightChild(nullptr) {}
		BinaryTreeNode(const T& _element, BinaryTreeNode<T>* _leftChild, BinaryTreeNode<T>* _rightChild)
			: element(_element)
			, leftChild(_leftChild)
			, rightChild(_rightChild) {}

		T element;
		BinaryTreeNode<T>* leftChild, *rightChild;
	};

	template <typename T>
	class BinaryTree
	{
	public:
		virtual ~BinaryTree() {}

		virtual bool Empty() const = 0;
		virtual int Size() const = 0;
		virtual void PreOrder(void(*)(T*)) = 0;
		virtual void InOrder(void(*)(T*)) = 0;
		virtual void PostOrder(void(*)(T*)) = 0;
		virtual void LevelOrder(void(*)(T*)) = 0;
	};

	template <typename T>
	class LinkedBinaryTree : public BinaryTree<BinaryTreeNode<T>>
	{
	public:
		LinkedBinaryTree()
			: m_Root(nullptr)
			, m_TreeSize(0) {}
		LinkedBinaryTree(const T& element, LinkedBinaryTree<T>& leftChildTree, LinkedBinaryTree<T>& rightChildTree);
		virtual ~LinkedBinaryTree() { Erase(); }

		BinaryTreeNode<T>* Root() const { return m_Root; }

		virtual bool Empty() const override { return m_TreeSize == 0; }
		virtual int Size() const override { return m_TreeSize; }
		virtual void PreOrder(void(*visit)(BinaryTreeNode<T>*) = &Output) override { InternalPreOrder(visit, m_Root); }
		virtual void InOrder(void(*visit)(BinaryTreeNode<T>*) = &Output) override { InternalInOrder(visit, m_Root); }
		virtual void PostOrder(void(*visit)(BinaryTreeNode<T>*) = &Output) override { InternalPostOrder(visit, m_Root); }
		virtual void LevelOrder(void(*visit)(BinaryTreeNode<T>*) = &Output) override { InternalLevelOrder(visit, m_Root); }

		int Height() const { HeightHelper(m_Root); }
		/** 通过后序遍历删除所有节点。*/
		void Erase();

	private:
		void InternalPreOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode);
		void InternalInOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode);
		void InternalPostOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode);
		void InternalLevelOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode);

		int InternalHeight(BinaryTreeNode<T>* startTreeNode) const;

		// 赋值给函数指针的类內方法必须为static！
		/** 删除指定节点。 */
		static void Dispose(BinaryTreeNode<T>* treeNode) { delete treeNode; }
		static void Output(BinaryTreeNode<T>* treeNode) { std::cout << treeNode->element << "->"; }

	private:
		BinaryTreeNode<T>* m_Root;
		int m_TreeSize;

	};

	template<typename T>
	LinkedBinaryTree<T>::LinkedBinaryTree(const T& element, LinkedBinaryTree<T>& leftChildTree, LinkedBinaryTree<T>& rightChildTree)
	{
		m_Root = new BinaryTreeNode<T>(element, leftChildTree.m_Root, rightChildTree.m_Root);
		m_TreeSize = leftChildTree.m_TreeSize + rightChildTree.m_TreeSize + 1;

		// 将原左右子树的所有权转移给该树
		leftChildTree.m_Root = rightChildTree.m_Root = nullptr;
		leftChildTree.m_TreeSize = rightChildTree.m_TreeSize = 0;
	}

	template<typename T>
	void LinkedBinaryTree<T>::Erase()
	{
		PostOrder(Dispose);
		m_Root = nullptr;
		m_TreeSize = 0;
	}

	template<typename T>
	void LinkedBinaryTree<T>::InternalPreOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode)
	{
		if (startTreeNode)
		{
			visit(startTreeNode);
			InternalPreOrder(visit, startTreeNode->leftChild);
			InternalPreOrder(visit, startTreeNode->rightChild);
		}
	}

	template<typename T>
	void LinkedBinaryTree<T>::InternalInOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode)
	{
		if (startTreeNode)
		{
			InternalInOrder(visit, startTreeNode->leftChild);
			visit(startTreeNode);
			InternalInOrder(visit, startTreeNode->rightChild);
		}
	}

	template<typename T>
	void LinkedBinaryTree<T>::InternalPostOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode)
	{
		if (startTreeNode)
		{
			InternalPostOrder(visit, startTreeNode->leftChild);
			InternalPostOrder(visit, startTreeNode->rightChild);
			visit(startTreeNode);
		}
	}

	template<typename T>
	void LinkedBinaryTree<T>::InternalLevelOrder(void(*visit)(BinaryTreeNode<T>*), BinaryTreeNode<T>* startTreeNode)
	{
		ArrayQueue<BinaryTreeNode<T>*> treeNodeQueue;
		while (startTreeNode)
		{
			visit(startTreeNode);
			
			if (startTreeNode->leftChild)
			{
				treeNodeQueue.Push(startTreeNode->leftChild);
			}
			if (startTreeNode->rightChild)
			{
				treeNodeQueue.Push(startTreeNode->rightChild);
			}

			try
			{
				startTreeNode = treeNodeQueue.Front();
			}
			catch (const std::exception&)
			{
				return;
			}
			treeNodeQueue.Pop();
		}
	}

	template<typename T>
	int LinkedBinaryTree<T>::InternalHeight(BinaryTreeNode<T>* startTreeNode) const
	{
		if (!startTreeNode)
			return 0;

		int leftHeight = InternalHeight(startTreeNode->leftChild);
		int rightHeight = InternalHeight(startTreeNode->rightChild);
		if (leftHeight > rightHeight)
		{
			return ++leftHeight;
		}
		else
		{
			return ++rightHeight;
		}
	}

}
