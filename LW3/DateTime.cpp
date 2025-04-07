#include "DateTime.h"
#include <ctime>
#include <iomanip>
#include <sstream>


namespace LW3
{
	namespace Models
	{
		DateTime::DateTime()
		{
			second = 1;
			minute = 1;
			hour = 1;
			day = 1;
			month = 1;
			year = 2000;
		}
		DateTime::DateTime(int second, int minute, int hour, int day, int month, int year)
		{
			this->second = second;
			this->minute = minute;
			this->hour = hour;
			this->day = day;
			this->month = month;
			this->year = year;
		}

		int DateTime::getSecond() const { return second; }
		int DateTime::getMinute() const { return minute; }
		int DateTime::getHour() const { return hour; }
		int DateTime::getDay() const { return day; }
		int DateTime::getMonth() const { return month; }
		int DateTime::getYear() const { return year; }

		void DateTime::setSecond(const int newSecondVal) { second = newSecondVal; }
		void DateTime::setMinute(const int newMinuteVal) { minute = newMinuteVal; }
		void DateTime::setHour(const int newHourVal) { hour = newHourVal; }
		void DateTime::setDay(const int newDayVal) { day = newDayVal; }
		void DateTime::setMonth(const int newMonthVal) { month = newMonthVal; }
		void DateTime::setYear(const int newYearVal) { year = newYearVal; }

		time_t DateTime::toUnixTime() const
		{
			tm timeStruct = {};
			timeStruct.tm_sec = second;
			timeStruct.tm_min = minute;
			timeStruct.tm_hour = hour;
			timeStruct.tm_mday = day;
			timeStruct.tm_mon = month - 1; // tm_mon is 0-based
			timeStruct.tm_year = year - 1900; // tm_year is years since 1900

			time_t unixTime = mktime(&timeStruct);
			return (unixTime != -1) ? unixTime : 0; // Handle invalid time conversion
		}
		std::string DateTime::toString() const
		{
			std::ostringstream oss;
			oss << std::setw(2) << std::setfill('0') << hour << ":"
				<< std::setw(2) << std::setfill('0') << minute << ":"
				<< std::setw(2) << std::setfill('0') << second
				<< " "
				<< std::setw(2) << std::setfill('0') << day << "."
				<< std::setw(2) << std::setfill('0') << month << "."
				<< std::setw(2) << std::setfill('0') << year
				<< "!";
			return oss.str();
		}

		bool DateTime::isValidDate() const
		{
			if (year < 0) return false;
			if (month < 1 || month > 12) return false;

			int maxDay = 31;
			if (month == 4 || month == 6 || month == 9 || month == 11)
				maxDay = 30;
			else if (month == 2)
			{
				bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
				maxDay = leap ? 29 : 28;
			}

			if (day < 1 || day > maxDay) return false;
			if (hour < 0 || hour > 23) return false;
			if (minute < 0 || minute > 59) return false;

			return true;
		}
		bool DateTime::tryParseDateTime(const char* dtStr, tm& result) {
			int tempSecond, tempMinute, tempHour, tempDay, tempMonth, tempYear;
			int scan = sscanf_s(dtStr, "%d:%d:%d %d.%d.%d!", &tempHour, &tempMinute, &tempSecond, &tempDay, &tempMonth, &tempYear);
			if (scan != 6)
				return false;

			result.tm_sec = tempSecond;
			result.tm_min = tempMinute;
			result.tm_hour = tempHour;
			result.tm_mday = tempDay;
			result.tm_mon = tempMonth;
			result.tm_year = tempYear;

			return true;
		}

		bool operator <(const DateTime& first, const DateTime& second) { return first.toUnixTime() < second.toUnixTime(); }
		bool operator ==(const DateTime& first, const DateTime& second) { return first.toUnixTime() == second.toUnixTime(); }
		bool operator <=(const DateTime& first, const DateTime& second) { return first.toUnixTime() <= second.toUnixTime(); }
	}
}
