#ifndef value_iterator_h_
#define value_iterator_h_

#include <iostream>
#include <utility>

#include "bidirectional_map.h"
#include "key_iterator.h"

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class K, class V>
class value_iterator {
public:
	friend class bidirectional_map<K, V>;
  value_iterator() : ptr_(NULL), set_(NULL) {}
  value_iterator(TreeNode<V, K>* p, const bidirectional_map<K, V> * s) : ptr_(p), set_(s) {}
  // operator* gives constant access to the value at the pointer
  std::pair<V, K> operator*() const;
  // comparions operators are straightforward
  bool operator== (const value_iterator& rgt) { return (set_ == rgt.set_ && ptr_ == rgt.ptr_); }
  bool operator!= (const value_iterator& rgt) { return (set_ != rgt.set_ || ptr_ != rgt.ptr_); }
	key_iterator<K, V> follow_link();
  // increment & decrement operators
  value_iterator<K, V> & operator++(); // pre-increment, ++itr
  value_iterator<K, V> operator++(int);  // post-increment, itr++
  value_iterator<K, V> & operator--(); // pre-decrement, --itr
  value_iterator<K, V> operator--(int); // post-decrement itr--

private:
  // representation
  TreeNode<V, K>* ptr_;
  const bidirectional_map<K, V>* set_;
};

  template <class K, class V>
  key_iterator<K, V> value_iterator<K, V>::follow_link() {
	  return key_iterator<K, V>(ptr_->link, set_);
  }

  template <class K, class V>
  std::pair<V, K> value_iterator<K, V>::operator*() const {
	return std::pair<V, K>(ptr_->value, (ptr_->link)->value);
  }

  // increment & decrement operators
  template <class K, class V> value_iterator<K, V> & value_iterator<K, V>::operator++() {  // pre-increment, ++itr
    if (ptr_->right != NULL) { // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) { ptr_ = ptr_->left; }
    } else { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
    return *this;
  }
  template <class K, class V> value_iterator<K, V> value_iterator<K, V>::operator++(int) {  // post-increment, itr++
    value_iterator<K, V> temp(*this);
    ++(*this);
    return temp;
  }
  template <class K, class V> value_iterator<K, V> & value_iterator<K, V>::operator--() { // pre-decrement, --itr
    if (ptr_ == NULL) { // so that it works for end()
      assert (set_ != NULL);
      ptr_ = set_->value_root;
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
  template <class K, class V> value_iterator<K, V> value_iterator<K, V>::operator--(int) { // post-decrement itr--
    value_iterator<K, V> temp(*this);
    --(*this);
    return temp;
  }


#endif