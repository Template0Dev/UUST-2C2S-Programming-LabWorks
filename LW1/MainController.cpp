#include "MainController.h"
#include "Utils.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>


namespace LW1
{
	namespace Controllers
	{
		void MainController::printCell(std::ostream& output, const std::string& text, int width) const
		{
			output << "| " << text;
			auto len = (int)text.size();
			for (int s = len; s < width; s++) output << " ";
			output << " ";
		}
		void MainController::printTable(std::ostream& output, const Models::Talk array[], int count) const 
		{
			if (count == 0) 
			{
				output << "Список пуст." << std::endl;
				return;
			}

			const std::string idHeader = "№";
			const std::string nameHeader = "Имя";
			const std::string surnameHeader = "Фамилия";
			const std::string patronymicHeader = "Отчество";
			const std::string phoneNumberHeader = "Телефон";
			const std::string callStartHeader = "Начало Разговора";
			const std::string callEndingHeader = "Конец Разговора";
			const std::string callTarificationHeader = "Тарификация Связи";

			auto maxIDColumnWidth = (int)idHeader.length();
			auto maxNameColumnWidth = (int)nameHeader.length();
			auto maxSurnameColumnWidth = (int)surnameHeader.length();
			auto maxPatronymicColumnWidth = (int)patronymicHeader.length();
			auto maxPhoneNumberColumnWidth = (int)phoneNumberHeader.length();
			auto maxCallStartColumnWidth = (int)callStartHeader.length();
			auto maxCallEndingColumnWidth = (int)callEndingHeader.length();
			auto maxCallTarificationColumnWidth = (int)callTarificationHeader.length();

			for (int i = 0; i < count; i++) 
			{
				maxIDColumnWidth = std::max(maxIDColumnWidth, (int)std::to_string(count).length());
				maxNameColumnWidth = std::max(maxNameColumnWidth, (int)array[i].getMobile().getName().length());
				maxSurnameColumnWidth = std::max(maxSurnameColumnWidth, (int)array[i].getMobile().getSurname().length());
				maxPatronymicColumnWidth = std::max(maxPatronymicColumnWidth, (int)array[i].getMobile().getPatronymic().length());
				maxPhoneNumberColumnWidth = std::max(maxPhoneNumberColumnWidth, (int)array[i].getMobile().getPhoneNumber().length());
				maxCallStartColumnWidth = std::max(maxCallStartColumnWidth, (int)array[i].getCallStart().toString().length());
				maxCallEndingColumnWidth = std::max(maxCallEndingColumnWidth, (int)array[i].getCallEnding().toString().length());
				maxCallTarificationColumnWidth = std::max(maxCallTarificationColumnWidth, (int)std::to_string(array[i].getTalkTarification()).length());
			}

			int totalWidth = 1
				+ 1 + maxIDColumnWidth + 2
				+ 1 + maxNameColumnWidth + 2
				+ 1 + maxSurnameColumnWidth + 2
				+ 1 + maxPatronymicColumnWidth + 2
				+ 1 + maxPhoneNumberColumnWidth + 2
				+ 1 + maxCallStartColumnWidth + 2
				+ 1 + maxCallEndingColumnWidth + 2
				+ 1 + maxCallTarificationColumnWidth + 2;

			for (int i = 0; i < totalWidth; i++) output << '=';
			output << '\n';

			printCell(output, idHeader, maxIDColumnWidth);
			printCell(output, nameHeader, maxNameColumnWidth);
			printCell(output, surnameHeader, maxSurnameColumnWidth);
			printCell(output, patronymicHeader, maxPatronymicColumnWidth);
			printCell(output, phoneNumberHeader, maxPhoneNumberColumnWidth);
			printCell(output, callStartHeader, maxCallStartColumnWidth);
			printCell(output, callEndingHeader, maxCallEndingColumnWidth);
			printCell(output, callTarificationHeader, maxCallTarificationColumnWidth);
			output << "|\n";

			for (int i = 0; i < totalWidth; i++) output << '-';
			output << '\n';

			for (int i = 0; i < count; i++) 
			{
				printCell(output, std::to_string(i), maxIDColumnWidth);
				printCell(output, array[i].getMobile().getName(), maxNameColumnWidth);
				printCell(output, array[i].getMobile().getSurname(), maxSurnameColumnWidth);
				printCell(output, array[i].getMobile().getPatronymic(), maxPatronymicColumnWidth);
				printCell(output, array[i].getMobile().getPhoneNumber(), maxPhoneNumberColumnWidth);
				printCell(output, array[i].getCallStart().toString(), maxCallStartColumnWidth);
				printCell(output, array[i].getCallEnding().toString(), maxCallEndingColumnWidth);
				printCell(output, std::to_string(array[i].getCallDuration()), maxCallTarificationColumnWidth);
				output << "|\n";

				if (i + 1 != count) 
					output << "|" << std::string(totalWidth - 2, '-') << "|\n";
			}

			for (int i = 0; i < totalWidth; i++) 
				output << '=';
			output << '\n';
		}
		void MainController::clearArray(Models::Talk array[], int& arrayCount)
		{
			// std::fill_n(array, arrayCount, NULL);
			arrayCount = 0;
		}

		void MainController::loadFromKeyboard(Models::Talk mainArray[], Models::Talk workArray[], int& mainCount, int& workCount)
		{
			int entriesCount;
			clearArray(mainArray, mainCount);
			clearArray(workArray, workCount);

			std::cout << "Введите количество записей (максимальное число " << MAX_SIZE << "): ";
			while (!(std::cin >> entriesCount) || entriesCount < 0 || entriesCount > MAX_SIZE)
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');

				std::cout << "Некорректное значение. Новое значение: ";
			}
			std::cin.ignore();

			for (int i = 0; i < entriesCount; i++) {
				std::cout << "Запись " << i + 1 << ":" << std::endl;
				Models::Talk newEntry = userGuidedTalkCreation();

				mainArray[mainCount] = newEntry;
				mainCount++;
				workArray[workCount] = newEntry;
				workCount++;
			}
			std::cout << std::endl << "Записи успешно добавлены в рабочий массив. Основной массив обновлён." << std::endl;
		}
		bool MainController::loadFromFile(const std::string& filename, Models::Talk mainArray[], Models::Talk workArray[], int& mainCount, int& workCount)
		{
			std::ifstream inFile(filename);
			if (!inFile.is_open()) {
				std::cerr << "Ошибка открытия файла: " << filename << std::endl;
				return false;
			}

			// Skip the top border, header, and header separator lines.
			std::string line;
			if (!std::getline(inFile, line)) { inFile.close(); return false; }
			if (!std::getline(inFile, line)) { inFile.close(); return false; }
			if (!std::getline(inFile, line)) { inFile.close(); return false; }

			// Clear arrays and begin the file processing.
			clearArray(mainArray, mainCount);
			clearArray(workArray, workCount);
			while (std::getline(inFile, line))
			{
				// Skip border and empty (non-filled) lines.
				if (line.empty() || line.at(0) == '+') continue;

				// Expecting 8 columns: ID, Имя, Фамилия, Отчество, Телефон, Начало разговора, Окончание разговора, Тарификация.
				std::string cells[8];
				int cellIndex = 0;
				size_t pos = 0;
				if (!line.empty() && line.at(0) == '|')
					pos = 1;

				// Extract cells separated by '|'.
				while (cellIndex < 8)
				{
					size_t nextPos = line.find('|', pos);
					if (nextPos == std::string::npos)
						break;
					std::string cell = line.substr(pos, nextPos - pos);
					cells[cellIndex] = trim(cell);
					cellIndex++;
					pos = nextPos + 1;
				}

				/*
				 * Columns mapping:
				 * cells[0] — ID (ignored).
				 * cells[1] - Имя;
				 * cells[2] - Фамилия;
				 * cells[3] - Отчество;
				 * cells[4] - Телефон;
				 * cells[5] - Начало разговора;
				 * cells[6] - Окончание разговора;
				 * cells[7] - Тарификация.
				*/
				std::string name = cells[1];
				std::string surname = cells[2];
				std::string patronymic = cells[3];
				std::string phone = cells[4];
				std::string callStartStr = cells[5];
				std::string callEndingStr = cells[6];
				std::string callTarificationStr = cells[7];

				tm startStamp;
				tm endingStamp;
				if (!Models::DateTime::tryParseDateTime(callStartStr.c_str(), startStamp)) continue;
				if (!Models::DateTime::tryParseDateTime(callEndingStr.c_str(), endingStamp)) continue;

				Models::DateTime callStart(startStamp.tm_sec, startStamp.tm_min, startStamp.tm_hour, startStamp.tm_mday, startStamp.tm_mon, startStamp.tm_year);
				Models::DateTime callEnding(endingStamp.tm_sec, endingStamp.tm_min, endingStamp.tm_hour, endingStamp.tm_mday, endingStamp.tm_mon, endingStamp.tm_year);
				if (!callStart.isValidDate() || !callEnding.isValidDate() || (callEnding < callStart))
					continue;

				Models::Mobile mobile(name, surname, patronymic, phone);
				Models::Talk talk(mobile, callStart, callEnding, stod(callTarificationStr));

				mainArray[mainCount] = talk;
				workArray[workCount] = talk;
				mainCount++;
				workCount++;
			}

			inFile.close();
			return true;
		}
		bool MainController::saveToFile(const std::string& fileName, const Models::Talk workArray[], int workCount) const
		{
			std::ofstream outputFile(fileName);
			if (!outputFile.is_open())
			{
				std::cerr << "Ошибка при открытии файла для записи: " << fileName << std::endl;
				return false;
			}

			printTable(outputFile, workArray, workCount);
			outputFile.close();
			return true;
		}

		bool MainController::addRecord(const Models::Talk& record, Models::Talk workArray[], int& workCount) const
		{
			if (workCount >= MAX_SIZE)
			{
				std::cerr << "Рабочий массив заполнен." << std::endl;
				return false;
			}

			workArray[workCount] = record;
			workCount++;
			return true;
		}
		bool MainController::deleteRecord(int index, Models::Talk workArray[], int& workCount) const
		{
			if (index < 0 || index >= workCount)
			{
				std::cerr << "Некорректный индекс элемента для удаления." << std::endl;
				return false;
			}

			workCount--;
			for (int i = index; i < workCount; i++)
				workArray[i] = workArray[i + 1];

			return true;
		}

		void MainController::displayData(const Models::Talk workArray[], int workCount) const
		{
			printTable(std::cout, workArray, workCount);
		}

		void MainController::sortByName(Models::Talk workArray[], int workCount) const
		{
			for (int i = 0; i < workCount - 1; i++)
			{
				int minIndex = i;
				for (int j = i + 1; j < workCount; j++)
				{
					Models::Mobile m1 = workArray[j].getMobile();
					Models::Mobile m2 = workArray[minIndex].getMobile();
					if (m1.getSurname() < m2.getSurname() ||
						(m1.getSurname() == m2.getSurname() && m1.getName() < m2.getName()) ||
						(m1.getSurname() == m2.getSurname() && m1.getName() == m2.getName() &&
							m1.getPatronymic() < m2.getPatronymic()))
					{
						minIndex = j;
					}
				}

				if (minIndex != i) std::swap(workArray[i], workArray[minIndex]);
			}
		}
		void MainController::sortByDate(Models::Talk workArray[], int workCount) const
		{
			for (int i = 0; i < workCount - 1; i++)
			{
				int minIndex = i;
				for (int j = i + 1; j < workCount; j++)
				{
					if (workArray[j].getCallStart() < workArray[minIndex].getCallStart())
					{
						minIndex = j;
					}
				}

				if (minIndex != i) std::swap(workArray[i], workArray[minIndex]);
			}
		}
		void MainController::sortByDuration(Models::Talk workArray[], int workCount) const
		{
			for (int i = 0; i < workCount - 1; i++)
			{
				int minIndex = i;
				for (int j = i + 1; j < workCount; j++)
				{
					if (workArray[j].getCallDuration() < workArray[minIndex].getCallDuration())
					{
						minIndex = j;
					}
				}

				if (minIndex != i) std::swap(workArray[i], workArray[minIndex]);
			}
		}

		void MainController::resetWorkingArray(const Models::Talk mainArray[], Models::Talk workArray[], int mainCount, int& workCount)
		{
			clearArray(workArray, workCount);

			workCount = mainCount;
			for (int i = 0; i < workCount; i++)
				workArray[i] = mainArray[i];
		}
	}
}
