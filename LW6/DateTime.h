#pragma once

#include <string>


namespace LW6
{
	namespace Models
	{
		struct DateTime
		{
		private:
			int second;
			int minute;
			int hour;
			int day;
			int month;
			int year;

		public:
			// Constructors.
			DateTime();
			DateTime(int second, int minute, int hour, int day, int month, int year);

			// Getters for Fields.
			int getSecond() const;
			int getMinute() const;
			int getHour() const;
			int getDay() const;
			int getMonth() const;
			int getYear() const;

			// Setters for Fields.
			void setSecond(const int newSecondVal);
			void setMinute(const int newMinuteVal);
			void setHour(const int newHourVal);
			void setDay(const int newDayVal);
			void setMonth(const int newMonthVal);
			void setYear(const int newYearVal);

			// Convert Functions.
			time_t toUnixTime() const;
			std::string toString() const;

			// Additional Functions.
			bool isValidDate() const;
			static bool tryParseDateTime(const char* dtStr, tm& result);

			// Operators Override.
			friend bool operator <(const DateTime& first, const DateTime& second);
			friend bool operator ==(const DateTime& first, const DateTime& second);
			friend bool operator <=(const DateTime& first, const DateTime& second);
		};
	}
}
