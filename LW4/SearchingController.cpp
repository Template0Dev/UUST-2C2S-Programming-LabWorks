#include "SearchingController.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <string>


namespace LW4
{
    namespace Controllers
    {
        namespace Data
        {


            Models::Talk* SearchingController::searchByPhoneNumber(const Models::Talk* array, int count, const std::string& phoneNumber, int& matchCount) const
            {
                matchCount = 0;
                for (int i = 0; i < count; i++)
                {
                    if (array[i].getMobile().getPhoneNumber().find(phoneNumber) == 0)
                    {
                        matchCount++;
                    }
                }

                auto* matches = new Models::Talk[matchCount];
                int index = 0;
                for (int i = 0; i < count; i++)
                {
                    if (array[i].getMobile().getPhoneNumber().find(phoneNumber) == 0)
                    {
                        matches[index++] = array[i];
                    }
                }

                return matches;
            }

            void SearchingController::sortByCallDate(Models::Talk* array, int count) const
            {
                for (int i = 0; i < count - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < count; j++)
                    {
                        if (array[j].getCallStart() < array[minIndex].getCallStart())
                        {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i)
                    {
                        Models::Talk temp = array[i];
                        array[i] = array[minIndex];
                        array[minIndex] = temp;
                    }
                }
            }

            void SearchingController::sortByCallTime(Models::Talk* array, int count) const
            {
                for (int i = 0; i < count - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < count; j++)
                    {
                        std::string timeI = array[minIndex].getCallStart().toString().substr(11);
                        std::string timeJ = array[j].getCallStart().toString().substr(11);
                        if (timeJ < timeI)
                        {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i)
                    {
                        Models::Talk temp = array[i];
                        array[i] = array[minIndex];
                        array[minIndex] = temp;
                    }
                }
            }

        }
    }
}
