#pragma once

#include "Talk.h"
#include "BasicOperationsController.h"
#include "GroupingOperationsController.h"
#include "SearchingOperationsController.h"
#include "GeneralData.h"


namespace LW5
{
	namespace Controllers
	{
		namespace Testers
		{
			class CopyControllersTester
			{
			public:
				void testBasicOperationsControllerCopyConstructor(const Data::BasicOperationsController controller, const Models::Talk* workArray, int workCount) const;
				void testGroupingOperationsControllerCopyConstructor(const Data::GroupingOperationsController groupingController, const Models::Talk* workArray, int workCount) const;
				void testSearchingOperationsControllerCopyConstructor(const Data::SearchingOperationsController searchingController, const Models::Talk* workArray, int workCount, const std::string* phoneNumber) const;
				void testGeneralDataRepositoryCopyConstructor(const Repos::GeneralData dataRepo, const Models::Talk* workArray, int workCount, const std::string& phoneNumber) const;
			};
		}
	}
}
