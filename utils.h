#pragma once
#include <iostream>
#include <string>
#include <sstream>


inline std::ofstream& InputLog() {
	static std::ofstream log("log.txt", std::ios::app);  // логирование
	return log;
}


template <typename T>
T GetCorrectNumber(T min, T max, std::string message) //ввод числа с проверкой
{
	std::cout << message << std::endl;
	InputLog() << message << std::endl;
	T x;
	std::string str;

	while (true)
	{
		std::getline(std::cin >> std::ws, str);
		std::stringstream ss(str);

		if ((ss >> x) && ss.peek() == EOF && x >= min && x <= max)
		{
			std::cerr << x << std::endl;
			InputLog() << str << std::endl;
			return x;
		}
		else { std::cout << "Incorrect input. Try again.\n"; }
		InputLog() << str << " -incorrect input" << std::endl;

	}
}


template <typename T>
std::string GetString(T message)  // ввод строки
{
	std::string x;
	std::cout << message;
	InputLog() << message << std::endl;
	std::getline(std::cin >> std::ws, x);
	std::cerr << x << std::endl;
	InputLog() << x << std::endl;
	return x;
}