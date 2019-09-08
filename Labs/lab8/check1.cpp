#include <iostream>
#include <stdlib.h>     // abs
#include <algorithm>    // min

int toOrigin(int x, int y) {
	int distance = std::min(abs(x),abs(y)); 
	if (x==0 || y==0) {
		return 1;
	}
	return toOrigin(x-1, y) + toOrigin(x, y-1);
}

int main () {
	std::cout << toOrigin(0,0) << std::endl;
	std::cout << toOrigin(2,1) << std::endl;
	std::cout << toOrigin(3,3) << std::endl;
	std::cout << toOrigin(0,3) << std::endl;
}