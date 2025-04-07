#include "Mobile.h"


namespace LW1 
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

	}
}
