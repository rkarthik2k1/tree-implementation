// NetworkCache.cpp : Defines the entry point for the console application.
//

#include "SimpleTree.h"
#include <string>
#include "BinaryTree.h"

void Test_SimpleTree()
{
   SimpleTree<string> myTree(3, "A_Data", "A");
   UINT childB{};
   UINT childC{};
   UINT childD{};
   UINT childE{};
   UINT childF{};
   UINT root = myTree.GetRootId();
   myTree.AddNode(root, "B_Data", "B", childB);
   myTree.AddNode(root, "C_Data", "C", childC);
   myTree.AddNode(childB, "D_Data", "D", childD);
   myTree.AddNode(childC, "E_Data", "E", childE);
   myTree.AddNode(childB, "F_Data", "F", childF);

   myTree.PrintTree();
   cout << "**************************************\n";
   myTree.RemoveNode(childC);
   myTree.RemoveNode(childE);
   myTree.PrintTree();
   cout << "**************************************\n";
}

// Run various operations on a binary tree
typedef vector<BTreeNode> LEVEL_LIST;
// Given the list of parent nodes, load the children into 
// a list
void GetNodesInLevel(vector<BTreeNode> parentNodes, LEVEL_LIST &levelList)
{
   for (int i = 0; i < parentNodes.size(); i++)
   {
      if (parentNodes[i].Left())
         levelList.push_back(*(parentNodes[i].Left()));
      if (parentNodes[i].Right())
         levelList.push_back(*(parentNodes[i].Right()));
   }
}

void TestBinaryTree()
{
   // Create a binary tree
   BinaryTree btree{0};
   btree.AddNode(1);
   btree.AddNode(2);

   btree.AddNode(3);
   btree.AddNode(4);

   btree.AddNode(5);
   btree.AddNode(6);

   btree.AddNode(7);
   btree.AddNode(8);

   btree.AddNode(9);
   btree.AddNode(10);

   // Print the tree

   // Read Binary Tree into a list
   // such that each level forms one list
   // and we have list of levels
   vector<BTreeNode> parentNodes;
   parentNodes.push_back(btree.GetRoot());

   int levels = btree.GetLevels();
   vector<BTreeNode> listTree;
   listTree.push_back(btree.GetRoot());

   // For each level, read the nodes in that level into a list
   for (int i = 1; i < levels; i++)
   {
      LEVEL_LIST levelList{};
      GetNodesInLevel(parentNodes, levelList);
      for (int j = 0; j < levelList.size(); j++)
         listTree.push_back(levelList[j]);
      parentNodes.clear();
      parentNodes = levelList;
   }

   for (int i = 0; i < listTree.size(); i++)
      cout << listTree[i].m_Id << "\n";

}

typedef struct
{
	UINT nodeId;
	string ipAddress;
}NetworkNode;

/*void PeformanceTest()
{
	Tree<NetworkNode> networkTree;
	for (int i = 0; i < 10000; i++)
	{
		NetworkNode node;
		node.nodeId = i+1;
		//node.ipAddress = std::to_string(i+1);
		string name{};
		name += "Node "; 
		name += node.ipAddress;
		networkTree.AddChild(i, node, name);
	}
	networkTree.PrintTree();
}*/
int main()
{
   Test_SimpleTree();
   //PeformanceTest();
   return 0;
}

