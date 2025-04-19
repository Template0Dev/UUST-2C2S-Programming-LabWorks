#include "CopyControllersTester.h"
#include <iostream>


namespace LW5
{
	namespace Controllers
	{
		namespace Testers
		{
			void CopyControllersTester::testBasicOperationsControllerCopyConstructor(const Data::BasicOperationsController controller, const Models::Talk* workArray, int workCount) const
			{
				std::cout << "Текущий объект:" << std::endl;
				controller.displayData(workArray, workCount);

				std::cout << std::endl << "Скопированный объект:" << std::endl;
				Data::BasicOperationsController(controller).displayData(workArray, workCount);
			}

			void CopyControllersTester::testGroupingOperationsControllerCopyConstructor(const Data::GroupingOperationsController groupingController, const Models::Talk* workArray, int workCount) const
			{
				int groupsCount = 0;
				auto const* groups = groupingController.groupByPhone(workArray, workCount, groupsCount);

				std::cout << std::endl << "Основной контроллер:" << std::endl;
				groupingController.printGroupsTable(std::cout, groups, groupsCount);

				auto newGroupController = Data::GroupingOperationsController(groupingController);
				int newGroupsCount = 0;
				auto const* newGroups = newGroupController.groupByPhone(workArray, workCount, newGroupsCount);

				std::cout << std::endl << "Копия контроллера:" << std::endl;
				newGroupController.printGroupsTable(std::cout, newGroups, newGroupsCount);
			}

			void CopyControllersTester::testSearchingOperationsControllerCopyConstructor(const Data::SearchingOperationsController searchingController, const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const
			{
				int matchCount = 0;
				auto const* matches = searchingController.searchByPhoneNumber(workArray, workCount, *phoneNumber, matchCount);

				std::cout << std::endl << "Основной контроллер:" << std::endl;
				searchingController.displayMatches(matches, matchCount);

				auto newSearchController = Data::SearchingOperationsController(searchingController);
				int newMatchCount = 0;
				auto const* newMatches = newSearchController.searchByPhoneNumber(workArray, workCount, *phoneNumber, newMatchCount);

				std::cout << std::endl << "Копия контроллера:" << std::endl;
				searchingController.displayMatches(newMatches, newMatchCount);
			}
		}
	}
}
