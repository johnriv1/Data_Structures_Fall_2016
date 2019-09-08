#include <cmath>
#include <iostream>

void compute_squares(unsigned int *a, unsigned int *b, unsigned int n) {
	unsigned int *p;
	unsigned int *q;
	for (p=a, q=b; p<a+n; ++p, ++q) {
		*q = pow(*p, 2);
	}
}

int main() {
	
	std::cout << "\nFirst check:" <<std::endl;
	unsigned int n = 3;
	unsigned int a[n] = {1,2,3};
	unsigned int b[n];
	compute_squares(a, b, n);

	for (unsigned int i = 0; i < n; ++i) {
		std::cout << b[i] << std::endl;
	}
	
	std::cout << "\nSecond check:" <<std::endl;
	n=1;
	unsigned int c[n] = {4};
	unsigned int d[n];
	compute_squares(c, d, n);

	for (unsigned int i = 0; i < n; ++i) {
		std::cout << d[i] << std::endl;
	}
	
	std::cout << "\nThird check:" <<std::endl;
	n=2;
	unsigned int e[n] = {0,9};
	unsigned int f[n];
	compute_squares(e, f, n);

	for (unsigned int i = 0; i < n; ++i) {
		std::cout << f[i] << std::endl;
	}
} 