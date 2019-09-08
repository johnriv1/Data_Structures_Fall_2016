#include "time.h"
#include <iostream>

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) {
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int H) {
	hour = H;
}

void Time::setMinute(int M) {
	minute = M;
}

void Time::setSecond(int S) {
	second = S;
}

void Time::PrintAmPm() {
	
	int hourPrint;
	std::string minutePrint, secondPrint;
	std::string AmPm = "am";
	hourPrint = hour;
	minutePrint = "";
	secondPrint = "";
	
	if (hour > 12) {
		hourPrint = hour-12;
		AmPm = "pm";
	}
	
	if (hourPrint == 12) {
		if (AmPm == "am"){
			AmPm = "pm";
		}
		else {
			AmPm = "am";
		}
	}
	
	if (hourPrint == 0) {
		hourPrint = 12;
		AmPm = "am";
	}
	
	if (minute < 10) {
		minutePrint = "0";
	}
	
	if (second < 10) {
		secondPrint = "0";
	}
	std::cout << hourPrint << ":" << minutePrint << minute << ":" << secondPrint << second << " " << AmPm << std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour() < t2.getHour()) {
		return true;
	}
	else if (t1.getHour() == t2.getHour()) {
		if (t1.getMinute() < t2.getMinute()) {
			return true;
		}
		else if (t1.getMinute() == t2.getMinute()){
			if (t1.getSecond() < t2.getSecond()) {
				return true;
			}
		}
	}
	return false;	
}