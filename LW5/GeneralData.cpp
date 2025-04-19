#include "GeneralData.h"
#include <iostream>


namespace LW5
{
    namespace Controllers
    {
        namespace Repos
        {
#pragma region Region: Basic Operations.

            void GeneralData::loadFromKeyboard(Models::Talk* mainArray, Models::Talk* workArray, int& mainCount, int& workCount) { basicOperationsController.loadFromKeyboard(mainArray, workArray, mainCount, workCount); }
            bool GeneralData::loadFromFile(const std::string& fileName, Models::Talk* mainArray, Models::Talk* workArray, int& mainCount, int& workCount) { return basicOperationsController.loadFromFile(fileName, mainArray, workArray, mainCount, workCount); }
            bool GeneralData::saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const { return basicOperationsController.saveToFile(fileName, workArray, workCount); }
            void GeneralData::displayData(const Models::Talk* workArray, int workCount) const { basicOperationsController.displayData(workArray, workCount); }

            bool GeneralData::addRecord(Models::Talk* workArray, int workCount, const Models::Talk* newEntry) const { return basicOperationsController.addRecord(*newEntry, workArray, workCount); }
            bool GeneralData::deleteRecord(Models::Talk*& workArray, int& workCount, int index) const { return basicOperationsController.deleteRecord(index, workArray, workCount); }

            void GeneralData::sortByName(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByName(workArray, workCount); }
            void GeneralData::sortByDate(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByDate(workArray, workCount); }
            void GeneralData::sortByDuration(Models::Talk* workArray, int workCount) const { basicOperationsController.sortByDuration(workArray, workCount); }

            void GeneralData::resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount) { basicOperationsController.resetWorkingArray(mainArray, workArray, mainCount, workCount); }

            void GeneralData::testBasicCopyConstructor(const Models::Talk* workArray, int workCount) const
            {
                std::cout << "Текущий объект:" << std::endl;
                basicOperationsController.displayData(workArray, workCount);

                std::cout << std::endl << "Скопированный объект:" << std::endl;
                Data::BasicOperationsController(basicOperationsController).displayData(workArray, workCount);
            }
            void GeneralData::testBasicAssignmentOperator(const Models::Talk* workArray, int workCount) const
            {
                Data::BasicOperationsController controllerA;
                Data::BasicOperationsController controllerB;
                controllerB = controllerA = basicOperationsController;

                std::cout << "Копия B:" << std::endl;
                controllerB.displayData(workArray, workCount);

                std::cout << std::endl << "Копия A:" << std::endl;
                controllerA.displayData(workArray, workCount);

                std::cout << std::endl << "Оригинал:" << std::endl;
                basicOperationsController.displayData(workArray, workCount);
            }
#pragma endregion

#pragma region Region: Grouping Operations.

            Models::Wrappers::GroupedTalk* GeneralData::groupByPhone(const Models::Talk* workArray, int workCount, int& groupCount) const { return groupingOperationsController.groupByPhone(workArray, workCount, groupCount); }

            void GeneralData::sortGroupsByCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.sortByTalkCount(groups, groupCount); }
            void GeneralData::sortGroupsByPhone(Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.sortByPhoneNumber(groups, groupCount); }

            void GeneralData::printGroups(std::ostream& os, const Models::Wrappers::GroupedTalk* groups, int groupCount) const { groupingOperationsController.printGroupsTable(os, groups, groupCount); }
            bool GeneralData::askUserAndSaveGroupsToFile(const Models::Wrappers::GroupedTalk* groups, int groupCount) const 
            { 
                char confirmation;
                std::cout << std::endl << "Сохранить результат группировки в файл (Y/N)? ";
                std::cin >> confirmation;
                if (confirmation == 'y' || confirmation == 'Y')
                {
                    std::string fileName;
                    std::cout << "Введите название файла для сохранения: ";
                    std::cin >> fileName;

                    auto result = groupingOperationsController.saveToFile(fileName, groups, groupCount);
                    if (result)
                        std::cout << "Файл успешно сохранён." << std::endl;
                }
            }

            void GeneralData::testGroupingCopyConstructor(const Models::Talk* workArray, int workCount) const
            {
                auto newGroupController = Data::GroupingOperationsController(groupingOperationsController);

                int newGroupsCount = 0;
                auto const* newGroups = newGroupController.groupByPhone(workArray, workCount, newGroupsCount);

                std::cout << std::endl << "Копия контроллера:" << std::endl;
                newGroupController.printGroupsTable(std::cout, newGroups, newGroupsCount);

                std::cout << std::endl << "Основной контроллер:" << std::endl;
            }
            void GeneralData::testGroupingAssignmentOperator(const Models::Talk* workArray, int workCount) const
            {
                Data::GroupingOperationsController newGroupingControllerA;
                Data::GroupingOperationsController newGroupingControllerB;
                newGroupingControllerB = newGroupingControllerA = groupingOperationsController;

                int newGroupsCountB = 0;
                auto const* newGroupsB = newGroupingControllerB.groupByPhone(workArray, workCount, newGroupsCountB);
                std::cout << std::endl << "Результат работы переприсвоенного контроллера (B):" << std::endl;
                newGroupingControllerB.printGroupsTable(std::cout, newGroupsB, newGroupsCountB);

                int newGroupsCountA = 0;
                auto const* newGroupsA = newGroupingControllerA.groupByPhone(workArray, workCount, newGroupsCountA);
                std::cout << std::endl << "Результат работы переприсвоенного контроллера (A):" << std::endl;
                newGroupingControllerA.printGroupsTable(std::cout, newGroupsA, newGroupsCountA);

                std::cout << std::endl << "Результат работы основного контроллера:" << std::endl;
            }
#pragma endregion

#pragma region Region: Searching Operations.

            Models::Talk* GeneralData::searchByPhone(const Models::Talk* workArray, int workCount, const std::string& phoneNumber, int& matchCount) { return searchingOperationsController.searchByPhoneNumber(workArray, workCount, phoneNumber, matchCount); }

            void GeneralData::sortMatchesByDate(Models::Talk* matches, int matchCount) const { searchingOperationsController.sortByCallDate(matches, matchCount); }
            void GeneralData::sortMatchesByTime(Models::Talk* matches, int matchCount) const { searchingOperationsController.sortByCallTime(matches, matchCount); }

            void GeneralData::displayMatches(const Models::Talk* matches, int matchCount) const { basicOperationsController.displayData(matches, matchCount); }
            bool GeneralData::askUserAndSaveMatchesToFile(const Models::Talk* matches, int matchCount) const 
            { 
                char confirmation;
                std::cout << "Сохранить результат поиска в файл (Y/N)? ";
                std::cin >> confirmation;
                if (confirmation == 'y' || confirmation == 'Y')
                {
                    std::string fileName;
                    std::cout << "Введите название файла для сохранения: ";
                    std::cin >> fileName;

                    auto result = basicOperationsController.saveToFile(fileName, matches, matchCount);
                    if (result)
                        std::cout << "Файл успешно сохранён." << std::endl;

                    return result;
                }

                return false;
            }

            void GeneralData::testSearchingCopyConstructor(const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const
            {
                auto newSearchController = Data::SearchingOperationsController(searchingOperationsController);

                int newMatchCount = 0;
                auto const* newMatches = newSearchController.searchByPhoneNumber(workArray, workCount, *phoneNumber, newMatchCount);

                std::cout << std::endl << "Копия контроллера:" << std::endl;
                displayMatches(newMatches, newMatchCount);

                std::cout << std::endl << "Основной контроллер:" << std::endl;
            }
            void GeneralData::testSearchingAssignmentOperator(const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const
            {
                Data::SearchingOperationsController newSearchControllerA;
                Data::SearchingOperationsController newSearchControllerB;
                newSearchControllerB = newSearchControllerA = searchingOperationsController;

                int newMatchesCountB = 0;
                auto const* newMatchesB = newSearchControllerB.searchByPhoneNumber(workArray, workCount, *phoneNumber, newMatchesCountB);
                std::cout << std::endl << "Результат работы переприсвоенного контроллера (B):" << std::endl;
                displayMatches(newMatchesB, newMatchesCountB);

                int newMatchesCountA = 0;
                auto const* newMatchesA = newSearchControllerA.searchByPhoneNumber(workArray, workCount, *phoneNumber, newMatchesCountA);
                std::cout << std::endl << "Результат работы переприсвоенного контроллера (A):" << std::endl;
                displayMatches(newMatchesA, newMatchesCountA);

                std::cout << std::endl << "Результат работы основного контроллера:" << std::endl;
            }
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
