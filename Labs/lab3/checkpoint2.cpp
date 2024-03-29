#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>


// NOTE: For this lab we'll use "uintptr_t", a specially defined
// integer type that is the same size in memory as a pointer.  We'll
// use this type everywhere, instead of "int".  On 32 bit
// machines/compilers, this type is probably 4 bytes, and on 64 bit
// machines/compilers, this is probably 8 bytes.


// GLOBAL VARIABLES used by print_stack, label_stack, and clear_stack
std::vector<uintptr_t*> GLOBAL_addresses;
std::vector<std::string> GLOBAL_labels;


// ==============================================================================
//
// This function does a limited print of the data stored on the stack
// in the range of the addresses currently "labeled" and stored in the
// global variables above.
//
// To make the output more readable, the function assumes that integer
// "values" will be between -1000 & 1000 and addresses will be within
// +/- 1000*4 (or *8) bytes from any of the labeled addresses.
// Anything else is assumed to be "garbage"
//
void print_stack() { 

  assert (GLOBAL_addresses.size() == GLOBAL_labels.size());
  if (GLOBAL_addresses.size() == 0) {
    std::cerr <<  "No labeled addresses to print" << std::endl;
    return;
  }

  // Identify the range of stack data to print
  uintptr_t* min_address = GLOBAL_addresses[0];
  uintptr_t* max_address = GLOBAL_addresses[0];
  int max_label_width = GLOBAL_labels[0].size();
  for (int i = 1; i < GLOBAL_addresses.size(); i++) {
    if (GLOBAL_addresses[i] > max_address) { max_address = GLOBAL_addresses[i]; }
    if (GLOBAL_addresses[i] < min_address) { min_address = GLOBAL_addresses[i]; }
    if (GLOBAL_labels[i].size() > max_label_width) { max_label_width = GLOBAL_labels[i].size(); }
  }

  // double check that my uintptr_t is actually the size of a pointer
  assert (sizeof(uintptr_t) == sizeof(void*));
  // double check that the start and end address are aligned 
  assert ((((uintptr_t)min_address) & (sizeof(uintptr_t)-1)) == 0);
  assert ((((uintptr_t)max_address) & (sizeof(uintptr_t)-1)) == 0);

  // double check that the range of address is reasonable 
  if (max_address-min_address > 1000) {
    std::cerr << "WARNING: trying to print too much" << std::endl;
    return;
  }

  // loop over all addresses in the range (plus some above & below)
  std::cout << "-----------------------------------------" << std::endl;
  for (uintptr_t* address = max_address+5; address >= min_address-5; address--) {
    std::string label = "";
    for (int i = 0; i < GLOBAL_addresses.size(); i++) {
      if (address == GLOBAL_addresses[i]) { label = GLOBAL_labels[i]; }
    }
    std::cout << std::setw(max_label_width) << label << " location: " << address;

    // this location might store a value (we assume all values are integers)
    int an_int = (int)(*address);
    // or it might store an address (so we cast it to a pointer)
    uintptr_t* an_address = (uintptr_t*)(*address);

    // if it's a value
    if (an_int > -1000 && an_int < 1000) {
      std::cout << "  VALUE:   " << an_int << std::endl;
    } 
    // if it's an address
    else if (an_address >= min_address-1000 && an_address <= max_address+1000) {
      std::cout << "  POINTER: " << an_address << std::endl;
    }
    // otherwise it's probably garbage
    else { 
      std::cout << "  garbage? " << std::endl;
    }
  }
  std::cout << "-----------------------------------------" << std::endl;
}


// add a label to a particular address in the stack
// NOTE: We use global variables for simplicity for this exercise
void label_stack(uintptr_t* address, const std::string& tag) {
  for (int i = 0; i < GLOBAL_addresses.size(); i++) {
    // check to see if that address is already labeled
    if (address == GLOBAL_addresses[i]) {
      // add additional labels
      GLOBAL_labels[i] += ", " + tag;      
      return;
    }
  }
  GLOBAL_addresses.push_back(address);
  GLOBAL_labels.push_back(tag);
}


// clear all previous labels
// NOTE: We use global variables for simplicity for this exercise
void clear_stack_labels() {
  GLOBAL_addresses.clear();
  GLOBAL_labels.clear();
}


void compute_squares(uintptr_t *a, uintptr_t *b, uintptr_t n) {
	uintptr_t *p;
	uintptr_t *q;
	for (p=a, q=b; p<(a+n); ++p, ++q) {
		*q = pow(*p,2);
	}
}

int main(){
	
	std::cout << "size of uintptr_t: " << sizeof(uintptr_t) << std::endl;
	std::cout << "" << std::endl;
	uintptr_t n = 3;
	uintptr_t a[3] = {1,2,3};
	uintptr_t b[3] = {0, 0, 0};
	
	std::cout << "Before and after correct use of function compute_squares" << std::endl;
	std::cout << "n address: " << &n << std::endl;
	std::cout << "a address: " << &a << std::endl;
	std::cout << "b address: " << &b << std::endl;
	
	label_stack(&n,"n");
	label_stack(&a[0],"a[0]");
	label_stack(&a[2],"a[2]");
	label_stack(&b[0],"b[0]");
	label_stack(&b[2],"b[2]");

	print_stack();
	
	compute_squares(a, b, n);
	
	print_stack();
	
	clear_stack_labels();
	
	n = 4;
	uintptr_t c[3] = {1,2,3};
	uintptr_t d[3] = {0,0,0};
	
	std::cout << "Before and after n > size of vectors" << std::endl;
	std::cout << "n address: " << &n << std::endl;
	std::cout << "c address: " << &c << std::endl;
	std::cout << "d address: " << &d << std::endl;
	
	label_stack(&n,"n");
	label_stack(&c[0],"c[0]");
	label_stack(&c[2],"c[2]");
	label_stack(&d[0],"d[0]");
	label_stack(&d[2],"d[2]");

	print_stack();
	
	compute_squares(c, d, n);
	
	print_stack();
	
	clear_stack_labels();
	
	n = 2;
	uintptr_t e[3] = {1,2,3};
	uintptr_t f[3] = {0,0,0};
	
	std::cout << "Before and after n < size of vectors" << std::endl;
	std::cout << "n address: " << &n << std::endl;
	std::cout << "e address: " << &e << std::endl;
	std::cout << "f address: " << &f << std::endl;
	
	label_stack(&n,"n");
	label_stack(&e[0],"e[0]");
	label_stack(&e[2],"e[2]");
	label_stack(&f[0],"f[0]");
	label_stack(&f[2],"f[2]");

	print_stack();
	
	compute_squares(e, f, n);
	
	print_stack();
	
}

