#include "TalkTableData.h"
#include "Utils.h"
#include <iostream>
#include <string>


namespace LW6
{
	namespace Models
	{
		namespace Wrappers
		{
			TalkTableData::TalkTableData(const int& id, const Talk& talk, const std::array<int, 8>& tableData)
			{
				this->id = id;
				this->talk = talk;
				this->tableData = tableData;
			}

			// Getters for Fields.
			int TalkTableData::getID() const
			{
				return id;
			}
			Talk TalkTableData::getTalk() const
			{
				return talk;
			}
			std::array<int, 8> TalkTableData::getTableData() const
			{
				return tableData;
			}

			// Setters for Fields.
			void TalkTableData::setID(const int& newIDVal)
			{
				id = newIDVal;
			}
			void TalkTableData::setTalk(const Talk& newTalkVal)
			{
				talk = newTalkVal;
			}
			void TalkTableData::setTableData(const std::array<int, 8>& newTableDataVal)
			{
				tableData = newTableDataVal;
			}

			// Operators.
			std::ostream& operator <<(std::ostream& out, const TalkTableData& instance)
			{
				printCell(out, std::to_string(instance.getID()), instance.getTableData().at(0));
				printCell(out, instance.getTalk().getMobile().getName(), instance.getTableData().at(1));
				printCell(out, instance.getTalk().getMobile().getSurname(), instance.getTableData().at(2));
				printCell(out, instance.getTalk().getMobile().getPatronymic(), instance.getTableData().at(3));
				printCell(out, instance.getTalk().getMobile().getPhoneNumber(), instance.getTableData().at(4));
				printCell(out, instance.getTalk().getCallStart().toString(), instance.getTableData().at(5));
				printCell(out, instance.getTalk().getCallEnding().toString(), instance.getTableData().at(6));
				printCell(out, std::to_string(instance.getTalk().getCallDuration()), instance.getTableData().at(7));

				out << "|\n";
				return out;
			}
		}
	}
}
