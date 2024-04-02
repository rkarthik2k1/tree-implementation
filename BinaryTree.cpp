#include "BinaryTree.h"
#include <iostream>

void BinaryTree::_printNode(BTreeNode *pNode)
{
   using namespace std;
   if (pNode)
   {
      cout << pNode->m_Id << "\n";
      _printNode(pNode->Left());
      _printNode(pNode->Right());
   }
}

bool BinaryTree::_addNode(int nodeId)
{
   bool bRet = false;

   // Get the next available parent from the parent queue
   // Note that root will be the first in the queue by default
   // as it was added in the ctor
   BTreeNode *pNode = m_ParentQueue.front();

   // Add the new node. First check if we can add it as left child.
   // Push this node to the queue
   if (pNode->Left() == nullptr)
   {
      pNode->AddLeft(nodeId);
      m_ParentQueue.push_back(pNode->Left());
      bRet = true;
   }
   else
   {
      if (pNode->Right() == nullptr)
      {
         pNode->AddRight(nodeId);
         m_ParentQueue.push_back(pNode->Right());

         // Once we are done with filling both left and right child
         // remove this parent from the queue so that the next
         // available parent can come in front
         m_ParentQueue.pop_front();
         bRet = true;
      }
   }

   return bRet;
}

// Adds a node to left subtree if nodeId <= current node id
// otherwise to the right subtree
bool BinaryTree::_addSearchTreeNode(BTreeNode *pParent, int nodeId)
{
   bool bRet = false;
   if (pParent != nullptr)
   {
      if (nodeId <= pParent->m_Id)
      {
         if (pParent->Left() != nullptr)
         {
            bRet = _addSearchTreeNode(pParent->Left(), nodeId);
         }
         else
         {
            pParent->AddLeft(nodeId);
            bRet = true;
         }
      }
      else
      {
         if (pParent->Right() != nullptr)
         {
            bRet = _addSearchTreeNode(pParent->Right(), nodeId);
         }
         else
         {
            pParent->AddRight(nodeId);
            bRet = true;
         }
      }

   }

   return bRet;
}

// In-order traversal is as follows
// 1. traverse left subtree
// 2. visit current node
// 3. traverse right subtree
void BinaryTree::_inOrder(BTreeNode *pNode)
{
   if (pNode != nullptr)
   {
      // Traverse Left
      if (pNode->Left())
      {
         _inOrder(pNode->Left());
      }
      
      // Visit Current node
      m_FunVisitNode(*pNode);

      // Traverse Right
      if (pNode->Right())
      {
         _inOrder(pNode->Right());
      }
   }
}

// Pre-order traversal is as follows
// 1. visit current node
// 2. traverse left subtree
// 3. traverse right subtree
void BinaryTree::_preOrder(BTreeNode *pNode)
{
   if (pNode != nullptr)
   {
      // Visit Current node
      m_FunVisitNode(*pNode);

      // Traverse Left
      if (pNode->Left())
      {
         _preOrder(pNode->Left());
      }
    
      // Traverse Right
      if (pNode->Right())
      {
         _preOrder(pNode->Right());
      }
   }
}

// Post-order traversal is as follows
// 1. traverse left subtree
// 2. traverse right subtree
// 3. visit current node
void BinaryTree::_postOrder(BTreeNode *pNode)
{
   if (pNode != nullptr)
   {
      // Traverse Left
      if (pNode->Left())
      {
         _postOrder(pNode->Left());
      }

      // Traverse Right
      if (pNode->Right())
      {
         _postOrder(pNode->Right());
      }

      // Visit Current node
      m_FunVisitNode(*pNode);
   }
}

bool BinaryTree::AddNode(int id)
{
   bool bRet = false;
   if (m_bSearchTree)
   {
      bRet = _addSearchTreeNode(m_pRoot, id);
   }
   else
   {
      bRet = _addNode(id);
   }
   if (bRet)
      m_Size++;

   return bRet;
}

void BinaryTree::Print()
{
   _printNode(m_pRoot);
}

void BinaryTree::Traverse(std::function<void(BTreeNode)> doVisit, e_TraverseOrder order)
{
   // If doVisit function is null then simply use lambda expression
   // to print the node id
   if (doVisit)
   {
      m_FunVisitNode = doVisit;
   }
   else
   {
      m_FunVisitNode = [](BTreeNode node) 
      { 
         cout << node.m_Id << "\n"; 
      };
   }

   // Call the appropriate traversal method. Default is in-order
   switch(order)
   {
      case e_TraverseOrder::e_PreOrder:
         _preOrder(m_pRoot);
         break;
      case e_TraverseOrder::e_PostOrder:
         _postOrder(m_pRoot);
         break;
      default:
         _inOrder(m_pRoot);
         break;
   }
}

BinaryTree::~BinaryTree()
{

}
