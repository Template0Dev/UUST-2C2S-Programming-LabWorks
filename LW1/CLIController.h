#pragma once

#include "Talk.h"
#include "MainController.h"


namespace LW1
{
	namespace Controllers
	{
		class CLIController
		{
			private:
				int mainCount = 0;
				Models::Talk mainArray[MainController::MAX_SIZE];

				int workCount = 0;
				Models::Talk workArray[MainController::MAX_SIZE];

			public:
				void beginWork();

			private:
				void proceedWorkCycle();
				void printCommandsMenu() const;

				bool addNewEntrySubFunction();
				bool removeEntrySubFunction();
		};
	}
}
