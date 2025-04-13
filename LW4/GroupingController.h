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
				/// <summary>
				/// Default constructor.
				/// </summary>
				GroupingController();
				/// <summary>
				/// The searching controller stateless itself, therefore it doesn't contain any data.
				/// But as it is a requirement, I implement this by calling default constructor.
				/// </summary>
				/// <param name="other">Other controller to copy.</param>
				GroupingController(const GroupingController& other);
				/// <summary>
				/// And again, the controller itself is stateles, but as requirement, I implement it.
				/// This is destructor.
				/// </summary>
				~GroupingController();

				Models::Wrappers::GroupedTalk* groupByPhone(const Models::Talk* array, int count, int& groupCount) const;

				void sortByTalkCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const;
				void sortByPhoneNumber(Models::Wrappers::GroupedTalk* groups, int groupCount) const;

				void printGroupsTable(std::ostream& output, const Models::Wrappers::GroupedTalk* groups, int count) const;
				bool saveToFile(const std::string& fileName, const Models::Wrappers::GroupedTalk* groups, int count) const;

				GroupingController& operator =(const GroupingController& other);
			};
		}
	}
}
