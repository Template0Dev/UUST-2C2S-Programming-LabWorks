#pragma once

#include "Talk.h"
#include "BasicOperationsController.h"


namespace LW4
{
    namespace Controllers
    {
        namespace Views
        {
            class CLIController
            {
            private:
                static const int INIT_SIZE = 128;

                int mainCount = 0;
                Models::Talk* mainArray;

                int workCount = 0;
                Models::Talk* workArray;

            public:
                CLIController();
                CLIController(const CLIController& other);
                ~CLIController();

                void beginWork();

            private:
                void proceedWorkCycle();
                void printCommandsMenu() const;

                bool addNewEntrySubFunction();
                bool removeEntrySubFunction();

                CLIController& operator =(const CLIController& other);
            };
        }
    }
}
