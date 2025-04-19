#pragma once

#include "Talk.h"
#include "BasicOperationsController.h"


namespace LW5
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
                friend void executeBasicOperation(CLIController& controller, int operation, const std::string& fileName);
                friend void executeGroupingOperation(const CLIController& controller, int operation);
                friend void executeSearchingOperation(CLIController& controller, int operation, const std::string& phoneNumber);

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
