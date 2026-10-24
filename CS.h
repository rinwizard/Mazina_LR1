#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class CS
{
	int id;
	std::string name;
	int workshop_amount;
	int workshop_working_amount;
	string station_class;
public:
	static int MaxID;
	CS();

	int GetId() const;
	string GetName() const;
	int GetWorkshopWorkingPercent() const;
	int GetWorkshopWorkingAmount() const;
	void RedactCS();
	friend istream& operator >> (std::istream& in, CS& cs);
	friend ostream& operator << (std::ostream& out, const CS& cs);
	friend ifstream& operator>>(std::ifstream& fin, CS& cs);
	friend ofstream& operator<<(std::ofstream& fout, const CS& cs);
};
