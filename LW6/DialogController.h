#pragma once

#include <string>


namespace LW5
{
	namespace Controllers
	{
		namespace Views
		{
			class DialogController
			{
			public:
				static bool askConfirmation(const std::string& confirmationMessage);
				static std::string getString(const std::string& requestMessage);
				static std::string getFileName();
			};
		}
	}
}