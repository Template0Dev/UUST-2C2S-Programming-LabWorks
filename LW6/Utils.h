#pragma once

#include "Talk.h"
#include <string>


namespace LW5
{
	std::string trim(const std::string& s);

	void printCell(std::ostream& output, const std::string& text, int width);

	Models::Talk userGuidedTalkCreation();

	std::string getPhoneNumber();
}
