#pragma once

#include "Talk.h"
#include "GroupedTalk.h"
#include <string>


namespace LW4
{
	namespace Controllers
	{
		namespace Data
		{
			class GroupingController
			{
			public:
				Models::Wrappers::GroupedTalk* groupByPhone(const Models::Talk* array, int count, int& groupCount) const;

				void sortByTalkCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
				void sortByPhoneNumber(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
			};
		}
	}
}
