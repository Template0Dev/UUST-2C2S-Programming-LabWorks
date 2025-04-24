#pragma once

#include "BasicOperationsController.h"
#include "GroupingOperationsController.h"
#include "SearchingOperationsController.h"


namespace LW6
{
    namespace Controllers
    {
        namespace Repos
        {
            class GeneralDataRepo 
            {
                public:
                    Data::BasicOperationsController basicOperationsController;
                    Data::GroupingOperationsController groupingOperationsController;
                    Data::SearchingOperationsController searchingOperationsController;

                    GeneralDataRepo() = default;
                    GeneralDataRepo(const GeneralDataRepo& other) = default;
                    ~GeneralDataRepo() = default;

                    void loadFromKeyboard(Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount);
                    bool loadFromFile(const std::string& fileName, Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount);
                    bool saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const;
                    void displayData(const Models::Talk* workArray, int workCount) const;
                    bool addRecord(Models::Talk*& array, int& count, const Models::Talk& newRecord) const;
                    bool deleteRecord(Models::Talk*& workArray, int& workCount, int index) const;
                    void sortByName(Models::Talk* workArray, int workCount) const;
                    void sortByDate(Models::Talk* workArray, int workCount) const;
                    void sortByDuration(Models::Talk* workArray, int workCount) const;
                    void resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount);

                    Models::Wrappers::GroupedTalk* groupByPhone(const Models::Talk* workArray, int workCount, int& groupCount) const;
                    void sortGroupsByCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    void sortGroupsByPhone(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    void printGroups(std::ostream& os, const Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    bool saveGroupsToFile(const std::string* fileName, const Models::Wrappers::GroupedTalk* groups, int groupCount) const;

                    Models::Talk* searchByPhone(const Models::Talk* workArray, int workCount, const std::string& phoneNumber, int& matchCount);
                    void sortMatchesByDate(Models::Talk* matches, int matchCount) const;
                    void sortMatchesByTime(Models::Talk* matches, int matchCount) const;
                    void displayMatches(const Models::Talk* matches, int matchCount) const;
                    bool saveMatchesToFile(const std::string* fileName, const Models::Talk* matches, int matchCount) const;

                    GeneralDataRepo& operator=(const GeneralDataRepo& other);
            };
        }
    }
}
