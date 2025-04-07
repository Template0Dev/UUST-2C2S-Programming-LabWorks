#include "GroupingController.h"
#include "GroupedTalk.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <cstring>


namespace LW4
{
    namespace Controllers
    {
        namespace Data
        {

            Models::Wrappers::GroupedTalk* GroupingController::groupByPhone(const Models::Talk* array, int count, int& groupCount) const
            {
                groupCount = 0;
                auto* tempGroups = new Models::Wrappers::GroupedTalk[count];

                for (int i = 0; i < count; i++)
                {
                    std::string phone = array[i].getMobile().getPhoneNumber();
                    bool found = false;

                    for (int j = 0; j < groupCount; j++)
                    {
                        if (tempGroups[j].phoneNumber == phone)
                        {
                            tempGroups[j].talkCount++;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        tempGroups[groupCount].phoneNumber = phone;
                        tempGroups[groupCount].talkCount = 1;
                        groupCount++;
                    }
                }

                auto* groups = new Models::Wrappers::GroupedTalk[groupCount];
                for (int i = 0; i < groupCount; i++)
                {
                    groups[i] = tempGroups[i];
                }

                delete[] tempGroups;
                return groups;
            }

            void GroupingController::sortByTalkCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const
            {
                for (int i = 0; i < groupCount - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < groupCount; j++)
                    {
                        if (groups[j].talkCount < groups[minIndex].talkCount)
                        {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i)
                    {
                        Models::Wrappers::GroupedTalk temp = groups[i];
                        groups[i] = groups[minIndex];
                        groups[minIndex] = temp;
                    }
                }
            }

            void GroupingController::sortByPhoneNumber(Models::Wrappers::GroupedTalk* groups, int groupCount) const
            {
                for (int i = 0; i < groupCount - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < groupCount; j++)
                    {
                        if (groups[j].phoneNumber < groups[minIndex].phoneNumber)
                        {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i)
                    {
                        Models::Wrappers::GroupedTalk temp = groups[i];
                        groups[i] = groups[minIndex];
                        groups[minIndex] = temp;
                    }
                }
            }

        }
    }
}
