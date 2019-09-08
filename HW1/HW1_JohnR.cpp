#include <fstream> // For Reading From & Writing To Files
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h> // atoi

//function for putting words into a vector
void read_words(std::ifstream & in_str, std::vector<std::string> & words) {
	std::string word;
	while (in_str >> word) {
		words.push_back(word);
	}
}

//Flush left function
void flush_left(std::vector<std::string> words, std::ofstream & out_str, unsigned int width) {
	//print the top border
	out_str << std::string(width + 4, '-') << std::endl;
	std::string linecontents;
	std::string wholeline;
	//while vector still has words
	std::cout << words.size() << std::endl; //
	for (unsigned int i=0; i < words.size(); i++) {
		//if entire line will still be within width restriction
		//std::cout << i << std::endl; //
		if ((linecontents + words[i] + " ").size() <= width) {
			//add words onto that line
			linecontents += (words[i] + " ");
			//std::cout << linecontents << std::endl; //
			wholeline = "| " + linecontents + " |";
		}
		//else, write line/ finish line and move onto the next
		else {
			//fill rest of line with remaining spaces
			//std::cout << (width-linecontents.size()) << std::endl;
			linecontents += std::string((width - linecontents.size()), ' ');
			//std::cout << linecontents << std::endl; //
			//write the finished line to file
			wholeline = "| " + linecontents + " |";
			out_str << wholeline << std::endl;
			//std::cout << wholeline << std::endl;
			//empty line contents for new line
			linecontents = "";
			//fill line contents with next word
			linecontents += (words[i] + " ");
			wholeline = "| " + linecontents + " |";
			if (i == (words.size()-1)){
				linecontents += std::string((width - linecontents.size()), ' ');
				wholeline = "| " + linecontents + " |";
				out_str << wholeline << std::endl;
			}
		}
	//print the bottom border
	}
	out_str << std::string(width + 4, '-') << std::endl;
	//std::cout << std::string(width + 4, '-') << std::endl; //
}

//Flush right function

//Full justify function

int main(int argc, char* argv[]) {
	
	std::vector<std::string> words;
	
	//open input stream
	std::ifstream in_str(argv[1]);
	//Check to see that it opened
	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	
	//open output stream
	std::ofstream out_str(argv[2]);
	//check to see if opened
	if (!out_str.good()) {
		std::cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}
	
	//fills words vector in
	read_words(in_str, words);
	
	//test to see if vector was filled in correctly
	/*for (int i=0; i<words.size(); i++)
		std::cout << words[i] << std::endl;
	*/
	
	unsigned int width = atoi(argv[3]);

	flush_left(words, out_str, width);
}
