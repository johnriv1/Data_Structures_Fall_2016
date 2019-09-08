#ifndef bidirectional_map_h_
#define bidirectional_map_h_

#include <iostream>
#include <utility>

template <class K, class V> class key_iterator;
template <class K, class V> class bidirectional_map;

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

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class K, class V>
class value_iterator {
public:
	friend class bidirectional_map<K, V>;

  value_iterator() : ptr_(NULL), set_(NULL) {}
  value_iterator(TreeNode<V, K>* p, const bidirectional_map<K, V> * s) : ptr_(p), set_(s) {}
	
  bool operator== (const value_iterator& rgt) { return (set_ == rgt.set_ && ptr_ == rgt.ptr_); }
  bool operator!= (const value_iterator& rgt) { return (set_ != rgt.set_ || ptr_ != rgt.ptr_); }
  
  key_iterator<K, V> follow_link() {
	  return key_iterator<K, V>(ptr_->link, set_);
  }

  std::pair<V, K> operator*() const {
	return std::pair<V, K>(ptr_->value, (ptr_->link)->value);
  }

  // increment & decrement operators
 value_iterator<K, V> & operator++() {  // pre-increment, ++itr
    if (ptr_->right != NULL) { // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) { ptr_ = ptr_->left; }
    } else { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
    return *this;
  }
  value_iterator<K, V> operator++(int) {  // post-increment, itr++
    value_iterator<K, V> temp(*this);
    ++(*this);
    return temp;
  }
   value_iterator<K, V> & operator--() { // pre-decrement, --itr
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
   value_iterator<K, V> operator--(int) { // post-decrement itr--
    value_iterator<K, V> temp(*this);
    --(*this);
    return temp;
  }
  
  private:
  // representation
  TreeNode<V, K>* ptr_;
  const bidirectional_map<K, V>* set_;
};

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class K, class V>
class key_iterator {
public:
	friend class bidirectional_map<K, V>;
  
  key_iterator() : ptr_(NULL), set_(NULL) {}
  key_iterator(TreeNode<K, V>* p, const bidirectional_map<K, V> * s) : ptr_(p), set_(s) {}
  bool operator== (const key_iterator& rgt) { return (set_ == rgt.set_ && ptr_ == rgt.ptr_); }
  bool operator!= (const key_iterator& rgt) { return (set_ != rgt.set_ || ptr_ != rgt.ptr_); }
  
  value_iterator<K, V> follow_link() {
	  return value_iterator<K, V>(ptr_->link, set_);
  }
  
  std::pair<K, V> operator*() const {
	return std::pair<K, V>(ptr_->value, (ptr_->link)->value);
  }

  // increment & decrement operators
   key_iterator<K, V> & operator++() {  // pre-increment, ++itr
    if (ptr_->right != NULL) { // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) { ptr_ = ptr_->left; }
    } else { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
    return *this;
  }
   key_iterator<K, V> operator++(int) {  // post-increment, itr++
    key_iterator<K, V> temp(*this);
    ++(*this);
    return temp;
  }
   key_iterator<K, V> & operator--() { // pre-decrement, --itr
    if (ptr_ == NULL) { // so that it works for end()
      assert (set_ != NULL);
      ptr_ = set_->key_root;
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
   key_iterator<K, V> operator--(int) { // post-decrement itr--
    key_iterator<K, V> temp(*this);
    --(*this);
    return temp;
  }
  
  private:
  // representation
  TreeNode<K, V>* ptr_;
  const bidirectional_map<K, V>* set_;
  };

// -------------------------------------------------------------------
// DS_ SET CLASS
template <class K, class V>
class bidirectional_map {
public:
  // DEFAULT CONSTRUCTOR, COPY CONSTRUCTOR, ASSIGNMENT OPERATOR, & DESTRUCTOR
  bidirectional_map() : key_root(NULL), value_root(NULL), size_(0) {}
  
  bidirectional_map(const bidirectional_map<K, V>& old) : size_(old.size_) { 
    key_root = this->copy_key_tree(old.key_root,NULL);
	value_root = this->copy_value_tree(old.value_root,NULL,key_root); }
	
  bidirectional_map& operator=(const bidirectional_map<K, V>& old);

  ~bidirectional_map() {
    this->destroy_key_tree(key_root);
    key_root = NULL;
	this->destroy_value_tree(value_root);
	value_root = NULL;
  }
  
  friend class key_iterator<K, V>;
  typedef key_iterator<K, V> key_iterator;
  friend class value_iterator<K, V>;
  typedef value_iterator<K, V> value_iterator;

  // ACCESSORS

  int size() const { return size_; }

  //search by key, return value
  V operator[](const K& key_value);
  //search by value, return key
  K operator[](const V& value_value);
  // FIND, INSERT & ERASE
  key_iterator find(const K& key_value) { return find(key_value, key_root); }
  value_iterator find(const V& value_value) { return find(value_value, value_root); }

  std::pair< key_iterator, bool > insert(const std::pair<K, V>& vals);
  
  int erase(K const& key_value);

  void print(std::ostream& ostr) const;

  // ITERATORS
  key_iterator key_begin() const;
  value_iterator value_begin() const;

  key_iterator key_end() const { return key_iterator(NULL,this); }
  value_iterator value_end() const { return value_iterator(NULL,this); }

private:
  // REPRESENTATION
  TreeNode<K, V>* key_root;
  TreeNode<V, K>* value_root;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode<K, V>* copy_key_tree(TreeNode<K, V>* old_root, TreeNode<K, V>* the_parent);
  TreeNode<V, K>* copy_value_tree(TreeNode<V, K>* old_root, TreeNode<V, K>* the_parent, TreeNode<K, V>* key_root);
  
  void destroy_key_tree(TreeNode<K, V>* p);
  void destroy_value_tree(TreeNode<V, K>* p);

  value_iterator find(const V& value_value, TreeNode<V, K>* value_root);
  key_iterator find(const K& key_value, TreeNode<K, V>* key_root);
  std::pair<key_iterator, bool> insertKey(const K& key_value, TreeNode<K, V>*& pk, TreeNode<K, V>* the_key_parent);
  std::pair<value_iterator, bool> insertValue(const V& value_value, TreeNode<V, K>*& pv, TreeNode<V, K>* the_value_parent);

  void print_keys_as_sideways_tree(std::ostream& ostr, const TreeNode<K, V>* p, int depth) const;
  void print_values_as_sideways_tree(std::ostream& ostr, const TreeNode<V, K>* p, int depth) const;
  
  int erase(const K& key_value, TreeNode<K, V>*& key_root);
  int erase(const V& value_value, TreeNode<V, K>*& value_root);

};

  template <class K, class V> 
  bidirectional_map<K, V>& bidirectional_map<K, V>::operator=(const bidirectional_map<K, V>& old) {
    if (&old != this) {
      this->destroy_tree(value_root);
	  this->destory_tree(key_root);
      value_root = this->copy_tree(old.value_root, NULL);
	  key_root = this->copy_tree(old.key_root, NULL);
      size_ = old.size_;
    }
    return *this;
  }

  // PRIVATE HELPER FUNCTIONS
  template <class K, class V> 
  TreeNode<K, V>* bidirectional_map<K, V>::copy_key_tree(TreeNode<K ,V>* old_root, TreeNode<K, V>* the_parent) {
    if (old_root == NULL) 
      return NULL;
    TreeNode<K, V> *answer = new TreeNode<K, V>(old_root->value);
    answer->left = copy_key_tree(old_root->left,answer);
    answer->right = copy_key_tree(old_root->right,answer);
    answer->parent = the_parent;
    return answer;
  }
  
  template <class K, class V> 
  TreeNode<V, K>* bidirectional_map<K, V>::copy_value_tree(TreeNode<V ,K>* old_root, TreeNode<V, K>* the_parent, TreeNode<K, V>* key_root) {
    if (old_root == NULL) 
      return NULL;

    TreeNode<V, K> *answer = new TreeNode<V, K>(old_root->value);
	TreeNode<V, K>* oldvalue_treeptr = old_root;
	while (oldvalue_treeptr->value != answer->value) {
		if (answer->value < oldvalue_treeptr->value) {
			oldvalue_treeptr = oldvalue_treeptr -> left;
		}
		else if (answer->value > oldvalue_treeptr->value) {
			oldvalue_treeptr = oldvalue_treeptr -> right;
		}
	}
	//now we have pointer to the same value in old tree
	//follow the link. This is the same key value that the new value will be linked to
	TreeNode<K, V>* keyval = oldvalue_treeptr->link;
	key_iterator newtree_keyitr = this->find(keyval->value);
	answer->link = (newtree_keyitr.ptr_);
	answer->link->link = answer;
    answer->left = copy_value_tree(old_root->left, answer, key_root);
    answer->right = copy_value_tree(old_root->right, answer, key_root);
    answer->parent = the_parent;
    return answer;
  }
  
  
  template <class K, class V> 
  void bidirectional_map<K, V>::print(std::ostream& ostr) const {
	std::cout << "=================================================" << std::endl;
	std::cout << "KEYS" << std::endl;
	print_keys_as_sideways_tree(ostr, key_root, 0);
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "VALUES" << std::endl;
	print_values_as_sideways_tree(ostr, value_root, 0);
	std::cout << "=================================================" << std::endl;
  }
  
  template <class K, class V> 
  void bidirectional_map<K, V>::print_keys_as_sideways_tree(std::ostream& ostr, const TreeNode<K, V>* p, int depth) const {
    if (p) {
      print_keys_as_sideways_tree(ostr, p->right, depth+1);
      for (int i=0; i<depth; ++i) ostr << "    ";
      ostr << p->value << " " << "[" << (p->link)->value << "]" << "\n";
      print_keys_as_sideways_tree(ostr, p->left, depth+1);
    }
  }
  
  template <class K, class V> 
  void bidirectional_map<K, V>::print_values_as_sideways_tree(std::ostream& ostr, const TreeNode<V, K>* p, int depth) const {
    if (p) {
      print_values_as_sideways_tree(ostr, p->right, depth+1);
      for (int i=0; i<depth; ++i) ostr << "    ";
      ostr << p->value << " " << "[" << (p->link)->value << "]" << "\n";
      print_values_as_sideways_tree(ostr, p->left, depth+1);
    }
  }
  
  template <class K, class V>
  V bidirectional_map<K, V>::operator[](const K& key_value){
	  key_iterator keyitr = this->find(key_value);
	  return ((keyitr.ptr_)->link)->value;
  }
  
  template <class K, class V>
  K bidirectional_map<K, V>::operator[](const V& value_value){
	  value_iterator valueitr = this->find(value_value);
	  return ((valueitr.ptr_)->link)->value;
  }
  
  // ITERATORS
  template <class K, class V> 
  key_iterator<K, V> bidirectional_map<K, V>::key_begin() const { 
    if (!key_root) return key_iterator(NULL,this);
    TreeNode<K, V>* p = key_root;
    while (p->left) p = p->left;
    return key_iterator(p,this);
  }
  
  template <class K, class V> 
  value_iterator<K, V> bidirectional_map<K, V>::value_begin() const { 
    if (!value_root) return value_iterator(NULL,this);
    TreeNode<V, K>* p = value_root;
    while (p->left) p = p->left;
    return value_iterator(p,this);
  }

  template <class K, class V> 
  void bidirectional_map<K, V>::destroy_key_tree(TreeNode<K, V>* p) {
    if (!p) return;
    destroy_key_tree(p->right);
    destroy_key_tree(p->left);
    delete p;
  }
  
  template <class K, class V> 
  void bidirectional_map<K, V>::destroy_value_tree(TreeNode<V, K>* p) {
    if (!p) return;
    destroy_value_tree(p->right);
    destroy_value_tree(p->left);
    delete p;
  }
  
  template <class K, class V> 
  key_iterator<K, V> bidirectional_map<K, V>::find(const K& key_value, TreeNode<K, V>* p) {
    if (!p) return this->key_end();
    if (p->value > key_value)
      return find(key_value, p->left);
    else if (p->value < key_value)
      return find(key_value, p->right);
    else
      return key_iterator(p,this);
  }
  
  template <class K, class V> 
  value_iterator<K, V> bidirectional_map<K, V>::find(const V& value_value, TreeNode<V, K>* p) {
    if (!p) return this->value_end();
    if (p->value > value_value)
      return find(value_value, p->left);
    else if (p->value < value_value)
      return find(value_value, p->right);
    else
      return value_iterator(p,this);
  }
  
  template <class K, class V> 
  //std::pair< key_iterator<K, V>, bool > bidirectional_map<K, V>::insert(std::pair(K const& key_value, V const& value_value)) { 
  std::pair< key_iterator<K, V>, bool > bidirectional_map<K, V>::insert(const std::pair<K, V>& vals) { 
	
	K key_value = vals.first;
	V value_value = vals.second;
	
    //std::pair< iterator, bool > insertKey_result = insertValue(key_value, key_root, NULL, value_value);
	//if (insertKey_result.first == iterator(NULL)
		
	//go into if statement if value and key is insertable
	if ((this->find(value_value) == this->value_end()) && (this->find(key_value) == this->key_end())) {
		
		std::pair< value_iterator, bool > insertValue_result = insertValue(value_value, value_root, NULL);
		std::pair< key_iterator, bool > insertKey_result = insertKey(key_value, key_root, NULL);
		
		//link them
		
		(insertValue_result.first).ptr_->link = (insertKey_result.first).ptr_;
		(insertKey_result.first).ptr_->link = (insertValue_result.first).ptr_;
		
		return insertKey_result;
		
	}
	//go into if statement if value is not insertable but key is
	else if (this->find(value_value) != this->value_end() && this->find(key_value) == this->key_end()) {
		//return NULL iterator because key does not exist before or after
		return std::pair<key_iterator, bool>(key_iterator(NULL, this), false);
	}
	//if key already exists, return iterator to preexisting key
	else if (this->find(key_value) != this->key_end()){
		//will return iterator to key that is already in map
		return insertKey(key_value, key_root, NULL);
	}
	
  }
  
  template <class K, class V> 
  std::pair<key_iterator<K, V>,bool> bidirectional_map<K, V>::insertKey(const K& key_value, TreeNode<K, V>*& pk, TreeNode<K, V>* the_key_parent) {  
	//if value is already in tree and is therefore non insertable, don't attempt to insert key
	if (!pk) {
	  pk = new TreeNode<K, V>(key_value);
	  pk->parent = the_key_parent;
	  this->size_++;
	  return std::pair<key_iterator,bool>(key_iterator(pk,this), true);
	}
	else if (key_value < pk->value)
	  return insertKey(key_value, pk->left, pk);
	else if (key_value > pk->value)
	  return insertKey(key_value, pk->right, pk);
	else
	  return std::pair<key_iterator,bool>(key_iterator(pk,this), false);
  }
  
  template <class K, class V> 
  std::pair<value_iterator<K, V>,bool> bidirectional_map<K, V>::insertValue(const V& value_value, TreeNode<V, K>*& pv, TreeNode<V, K>* the_value_parent) {
	//if key is already in tree and is therefore non insertable, don't attempt to insert value
	//if (this->find(key_value) == end()) {
		if (!pv) {
		  pv = new TreeNode<V, K>(value_value);
		  pv->parent = the_value_parent;
		  return std::pair<value_iterator,bool>(value_iterator(pv,this), true);
		}
		else if (value_value < pv->value)
		  return insertValue(value_value, pv->left, pv);
		else if (value_value > pv->value)
		  return insertValue(value_value, pv->right, pv);
		else
		  return std::pair<value_iterator,bool>(value_iterator(pv,this), false);
	}

  template <class K, class V> 
  int bidirectional_map<K, V>::erase(K const& key_value) {
	key_iterator keyitr = this->find(key_value);
	if (keyitr != this->key_end()) {
		V value_value = ((keyitr.ptr_)->link)->value;
		int erasekey = erase(key_value, key_root);
		int erasevalue = erase(value_value, value_root);
		return erasekey;
	}
	return 0;
  }

  template <class K, class V> 
  int bidirectional_map<K, V>::erase(K const& key_value, TreeNode<K, V>* &p) {
    if (!p) return 0;
    // look left & right
   if (p->value < key_value)
      return erase(key_value, p->right);
   else if (p->value > key_value)
      return erase(key_value, p->left);

    // Found the node.  Let's delete it
    assert (p->value == key_value);
    if (!p->left && !p->right) { // leaf
      delete p;
      p=NULL;       
    } else if (!p->left) { // no left child
      TreeNode<K, V>* q = p; 
      p=p->right; 
      assert (p->parent == q);
      p->parent = q->parent;
      delete q; 
    } else if (!p->right) { // no right child
      TreeNode<K, V>* q = p; 
      p=p->left;
      assert (p->parent == q);
      p->parent = q->parent;
      delete q; 
    } else { // Find rightmost node in left subtree
	  TreeNode<K, V>* temp = p;
      TreeNode<K, V>* q = p->left;
      while (q->right) q = q->right;
      //p->value = q->value;
      // recursively remove the value from the left subtree
      //int check = erase(q->value, p->left);
      //assert (check == 1);
	  if (q->parent != p){
		q->parent->right = NULL;
		q->left = p->left;
	  }
	  q->right = p->right;
	  q->parent = p->parent;
	  q->right->parent = q;
	  q->left->parent = q;
	  if (q->parent == NULL) {
		key_root = q;
	  }
	  delete temp;
    }
    return 1;
  }

  template <class K, class V> 
  int bidirectional_map<K, V>::erase(V const& value_value, TreeNode<V, K>* &p) {
    if (!p) return 0;
 
    // look left & right
   if (p->value < value_value)
      return erase(value_value, p->right);
    else if (p->value > value_value)
      return erase(value_value, p->left);

    // Found the node.  Let's delete it
    assert (p->value == value_value);
    if (!p->left && !p->right) { // leaf
      delete p;
      p=NULL;       
      this->size_--;    
    } else if (!p->left) { // no left child
      TreeNode<V, K>* q = p; 
      p=p->right; 
      assert (p->parent == q);
      p->parent = q->parent;
      delete q; 
      this->size_--;    
    } else if (!p->right) { // no right child
      TreeNode<V, K>* q = p; 
      p=p->left;
      assert (p->parent == q);
      p->parent = q->parent;
      delete q; 
      this->size_--;
    } else { // Find rightmost node in left subtree
	  TreeNode<V, K>* temp = p;
      TreeNode<V, K>* q = p->left;
      while (q->right) q = q->right;
	  if (q->parent != p){
		q->parent->right = NULL;
		q->left = p->left;
	  }
	  q->right = p->right;
	  q->parent = p->parent;
	  q->right->parent = q;
	  q->left->parent = q;
	  if (q->parent == NULL) {
		value_root = q;
	  }
	  delete temp;
	  this->size_--;
    }
    return 1;
  }

#endif