#include "CopyConstructorsTester.h"
#include <iostream>


namespace LW6
{
	namespace Controllers
	{
		namespace Testers
		{
			void CopyConstructorsTester::testBasicOperationsControllerCopyConstructor(const Data::BasicOperationsController controller, const Models::Talk* workArray, int workCount) const
			{
				std::cout << "Текущий объект:" << std::endl;
				controller.displayData(workArray, workCount);

				std::cout << std::endl << "Скопированный объект:" << std::endl;
				Data::BasicOperationsController(controller).displayData(workArray, workCount);
			}

			void CopyConstructorsTester::testGroupingOperationsControllerCopyConstructor(const Data::GroupingOperationsController groupingController, const Models::Talk* workArray, int workCount) const
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

			void CopyConstructorsTester::testSearchingOperationsControllerCopyConstructor(const Data::SearchingOperationsController searchingController, const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const
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

			void CopyConstructorsTester::testGeneralDataRepositoryCopyConstructor(const Repos::GeneralDataRepo dataRepo, const Models::Talk* workArray, int workCount, const std::string& phoneNumber) const
			{
				auto const repoCopy = Repos::GeneralDataRepo(dataRepo);

				// Basic Repo test.
				std::cout << std::endl << std::endl << "[ БАЗОВЫЙ РЕПОЗИТОРИЙ ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerCopyConstructor(dataRepo.basicOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerCopyConstructor(dataRepo.groupingOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerCopyConstructor(dataRepo.searchingOperationsController, workArray, workCount, &phoneNumber);

				// Repo's Copy test.
				std::cout << std::endl << std::endl << "[ КОПИЯ РЕПОЗИТОРИЯ ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerCopyConstructor(repoCopy.basicOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerCopyConstructor(repoCopy.groupingOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerCopyConstructor(repoCopy.searchingOperationsController, workArray, workCount, &phoneNumber);
			}

			void CopyConstructorsTester::testInheritedDataRepositoryCopyConstructor(Repos::InheritedDataRepo dataRepo, const Models::Talk* workArray, int workCount, const std::string& phoneNumber) const
			{
				auto repoCopy = Repos::InheritedDataRepo(dataRepo);

				// Basic Repo test.
				std::cout << std::endl << std::endl << "[ БАЗОВЫЙ РЕПОЗИТОРИЙ ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerCopyConstructor(dataRepo.getBOPS(), workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerCopyConstructor(dataRepo.getGOPS(), workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerCopyConstructor(dataRepo.getSOPS(), workArray, workCount, &phoneNumber);

				// Repo's Copy test.
				std::cout << std::endl << std::endl << "[ КОПИЯ РЕПОЗИТОРИЯ ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerCopyConstructor(repoCopy.getBOPS(), workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerCopyConstructor(repoCopy.getGOPS(), workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerCopyConstructor(repoCopy.getSOPS(), workArray, workCount, &phoneNumber);
			}
		}
	}
}
