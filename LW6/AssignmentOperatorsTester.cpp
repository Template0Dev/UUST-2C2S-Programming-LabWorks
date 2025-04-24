#include "AssignmentOperatorsTester.h"
#include <iostream>


namespace LW5
{
	namespace Controllers
	{
		namespace Testers
		{
			void AssignmentOperatorsTester::testBasicOperationsControllerAssignmentOperator(const Data::BasicOperationsController controller, const Models::Talk* workArray, int workCount) const
			{
				Data::BasicOperationsController controllerA;
				Data::BasicOperationsController controllerB;
				controllerB = controllerA = controller;

				std::cout << "Копия B:" << std::endl;
				controllerB.displayData(workArray, workCount);

				std::cout << std::endl << "Копия A:" << std::endl;
				controllerA.displayData(workArray, workCount);

				std::cout << std::endl << "Оригинал:" << std::endl;
				controller.displayData(workArray, workCount);
			}

			void AssignmentOperatorsTester::testGroupingOperationsControllerAssignmentOperator(const Data::GroupingOperationsController groupingController, const Models::Talk* workArray, int workCount) const
			{
				Data::GroupingOperationsController newGroupingControllerA;
				Data::GroupingOperationsController newGroupingControllerB;
				newGroupingControllerA = newGroupingControllerB = groupingController;

				int groupsCount = 0;
				auto const* groups = groupingController.groupByPhone(workArray, workCount, groupsCount);
				std::cout << std::endl << "Результат работы основного контроллера:" << std::endl;
				newGroupingControllerA.printGroupsTable(std::cout, groups, groupsCount);

				int newGroupsCountA = 0;
				auto const* newGroupsA = newGroupingControllerA.groupByPhone(workArray, workCount, newGroupsCountA);
				std::cout << std::endl << "Результат работы переприсвоенного контроллера (A):" << std::endl;
				newGroupingControllerA.printGroupsTable(std::cout, newGroupsA, newGroupsCountA);

				int newGroupsCountB = 0;
				auto const* newGroupsB = newGroupingControllerB.groupByPhone(workArray, workCount, newGroupsCountB);
				std::cout << std::endl << "Результат работы переприсвоенного контроллера (B):" << std::endl;
				newGroupingControllerB.printGroupsTable(std::cout, newGroupsB, newGroupsCountB);
			}

			void AssignmentOperatorsTester::testSearchingOperationsControllerAssignmentOperator(const Data::SearchingOperationsController searchingController, const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const
			{
				Data::SearchingOperationsController newSearchControllerA;
				Data::SearchingOperationsController newSearchControllerB;
				newSearchControllerA = newSearchControllerB = searchingController;

				int matchCount = 0;
				auto const* matches = searchingController.searchByPhoneNumber(workArray, workCount, *phoneNumber, matchCount);
				std::cout << std::endl << "Результат работы основного контроллера:" << std::endl;
				searchingController.displayMatches(matches, matchCount);

				int newMatchesCountA = 0;
				auto const* newMatchesA = newSearchControllerA.searchByPhoneNumber(workArray, workCount, *phoneNumber, newMatchesCountA);
				std::cout << std::endl << "Результат работы переприсвоенного контроллера (A):" << std::endl;
				searchingController.displayMatches(newMatchesA, newMatchesCountA);

				int newMatchesCountB = 0;
				auto const* newMatchesB = newSearchControllerB.searchByPhoneNumber(workArray, workCount, *phoneNumber, newMatchesCountB);
				std::cout << std::endl << "Результат работы переприсвоенного контроллера (B):" << std::endl;
				searchingController.displayMatches(newMatchesB, newMatchesCountB);
			}

			void AssignmentOperatorsTester::testGeneralDataRepositoryAssignmentOperator(const Repos::GeneralDataRepo dataRepo, const Models::Talk* workArray, int workCount, const std::string& phoneNumber) const
			{
				Repos::GeneralDataRepo newRepoA;
				Repos::GeneralDataRepo newRepoB;
				newRepoA = newRepoB = dataRepo;

				// Testing Basic Repo.
				std::cout << std::endl << std::endl << "[ ОСНОВНОЙ РЕПОЗИТОРИЙ ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerAssignmentOperator(dataRepo.basicOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerAssignmentOperator(dataRepo.groupingOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerAssignmentOperator(dataRepo.searchingOperationsController, workArray, workCount, &phoneNumber);

				// Testing Repo's Copy — A.
				std::cout << std::endl << std::endl << "[ ПЕРЕПРИСВОЕННЫЙ РЕПОЗИТОРИЙ (A) ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerAssignmentOperator(newRepoA.basicOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerAssignmentOperator(newRepoA.groupingOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerAssignmentOperator(newRepoA.searchingOperationsController, workArray, workCount, &phoneNumber);

				// Testing Repo's Copy — B.
				std::cout << std::endl << std::endl << "[ ПЕРЕПРИСВОЕННЫЙ РЕПОЗИТОРИЙ (B) ]" << std::endl;
				std::cout << "Базовые операции:" << std::endl;
				testBasicOperationsControllerAssignmentOperator(newRepoB.basicOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции группировки:" << std::endl;
				testGroupingOperationsControllerAssignmentOperator(newRepoB.groupingOperationsController, workArray, workCount);

				std::cout << std::endl << "Операции поиска:" << std::endl;
				testSearchingOperationsControllerAssignmentOperator(newRepoB.searchingOperationsController, workArray, workCount, &phoneNumber);

			}
		}
	}
}
