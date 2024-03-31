#pragma once
//#include <vector>
#include <list>
#include <iostream>
using namespace std;

using UINT = unsigned int;

// Uncomment below to switch to Tree using vector
// using CONTAINER_UINT = vector<UINT>;
using CONTAINER_UINT = list<UINT>;
using UINT8 = unsigned char;
constexpr int MAX_NODES_LIST = 1000;

template <typename T>
class SimpleTree
{
   //USE THIS definition of struct Node for VSCODE
   //This is required for this version of VS Code C++ compiler
   //In VC++ the commented out definition worked fine
   struct Node
   {
      UINT uiId{};
      string strName{};
      UINT uiParentId{UINT32_MAX};
      T data;
      CONTAINER_UINT listChildrenId{};
   };

   /*USE THIS FOR VC++. In VC++ this definition worked fine
   typedef struct
   {
      UINT uiId{};
      string strName{};
      UINT uiParentId{UINT32_MAX};
      T data;
      CONTAINER_UINT listChildrenId{};
   } Node;*/

   // Uncomment below to switch to Tree using vector
   //using CONTAINER_NODE = vector<Node>;
   using CONTAINER_NODE = list<Node>;
private:
   CONTAINER_NODE m_Tree{};
   UINT m_CurrNodeId{};
   UINT m_RootId{};
   UINT8 m_MaxNodes{};

   void _createRoot(const T &data, const string &strName);
   void _removeChildren(const UINT uiParent);
   void _printSubTree(const UINT uiParentId) const;
   UINT _generateNodeId();
   bool _getNodeInfo(UINT nodeId, Node &node) const;

public:
   SimpleTree(UINT8 maxNodes, const T &rootData, const string &strRootName) : m_MaxNodes(maxNodes)
   {
      _createRoot(rootData, strRootName);
   };
   ~SimpleTree(){};

   bool AddNode(const UINT uiParent, const T &data, const string &strName, UINT &childId);
   void RemoveNode(const UINT id);
   bool GetChildren(const UINT uiParent, CONTAINER_UINT &childrenId) const;
   void PrintTree() const;
   T GetNodeData(UINT uiId) const;
   UINT GetRootId() { return m_RootId; };
};

template <class T>
inline void SimpleTree<T>::_createRoot(const T &data, const string &strName)
{
   Node root{};
   root.data = data;
   root.strName = strName;

   m_RootId = root.uiId;
   m_Tree.push_back(root);
}

// Remove a node from the Tree
template <class T>
void SimpleTree<T>::RemoveNode(const UINT id)
{
   Node node{};
   if (_getNodeInfo(id, node))
   {
      // Remove all children of id
      _removeChildren(id);

      // remove node
      for (auto iter = m_Tree.begin(); iter != m_Tree.end(); iter++)
      {
         if (iter->uiId == id)
         {
            m_Tree.erase(iter);
            break;
         }
      }

      // remove this id from its parents list
      for (auto iter = m_Tree.begin(); iter != m_Tree.end(); iter++)
      {
         if (iter->uiId == node.uiParentId)
         {
            for (auto itr = iter->listChildrenId.begin(); itr != iter->listChildrenId.end(); itr++)
            {
               if (id == *itr)
               {
                  iter->listChildrenId.erase(itr);
                  break;
               }
            }
            break;
         }
      }
   }
}

// Remove all children ids from the specfiied parent, this is private and used by RemoveNode
template <class T>
void SimpleTree<T>::_removeChildren(const UINT uiParent)
{
   Node nodeParent{};
   _getNodeInfo(uiParent, nodeParent);
   for (auto &child : nodeParent.listChildrenId)
   {
      RemoveNode(child);
   }
}

// Add a node to the parent specified by uiParent
// The method returns child's id by reference
template <class T>
inline bool SimpleTree<T>::AddNode(const UINT uiParent, const T &data, const string &strName, UINT &childId)
{
   bool bRet = false;

   childId = _generateNodeId();
   if (childId < MAX_NODES_LIST)
   {
      bool bAddChild = false;

      // Insert child id into Parent's list. Make sure parent list
      // is not more than m_MaxNodes
      for (auto iter = m_Tree.begin(); iter != m_Tree.end(); iter++)
      {
         if ((iter->uiId == uiParent) && (iter->listChildrenId.size() < m_MaxNodes))
         {
            iter->listChildrenId.push_back(childId);
            bAddChild = true;
            break;
         }
      }
      if (bAddChild)
      {
         Node nodeChild{};

         nodeChild.uiParentId = uiParent;
         nodeChild.uiId = childId;
         nodeChild.data = data;
         nodeChild.strName = strName;

         // Add child node to the list
         m_Tree.push_back(nodeChild);
      }
   }
   return bRet;
}

template <class T>
bool SimpleTree<T>::GetChildren(const UINT uiParent, CONTAINER_UINT &childrenIdList) const
{
   childrenIdList.empty();
   for (auto &node : m_Tree)
   {
      if (node.uiId == uiParent)
      {
         childrenIdList = node.listChildren;
      }
   }
   return (childrenIdList.size() > 0);
}

template <class T>
void SimpleTree<T>::PrintTree() const
{
   if (m_Tree.size() > 1)
   {
      //cout << "Root: " << m_Tree[0].strName << "\n";
      _printSubTree(0);
   }
   else
   {
      cout << "Empty Tree\n";
   }
}

template <class T>
void SimpleTree<T>::_printSubTree(const UINT uiParentId) const
{
   cout << "----------------------------\n";
   Node parentNode{};
   if (_getNodeInfo(uiParentId, parentNode))
   {
      if (parentNode.listChildrenId.size() > 0)
      {
         cout << parentNode.strName << "\n";
         for (auto nodeId : parentNode.listChildrenId)
         {
            Node childNode{};
            if (_getNodeInfo(nodeId, childNode))
            {
               cout << "child ----> " << childNode.strName << endl;
            }
         }
         for (auto node : parentNode.listChildrenId)
         {
            _printSubTree(node);
         }
      }
      else
      {
         cout << parentNode.strName << "\n";
         cout << "No children\n";
      }
   }
}

template <class T>
inline UINT SimpleTree<T>::_generateNodeId()
{
   return ++m_CurrNodeId;
}

template <class T>
inline bool SimpleTree<T>::_getNodeInfo(UINT nodeId, Node &node) const
{
   bool bFound = false;
   for (auto &tmpNode : m_Tree)
   {
      if (tmpNode.uiId == nodeId)
      {
         node = tmpNode;
         bFound = true;
         break;
      }
   }
   return bFound;
}

template <class T>
T SimpleTree<T>::GetNodeData(UINT uiId) const
{
   Node node{};
   _getNodeInfo(uiId, node);
   return node.data;
}
