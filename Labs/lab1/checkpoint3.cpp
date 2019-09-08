#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value

int main() {
	
	int length;
	float Total = 0;
	
	//gives length an integer value
	std::cout << "How many values will you enter" << std::endl;
	std::cin >> length;
	
	//creates an array with length of 'length'
	float values[length];
	
	std::cout << "Enter all your values" << std::endl;
	// Takes input as it comes in and puts it in array
	for (int i=0; i < length; i++) {
		std::cin >> values[i];
	}
	
	//calculate the total
	for (int a=0; a < length; a++) {
		Total += values[a];
	}
	
	//calculate the average
	float Average = (Total) / length;
	
	std::cout << "The Average is " << Average << std::endl;
	std::cout << "The numbers less than the average are:" << std::endl;
	// goes through array and prints the numbers that are less than the average
	for (int j=0; j<length; j++){
		if (values[j] < Average) {
			std::cout << values[j] << std::endl;
		}
	}
}