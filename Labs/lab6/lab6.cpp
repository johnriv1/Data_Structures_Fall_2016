#include <iostream>
#include <list>
#include <string>

// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
  int value;
  Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
  // print the name of this list
  std::cout << name;
  // use a temporary pointer to walk down the list
  Node *tmp = my_linked_list;
  while (tmp != NULL) {
    // print out each element
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list(const std::list<int> &lst) {

  // create a linked list chain of Nodes, populating the structure
  // with the data in the STL list

  // NOTE: this code should work for input STL lists of arbitrary
  // length

  Node *a = new Node;
  Node *head = a;
  std::list<int>::const_iterator p;
  std::list<int>::const_iterator q = lst.end();
  q--;
  for (p = lst.begin(); p!=lst.end(); p++) {
	if (q != p) {
		a->value = *p;
		a->ptr = new Node;
		a = a->ptr;
	}
	else {
		a->value = *p;
		a->ptr = NULL;
	}
  }
  return head;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {

  // rearrange the pointers in the linked list chain of Nodes,
  // so that the structure is reversed.  

  // NOTE: Do not edit the values of the Nodes.  Do not create any new
  // Node objects (don't call 'new').  Instead, change the ptrs of the
  // existing Nodes to shuffle the order.

  Node *f = input;
  Node *rEnd = NULL;
  Node *rHead;
  while (f != NULL) {
	rHead = NULL;
	rEnd = rHead; 
	f = f->ptr;
	rEnd -> ptr = f;
  }
  rEnd = input;

}


// ===========================================================================

int main() {

  // manually create a linked list of notes with 4 elements
  Node* a = new Node; 
  a->value = 6; 
  a->ptr = new Node;
  a->ptr->value = 7;
  a->ptr->ptr = new Node;
  a->ptr->ptr->value = 8;
  a->ptr->ptr->ptr = new Node;
  a->ptr->ptr->ptr->value = 9;
  a->ptr->ptr->ptr->ptr = NULL;
  // print out this list
  print_linked_list("a",a);

  // create an STL list with 4 elements
  std::list<int> b;
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);
  b.push_back(10);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c = make_linked_list_from_STL_list(b);
  // print that data
  print_linked_list("c",c);

  // 
  // WRITE A FEW MORE TEST CASES OF make_linked_list_from_STL_list
  //
	
  // create an STL list with 3 elements
  std::list<int> b1;
  b1.push_back(10);
  b1.push_back(11);
  b1.push_back(12);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c1 = make_linked_list_from_STL_list(b1);
  // print that data
  print_linked_list("c1",c1);
  
  // create an STL list with 1 element
  std::list<int> b2;
  b2.push_back(10);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c2 = make_linked_list_from_STL_list(b2);
  // print that data
  print_linked_list("c2",c2);

  
  // reverse a linked list of nodes
  //Node* d = reverse_nodes_in_linked_list(c);
  // print this data
  //print_linked_list("d",d);

  // 
  // WRITE A FEW MORE TEST CASES OF reverse_nodes_in_linked_list
  //


  // NOTE: We are not deleting any of the Nodes we created...  so this
  //       program has some memory leaks!  More on this in future
  //       lectures & labs :)

}

// ===========================================================================
