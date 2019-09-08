#include "time.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	
	/*
	int hour, minute, second;
	
	std::cin >> hour >> minute >> second;
	
	
	Time t1;
	Time t2(hour, minute, second);
	
	std::cout << t1.getHour() << ":" << t1.getMinute()  << ":" << t1.getSecond() << std::endl;
	
	std::cout << t2.getHour() << ":" << t2.getMinute()  << ":" << t2.getSecond() << std::endl;
	*/

	//Check2
	
	/*
	
	int newHour, newMinute, newSecond;
	
	std::cin >> newHour >> newMinute >> newSecond;
	
	t2.setHour(newHour);
	t2.setMinute(newMinute);
	t2.setSecond(newSecond);
	
	t2.PrintAmPm();
	
	Time t3(12, 0 , 0);
	t3.PrintAmPm();
	Time t4(24,0,0);
	t4.PrintAmPm();
	Time t5(1, 1, 1);
	t5.PrintAmPm();
	Time t6(13, 1, 1);
	t6.PrintAmPm();
	*/
	
	std::vector<Time> Times;
	
	Time t7(5, 5, 6);
	Time t8(5, 5, 5);
	Time t9(5, 4, 6);
	Time t10(4, 4, 6);
	Time t11(10, 59, 59);
	Time t12(23, 1, 1);
	
	Times.push_back(t7);
	Times.push_back(t8);
	Times.push_back(t9);
	Times.push_back(t10);
	Times.push_back(t11);
	Times.push_back(t12);
	
	sort(Times.begin(), Times.end(), IsEarlierThan);
	
	for (int i=0; i < 6; i++){
		Times[i].PrintAmPm();
	}
}