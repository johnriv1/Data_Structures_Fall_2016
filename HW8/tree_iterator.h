#ifndef key_iterator_h_
#define key_iterator_h_

#include <iostream>
#include <utility>

#include "bidirectional_map.h"

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class K>
class key_iterator {
public:
  key_iterator() : ptr_(NULL), set_(NULL) {}
  key_iterator(TreeNode<K>* p, const bidirectional_map<K> * s) : ptr_(p), set_(s) {}
  // operator* gives constant access to the value at the pointer
  const K& operator*() const { return ptr_->value; }
  // comparions operators are straightforward
  bool operator== (const key_iterator& rgt) { return (set_ == rgt.set_ && ptr_ == rgt.ptr_); }
  bool operator!= (const key_iterator& rgt) { return (set_ != rgt.set_ || ptr_ != rgt.ptr_); }

  // increment & decrement operators
  key_iterator<K> & operator++(); // pre-increment, ++itr
  key_iterator<K> operator++(int);  // post-increment, itr++
  key_iterator<K> & operator--(); // pre-decrement, --itr
  key_iterator<K> operator--(int); // post-decrement itr--

private:
  // representation
  TreeNode<K>* ptr_;
  const bidirectional_map<K>* set_;
};

  // increment & decrement operators
  template <class K> key_iterator<K> & key_iterator::operator++() {  // pre-increment, ++itr
    if (ptr_->right != NULL) { // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) { ptr_ = ptr_->left; }
    } else { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
    return *this;
  }
  template <class K> key_iterator<K> key_iterator::operator++(int) {  // post-increment, itr++
    key_iterator<K> temp(*this);
    ++(*this);
    return temp;
  }
  template <class K> key_iterator<K> & key_iterator::operator--() { // pre-decrement, --itr
    if (ptr_ == NULL) { // so that it works for end()
      assert (set_ != NULL);
      ptr_ = set_->root_;
      while (ptr_->right != NULL) { ptr_ = ptr_->right; }
    } else if (ptr_->left != NULL) { // find the rightmost child of the left node
      ptr_ = ptr_->left;
      while (ptr_->right != NULL) { ptr_ = ptr_->right; }
    } else { // go upwards along left brances... stop after the first right
      while (ptr_->parent != NULL && ptr_->parent->left == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
    return *this;
  }
  template <class K> key_iterator<K> key_iterator::operator--(int) { // post-decrement itr--
    key_iterator<K> temp(*this);
    --(*this);
    return temp;
  }


#endif