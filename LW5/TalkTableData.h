#pragma once

#include "Talk.h"
#include <array>


namespace LW5
{
	namespace Models
	{
		namespace Wrappers
		{
			struct TalkTableData
			{
			private:
				int id;
				Talk talk;
				std::array<int, 8> tableData;

			public:
				// Constructors.
				TalkTableData(const int& id, const Talk& talk, const std::array<int, 8>& tableData);

				// Getters for Fields.
				int getID() const;
				Talk getTalk() const;
				std::array<int, 8> getTableData() const;

				// Setters for Fields.
				void setID(const int& newIDVal);
				void setTalk(const Talk& newTalkVal);
				void setTableData(const std::array<int, 8>& newTableDataVal);

				// Operators.
				friend std::ostream& operator <<(std::ostream& out, const TalkTableData& instance);
			};
		}
	}
}
