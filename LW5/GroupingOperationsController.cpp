#include "GroupingOperationsController.h"
#include "GroupedTalk.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <array>


namespace LW5
{
    namespace Controllers
    {
        namespace Data
        {
            GroupingOperationsController::GroupingOperationsController()
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
            GroupingOperationsController::GroupingOperationsController(const GroupingOperationsController& other)
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
            GroupingOperationsController::~GroupingOperationsController()
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

            Models::Wrappers::GroupedTalk* GroupingOperationsController::groupByPhone(const Models::Talk* array, int count, int& groupCount) const
            {
                groupCount = 0;
                auto* tempGroups = new Models::Wrappers::GroupedTalk[count];

                for (int i = 0; i < count; i++)
                {
                    std::string phone = array[i].getMobile().getPhoneNumber();
                    bool found = false;

                    for (int j = 0; j < groupCount; j++)
                    {
                        if (tempGroups[j].phoneNumber == phone)
                        {
                            tempGroups[j].talkCount++;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        tempGroups[groupCount].phoneNumber = phone;
                        tempGroups[groupCount].talkCount = 1;
                        groupCount++;
                    }
                }

                auto* groups = new Models::Wrappers::GroupedTalk[groupCount];
                for (int i = 0; i < groupCount; i++)
                {
                    groups[i] = tempGroups[i];
                }

                delete[] tempGroups;
                return groups;
            }

            void GroupingOperationsController::sortByTalkCount(Models::Wrappers::GroupedTalk* groups, int groupCount) const
            {
                for (int i = 0; i < groupCount - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < groupCount; j++)
                    {
                        if (groups[j].talkCount > groups[minIndex].talkCount)
                        {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i)
                    {
                        Models::Wrappers::GroupedTalk temp = groups[i];
                        groups[i] = groups[minIndex];
                        groups[minIndex] = temp;
                    }
                }
            }
            void GroupingOperationsController::sortByPhoneNumber(Models::Wrappers::GroupedTalk* groups, int groupCount) const
            {
                for (int i = 0; i < groupCount - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < groupCount; j++)
                    {
                        if (groups[j].phoneNumber < groups[minIndex].phoneNumber)
                        {
                            minIndex = j;
                        }
                    }
                    if (minIndex != i)
                    {
                        Models::Wrappers::GroupedTalk temp = groups[i];
                        groups[i] = groups[minIndex];
                        groups[minIndex] = temp;
                    }
                }
            }

            void GroupingOperationsController::printGroupsTable(std::ostream& output, const Models::Wrappers::GroupedTalk* groups, int count) const
            {
                if (count == 0)
                {
                    output << "Список групп пуст." << std::endl;
                    return;
                }

                const std::array<std::string, 2> headers = {
                    "Номер",
                    "Количество звонков"
                };

                std::array<int, 2> columnWidths = {
                    static_cast<int>(headers[0].length()),
                    static_cast<int>(headers[1].length())
                };

                for (int i = 0; i < count; i++)
                {
                    columnWidths[0] = std::max(columnWidths[0], static_cast<int>(groups[i].phoneNumber.length()));
                    columnWidths[1] = std::max(columnWidths[1], static_cast<int>(std::to_string(groups[i].talkCount).length()));
                }

                int totalWidth = 1;
                for (int width : columnWidths)
                    totalWidth += width + 3;

                output << std::string(totalWidth, '=') << '\n';
                for (size_t i = 0; i < headers.size(); i++)
                    printCell(output, headers[i], columnWidths[i]);
                output << "|\n";

                output << std::string(totalWidth, '-') << '\n';

                for (int i = 0; i < count; i++)
                {
                    if (i != 0)
                        output << std::string(totalWidth, '-') << std::endl;

                    printCell(output, groups[i].phoneNumber, columnWidths[0]);
                    printCell(output, std::to_string(groups[i].talkCount), columnWidths[1]);
                    output << "|" << std::endl;
                }

                output << std::string(totalWidth, '=') << '\n';
            }
            bool GroupingOperationsController::saveToFile(const std::string& fileName, const Models::Wrappers::GroupedTalk* groups, int count) const
            {
                std::ofstream outputFile(fileName);
                if (!outputFile.is_open())
                {
                    std::cerr << "Ошибка при открытии файла для записи: " << fileName << std::endl;
                    return false;
                }

                printGroupsTable(outputFile, groups, count);
                outputFile.close();
            }

            GroupingOperationsController& GroupingOperationsController::operator =(const GroupingOperationsController& other)
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

                return *this;
            }
        }
    }
}
