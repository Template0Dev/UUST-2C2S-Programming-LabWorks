#include "DialogController.h"
#include <iostream>


namespace LW5
{
	namespace Controllers
	{
		namespace Views
		{
			bool DialogController::askConfirmation(const std::string& confirmationMessage)
			{
				char confirmation;
				std::cout << confirmationMessage << " (Y/N)? ";
				std::cin >> confirmation;

				if (confirmation == 'y' || confirmation == 'Y')
					return true;
				return false;
			}

			std::string DialogController::getString(const std::string& requestMessage)
			{
				std::string result;
				std::cout << requestMessage << ": ";
				std::cin >> result;

				return result;
			}

			std::string DialogController::getFileName() { return getString(std::string("¬ведите название файла")); }
		}
	}
}
