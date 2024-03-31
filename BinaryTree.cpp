#include "BinaryTree.h"
#include <iostream>

void BinaryTree::PrintNode(BTreeNode *pNode)
{
   using namespace std;
   if (pNode)
   {
      cout << pNode->m_Id << "\n";
      PrintNode(pNode->Left());
      PrintNode(pNode->Right());
   }
}

void BinaryTree::AddNode(int id)
{
   // Get the next available parent from the parent queue
   // Note that root will be the first in the queue by default
   // as it was added in the ctor
   BTreeNode *pNode = m_ParentQueue.front();

   // Add the new node. First check if we can add it as left child
   // Push this node to the queue
   if (pNode->Left() == nullptr)
   {
      pNode->AddLeft(id);
      m_Size++;

      m_ParentQueue.push_back(pNode->Left());
   }
   else
   {
      if (pNode->Right() == nullptr)
      {
         pNode->AddRight(id);
         m_Size++;
         m_ParentQueue.push_back(pNode->Right());

         // Once we are done with filling both left and right child
         // remove this parent from the queue so that the next
         // available parent can come in front
         m_ParentQueue.pop_front();
      }
   }
}

void BinaryTree::Print()
{
   PrintNode(m_pRoot);
}