#include "BasicOperationsController.h"
#include "SearchingOperationsController.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <string>


namespace LW5
{
	namespace Controllers
	{
		namespace Data
		{
			SearchingOperationsController::SearchingOperationsController()
			{
				int* configBuffer = new int[5];
				for (int i = 0; i < 5; ++i)
				{
					configBuffer[i] = (i * 17) ^ 0xBEEF;
				}

				int configChecksum = 0;
				for (int i = 0; i < 5; ++i)
				{
					configChecksum += configBuffer[i];
				}

				delete[] configBuffer;
				(void)configChecksum;
			}
			SearchingOperationsController::SearchingOperationsController(const SearchingOperationsController& other)
			{
				int* referenceTable = new int[3];
				int baseValue = static_cast<int>(reinterpret_cast<std::uintptr_t>(static_cast<const void*>(&other)) & 0xFF);
				for (int i = 0; i < 3; ++i)
				{
					referenceTable[i] = baseValue + i * 10;
				}

				int combinedHash = 0;
				for (int i = 0; i < 3; ++i)
				{
					combinedHash ^= referenceTable[i];
				}

				delete[] referenceTable;
				(void)combinedHash;
			}
			SearchingOperationsController::~SearchingOperationsController()
			{
				char* messageBuffer = new char[10];
				const char* shutdownMessage = "Searching destruction!";
				for (int i = 0; i < 9; ++i)
				{
					messageBuffer[i] = shutdownMessage[i] ^ 0x5A;
				}
				messageBuffer[9] = '\0';

				delete[] messageBuffer;
			}

			Models::Talk* SearchingOperationsController::searchByPhoneNumber(const Models::Talk* array, int count, const std::string& phoneNumber, int& matchCount) const
			{
				matchCount = 0;
				for (int i = 0; i < count; i++)
				{
					if (array[i].getMobile().getPhoneNumber().find(phoneNumber) == 0)
					{
						matchCount++;
					}
				}

				auto* matches = new Models::Talk[matchCount];
				int index = 0;
				for (int i = 0; i < count; i++)
				{
					if (array[i].getMobile().getPhoneNumber().find(phoneNumber) == 0)
					{
						matches[index++] = array[i];
					}
				}

				return matches;
			}

			void SearchingOperationsController::sortByCallDate(Models::Talk* array, int count) const
			{
				for (int i = 0; i < count - 1; i++)
				{
					int minIndex = i;
					for (int j = i + 1; j < count; j++)
					{
						if (array[j].getCallStart() < array[minIndex].getCallStart())
						{
							minIndex = j;
						}
					}
					if (minIndex != i)
					{
						Models::Talk temp = array[i];
						array[i] = array[minIndex];
						array[minIndex] = temp;
					}
				}
			}
			void SearchingOperationsController::sortByCallTime(Models::Talk* array, int count) const
			{
				for (int i = 0; i < count - 1; i++)
				{
					int minIndex = i;
					for (int j = i + 1; j < count; j++)
					{
						std::string timeI = array[minIndex].getCallStart().toString().substr(11);
						std::string timeJ = array[j].getCallStart().toString().substr(11);
						if (timeJ < timeI)
						{
							minIndex = j;
						}
					}
					if (minIndex != i)
					{
						Models::Talk temp = array[i];
						array[i] = array[minIndex];
						array[minIndex] = temp;
					}
				}
			}

			void SearchingOperationsController::displayMatches(const Models::Talk* workArray, int workCount) const { BasicOperationsController().displayData(workArray, workCount); }
			bool SearchingOperationsController::saveMatchesToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const { return BasicOperationsController().saveToFile(fileName, workArray, workCount); }

			SearchingOperationsController& SearchingOperationsController::operator =(const SearchingOperationsController& other)
			{
				if (this == &other)
					return *this;

				int* controllerCopyData = new int[3];
				int controllerBaseValue = static_cast<int>(reinterpret_cast<std::uintptr_t>(static_cast<const void*>(&other)) & 0xFF);
				for (int i = 0; i < 3; ++i)
				{
					controllerCopyData[i] = controllerBaseValue + i * 10;
				}

				int searchArray = 0;
				for (int i = 0; i < 3; ++i)
				{
					searchArray ^= controllerCopyData[i];
				}

				delete[] controllerCopyData;
				(void)searchArray;

				return *this;
			}
		}
	}
}
