#pragma once

#include <string>
#include <vector>
#include <list>

using namespace std;

#pragma once

#include <string>
#include <vector>
#include <list>

using namespace std;

//A node in the binary tree
class BTreeNode
{
   //Pointer to left child 
   BTreeNode* m_pLeft{};

   //Pointer to right child 
   BTreeNode* m_pRight{};
public:
   BTreeNode() {}
   int m_Id{};
   BTreeNode(int id) : m_Id( id ) {}

   // Add left child
   void AddLeft(int id)
   {
      if (m_pLeft == nullptr)
      {
         m_pLeft = new BTreeNode(id);
      }
   }

   // Add right child
   void AddRight(int id)
   {
      if (m_pRight == nullptr)
      {
         m_pRight = new BTreeNode(id);
      }
   }

   // Return pointer to left child
   BTreeNode* Left()
   {
      return m_pLeft;
   }

   // Return pointer to right child
   BTreeNode* Right()
   {
      return m_pRight;
   }
};

// Binary tree of BTreeNode objects
class BinaryTree
{
   // Pointer to the root of the binary tree
   BTreeNode* m_pRoot{};

   // Queue of the parents
   list<BTreeNode*> m_ParentQueue{};
   int m_Size{};

   // Print node info
   void PrintNode(BTreeNode* pNode);
public:
   BinaryTree(int rootId)
   {
      m_pRoot = new BTreeNode(rootId);
      m_ParentQueue.push_back(m_pRoot);
      m_Size = 1;
   }

   // Add node to the next available parent in m_ParentQueue
   void AddNode(int id);

   // Print the nodes in the tree
   void Print();

   // Get instance of the root object
   BTreeNode GetRoot()
   {
      return *m_pRoot;
   }

   // Get levels in the tree
   int GetLevels()
   {
      return (m_Size / 2) - 1;
   }
};