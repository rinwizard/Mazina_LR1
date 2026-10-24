#pragma once
#include <iostream>
#include <fstream>

class Pipe
{
	int id;
	std::string name;
	std::string km_marker;
	int length;
	int diameter;
	bool in_repair;
public:
	static int MaxID;
	Pipe();

	int GetId() const;
	std::string GetName() const;
	bool GetStatus() const;
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::ifstream& operator>>(std::ifstream& fin, Pipe& p);
	friend std::ofstream& operator<<(std::ofstream& fout, const Pipe& p);
	void RedactPipe();

};
