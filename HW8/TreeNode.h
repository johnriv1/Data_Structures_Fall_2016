#ifndef TreeNode_h_
#define TreeNode_h_

#include <iostream>
#include <utility>

// -------------------------------------------------------------------
// TREE NODE CLASS 
template <class T1, class T2>
class TreeNode {
public:
  TreeNode() : left(NULL), right(NULL), parent(NULL), link(NULL) {}
  TreeNode(const T1& init) : value(init), left(NULL), right(NULL), parent(NULL), link(NULL) {}
  T1 value;
  TreeNode<T1, T2>* left;
  TreeNode<T1, T2>* right;
  TreeNode<T1, T2>* parent; // to allow implementation of iterator increment & decrement
  TreeNode<T2, T1>* link;
};

#endif