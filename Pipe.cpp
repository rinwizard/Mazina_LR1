#include "Pipe.h"
#include "utils.h"

#include <cmath>
#include <iostream>
#include <fstream>

int Pipe::MaxID = 0;

Pipe::Pipe() {
	id = ++MaxID;
	name = "";
	length = 0;
	diameter = 0.0;
	in_repair = false;
}


int Pipe::GetMaxId()
{
	return MaxID;
}

void Pipe::SetMaxId(const std::unordered_map<int, Pipe>& pipes)
{
	MaxID = 0;
	for (auto& [id, p] : pipes)
		if (id > MaxID)
			MaxID = id;
}

std::string Pipe::GetName() const {
	return name;
}

int Pipe::GetId() const{
	return id;
}


bool Pipe::GetStatus() const {
	return in_repair;
}

void Pipe::RedactPipe()
{
	in_repair = !in_repair;
}

std::istream& operator >> (std::istream& in, Pipe& p)
{
	std::string name = GetString("Enter Pipe's name: ");
	p.name = name;
	p.length = GetCorrectNumber(0, 10000, "Enter Pipe's length: ");
	p.diameter = GetCorrectNumber(0, 10000, "Enter Pipe's diameter: ");
	p.in_repair = false;
	return in;
}


std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "\nPipe id: " << p.id << "\n"
		<< "Name: " << p.name << '\n'
		<< "Pipe's Length: " << p.length << "\n"
		<< "Pipe's Diameter: " << p.diameter << "\n"
		<< "Pipe's Status (1 - in repair, 0 - not): " << p.in_repair << "\n"
		<< std::endl;
	return out;
}


std::ifstream& operator>>(std::ifstream& fin, Pipe& p)
{
	fin >> p.id >> p.name >> p.length >> p.diameter >> p.in_repair;
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Pipe& p)
{
	fout << p.id << std::endl 
		<< p.name << std::endl 
		<< p.length << std::endl
		<< p.diameter << std::endl 
		<< p.in_repair << std::endl;
	return fout;
}
