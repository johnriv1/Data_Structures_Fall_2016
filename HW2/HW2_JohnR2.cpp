#include <fstream> // For Reading From & Writing To Files
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iomanip>

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
	
	std::string x = "";
	std::string match_num;
	std::string lane_num;
	std::vector<std::string> EventNameVec;
	std::vector<std::string> line_info_vec;
	std::vector<Participation> all_partic_info_vec;
	
	
	//if read into x and what is read is "EVENT" then start new partic_info_vec
	//while ((x == "EVENT") || ((in_str >> x) && (x == "EVENT"))) {
	while (((x == "HEAT") || (x =="SEMI") || (x =="FINAL") || (x == "EVENT")) || in_str >> x) {
		//read in event name and but words that make it up into a vector
		if (x == "EVENT" && in_str >> x) {
			EventNameVec.clear();
			EventNameVec.push_back(x);
			//While I have not finished reading in event name 
			//(after name is either SEMI HEAT or FINAL, so if x is one of those we know we have finished reading in name)
			while ((in_str >> x) && ((x!= "HEAT") && (x!="SEMI") && (x!="FINAL"))) {
				EventNameVec.push_back(x);
			}
			//std::cout << EventNameVec[0] << EventNameVec[1] << EventNameVec[2] << std::endl;
		}
		//x will be either HEAT, SEMI, or FINAL, the line will be info of one of the participations, 
		//  which will get put into a vector and then be used as an argument for the participation class.
		if ((x == "HEAT") || (x =="SEMI") || (x =="FINAL")) {
			if ((x == "HEAT") || (x == "SEMI")) {
				//std::cout << x << std::endl;
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
				//std::cout << x << std::endl;
				line_info_vec.push_back(x);
				in_str >> lane_num;                      //which lane participant swimmed in
				line_info_vec.push_back(lane_num);
				while ((in_str >> x) && (x!="EVENT") && (x!="HEAT") && (x!="SEMI") && (x!="FINAL")) {
					line_info_vec.push_back(x);
				}
			}
			//std::cout << EventNameVec[0] << EventNameVec[1] << EventNameVec[2] << std::endl;
			Participation p1(EventNameVec, line_info_vec);
			all_partic_info_vec.push_back(p1);
			line_info_vec.clear();
		}
	}
	
	std::string argv3(argv[3]);
	if (argv3 == "events") {
		//all_partic_info_vec by who swam fastest to who swam slowest.
		sort(all_partic_info_vec.begin(), all_partic_info_vec.end(), IsFasterThan);
		
		std::vector<std::string> EventNames_Vector;
		
		for (unsigned int i = 0; i< all_partic_info_vec.size(); i++) {
			//if event name vector doesnt contain event name, add it to vector. 
			if (std::find(EventNames_Vector.begin(), EventNames_Vector.end(), all_partic_info_vec[i].getEventName()) == EventNames_Vector.end()) {
				EventNames_Vector.push_back(all_partic_info_vec[i].getEventName());
			}
		}
		
		sort(EventNames_Vector.begin(), EventNames_Vector.end());
		
		//start writing output
		bool flag;
		unsigned int j = 0;
		int count = 0;
		int spacecount =0;
		//going to write out for each event
		for (unsigned int i = 0; i < EventNames_Vector.size(); i++) {
			spacecount = 0;
			count = 0;
			flag = false;
			out_str << 	std::setw(33) << std::left << EventNames_Vector[i];
			spacecount += 33;
			//goes through all_partic_info_vec until it gets a participation in the Event that we are currently looping through. 
			//This will lets us know how many times we will have to output for this event, 
			//which will let me output the correct labels for the distances.
			while (flag != true && j<all_partic_info_vec.size()) {
				j++;
				if (all_partic_info_vec[j].getEventName() == EventNames_Vector[i]) {
					for (unsigned int k = 0; k < (((all_partic_info_vec[j]).getTimesVec()).size()); k++) {
						out_str << std::setw(9) << std::right << std::to_string(50 * (k+1)) + "m";
						spacecount += 9;
						flag = true; 
					}
				}
			}
			out_str << std::setw(12) << std::right << "FINAL" << std::endl;
			spacecount += 12;
			for (unsigned int m=0; m<spacecount; m++) {
				out_str << "-";
			}
			out_str << "" << std::endl;
			for (unsigned int l=0; l< all_partic_info_vec.size(); l++) {
				if (all_partic_info_vec[l].getEventName() == EventNames_Vector[i] && count < 5) {
					all_partic_info_vec[l].output_line_events(out_str);
					count += 1;
				}
			}
			out_str << "" << std::endl;
		}
	}
	
	else if (argv3 == "participants") {
		
		std::vector<Participation> all_partic_info_vec_nodups;
		bool found = false;
		for (unsigned int i = 0; i < all_partic_info_vec.size(); i ++) {
			//if the no duplicates vector is empty, push back first value(class) of all_partic_info_vec
			found = false;
			if (all_partic_info_vec_nodups.size() == 0) {
				all_partic_info_vec_nodups.push_back(all_partic_info_vec[i]);
				found = true;     //so that we don't pushback the same one again in the if (found==false) statement below
 			}
			else {
				//goes through all_partic_info_vec_nodups to see if the current person in all_partic_info_vec has already been added to all_partic_info_vec_nodups
				for (unsigned int j = 0; j < all_partic_info_vec_nodups.size(); j ++) {
					//if we have encountered the same person
					if (all_partic_info_vec[i].getWholename() == all_partic_info_vec_nodups[j].getWholename()) {
						//if all_partic_info_vec[i] round is heat
						if (all_partic_info_vec[i].getRound() == "HEAT"){
							all_partic_info_vec_nodups[j].addHeat();
						}
						//if round is semi
						else if (all_partic_info_vec[i].getRound() == "SEMI") {
							all_partic_info_vec_nodups[j].addSemi();
						}
						//if round is final
						else if (all_partic_info_vec[i].getRound() == "FINAL") {
							all_partic_info_vec_nodups[j].addFinal();
						}
						found = true;
					}
				}
			}
			//if person was not already in all_partic_info_vec_nodups
			if (found == false) {
				all_partic_info_vec_nodups.push_back(all_partic_info_vec[i]);
			}
		}
		
		//std::cout << all_partic_info_vec_nodups.size() << std::endl;
		
		//Now that we have a vector with no duplicates and with each class having the right amount of heats, smis, and finals the person has participated in, we sort vector by country name.
		sort(all_partic_info_vec_nodups.begin(), all_partic_info_vec_nodups.end(), CountrySort);
		
		out_str << "COUNTRY  PARTICIPANT                HEATS  SEMIS  FINALS" << std::endl;
		out_str << "--------------------------------------------------------" << std::endl;
		for (unsigned int i =0; i<all_partic_info_vec_nodups.size(); i++) {
			all_partic_info_vec_nodups[i].output_line_participants(out_str);
		}
	}
}
	