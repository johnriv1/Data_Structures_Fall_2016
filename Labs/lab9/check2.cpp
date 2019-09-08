#include <map>
#include <iostream>
#include <vector>
#include <fstream> // For Reading From & Writing To Files

void printModes(std::ifstream& istr){
	std::map<std::string, int> counters;
	std::string i;
	while (istr >> i) {
		std::map<std::string, int>::iterator tmp = counters.find(i);
		if (tmp == counters.end()) {
			counters.insert(std::make_pair(i, 1));
		}
		else {
			tmp -> second ++;
		}
	}
	int max = 0;
	std::vector<std::string> modes;
	std::map<std::string, int>::const_iterator it;
	for (it = counters.begin(); it != counters.end(); ++it) {
		if (it->second > max) {
			max = it->second;
			if (modes.size() > 0) {
				modes.clear();
			}
			modes.push_back(it->first);
		}
		else if (it->second == max) {
			modes.push_back(it -> first);
		}
	}
	std::cout << "The Modes Are" << std::endl;
	for (unsigned int k=0; k < modes.size(); k++) {
		std::cout << modes[k] << std::endl;
	}
}
int main(int argc, char* argv[]) {
	
	std::ifstream istr(argv[1]);
	if (!istr.good()) {
		std::cerr << "ERROR!  cannot open " << argv[1] << std::endl;
		exit(0);
	}
	
	//std::vector<int> v = {19, 83, -12, 83, 65, 19, 45, -12, 45, 19, 45};
	//printModes(v);
	//std::vector<int> v1 = {45, 45, 45, 45, 45, 45};
	//printModes(v1);
	//std::vector<int> v2 = {0,1, 2, 3};
	//printModes(v2);
	//std::vector<int> v3;
	//printModes(v3);
	//std::vector<int> v4 = {0, -1, -1, -2};
	//printModes(v4);
	
	printModes(istr);
	return 0;
}