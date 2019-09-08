#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "Participation.h"

//function for converting all time string values into doubles that can be used to measure the time differences inbetween each lap.
std::vector<double> Time_strs_to_Time_doub(std::vector<std::string> Times) {
	std::vector<double> Time_doubs;
	double minutes_num;
	double temp;
	for (unsigned int i = 0; i < Times.size(); i++) {
		//if time is a minute or more
		if (Times[i].size() == 7) {
			std::string minutes_str(1, Times[i][0]);
			minutes_num = ::atof(minutes_str.c_str());
			Times[i].erase(0,2);
			temp = (::atof(Times[i].c_str())) + 60*minutes_num;
			Time_doubs.push_back(temp);
		}
		else {
			double temp = (::atof(Times[i].c_str()));
			Time_doubs.push_back(temp);
		}
	}
	
	return Time_doubs;
}

Participation::Participation(const std::vector<std::string>&  EventNameVec, const std::vector<std::string>&  line_info_vec) {
	
	EventName_ = "";
	
	//get entire event name from the first argument.
	for (unsigned int i = 0; i < EventNameVec.size(); i++) {
		//if its last word in name, don't add the space for the next word. 
		if (i == (EventNameVec.size()-1)) {
			EventName_ += EventNameVec[i];
		} 
		else {
			EventName_ += EventNameVec[i] + " ";
		}
	}
	
	Round_ = line_info_vec[0];
	
	if (Round_ == "FINAL") {
		Heatnum_ = 0;
		Seminum_ = 0;
		Finalnum_ = 1;
	}
	else if (Round_ == "SEMI") {
		Heatnum_ = 0;
		Seminum_ = 1;
		Finalnum_ = 0;
	}
	else if (Round_ == "HEAT") {
		Heatnum_ = 1;
		Seminum_ = 0;
		Finalnum_ = 0;
	}
	
	// If it is not Final round, assign variable keeping in mind that we assign an extra one that final does not have, Semi_Heat num
	if (Round_ != "FINAL") {
		SemiHeat_num_ = line_info_vec[1];
		Lane_ = line_info_vec[2];
		Fname_ = line_info_vec[3];
		Lname_ = line_info_vec[4];
		Country_ = line_info_vec[5];
		for (unsigned int i=6; i < line_info_vec.size(); i++) {
			Times_.push_back(line_info_vec[i]);
		}
	}
	else if (Round_ == "FINAL") {
		Lane_ = line_info_vec[1];
		Fname_ = line_info_vec[2];
		Lname_ = line_info_vec[3];
		Country_ = line_info_vec[4];
		for (unsigned int i=5; i < line_info_vec.size(); i++) {
			Times_.push_back(line_info_vec[i]);
		}
	}
	
	FinalTime_ = Times_[Times_.size()-1];
	Wholename_ = Fname_ + " " + Lname_;
	
	std::vector<double> Time_doubles = Time_strs_to_Time_doub(Times_);
	//calculate differences in lap times and put them on a seperate vector
	Time_differences_.push_back(Time_doubles[0]); 
	for (unsigned int i=1; i < Time_doubles.size(); i++) {
		double difference = (Time_doubles[i] - Time_doubles[i-1]);
		Time_differences_.push_back(difference); 
	}
}

//write line info to file
std::ostream& Participation::output_line_events(std::ostream& out_str) const{
	out_str << std::setw(37) << std::left << Wholename_;
	for (unsigned int i = 0; i < Time_differences_.size(); i++) {
		out_str << std::setw(9) << std::left << std::fixed << std::setprecision(2);
		out_str << Time_differences_[i];
	}
	out_str << std::setw(8) << std::right << Times_[Times_.size()-1] << std::endl;
	return out_str;
}

//This one is going to have to be done outside the function in main file.
std::ostream& Participation::output_line_participants(std::ostream& out_str) const{
	out_str << std::setw(9) << std::left << Country_;
	out_str << std::setw(31) << std::left << Wholename_;
	out_str << std::setw(7) << std::left << Heatnum_;
	out_str << std::setw(8) << std::left << Seminum_;
	out_str << Finalnum_ << std::endl; 
	return out_str;
}

void Participation::addHeat() {
	Heatnum_ += 1;
}

void Participation::addSemi() {
	Seminum_ += 1;
}

void Participation::addFinal() {
	Finalnum_ += 1;
}

//third argument for sort function
bool IsFasterThan(const Participation& P1, const Participation& P2) {
	
	std::vector<std::string> P1TimesVec = P1.getTimesVec();
	std::vector<std::string> P2TimesVec = P2.getTimesVec();
	std::string P1FinalTime_String = P1TimesVec[P1TimesVec.size() - 1];
	std::string P2FinalTime_String = P2TimesVec[P2TimesVec.size() - 1];
	double minutes1_num;
	double minutes2_num;
	double P1FinalTime_Double;
	double P2FinalTime_Double;
	
	//get the final time for P1 in the form of a double for comparison
	if (P1FinalTime_String.size() == 7) {
		std::string minutes_str(1, P1FinalTime_String[0]);
		minutes1_num = ::atof(minutes_str.c_str());
		P1FinalTime_String.erase(0,2);
		P1FinalTime_Double = (::atof(P1FinalTime_String.c_str())) + 60*minutes1_num;
	}
	else {
		P1FinalTime_Double = (::atof(P1FinalTime_String.c_str()));
	}
	
	//get the final time for P2 in the form of a double for comparison
	if (P2FinalTime_String.size() == 7) {
		std::string minutes_str(1, P2FinalTime_String[0]);
		minutes2_num = ::atof(minutes_str.c_str());
		P2FinalTime_String.erase(0,2);
		P2FinalTime_Double = (::atof(P2FinalTime_String.c_str())) + 60*minutes2_num;
	}
	else {
		P2FinalTime_Double = (::atof(P2FinalTime_String.c_str()));
	}
	
	//start checking if P1's final time is smaller than P2's final time
		// or if they're equal, sort by alphabetical order of Last name or First name (if last names are the same)
	if (P1FinalTime_Double < P2FinalTime_Double) {
		return true;
	}
	else if (P1FinalTime_Double == P2FinalTime_Double) {
		if (P1.getLname() < P2.getLname()) {
			return true;
		}
		else if (P1.getLname() == P2.getLname()) {
			if (P1.getFname() < P2.getFname()) {
				return true;
			}
		}
	}
	return false;
}

bool CountrySort(const Participation& P1, const Participation& P2) {
	if (P1.getCountry() < P2.getCountry()) {
		return true;
	}
	else if (P1.getCountry() == P2.getCountry()) {
		if (P1.getLname() < P2.getLname()) {
			return true;
		}
		else if (P1.getLname() == P2.getLname()) {
			if (P1.getFname() < P1.getFname()) {
				return true;
			}
		}
	}
	return false;
}
