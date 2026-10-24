#include "CS.h"
#include "utils.h"

#include <cmath>

#include <iostream>
#include <fstream>


int CS::MaxID = 0;

CS::CS() {
	id = ++MaxID;
	name = "";
	workshop_amount = 0;
	workshop_working_amount = 0;
	station_class = " ";
}

string CS::GetName() const {
	return name;
}

int CS::GetId() const {
	return id;
}

int CS::GetWorkshopWorkingPercent() const {
	return workshop_amount * 100 / workshop_working_amount;
}

int CS::GetWorkshopWorkingAmount() const {
	return workshop_working_amount;
}

void CS::RedactCS()
{
	workshop_working_amount = GetCorrectNumber(1, workshop_amount, "Enter the amount of workshops in work:");
}

std::istream& operator >> (std::istream& in, CS& cs)
{
	cs.name = GetString("Enter CS's name: ");
	cs.workshop_amount = GetCorrectNumber(0, 10000, "Enter workshop amount: ");
	cs.workshop_working_amount = GetCorrectNumber(0, cs.workshop_amount, "Enter amount of worshops in work: ");
	cs.station_class = GetString("Enter CS's station class: ");
	return in;
}


std::ostream& operator << (std::ostream& out, const CS& cs)
{
	out << "\nCS id: " << cs.id << "\n" << "Name: " << cs.name << '\n'
		<< "Workshop amount: " << cs.workshop_amount << '\n'
		<< "Workshop in work amount: " << cs.workshop_working_amount << "\n"
		<< "Station class: " << cs.station_class << "\n"
		<< endl;
	return out;
}


ifstream& operator>>(ifstream& fin, CS& cs)
{
	fin >> cs.id >> cs.name >> cs.workshop_amount >> cs.workshop_working_amount >> cs.station_class;
	return fin;
}

ofstream& operator<<(ofstream& fout, const CS& cs)
{
	fout << cs.id << endl 
		<< cs.name << endl 
		<< cs.workshop_amount << endl 
		<< cs.workshop_working_amount << endl 
		<< cs.station_class << endl;
	return fout;
}
