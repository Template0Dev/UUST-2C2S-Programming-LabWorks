#pragma once

#include "Talk.h"
#include "MainController.h"


namespace LW2
{
    namespace Controllers
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
                ~CLIController();

                void beginWork();

            private:
                void proceedWorkCycle();
                void printCommandsMenu() const;

                bool addNewEntrySubFunction();
                bool removeEntrySubFunction();
            };
    }
}
