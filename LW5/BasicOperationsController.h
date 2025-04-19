#pragma once

#include "Talk.h"
#include <string>
#include <ostream>


namespace LW5
{
    namespace Controllers
    {
        namespace Data
        {
            class BasicOperationsController
            {
            private:
                void printTable(std::ostream& output, const Models::Talk* array, int count) const;

                void clearArray(Models::Talk*& array, int& arrayCount);
                Models::Talk* resizeArray(Models::Talk* array, int oldCount, int newCount) const;
                void appendRecord(Models::Talk*& array, int& count, const Models::Talk& record) const;

            public:
                void loadFromKeyboard(Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount);
                bool loadFromFile(const std::string& fileName, Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount);
                bool saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const;

                bool addRecord(const Models::Talk& record, Models::Talk*& workArray, int& workCount) const;
                bool deleteRecord(int index, Models::Talk*& workArray, int& workCount) const;

                void displayData(const Models::Talk* workArray, int workCount) const;

                /// <summary>
                /// Это функция, реализующая комплексную сортировку с использованием перегрузки операндов.
                /// </summary>
                /// <param name="workArray"></param>
                /// <param name="workCount"></param>
                void sortByName(Models::Talk* workArray, int workCount) const;
                void sortByDate(Models::Talk* workArray, int workCount) const;
                void sortByDuration(Models::Talk* workArray, int workCount) const;

                void resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount);
            };
        }
    }
}
