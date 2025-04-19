#pragma once

#include "Talk.h"
#include <string>


namespace LW5
{
    namespace Controllers
    {
        namespace Data
        {
            class SearchingOperationsController
            {
            public:
                /// <summary>
                /// Default constructor.
                /// </summary>
                SearchingOperationsController();
                /// <summary>
                /// The searching controller stateless itself, therefore it doesn't contain any data.
                /// But as it is a requirement, I implement this by calling default constructor.
                /// </summary>
                /// <param name="other">Other controller to copy.</param>
                SearchingOperationsController(const SearchingOperationsController& other);
                /// <summary>
                /// And again, the constructor itself is stateles, but as requirement, I implement it.
                /// This is destructor.
                /// </summary>
                ~SearchingOperationsController();

                Models::Talk* searchByPhoneNumber(const Models::Talk* array, int count, const std::string& phoneNumber, int& matchCount) const;

                void sortByCallDate(Models::Talk* array, int count) const;
                void sortByCallTime(Models::Talk* array, int count) const;

                void displayMatches(const Models::Talk* workArray, int workCount) const;
                bool saveMatchesToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const;

                SearchingOperationsController& operator =(const SearchingOperationsController& other);
            };
        }
    }
}
