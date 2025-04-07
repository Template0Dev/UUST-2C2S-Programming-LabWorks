#include "MainController.h"
#include "Utils.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>


namespace LW2
{
    namespace Controllers
    {
        void MainController::printCell(std::ostream& output, const std::string& text, int width) const
        {
            output << "| " << text;
            auto len = static_cast<int>(text.size());
            for (int s = len; s < width; s++)
            {
                output << " ";
            }
            output << " ";
        }
        void MainController::printTable(std::ostream& output, const Models::Talk* array, int count) const
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

            auto maxIDColumnWidth = static_cast<int>(idHeader.length());
            auto maxNameColumnWidth = static_cast<int>(nameHeader.length());
            auto maxSurnameColumnWidth = static_cast<int>(surnameHeader.length());
            auto maxPatronymicColumnWidth = static_cast<int>(patronymicHeader.length());
            auto maxPhoneNumberColumnWidth = static_cast<int>(phoneNumberHeader.length());
            auto maxCallStartColumnWidth = static_cast<int>(callStartHeader.length());
            auto maxCallEndingColumnWidth = static_cast<int>(callEndingHeader.length());
            auto maxCallTarificationColumnWidth = static_cast<int>(callTarificationHeader.length());

            for (int i = 0; i < count; i++)
            {
                maxIDColumnWidth = std::max(maxIDColumnWidth, static_cast<int>(std::to_string(count).length()));
                maxNameColumnWidth = std::max(maxNameColumnWidth, static_cast<int>(array[i].getMobile().getName().length()));
                maxSurnameColumnWidth = std::max(maxSurnameColumnWidth, static_cast<int>(array[i].getMobile().getSurname().length()));
                maxPatronymicColumnWidth = std::max(maxPatronymicColumnWidth, static_cast<int>(array[i].getMobile().getPatronymic().length()));
                maxPhoneNumberColumnWidth = std::max(maxPhoneNumberColumnWidth, static_cast<int>(array[i].getMobile().getPhoneNumber().length()));
                maxCallStartColumnWidth = std::max(maxCallStartColumnWidth, static_cast<int>(array[i].getCallStart().toString().length()));
                maxCallEndingColumnWidth = std::max(maxCallEndingColumnWidth, static_cast<int>(array[i].getCallEnding().toString().length()));
                maxCallTarificationColumnWidth = std::max(maxCallTarificationColumnWidth, static_cast<int>(std::to_string(array[i].getTalkTarification()).length()));
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

            for (int i = 0; i < totalWidth; i++)
                output << '=';
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

            for (int i = 0; i < totalWidth; i++)
                output << '-';
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

        void MainController::clearArray(Models::Talk*& array, int& arrayCount)
        {
            if (array)
            {
                delete[] array;
                array = nullptr;
            }

            arrayCount = 0;
        }
        Models::Talk* MainController::resizeArray(Models::Talk* array, int oldCount, int newCount) const
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
        void MainController::appendRecord(Models::Talk*& array, int& count, const Models::Talk& record) const
        {
            array = resizeArray(array, count, count + 1);
            array[count] = record;
            count++;
        }

        void MainController::loadFromKeyboard(Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount)
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
        bool MainController::loadFromFile(const std::string& filename, Models::Talk*& mainArray, Models::Talk*& workArray, int& mainCount, int& workCount)
        {
            std::ifstream inFile(filename);
            if (!inFile.is_open())
            {
                std::cerr << "Ошибка открытия файла: " << filename << std::endl;
                return false;
            }

            // Пропускаем строки с рамкой и заголовком.
            std::string line;
            if (!std::getline(inFile, line)) { inFile.close(); return false; }
            if (!std::getline(inFile, line)) { inFile.close(); return false; }
            if (!std::getline(inFile, line)) { inFile.close(); return false; }

            // Очищаем массивы.
            clearArray(mainArray, mainCount);
            clearArray(workArray, workCount);

            // Считываем строки файла.
            while (std::getline(inFile, line))
            {
                // Пропускаем рамки и пустые строки.
                if (line.empty() || line.at(0) == '+') continue;

                // Ожидается 8 столбцов: ID, Имя, Фамилия, Отчество, Телефон, Начало разговора, Конец разговора, Тарификация.
                std::string cells[8];
                int cellIndex = 0;
                size_t pos = 0;
                if (!line.empty() && line.at(0) == '|')
                    pos = 1;

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

                // Распределение столбцов:
                // cells[0] – ID (игнорируется);
                // cells[1] – Имя;
                // cells[2] – Фамилия;
                // cells[3] – Отчество;
                // cells[4] – Телефон;
                // cells[5] – Начало разговора;
                // cells[6] – Конец разговора;
                // cells[7] – Тарификация.
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

                // Добавляем запись в оба массива.
                appendRecord(mainArray, mainCount, talk);
                appendRecord(workArray, workCount, talk);
            }

            inFile.close();
            return true;
        }
        bool MainController::saveToFile(const std::string& fileName, const Models::Talk* workArray, int workCount) const
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

        bool MainController::addRecord(const Models::Talk& record, Models::Talk*& workArray, int& workCount) const
        {
            appendRecord(workArray, workCount, record);
            return true;
        }
        bool MainController::deleteRecord(int index, Models::Talk*& workArray, int& workCount) const
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

        void MainController::displayData(const Models::Talk* workArray, int workCount) const
        {
            printTable(std::cout, workArray, workCount);
        }

        void MainController::sortByName(Models::Talk* workArray, int workCount) const
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
                if (minIndex != i)
                    std::swap(workArray[i], workArray[minIndex]);
            }
        }
        void MainController::sortByDate(Models::Talk* workArray, int workCount) const
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
        void MainController::sortByDuration(Models::Talk* workArray, int workCount) const
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

        void MainController::resetWorkingArray(const Models::Talk* mainArray, Models::Talk*& workArray, int mainCount, int& workCount)
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
