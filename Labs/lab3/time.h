#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>

class Time {

public:
	Time();
	Time(uintptr_t hour, uintptr_t minute, uintptr_t second);
	
	//ACCESSORS
	uintptr_t getHour() const;
	uintptr_t getMinute() const;
	uintptr_t getSecond() const;
	
	//MODIFIERS
	void setHour(uintptr_t aHour);
	void setMinute(uintptr_t aMinute);
	void setSecond(uintptr_t aSecond);
	
	//Other
	void PrintAmPm();
	
private:
	uintptr_t hour;
	uintptr_t minute;
	uintptr_t second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);