# tree-implementation

This repo contains C++ implementations of n-nary and binary trees. I have also given solutions to some problems involving binary trees

Classes
-------

1. SimpleTree
This is an n-nary tree implementation. The tree is simply a list of nodes . Every node has an id, parent id and a templatized data. Hence the Tree class is implemented as a template class. Every node has a list of children ids. The implementation allows for quick building of a tree. Searching a node and children should run in o(N). 
Subtree operations are expensive though. A variant of this was developed by me several years back for one of the products in an organization
This implementation can be used with std::vector or std::list. I have added comments on how to switch between the two by commenting out few macros
 - File(s): SimpleTree.h

2. BinaryTree - Implementation of a Binary Tree
 - File(s): BinaryTree.h, BnaryTree.cpp

The file TestTree.cpp contains some example using binary trees

I have used MS Visual Code to develop and test this on Windows. It should be possible to use this repo on other platforms like Linux as-is or with some minor modification
