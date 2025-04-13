#pragma once

#include "Talk.h"
#include <string>


namespace LW4
{
	std::string trim(const std::string& s);

	void printCell(std::ostream& output, const std::string& text, int width);

	Models::Talk userGuidedTalkCreation();

	std::string getPhoneNumber();
}
