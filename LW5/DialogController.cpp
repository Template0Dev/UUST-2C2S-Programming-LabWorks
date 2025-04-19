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

			std::string DialogController::getFileName()
			{
				std::string fileName;
				std::cout << "Введите название файла для сохранения: ";
				std::cin >> fileName;

				return fileName;
			}
		}
	}
}
