#pragma once

#include "Talk.h"
#include "BasicOperationsController.h"
#include "GroupingOperationsController.h"
#include "SearchingOperationsController.h"


namespace LW5
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
			};
		}
	}
}
