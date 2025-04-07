#pragma once

#include "Talk.h"
#include <string>
#include <ostream>


namespace LW1
{
	namespace Controllers
	{
		class MainController
		{
			private:
				void printCell(std::ostream& output, const std::string& text, int width) const;
				void printTable(std::ostream& output, const Models::Talk array[], int count) const;
				void clearArray(Models::Talk array[], int& arrayCount);
				
			public:
				static const int MAX_SIZE = 128;

				void loadFromKeyboard(Models::Talk mainArray[], Models::Talk workArray[], int& mainCount, int& workCount);
				bool loadFromFile(const std::string& fileName, Models::Talk mainArray[], Models::Talk workArray[], int& mainCount, int& workCount);
				bool saveToFile(const std::string& fileName, const Models::Talk workArray[], int workCount) const;

				bool addRecord(const Models::Talk& record, Models::Talk workArray[], int& workCount) const;
				bool deleteRecord(int index, Models::Talk workArray[], int& workCount) const;

				void displayData(const Models::Talk workArray[], int workCount) const;

				void sortByName(Models::Talk workArray[], int workCount) const;
				void sortByDate(Models::Talk workArray[], int workCount) const;
				void sortByDuration(Models::Talk workArray[], int workCount) const;

				void resetWorkingArray(const Models::Talk mainArray[], Models::Talk workArray[], int mainCount, int& workCount);
		};
	}
}
