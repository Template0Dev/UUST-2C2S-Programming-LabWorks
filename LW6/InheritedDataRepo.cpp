#include "InheritedDataRepo.h"


namespace LW6
{
    namespace Controllers
    {
        namespace Repos
        {
            Data::BasicOperationsController& InheritedDataRepo::getBOPS() { return static_cast<Data::BasicOperationsController&>(*this); }
            Data::GroupingOperationsController& InheritedDataRepo::getGOPS() { return static_cast<Data::GroupingOperationsController&>(*this); }
            Data::SearchingOperationsController& InheritedDataRepo::getSOPS() { return static_cast<Data::SearchingOperationsController&>(*this); }

            InheritedDataRepo::InheritedDataRepo() : Data::BasicOperationsController(), Data::GroupingOperationsController(), Data::SearchingOperationsController() {};
            InheritedDataRepo::InheritedDataRepo(const InheritedDataRepo& other) : Data::BasicOperationsController(other), Data::GroupingOperationsController(other), Data::SearchingOperationsController(other) {};
            InheritedDataRepo::~InheritedDataRepo() = default;

            InheritedDataRepo& InheritedDataRepo::operator =(const InheritedDataRepo& other)
            {
                if (this != &other)
                {
                    Data::BasicOperationsController::operator =(other);
                    Data::GroupingOperationsController::operator =(other);
                    Data::SearchingOperationsController::operator =(other);
                }

                return *this;
            }
        }
    }
}
