#include <string>
#include <vector>

class Participation {
public:

	//CONSTRUCTOR
	//vector contents: Eventname1, Eventname2, Eventname3, Round, **SemiHeat_num, First name, Last name, Country, Times)
	Participation(const std::vector<std::string>&  EventNameVec, const std::vector<std::string>&  line_info_vec);
	
	//ACCESSORS
	//many of these are for testing purposes
	std::string getFname() const { return Fname_; }
	std::string getLname() const { return Lname_; }
	std::string getWholename() const { return Wholename_; }
	std::string getRound() const { return Round_; }
	std::string getEventName() const { return EventName_; }
	std::string getLane() const { return Lane_; }
	std::string getCountry() const { return Country_; }
	std::vector<std::string> getTimesVec() const { return Times_; }
	std::vector<double> getTimesDifferencesVec() const { return Time_differences_; }
	std::string getFinalTime() const { return FinalTime_; }
	int getHeatNum() const { return Heatnum_; }
	int getSemiNum() const { return Seminum_; }
	int getFinalNum() const { return Finalnum_; }
	
	//MODIFIERS
	void addHeat();
	void addSemi();
	void addFinal();
	
	//OTHER
	std::ostream& output_line_events(std::ostream& out_str) const;
	std::ostream& output_line_participants(std::ostream& out_str) const;
	
private:
	std::string EventName_;
	std::string Round_;
	std::string SemiHeat_num_;
	std::string Lane_;
	std::string Fname_;
	std::string Lname_;
	std::string Wholename_;
	std::string Country_;
	std::vector <std::string> Times_;
	std::vector <double> Time_differences_;
	std::string FinalTime_;
	int Heatnum_;
	int Seminum_;
	int Finalnum_;
	
}
;

bool IsFasterThan(const Participation& P1, const Participation& P2);
bool CountrySort(const Participation& P1, const Participation& P2);