class Time {

public:
	Time();
	Time(int hour, int minute, int second);
	
	//ACCESSORS
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	
	//MODIFIERS
	void setHour(int aHour);
	void setMinute(int aMinute);
	void setSecond(int aSecond);
	
	//Other
	void PrintAmPm();
	
private:
	int hour;
	int minute;
	int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);