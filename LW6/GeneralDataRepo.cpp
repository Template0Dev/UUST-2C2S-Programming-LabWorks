#include "GeneralDataRepo.h"


namespace LW6
{
    namespace Controllers
    {
        namespace Repos
        {
#pragma region Region: Basic Operations.

            void GeneralDataRepo::loadFromKeyboard(Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount) { basicOperationsController.loadFromKeyboard(mainArray, workArray, mainCount, workCount); }
            bool GeneralDataRepo::loadFromFile(const std::string& fileName, Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount) { return basicOperationsController.loadFromFile(fileName, mainArray, workArray, mainCount, workCount); }
            bool GeneralDataRepo::saveRecordsToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const { return basicOperationsController.saveRecordsToFile(fileName, workArray, workCount); }
            void GeneralDataRepo::displayData(const Models::Talk* workArray, int workCount) const { basicOperationsController.displayData(workArray, workCount); }

            bool GeneralDataRepo::addRecord(Models::Talk*& array, int& count, const Models::Talk& newRecord) const { return basicOperationsController.addRecord(newRecord, array, count); }
            bool GeneralDataRepo::deleteRecord(Models::Talk*& workArray, int& workCount, int index) const { return basicOperationsController.deleteRecord(index, workArray, workCount); }

            void GeneralDataRepo::sortByName(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByName(workArray, workCount); }
            void GeneralDataRepo::sortByDate(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByDate(workArray, workCount); }
            void GeneralDataRepo::sortByDuration(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByDuration(workArray, workCount); }

            void GeneralDataRepo::resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount) { basicOperationsController.resetWorkingArray(mainArray, workArray, mainCount, workCount); }
#pragma endregion

#pragma region Region: Grouping Operations.

            Models::Wrappers::GroupedTalk* GeneralDataRepo::groupByPhone(const Models::Talk* workArray, int workCount, int& groupCount) const { return groupingOperationsController.groupByPhone(workArray, workCount, groupCount); }

            void GeneralDataRepo::sortGroupsByCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.sortByTalkCount(groups, groupCount); }
            void GeneralDataRepo::sortGroupsByPhone(Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.sortByPhoneNumber(groups, groupCount); }

            void GeneralDataRepo::printGroups(std::ostream& os, const Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.printGroupsTable(os, groups, groupCount); }
            bool GeneralDataRepo::saveGroupsToFile(const std::string* fileName, const Models::Wrappers::GroupedTalk* groups, int groupCount) const { return groupingOperationsController.saveGroupsToFile(*fileName, groups, groupCount); }
#pragma endregion

#pragma region Region: Searching Operations.

            Models::Talk* GeneralDataRepo::searchByPhone(const Models::Talk* workArray, int workCount, const std::string& phoneNumber, int& matchCount) { return searchingOperationsController.searchByPhoneNumber(workArray, workCount, phoneNumber, matchCount); }

            void GeneralDataRepo::sortMatchesByDate(Models::Talk* matches, int matchCount) const { searchingOperationsController.sortByCallDate(matches, matchCount); }
            void GeneralDataRepo::sortMatchesByTime(Models::Talk* matches, int matchCount) const { searchingOperationsController.sortByCallTime(matches, matchCount); }

            void GeneralDataRepo::displayMatches(const Models::Talk* matches, int matchCount) const { searchingOperationsController.displayMatches(matches, matchCount); }
            bool GeneralDataRepo::saveMatchesToFile(const std::string* fileName, const Models::Talk* matches, int matchCount) const { return searchingOperationsController.saveMatchesToFile(*fileName, matches, matchCount); }
#pragma endregion

            GeneralDataRepo& GeneralDataRepo::operator=(const GeneralDataRepo& other)
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
