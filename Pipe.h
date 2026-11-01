#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>

class Pipe
{
	int id;
	std::string name;
	int length;
	int diameter;
	bool in_repair;
	static int MaxID;
public:
	
	Pipe();
	int GetId() const;
	static int GetMaxId();
	static void SetMaxId(const std::unordered_map<int, Pipe>& pipes);
	std::string GetName() const;
	bool GetStatus() const;
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::ifstream& operator>>(std::ifstream& fin, Pipe& p);
	friend std::ofstream& operator<<(std::ofstream& fout, const Pipe& p);
	void RedactPipe();

};
