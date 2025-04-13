#include "Utils.h"
#include <iostream>


namespace LW4
{
	std::string trim(const std::string& s)
	{
		size_t start = s.find_first_not_of(" \t");
		size_t end = s.find_last_not_of(" \t");

		return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
	}

	void printCell(std::ostream& output, const std::string& text, int width)
	{
		output << "| " << text;
		auto len = static_cast<int>(text.size());
		for (int s = len; s < width; s++)
		{
			output << " ";
		}
		output << " ";
	}

	Models::Talk userGuidedTalkCreation()
	{
		Models::Talk talk;
		std::cin >> talk;
		return talk;
	}

	std::string getPhoneNumber()
	{
		std::string phoneNumber;
		std::cout << "Введите номер телефона для поиска: ";
		std::getline(std::cin, phoneNumber);

		return phoneNumber;
	}
}
