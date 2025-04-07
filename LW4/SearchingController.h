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
                Models::Talk* searchByPhoneNumber(const Models::Talk* array, int count, const std::string& phoneNumber, int& matchCount) const;

                void sortByCallDate(Models::Talk* array, int count) const;
                void sortByCallTime(Models::Talk* array, int count) const;
            };
        }
    }
}
