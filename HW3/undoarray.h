#ifndef _undoarray_h
#define _undoarray_h

#include <iostream>
#include <iomanip>
#include <cstdlib>

//Declarations

template <class T>
class UndoArray {
public:
	//CONSTRUCTOR
	UndoArray(unsigned int n) { this -> create(n);}            
	//COPY CONSTRUCTOR                                   	
	UndoArray(const UndoArray& a) { copy(a); }              
	//ASSIGNMENT OPERATOR                                  
	UndoArray& operator=(const UndoArray& a);                 
	//DESTRUCTOR                                                
	~UndoArray();                                              
	
	//MEMBER FUNCTIONS AND OTHER OPERATORS
	unsigned int size() const { return size_; }            
	bool initialized(unsigned int i);                       
	const T& get(unsigned int i) const;                     
	void set(unsigned int i, const T& val);                     
	void print() const;                                           
	void undo(unsigned int i);
	void push_back(const T& t);

private:
	//PRIVATE MEMBER FUNCTIONS
	void create(unsigned int n);                              
	void copy(const UndoArray<T>& a);                        
	
	//REPRESENTATION
	unsigned int size_;
	unsigned int* counts_;   //pointer to array
	T** values_;   //pointer to array of pointers to arrays.
};

//Implementations

//CONSTRUCTOR
template <class T> void UndoArray<T>::create(unsigned int n) {
	size_ = n;
	counts_ = new unsigned int[n];         //counts now points to array of ints on heap
	for (unsigned int j = 0; j < n; j++) {
		counts_[j] = 0;
	}
	values_ = new T*[n];                     //values now points to array of pointers on heap
	for (unsigned int i = 0; i<n; i++) {
		values_[i] = NULL;                   //make each pointer in values array point to NULL
	}
}

//COPY CONSTRUCTOR
template <class T> void UndoArray<T>::copy(const UndoArray<T>& a) {
	size_ = a.size_;
	counts_ = new unsigned int[a.size_];
	for (unsigned int i = 0; i<a.size_; i++) {
		counts_[i] = a.counts_[i];
	}
	//make values point to new array of pointers to the size of counts
	values_ = new T*[a.size_];
	for (unsigned int i = 0; i<a.size_; i++) {
		//if the counts for a for this index is 0, make pointer for copy for this index point to NULL
		if (a.counts_[i] == 0) {
			values_[i] = NULL;
		}
		else {
			//allocate array for pointer
			values_[i] = new T[a.counts_[i]];      
			//loop through array just allocated and fill it with same values in a
			for (unsigned int j=0; j<a.counts_[i]; j++) {
				values_[i][j] = a.values_[i][j];
			}
		}
	}
}

//ASSIGNMENT OPERATOR
template <class T> UndoArray<T>& UndoArray<T>::operator=(const UndoArray<T>& a) {
	if (this != &a) {
		//delete pointers of pointers
		for (unsigned int i=0; i < size_; i++) {
			if (counts_[i] == 0) {
				delete values_[i];
			}
			else {
				delete [] values_[i];
			}
		}
		//delete array of pointers
		delete [] values_;
		delete [] counts_;
		//assignement
		this -> copy(a);
	}
	return *this;
}

//DESTRUCTOR
template <class T> UndoArray<T>::~UndoArray() {
	//delete pointers of pointers
	for (unsigned int i=0; i < size_; i++) {
		if (counts_[i] == 0) {
			delete values_[i];
		}
		else {
			delete [] values_[i];
		}
	}
	//delete array of pointers
	delete [] values_;
	delete [] counts_;
}

//get function
template <class T> const T& UndoArray<T>::get(unsigned int i) const{
	if (i > (size_-1)) {
		std::cerr << "ERROR: INDEX OUT OF RANGE" << std::endl;
		exit(1);
	}
	else if (counts_[i] == 0) {
		std::cerr << "ERROR: UNINITIALIZED INDEX" << std::endl;
		exit(1);
	}
	else {
		return values_[i][counts_[i]-1];
	}
}

//set function 
template <class T> void UndoArray<T>::set(unsigned int i, const T& val){
	if (i > (size_-1)) {
		std::cerr << "ERROR: INDEX OUT OF RANGE" << std::endl;
		exit(1);
	}
	unsigned int prevCounts = counts_[i];
	counts_[i] += 1;
	T* temp = values_[i];
	values_[i] = new T[counts_[i]];
	// loops through new allocated array prevCounts amount of times and copies the values of old array
	for (unsigned int j = 0; j < prevCounts; j++) {
		values_[i][j] = temp[j];
	}
	delete [] temp;
	// set final(new) value
	values_[i][counts_[i]-1] = val;
}

//print function
template <class T> void UndoArray<T>::print() const {
	
	std::cout << "size_:    " << size_ << std::endl;
	std::cout << "counts_:";
	for (unsigned int j = 0; j < size_; j++) {
		std::cout << "  " << counts_[j];
	}
	std::cout << std::endl;
	std::cout << "values_:";
	for (unsigned int k = 0; k < size_; k++) {
		if (values_[k] != NULL) {
			std::cout << "  .";
		}
		else {
			std::cout << "  /";
		}
	}
	std::cout << std::endl;
	
	int maxCount = 0;
	for (unsigned int i = 0; i < size_; i++){
		if (counts_[i] > maxCount) {
			maxCount = counts_[i];
		}
	}
	//loop through max count, then loop through sizes, then print value unless current value of j(looping through max count) is greater than 
	//actual number at the index of counts_
	for (unsigned int j = 0; j < maxCount; j++) {
		std::cout << "        ";
		for (unsigned int i = 0; i < size_; i++) {
			if (j < counts_[i]) {
				std::cout << std::setw(3) << std::right << values_[i][j];
			}
			else {
				std::cout << std::setw(3) << std::right << ' ';
			}
		}
		std::cout << std::endl;
	}
}

//undo function
template <class T> void UndoArray<T>::undo(unsigned int i) {
	if (i > (size_-1)) {
		std::cerr << "ERROR: INDEX OUT OF RANGE" << std::endl;
		exit(1);
	}
	if (counts_[i] == 0){
		std::cerr << "ERROR: INDEX HAS NO VALUES" << std::endl;
		exit(1);
	}
	else {
		counts_[i] -= 1;
		T* temp = values_[i];
		if (counts_[i] == 0) {
			values_[i] = NULL;
		}
		else {
			values_[i] = new T[counts_[i]];
			for (unsigned int j = 0; j < counts_[i]; j++) {
				values_[i][j] = temp[j];
			}
		}
		delete [] temp;
	}
}

template <class T> bool UndoArray<T>::initialized(unsigned int i) {
	if (i > (size_-1)) {
		std::cerr << "ERROR: INDEX OUT OF RANGE" << std::endl;
		exit(1);
	}
	return (counts_[i] != 0);
}
#endif