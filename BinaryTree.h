#pragma once

#include <string>
#include <vector>
#include <list>
#include <functional>

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

enum class e_TraverseOrder
{
   e_InOrder,
   e_PreOrder,
   e_PostOrder
};

// Binary tree of BTreeNode objects
class BinaryTree
{

////////// Data Members /////////////////////////
   // Pointer to the root of the binary tree
   BTreeNode* m_pRoot{};

   // Queue of the parents
   list<BTreeNode*> m_ParentQueue{};

   // Tree size
   int m_Size{};

   // Is this a search tree?
   bool m_bSearchTree{};

   std::function<void(BTreeNode)> m_FunVisitNode{};
   
/////////////////////////////////////////////////

///////// METHODS ///////////////////////////////
   // Print node info
   void _printNode(BTreeNode* pNode);

   // Add a node w/o forming a search tree
   bool _addNode(int nodeId);

   // Add a node forming a search tree
   bool _addSearchTreeNode(BTreeNode* pParent, int nodeId);

   void _inOrder(BTreeNode* pNode);
   void _preOrder(BTreeNode *pNode);
   void _postOrder(BTreeNode *pNode);

   /////////////////////////////////////////////////

public:
   BinaryTree(int rootId, bool bSearchTree=false): m_Size(1), m_bSearchTree(bSearchTree)
   {
      m_pRoot = new BTreeNode(rootId);

      // We need the queue only if not creating a search tree
      if (!bSearchTree)
         m_ParentQueue.push_back(m_pRoot);
   }

   // Add node to the next available parent in m_ParentQueue
   bool AddNode(int id);

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

   void Traverse(std::function<void(BTreeNode)> doVisit, e_TraverseOrder order=e_TraverseOrder::e_InOrder);

   ~BinaryTree();
};