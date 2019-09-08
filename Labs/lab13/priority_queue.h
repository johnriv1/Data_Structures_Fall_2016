#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
	for (int i = 0; i < values.size(); i++) {
		m_heap.push_back(values[i]);
		percolate_up(m_heap.size() - 1);
	}
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
	m_heap.push_back(entry);
	percolate_up(m_heap.size() - 1);
  }
  
  void percolate_up(int i)
  {
    while (i!=0) {
	  //if value of current index is less than value of its parent
	  if  ( m_heap[i] < m_heap[(i-1)/2] ) {
	    //swap them
		T curr = m_heap[i];
		T parent = m_heap[(i-1)/2];
		m_heap[i] = parent;
		m_heap[(i-1)/2] = curr;
		//set index to the index of the parent
		i = (i-1)/2;
      }
	  //if its valid
	  else {
		break;
	  }
	}
  }

  void pop() 
  {
    assert( !m_heap.empty() );
	int i;
	i = ((((signed int) m_heap.size()-1)-1)/2);
	if (i > 0) {
		int left = 2*i + 1;
		int right = 2*i + 2;
		if (right <= (m_heap.size() - 1)){
			m_heap[0] = m_heap[right];
			m_heap.pop_back();
		}
		else if (left <= (m_heap.size() - 1)) {
			m_heap[0] = m_heap[left];
			m_heap.pop_back();
		}
		percolate_down(0);
	}
	else {
		m_heap.pop_back();
		percolate_down(0);
	}
  }
  
  void percolate_down(int i)
  {
	//while i has a left child
	while ((2*i+1) <= (m_heap.size()-1)) {
		int child;
		//if it has a right child and if value of right child is less than value of left child
		if (((2*i+2) <= (m_heap.size() - 1)) && (m_heap[2*i+2] < m_heap[2*i+1])) {
			child = 2*i+2;
		}
		else {
			child = 2*i+1;
		}
		if (m_heap[child] < m_heap[i]) {
			//swap them
			T child_val = m_heap[child];
			T curr_val = m_heap[i];
			m_heap[child] = curr_val;
			m_heap[i] = child_val;
			i = child;
		}
		else {
			break;
		}
	}  
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }
  
  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
	for (int i = 0; i < heap.size(); i++) {
		//if it has a right child and a left child
		if ((2*i+2) <= (heap.size() - 1)) {
			if (heap[i] > heap[2*i+1] && heap[i] > heap[2*i+2]) {
				return false;
			}
		}
		//if it only has a left child
		else if ((2*i+1) <= (heap.size() - 1)) {
			if (heap[i] > heap[2*i+1]) {
				return false;
			}
		}
	}
	return true;
  }
/*
  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
	int i = 0;
	return this->check_heap( this->m_heap, i);
  }
  
  bool check_heap( const std::vector<T>& heap, int i)
  {
	if (i > (((signed int) heap.size()-1)-1)/2) {
		return true;
	}
	//if it has a right child and a left child
	if ((2*i+2) <= (heap.size() - 1)) {
		if (heap[i] < heap[2*i+1] && heap[i] < heap[2*i+2]) {
			return (check_heap(heap, 2*i+1)) && (check_heap(heap, 2*i+2));
		}
		return false;
	}
	//if it only has a right child
	else {
		if (heap[i] < heap[2*i+1]) {
			return (check_heap(heap, 2*i+1));
		}
		return false;
	}
  }
  */

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
	for (int i = 0; i < v.size(); i++) {
		perculate_down(i);
	}
}

#endif
