#pragma once

#include "Talk.h"
#include <string>


namespace LW4
{
    namespace Controllers
    {
        namespace Data
        {
            class SearchingController
            {
            public:
                /// <summary>
                /// Default constructor.
                /// </summary>
                SearchingController();
                /// <summary>
                /// The searching controller stateless itself, therefore it doesn't contain any data.
                /// But as it is a requirement, I implement this by calling default constructor.
                /// </summary>
                /// <param name="other">Other controller to copy.</param>
                SearchingController(const SearchingController& other);
                /// <summary>
                /// And again, the constructor itself is stateles, but as requirement, I implement it.
                /// This is destructor.
                /// </summary>
                ~SearchingController();

                Models::Talk* searchByPhoneNumber(const Models::Talk* array, int count, const std::string& phoneNumber, int& matchCount) const;

                void sortByCallDate(Models::Talk* array, int count) const;
                void sortByCallTime(Models::Talk* array, int count) const;

                SearchingController& operator =(const SearchingController& other);
            };
        }
    }
}
