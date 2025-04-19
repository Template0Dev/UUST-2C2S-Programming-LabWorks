#include "BasicOperationsController.h"
#include "TalkTableData.h"
#include "Utils.h"
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


namespace LW5
{
	namespace Controllers
	{
		namespace Data
		{
			void BasicOperationsController::printTable(std::ostream& output, const Models::Talk* array, int count) const
			{
				if (count == 0)
				{
					output << "Список пуст." << std::endl;
					return;
				}

				// Расчёт ширины столбцов.
				const std::array<std::string, 8> headers = {
					"ID",
					"Имя",
					"Фамилия",
					"Отчество",
					"Телефон",
					"Начало Разговора",
					"Конец Разговора",
					"Тарификация"
				};
				std::array<int, 8> columnWidths = {
					static_cast<int>(headers.at(0).length()),
					static_cast<int>(headers.at(1).length()),
					static_cast<int>(headers.at(2).length()),
					static_cast<int>(headers.at(3).length()),
					static_cast<int>(headers.at(4).length()),
					static_cast<int>(headers.at(5).length()),
					static_cast<int>(headers.at(6).length()),
					static_cast<int>(headers.at(7).length())
				};
				for (int i = 0; i < count; i++)
				{
					columnWidths[0] = std::max(columnWidths[0], static_cast<int>(std::to_string(count).length()));
					columnWidths[1] = std::max(columnWidths[1], static_cast<int>(array[i].getMobile().getName().length()));
					columnWidths[2] = std::max(columnWidths[2], static_cast<int>(array[i].getMobile().getSurname().length()));
					columnWidths[3] = std::max(columnWidths[3], static_cast<int>(array[i].getMobile().getPatronymic().length()));
					columnWidths[4] = std::max(columnWidths[4], static_cast<int>(array[i].getMobile().getPhoneNumber().length()));
					columnWidths[5] = std::max(columnWidths[5], static_cast<int>(array[i].getCallStart().toString().length()));
					columnWidths[6] = std::max(columnWidths[6], static_cast<int>(array[i].getCallEnding().toString().length()));
					columnWidths[7] = std::max(columnWidths[7], static_cast<int>(std::to_string(array[i].getCallDuration()).length()));
				}

				// Расчёт общей ширины.
				int totalWidth = 1;
				for (int width : columnWidths)
					totalWidth += width + 3;

				// Вывод заголовка таблицы.
				output << std::string(totalWidth, '=') << '\n';
				for (size_t i = 0; i < headers.size(); i++)
					printCell(output, headers[i], columnWidths[i]);
				output << "|\n";

				// Вывод основной таблицы.
				for (int i = 0; i < count; i++)
				{
					output << std::string(totalWidth, '-') << '\n';

					Models::Wrappers::TalkTableData talkData(i, array[i], columnWidths);
					output << talkData;
				}
				output << std::string(totalWidth, '=') << '\n';
			}

			void BasicOperationsController::clearArray(Models::Talk*& array, int& arrayCount)
			{
				if (array)
				{
					delete[] array;
					array = nullptr;
				}

				arrayCount = 0;
			}
			Models::Talk* BasicOperationsController::resizeArray(Models::Talk* array, int oldCount, int newCount) const
			{
				auto* newArray = new Models::Talk[newCount];
				int minCount = (oldCount < newCount) ? oldCount : newCount;
				for (int i = 0; i < minCount; i++)
				{
					newArray[i] = array[i];
				}

				delete[] array;
				return newArray;
			}
			void BasicOperationsController::appendRecord(Models::Talk*& array, int& count, const Models::Talk& record) const
			{
				array = resizeArray(array, count, count + 1);
				array[count] = record;
				count++;
			}

			void BasicOperationsController::loadFromKeyboard(Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount)
			{
				int entriesCount;
				clearArray(mainArray, mainCount);
				clearArray(workArray, workCount);

				std::cout << "Введите количество записей: ";
				while (!(std::cin >> entriesCount) || entriesCount < 0)
				{
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "Некорректное значение. Новое значение: ";
				}
				std::cin.ignore();

				// Выделяем новый массив нужного размера.
				mainArray = new Models::Talk[entriesCount];
				workArray = new Models::Talk[entriesCount];
				mainCount = workCount = 0;

				for (int i = 0; i < entriesCount; i++)
				{
					std::cout << "Запись " << i + 1 << ":" << std::endl;
					Models::Talk newEntry = userGuidedTalkCreation();

					mainArray[mainCount++] = newEntry;
					workArray[workCount++] = newEntry;
				}
				std::cout << std::endl << "Записи успешно добавлены. Основной массив обновлён." << std::endl;
			}
			bool BasicOperationsController::loadFromFile(const std::string& filename, Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount) {
				std::ifstream inFile(filename);
				if (!inFile.is_open()) {
					std::cerr << "Ошибка открытия файла: " << filename << std::endl;
					return false;
				}

				std::string line;
				for (int i = 0; i < 3; ++i) {
					if (!std::getline(inFile, line)) {
						inFile.close();
						return false;
					}
				}

				clearArray(mainArray, mainCount);
				clearArray(workArray, workCount);

				Models::Talk talk;
				while (inFile >> talk)
				{
					std::getline(inFile, line);

					appendRecord(mainArray, mainCount, talk);
					appendRecord(workArray, workCount, talk);
				}

				inFile.close();
				return true;
			}
			bool BasicOperationsController::saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const
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

			bool BasicOperationsController::addRecord(const Models::Talk& record, Models::Talk*& workArray, int& workCount) const
			{
				appendRecord(workArray, workCount, record);
				return true;
			}
			bool BasicOperationsController::deleteRecord(int index, Models::Talk*& workArray, int& workCount) const
			{
				if (index < 0 || index >= workCount)
				{
					std::cerr << "Некорректный индекс элемента для удаления." << std::endl;
					return false;
				}

				// Создаем новый массив меньшего размера.
				auto newArray = new Models::Talk[workCount - 1];
				for (int i = 0, j = 0; i < workCount; i++)
				{
					if (i == index)
						continue;
					newArray[j++] = workArray[i];
				}
				delete[] workArray;
				workArray = newArray;
				workCount--;
				return true;
			}

			void BasicOperationsController::displayData(const Models::Talk* workArray, int workCount) const
			{
				printTable(std::cout, workArray, workCount);
			}

			void BasicOperationsController::sortByName(Models::Talk* workArray, int workCount) const
			{
				for (int i = 0; i < workCount - 1; i++)
				{
					int minIndex = i;
					for (int j = i + 1; j < workCount; j++)
					{
						Models::Mobile m1 = workArray[j].getMobile();
						Models::Mobile m2 = workArray[minIndex].getMobile();
						if (m1 < m2)
						{
							minIndex = j;
						}
					}
					if (minIndex != i)
						std::swap(workArray[i], workArray[minIndex]);
				}
			}
			void BasicOperationsController::sortByDate(Models::Talk* workArray, int workCount) const
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
					if (minIndex != i)
						std::swap(workArray[i], workArray[minIndex]);
				}
			}
			void BasicOperationsController::sortByDuration(Models::Talk* workArray, int workCount) const
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
					if (minIndex != i)
						std::swap(workArray[i], workArray[minIndex]);
				}
			}

			void BasicOperationsController::resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount)
			{
				clearArray(workArray, workCount);
				workArray = new Models::Talk[mainCount];
				for (int i = 0; i < mainCount; i++)
				{
					workArray[i] = mainArray[i];
				}
				workCount = mainCount;
			}
		}
	}
}
