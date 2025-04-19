#pragma once

#include "BasicOperationsController.h"
#include "GroupingOperationsController.h"
#include "SearchingOperationsController.h"


namespace LW5
{
    namespace Controllers
    {
        namespace Repos
        {
            class GeneralData 
            {
                public:
                    Data::BasicOperationsController basicOperationsController;
                    Data::GroupingOperationsController groupingOperationsController;
                    Data::SearchingOperationsController searchingOperationsController;

                    GeneralData() = default;
                    GeneralData(const GeneralData& other) = default;
                    ~GeneralData() = default;

                    void loadFromKeyboard(Models::Talk* mainArray, Models::Talk* workArray, int& mainCount, int& workCount);
                    bool loadFromFile(const std::string& fileName, Models::Talk* mainArray, Models::Talk* workArray, int& mainCount, int& workCount);
                    bool saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const;
                    void displayData(const Models::Talk* workArray, int workCount) const;
                    bool addRecord(Models::Talk* workArray, int workCount, const Models::Talk* newEntry) const;
                    bool deleteRecord(Models::Talk*& workArray, int& workCount, int index) const;
                    void sortByName(Models::Talk* workArray, int workCount) const;
                    void sortByDate(Models::Talk* workArray, int workCount) const;
                    void sortByDuration(Models::Talk* workArray, int workCount) const;
                    void resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount);
                    void testBasicCopyConstructor(const Models::Talk* workArray, int workCount) const;
                    void testBasicAssignmentOperator(const Models::Talk* workArray, int workCount) const;

                    Models::Wrappers::GroupedTalk* groupByPhone(const Models::Talk* workArray, int workCount, int& groupCount) const;
                    void sortGroupsByCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    void sortGroupsByPhone(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    void printGroups(std::ostream& os, const Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    bool askUserAndSaveGroupsToFile(const Models::Wrappers::GroupedTalk* groups, int groupCount) const;
                    void testGroupingCopyConstructor(const Models::Talk* workArray, int workCount) const;
                    void testGroupingAssignmentOperator(const Models::Talk* workArray, int workCount) const;

                    Models::Talk* searchByPhone(const Models::Talk* workArray, int workCount, const std::string& phoneNumber, int& matchCount);
                    void sortMatchesByDate(Models::Talk* matches, int matchCount) const;
                    void sortMatchesByTime(Models::Talk* matches, int matchCount) const;
                    void displayMatches(const Models::Talk* matches, int matchCount) const;
                    bool askUserAndSaveMatchesToFile(const Models::Talk* matches, int matchCount) const;
                    void testSearchingCopyConstructor(const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const;
                    void testSearchingAssignmentOperator(const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const;

                    GeneralData& operator=(const GeneralData& other);
            };
        }
    }
}
