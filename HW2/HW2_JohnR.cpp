#include <fstream> // For Reading From & Writing To Files
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Participation.h"

int main(int argc, char* argv[]) {

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
	
	std::string x, match_num, lane_num;
	std::vector<std::string> EventNameVec;
	std::vector<std::string> line_info_vec;
	std::vector<Participation> all_partic_info_vec;
	
	
	//if read into x and what is read is "EVENT" then start new partic_info_vec
	while ((x == "EVENT") || ((in_str >> x) && (x == "EVENT"))) {		
		//read in event name and but words that make it up into a vector
		if (in_str >> x) {
			EventNameVec.push_back(x);
			//While I have not finished reading in event name 
			//(after name is either SEMI HEAT or FINAL, so if x is one of those we know we have finished reading in name)
			while ((in_str >> x) && ((x!= "HEAT") && (x!="SEMI") && (x!="FINAL"))) {
				EventNameVec.push_back(x);
			}
		}
		//x will be either HEAT, SEMI, or FINAL, the line will be info of one of the participations, 
		//  which will get put into a vector and then be used as an argument for the participation class.
		if ((x == "HEAT") || (x =="SEMI") || (x =="FINAL")) {
			if ((x == "HEAT") || (x == "SEMI")) {
				line_info_vec.push_back(x);
				in_str >> match_num;                     //which semi or heat participant was apart of
				line_info_vec.push_back(match_num);
				in_str >> lane_num;                      //which lane participant swimmed in
				line_info_vec.push_back(lane_num);
				while ((in_str >> x) && (x!="EVENT") && (x!="HEAT") && (x!="SEMI") && (x!="FINAL")) {
					line_info_vec.push_back(x);
				}
			}
			else if (x == "FINAL") {
				line_info_vec.push_back(x);
				in_str >> lane_num;                      //which lane participant swimmed in
				line_info_vec.push_back(lane_num);
				while ((in_str >> x) && (x!="EVENT") && (x!="HEAT") && (x!="SEMI") && (x!="FINAL")) {
					line_info_vec.push_back(x);
				}
			}
		std::cout << EventNameVec[0] << EventNameVec[1] << EventNameVec[2] << std::endl;
		Participation p1(EventNameVec, line_info_vec);
		all_partic_info_vec.push_back(p1);
		line_info_vec.clear();
		EventNameVec.clear();
		}
	}
	
	std::cout << all_partic_info_vec.size() << " lines were recorded" << std::endl;
	std::cout << all_partic_info_vec[0].getRound() << std::endl;
	std::cout << all_partic_info_vec[0].getLane() << std::endl;
	std::cout << all_partic_info_vec[0].getFname() << std::endl;
	std::cout << all_partic_info_vec[0].getLname() << std::endl;
	std::cout << all_partic_info_vec[0].getCountry() << std::endl;
	std::vector <std::string> CopyVec(all_partic_info_vec[0].getTimesVec());
	for (unsigned int i = 0; i < CopyVec.size(); i++) {
		std::cout << CopyVec[i] << std::endl;
	}
	
}
	