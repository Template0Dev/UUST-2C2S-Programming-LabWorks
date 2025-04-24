#pragma once

#include "Talk.h"
#include "BasicOperationsController.h"
#include "GroupingOperationsController.h"
#include "SearchingOperationsController.h"
#include "GeneralDataRepo.h"
#include "InheritedDataRepo.h"


namespace LW6
{
	namespace Controllers
	{
		namespace Testers
		{
			class AssignmentOperatorsTester
			{
			public:
				void testBasicOperationsControllerAssignmentOperator(const Data::BasicOperationsController controller, const Models::Talk* workArray, int workCount) const;
				void testGroupingOperationsControllerAssignmentOperator(const Data::GroupingOperationsController groupingController, const Models::Talk* workArray, int workCount) const;
				void testSearchingOperationsControllerAssignmentOperator(const Data::SearchingOperationsController searchingController, const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const;

				void testGeneralDataRepositoryAssignmentOperator(const Repos::GeneralDataRepo dataRepo, const Models::Talk* workArray, int workCount, const std::string& phoneNumber) const;
				void testInheritedDataRepositoryAssignmentOperator(const Repos::InheritedDataRepo dataRepo, const Models::Talk* workArray, int workCount, const std::string& phoneNumber) const;
			};
		}
	}
}
