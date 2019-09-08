#include <fstream> // For Reading From & Writing To Files
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h> // atoi
#include <string>

//function for putting words into a vector
void read_words(std::ifstream & in_str, std::vector<std::string> & words) {
	std::string word;
	while (in_str >> word) {
		words.push_back(word);
	}
}

void write_fulljustify(int numspaces_needed, std::vector <std::string> LineWords, std::ofstream & out_str) {
	int x;  //number of spaces inbetween two words/ after word at current index
	float y;  //used to compare to x and see if x is a whole number
	int i = 0;
	int rem_spaces = numspaces_needed;  //number of spaces left that we need to put into the line
	//if there is only one word on the line
	if (LineWords.size() == 1) {
		LineWords[0] += std::string(rem_spaces, ' ');
	}
	else {
		while (rem_spaces > 0) {
			x = (rem_spaces)/(LineWords.size() - 1 - i);
			y = (rem_spaces*1.0)/(LineWords.size() - 1 - i);
			//check if division results in whole number
			if (x == y) {
				rem_spaces -= x;
				LineWords[i] += std::string(x, ' ');
			}
			else {
				x += 1;
				rem_spaces -= x;
				LineWords[i] += std::string(x, ' ');
			}
			std::cout << x << std::endl;
			i += 1;
		}
	}
	//loop through vector, writing each string to file as part of one line
	out_str << "| ";
	for (unsigned int j = 0; j<LineWords.size(); j++) {
		out_str << LineWords[j];
	}
	out_str << " |" << std::endl;
}

//Flush left function
void flush_left(std::vector<std::string> words, std::ofstream & out_str, unsigned int width) {
	//print the top border
	out_str << std::string(width + 4, '-') << std::endl;
	std::string linecontents;
	//while vector still has words
	for (unsigned int i=0; i < words.size(); i++) {
		//if entire line + ' ' will still be within width restriction
		if ((linecontents + words[i] + " ").size() <= width) {
			//add word + ' ' onto that line
			linecontents += (words[i] + " ");
			// if we are on last index, fill next line with remaining ' '
			if (i == (words.size()-1)){
				linecontents += std::string((width - linecontents.size()), ' ');
				out_str << "| " + linecontents + " |" << std::endl;
			}
		}
		else {
			//if line contents + word and no space is equal to the width ,add words onto that line without the space
			if ((linecontents + words[i]).size() == width) {
				linecontents += (words[i]);
			}
			//regardless of having a space following or not, next word will not fit
			else {
				//fill rest of line with remaining spaces
				linecontents += std::string((width - linecontents.size()), ' ');
				//write the finished line to file
				out_str << "| " + linecontents + " |" << std::endl;
				//empty line contents for new line
				linecontents = "";
				//fill line contents with word
				linecontents += (words[i] + " ");
				// if we are on last index, fill line with remaining ' '
				if (i == (words.size()-1)){
					linecontents += std::string((width - linecontents.size()), ' ');
					out_str << "| " + linecontents + " |" << std::endl;
				}
			}
		}
	//print the bottom border
	}
	out_str << std::string(width + 4, '-') << std::endl;
	//std::cout << std::string(width + 4, '-') << std::endl; //
}

//Flush right function
void flush_right(std::vector<std::string> words, std::ofstream & out_str, unsigned int width) {
	//print the top border
	out_str << std::string(width + 4, '-') << std::endl;
	std::string linecontents;
	//while vector still has words
	for (unsigned int i=0; i < words.size(); i++) {
		//if entire line + ' ' will still be within width restriction
		if ((linecontents + " " + words[i]).size() <= width) {
			//add word + ' ' onto that line
			linecontents += (" " + words[i]);
			// if we are on last index, fill next line with remaining ' ' and write.
			if (i == (words.size()-1)){
				linecontents.insert(0,std::string((width - linecontents.size()), ' '));
				out_str << "| " + linecontents + " |" << std::endl;
			}
		}
		else {
			//if line contents + word and no space is equal to the width
			if ((linecontents + words[i]).size() == width) {
				//delete ' ' from left side to make room for ' ' and word on right side
				linecontents.erase(0,1);
				linecontents += (" " + words[i]);
			}
			//regardless of having a space following or not, next word will not fit
			else {
				//fill rest of line with remaining spaces
				linecontents.insert(0,std::string((width - linecontents.size()), ' '));
				//write the finished line to file
				out_str << "| " + linecontents + " |" << std::endl;
				//empty line contents for new line
				linecontents = "";
				//fill line contents with next word
				linecontents += (" " + words[i]);
				// if we are on last index, fill line with remaining ' '
				if (i == (words.size()-1)){
					linecontents.insert(0,std::string((width - linecontents.size()), ' '));
					out_str << "| " + linecontents + " |" << std::endl;
				}
			}
		}
	}
	//print the bottom border
	out_str << std::string(width + 4, '-') << std::endl;
}

//Full justify function
void full_justify(std::vector<std::string> words, std::ofstream & out_str, unsigned int width) {
	
	//print the top border
	out_str << std::string(width + 4, '-') << std::endl;
	//linecontents only used to make sure word with at least one space will fit in between them
	std::string linecontents;
	//LineWords is vector containing words for current line, will be used as an argument for write_fulljustify function.
	//Necessary amount of spaces will be added onto the end of the words(strings) and then outputted 
	std::vector <std::string> LineWords;
	//numspaces_needed will be the amount of spaces needed to fill up line
	int numspaces_needed;
	//letters_string is total amount of characters from the words that will be filling up line already. Will be used to calculate numspaces_needed.
	std::string letters_string;
	
	//while vector still has words to go through
	for (unsigned int i=0; i < words.size(); i++) {
		//if entire line + ' ' will still be within width restriction
		if ((linecontents + words[i] + " ").size() <= width) {
			
			linecontents += (words[i] + " ");
			LineWords.push_back(words[i]);
			letters_string += words[i];
			
			// if we are on last index, Left Justify current line
			if (i == (words.size()-1)){
				linecontents += std::string((width - linecontents.size()), ' ');
				out_str << "| " + linecontents + " |" << std::endl;
			}
		}
		else {
			//if line contents + word and no space is equal to the width
			if ((linecontents + words[i]).size() == width) {
				//add word onto linecontents without the space (pressing against edge of border)
				linecontents += (words[i]);
				LineWords.push_back(words[i]);
				letters_string += words[i];
			}
			//regardless of having a ' ' following or not, word will not fit
			else {
				//write the finished line to file
				numspaces_needed = (width - letters_string.size());
				write_fulljustify(numspaces_needed, LineWords, out_str);
				//reset values for new line for new line
				linecontents = "";
				LineWords.clear();
				letters_string = "";
				//fill line contents with word
				linecontents += (words[i] + " ");
				LineWords.push_back(words[i]);
				letters_string += (words[i]);
				// if we are on last index, Left Justify current line
				if (i == (words.size()-1)){
					linecontents += std::string((width - linecontents.size()), ' ');
					out_str << "| " + linecontents + " |" << std::endl;
				}
			}
		}
	}
	//print the bottom border
	out_str << std::string(width + 4, '-') << std::endl;
}

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
	
	unsigned int width = atoi(argv[3]); //converts command line argument 3 to an int
	
	std::string argv4(argv[4]); //changes command line argument to std::string
	
	if (argv4 == "flush_left"){
		flush_left(words, out_str, width);
	}
	else if (argv4 == "flush_right") {
		flush_right(words, out_str, width);
	}
	else if (argv4 == "full_justify") {
		full_justify(words, out_str, width);
	}
	
}
