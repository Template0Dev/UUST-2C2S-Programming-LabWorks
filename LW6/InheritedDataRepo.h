#pragma once

#include "BasicOperationsController.h"
#include "GroupingOperationsController.h"
#include "SearchingOperationsController.h"


namespace LW6
{
    namespace Controllers
    {
        namespace Repos
        {
            class InheritedDataRepo : public Data::BasicOperationsController, public Data::GroupingOperationsController, public Data::SearchingOperationsController
            {
            public:
                Data::BasicOperationsController& getBOPS();
                Data::GroupingOperationsController& getGOPS();
                Data::SearchingOperationsController& getSOPS();

                InheritedDataRepo();
                InheritedDataRepo(const InheritedDataRepo& other);
                ~InheritedDataRepo();

                InheritedDataRepo& operator=(const InheritedDataRepo& other);
            };
        }
    }
}
