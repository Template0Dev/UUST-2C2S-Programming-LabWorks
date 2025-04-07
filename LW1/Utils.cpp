#include "Utils.h"
#include <iostream>


namespace LW1
{
	std::string trim(const std::string& s)
	{
		size_t start = s.find_first_not_of(" \t");
		size_t end = s.find_last_not_of(" \t");

		return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
	}

	Models::Talk userGuidedTalkCreation()
	{
		std::string name;
		std::cout << "Имя: ";
		std::cin >> name;

		std::string surname;
		std::cout << "Фамилия: ";
		std::cin >> surname;

		std::string patronymic;
		std::cout << "Отчество: ";
		std::cin >> patronymic;

		std::string phone;
		std::cout << "Телефон: ";
		std::cin >> phone;

		Models::DateTime callStart;
		Models::DateTime callEnding;
		for (int j = 0; j < 2;)
		{
			tm rawDateData {};
			std::cout << "Необходимо ввести дату (время) [hh MM ss dd mm yyyy] " << (j == 0 ? "начала разговора" : "конца разговора") << ": ";
			while (!(std::cin >> rawDateData.tm_hour >> rawDateData.tm_min >> rawDateData.tm_sec >> rawDateData.tm_mday >> rawDateData.tm_mon >> rawDateData.tm_year))
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}

			Models::DateTime dateTime(rawDateData.tm_sec, rawDateData.tm_min, rawDateData.tm_hour, rawDateData.tm_mday, rawDateData.tm_mon, rawDateData.tm_year);
			if (!dateTime.isValidDate())
			{
				std::cout << "Введённая дата некорректна. Необходимо повторить ввод." << std::endl;
				continue;
			}

			if (j == 0) callStart = dateTime;
			else callEnding = dateTime;
			j++;
		}

		double talkTarification;
		std::cout << "Необходимо ввести тарификацию разговора (стоимость за минуту): ";
		while (!(std::cin >> talkTarification))
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		Models::Mobile mobile(name, surname, patronymic, phone);
		Models::Talk talk(mobile, callStart, callEnding, talkTarification);

		return talk;
	}
}
