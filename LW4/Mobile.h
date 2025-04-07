#pragma once

#include <string>


namespace LW4
{
	namespace Models
	{
		struct Mobile
		{
		private:
			std::string name;
			std::string surname;
			std::string patronymic;
			std::string phoneNumber;

		public:
			// Constructors.
			Mobile();
			Mobile(const std::string& name, const std::string& surname, const std::string& patronymic, const std::string& phoneNumber);

			// Getters for Fields.
			std::string getName() const;
			std::string getSurname() const;
			std::string getPatronymic() const;
			std::string getPhoneNumber() const;

			// Setters for Fields.
			void setName(const std::string& newNameVal);
			void setSurname(const std::string& newSurnameVal);
			void setPatronymic(const std::string& newPatronymicVal);
			void setPhoneNumber(const std::string& newPhoneNumberVal);

			// Operators.
			friend bool operator <(const Mobile& firstOne, const Mobile& secondOne);
			friend bool operator ==(const Mobile& firstOne, const Mobile& secondOne);
		};
	}
}
