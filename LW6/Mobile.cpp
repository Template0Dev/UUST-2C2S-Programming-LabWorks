#include "Mobile.h"
#include <tuple>


namespace LW6
{
	namespace Models
	{
		Mobile::Mobile()
		{
			name = "";
			surname = "";
			patronymic = "";
			phoneNumber = "";
		}
		Mobile::Mobile(const std::string& name, const std::string& surname, const std::string& patronymic, const std::string& phoneNumber)
		{
			this->name = name;
			this->surname = surname;
			this->patronymic = patronymic;
			this->phoneNumber = phoneNumber;
		}

		std::string Mobile::getName() const { return name; }
		std::string Mobile::getSurname() const { return surname; }
		std::string Mobile::getPatronymic() const { return patronymic; }
		std::string Mobile::getPhoneNumber() const { return phoneNumber; }

		void Mobile::setName(const std::string& newNameVal) { name = newNameVal; }
		void Mobile::setSurname(const std::string& newSurnameVal) { surname = newSurnameVal; }
		void Mobile::setPatronymic(const std::string& newPatronymicVal) { patronymic = newPatronymicVal; }
		void Mobile::setPhoneNumber(const std::string& newPhoneNumberVal) { phoneNumber = newPhoneNumberVal; }

		bool operator <(const Mobile& firstOne, const Mobile& secondOne)
		{
			if (firstOne.getSurname() != secondOne.getSurname())
				return firstOne.getSurname() < secondOne.getSurname();

			if (firstOne.getName() != secondOne.getName())
				return firstOne.getName() < secondOne.getName();

			if (firstOne.getPatronymic() != secondOne.getPatronymic())
				return firstOne.getPatronymic() < secondOne.getPatronymic();

			return firstOne.getPhoneNumber() < secondOne.getPhoneNumber();
		}
		bool operator ==(const Mobile& firstOne, const Mobile& secondOne)
		{
			bool propertiesEquality;

			propertiesEquality = firstOne.getSurname() == secondOne.getSurname();
			if (!propertiesEquality) return false;

			propertiesEquality = firstOne.getName() == secondOne.getName();
			if (!propertiesEquality) return false;

			propertiesEquality = firstOne.getPatronymic() == secondOne.getPatronymic();
			if (!propertiesEquality) return false;

			return firstOne.getPhoneNumber() == secondOne.getPhoneNumber();
		}
	}
}
