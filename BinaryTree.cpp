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

   // Add the new node. First check if we can add it as left child
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

BinaryTree::~BinaryTree()
{

}
