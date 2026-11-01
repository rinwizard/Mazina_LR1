#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
class CS
{
	int id;
	std::string name;
	int workshop_amount;
	int workshop_working_amount;
	std::string station_class;
	static int MaxID;
public:
	CS();

	int GetId() const;
	static int GetMaxId();
	static void SetMaxId(const std::unordered_map<int, CS>& css);
	std::string GetName() const;
	int GetWorkshopWorkingPercent() const;
	int GetWorkshopWorkingAmount() const;
	void RedactCS();
	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ostream& operator << (std::ostream& out, const CS& cs);
	friend std::ifstream& operator>>(std::ifstream& fin, CS& cs);
	friend std::ofstream& operator<<(std::ofstream& fout, const CS& cs);
};
