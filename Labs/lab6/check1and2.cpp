#include <iostream>
#include <vector>
#include <list>

void printVec(const std::vector<int>& v1) {
	std::cout << "Size of vector is: " << v1.size() << std::endl;
	std::cout << "Vector is:";
	for (unsigned int i=0; i < v1.size(); i++) {
		std::cout << " " << v1[i];
	}
	std::cout << "\n" << std::endl;
}

void printList(std::list<int>& l1) {
	std::cout << "Size of list is: " << l1.size() << std::endl;
	std::list<int>::iterator i;
	std::cout << "List is:";
	for (i=l1.begin(); i != l1.end(); i++) {
		std::cout << " " << *i;
	}
	std::cout << "\n" << std::endl;
}

void reverse_vector(std::vector<int>& v1) {
	for (unsigned int i = 0; i < (v1.size()/2); i++) {
		int valCopy = v1[i];
		v1[i] = v1[v1.size() - (i+1)];
		v1[v1.size() - (i+1)] = valCopy;
	}
}

void reverse_list(std::list<int>& l1){
	std::list<int>::reverse_iterator ri;
	std::list<int>::iterator i;
	unsigned int count = 0;
	for( ri = l1.rbegin(), i=l1.begin(); ri != l1.rend() && i!=l1.end(); ++ri, ++i ) {
		int valCopy = *i;
		*i = *ri;
		*ri = valCopy;
		count += 1;
		if (count >= (l1.size()/2)) {
			break;
		}
	}
}


int main() {
	std::cout << "\nUSING VECTORS\n" << std::endl;
	//does it work with vector with even amount of ints
	std::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	v1.push_back(7);
	v1.push_back(8);
	printVec(v1);
	reverse_vector(v1);
	printVec(v1);
	//does it work with vector with odd amount of ints
	std::vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	printVec(v2);
	reverse_vector(v2);
	printVec(v2);
	//does it work with vector with one value
	std::vector<int> v3;
	v3.push_back(1);
	printVec(v3);
	reverse_vector(v3);
	printVec(v3);
	//does it work with vector with 2 values
	std::vector<int> v4;
	v4.push_back(1);
	v4.push_back(2);
	printVec(v4);
	reverse_vector(v4);
	printVec(v4);
	//does it work with vector that is empty
	std::vector<int> v5;
	printVec(v5);
	reverse_vector(v5);
	printVec(v5);
	
	std::cout << "USING LISTS AND ITERATORS\n" << std::endl;
	//does it work with list with even amount of ints
 	std::list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.push_back(7);
	l1.push_back(8);
	printList(l1);
	reverse_list(l1);
	printList(l1);
	//does it work with lists with odd amount of ints
	std::list<int> l2;
	l2.push_back(1);
	l2.push_back(2);
	l2.push_back(3);
	l2.push_back(4);
	l2.push_back(5);
	printList(l2);
	reverse_list(l2);
	printList(l2);
	//does it work with lists with one value
	std::list<int> l3;
	l3.push_back(1);
	printList(l3);
	reverse_list(l3);
	printList(l3);
	//does it work with lists with two values
	std::list<int> l4;
	l4.push_back(1);
	l4.push_back(2);
	printList(l4);
	reverse_list(l4);
	printList(l4);
	//does it work with lists that is empty
	std::list<int> l5;
	printList(l5);
	reverse_list(l5);
	printList(l5);
}