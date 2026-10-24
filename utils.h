#pragma once
#include <iostream>
#include <string>
#include <sstream>

//#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
//						std::cerr << str << std::endl
//
//#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl
//
//class redirect_output_wrapper
//{
//	std::ostream& stream;
//	std::streambuf* const old_buf;
//public:
//	redirect_output_wrapper(std::ostream& src)
//		:old_buf(src.rdbuf()), stream(src)
//	{
//	}
//
//	~redirect_output_wrapper() {
//		stream.rdbuf(old_buf);
//	}
//	void redirect(std::ostream& dest)
//	{
//		stream.rdbuf(dest.rdbuf());
//	}
//};



template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	std::string str;

	while (true)
	{
		std::getline(std::cin >> std::ws, str);
		std::stringstream ss(str);

		if ((ss >> x) && ss.peek() == EOF && x >= min && x <= max)
		{
			std::cerr << x << std::endl;
			return x;
		}
		else { std::cout << "Incorrect input. Try again.\n"; }

	}
}


template <typename T>
std::string GetString(T message)
{
	std::string x;
	std::cout << message;
	std::getline(std::cin >> std::ws, x);
	std::cerr << x << std::endl;
	return x;
}