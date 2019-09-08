#include "time.h"
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond) {
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

uintptr_t Time::getHour() const {
	return hour;
}

uintptr_t Time::getMinute() const {
	return minute;
}

uintptr_t Time::getSecond() const {
	return second;
}

void Time::setHour(uintptr_t H) {
	hour = H;
}

void Time::setMinute(uintptr_t M) {
	minute = M;
}

void Time::setSecond(uintptr_t S) {
	second = S;
}

void Time::PrintAmPm() {
	
	uintptr_t hourPrint;
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