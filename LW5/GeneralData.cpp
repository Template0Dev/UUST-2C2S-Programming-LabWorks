#include "GeneralData.h"


namespace LW5
{
    namespace Controllers
    {
        namespace Repos
        {
#pragma region Region: Basic Operations.

            void GeneralData::loadFromKeyboard(Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount) { basicOperationsController.loadFromKeyboard(mainArray, workArray, mainCount, workCount); }
            bool GeneralData::loadFromFile(const std::string& fileName, Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount) { return basicOperationsController.loadFromFile(fileName, mainArray, workArray, mainCount, workCount); }
            bool GeneralData::saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const { return basicOperationsController.saveToFile(fileName, workArray, workCount); }
            void GeneralData::displayData(const Models::Talk* workArray, int workCount) const { basicOperationsController.displayData(workArray, workCount); }

            bool GeneralData::addRecord(Models::Talk*& array, int& count, const Models::Talk& newRecord) const { return basicOperationsController.addRecord(newRecord, array, count); }
            bool GeneralData::deleteRecord(Models::Talk*& workArray, int& workCount, int index) const { return basicOperationsController.deleteRecord(index, workArray, workCount); }

            void GeneralData::sortByName(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByName(workArray, workCount); }
            void GeneralData::sortByDate(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByDate(workArray, workCount); }
            void GeneralData::sortByDuration(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByDuration(workArray, workCount); }

            void GeneralData::resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount) { basicOperationsController.resetWorkingArray(mainArray, workArray, mainCount, workCount); }
#pragma endregion

#pragma region Region: Grouping Operations.

            Models::Wrappers::GroupedTalk* GeneralData::groupByPhone(const Models::Talk* workArray, int workCount, int& groupCount) const { return groupingOperationsController.groupByPhone(workArray, workCount, groupCount); }

            void GeneralData::sortGroupsByCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.sortByTalkCount(groups, groupCount); }
            void GeneralData::sortGroupsByPhone(Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.sortByPhoneNumber(groups, groupCount); }

            void GeneralData::printGroups(std::ostream& os, const Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.printGroupsTable(os, groups, groupCount); }
            bool GeneralData::saveGroupsToFile(const std::string* fileName, const Models::Wrappers::GroupedTalk* groups, int groupCount) const { return groupingOperationsController.saveToFile(*fileName, groups, groupCount); }
#pragma endregion

#pragma region Region: Searching Operations.

            Models::Talk* GeneralData::searchByPhone(const Models::Talk* workArray, int workCount, const std::string& phoneNumber, int& matchCount) { return searchingOperationsController.searchByPhoneNumber(workArray, workCount, phoneNumber, matchCount); }

            void GeneralData::sortMatchesByDate(Models::Talk* matches, int matchCount) const { searchingOperationsController.sortByCallDate(matches, matchCount); }
            void GeneralData::sortMatchesByTime(Models::Talk* matches, int matchCount) const { searchingOperationsController.sortByCallTime(matches, matchCount); }

            void GeneralData::displayMatches(const Models::Talk* matches, int matchCount) const { searchingOperationsController.displayMatches(matches, matchCount); }
            bool GeneralData::saveMatchesToFile(const std::string* fileName, const Models::Talk* matches, int matchCount) const { return searchingOperationsController.saveMatchesToFile(*fileName, matches, matchCount); }
#pragma endregion

            GeneralData& GeneralData::operator=(const GeneralData& other)
            {
                if (this == &other)
                    return *this;

                basicOperationsController = other.basicOperationsController;
                groupingOperationsController = other.groupingOperationsController;
                searchingOperationsController = other.searchingOperationsController;
                return *this;
            }
        }
    }
}
