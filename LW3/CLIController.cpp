#include "CLIController.h"
#include "MainController.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <string>


namespace LW3
{
    namespace Controllers
    {
        CLIController::CLIController()
        {
            mainArray = new Models::Talk[INIT_SIZE];
            workArray = new Models::Talk[INIT_SIZE];
        }

        CLIController::CLIController(const CLIController& other) : mainCount(other.mainCount), workCount(other.workCount)
        {
            mainArray = new Models::Talk[mainCount];
            workArray = new Models::Talk[workCount];

            for (int i = 0; i < mainCount; ++i)
            {
                mainArray[i] = other.mainArray[i];
            }

            for (int i = 0; i < workCount; ++i)
            {
                workArray[i] = other.workArray[i];
            }
        }

        CLIController::~CLIController()
        {
            delete[] mainArray;
            delete[] workArray;
        }

        void CLIController::beginWork()
        {
            proceedWorkCycle();
        }

        void CLIController::proceedWorkCycle()
        {
            int choice;

            do
            {
                printCommandsMenu();
                while (!(std::cin >> choice))
                {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');

                    std::cout << "Некорректный ввод. Повтор: ";
                }
                std::cin.ignore();

                // Меню команд.
                switch (choice)
                {
                    case 1:
                    {
                        MainController().loadFromKeyboard(mainArray, workArray, mainCount, workCount);
                        break;
                    }
                    case 2:
                    {
                        std::string fileName;
                        std::cout << "Введите имя файла для загрузки: ";
                        std::getline(std::cin, fileName);

                        if (MainController().loadFromFile(fileName, mainArray, workArray, mainCount, workCount))
                            std::cout << "Данные успешно загружены из файла. Общее количество импортированных записей: " << mainCount << "." << std::endl;
                        else
                            std::cout << "Не удалось загрузить данные." << std::endl;

                        break;
                    }
                    case 3:
                    {
                        std::string fileName;
                        std::cout << "Введите имя файла для сохранения: ";
                        std::getline(std::cin, fileName);

                        if (MainController().saveToFile(fileName, workArray, workCount))
                            std::cout << "Удалось сохранить данные в файл." << std::endl;
                        else
                            std::cout << "Ошибка при сохранении файла." << std::endl;

                        break;
                    }
                    case 4:
                    {
                        bool result = addNewEntrySubFunction();
                        if (result)
                            std::cout << "Запись успешно добавлена." << std::endl;
                        else
                            std::cout << "Добавить запись не удалось." << std::endl;

                        break;
                    }
                    case 5:
                    {
                        bool result = removeEntrySubFunction();
                        if (result)
                            std::cout << "Запись удалена." << std::endl;
                        else
                            std::cout << "Ошибка при удалении записи." << std::endl;

                        break;
                    }
                    case 6:
                    {
                        MainController().displayData(workArray, workCount);
                        break;
                    }
                    case 7:
                    {
                        MainController().sortByName(workArray, workCount);
                        std::cout << "Сортировка по ФИО выполнена." << std::endl;

                        break;
                    }
                    case 8:
                    {
                        MainController().sortByDate(workArray, workCount);
                        std::cout << "Сортировка по дате разговора выполнена." << std::endl;

                        break;
                    }
                    case 9:
                    {
                        MainController().sortByDuration(workArray, workCount);
                        std::cout << "Сортировка по длительности разговора выполнена." << std::endl;

                        break;
                    }
                    case 10:
                    {
                        MainController().resetWorkingArray(mainArray, workArray, mainCount, workCount);
                        std::cout << "Рабочая копия сброшена к исходной." << std::endl;

                        break;
                    }
                    case 100:
                    {
                        auto copiedController = CLIController(*this);

                        std::cout << "Текущий объект:" << std::endl;
                        MainController().displayData(workArray, workCount);

                        std::cout << std::endl << "Скопированный объект:" << std::endl;
                        MainController().displayData(copiedController.workArray, copiedController.workCount);

                        break;
                    }
                    case 200:
                    {
                        auto newController = CLIController();
                        newController = *this;

                        std::cout << "Текущий объект:" << std::endl;
                        MainController().displayData(workArray, workCount);

                        std::cout << std::endl << "Присвоенный объект:" << std::endl;
                        MainController().displayData(newController.workArray, newController.workCount);

                        break;
                    }
                    case 0:
                    {
                        std::cout << "Выход из программы." << std::endl;
                        break;
                    }
                    default:
                    {
                        std::cout << "Неверный выбор. Повторите." << std::endl;
                        break;
                    }
                }

                if (choice != 0)
                {
                    std::cout << "Процедура завершена..." << std::endl;
                    system("PAUSE");
                }
                system("CLS");
            } while (choice != 0);
        }

        void CLIController::printCommandsMenu() const
        {
            std::cout << "Меню:" << std::endl;
            std::cout << "1. Загрузка данных с клавиатуры" << std::endl;
            std::cout << "2. Загрузка данных из файла" << std::endl;
            std::cout << "3. Сохранение обработки в файл" << std::endl;
            std::cout << "4. Добавление записи" << std::endl;
            std::cout << "5. Удаление записи" << std::endl;
            std::cout << "6. Вывод данных на экран" << std::endl;
            std::cout << "7. Алфавитная сортировка по ФИО (комплексная сортировка с перегрузкой)" << std::endl;
            std::cout << "8. Сортировка по дате разговора" << std::endl;
            std::cout << "9. Сортировка по длительности разговора" << std::endl;
            std::cout << "10. Сброс рабочей копии к исходной" << std::endl;
            std::cout << "100. Проверка конструктора копирования" << std::endl;
            std::cout << "200. Проверка перегрузки присваивания" << std::endl;
            std::cout << "0. Выход" << std::endl;

            std::cout << std::endl << "Выберите действие: ";
        }

        bool CLIController::addNewEntrySubFunction()
        {
            Models::Talk newEntry = userGuidedTalkCreation();
            return MainController().addRecord(newEntry, workArray, workCount);
        }

        bool CLIController::removeEntrySubFunction()
        {
            int index;
            std::cout << "Введите индекс записи для удаления (начиная с 0): ";
            while (!(std::cin >> index))
            {
                std::cout << "Некорректный ввод. Повторите: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            std::cin.ignore();

            return MainController().deleteRecord(index, workArray, workCount);
        }

        CLIController& CLIController::operator =(const CLIController& other)
        {
            // Предотвращение самокопирования.
            if (this == &other)
                return *this;

            delete[] mainArray;
            delete[] workArray;

            mainCount = other.mainCount;
            workCount = other.workCount;

            mainArray = new Models::Talk[mainCount];
            workArray = new Models::Talk[workCount];

            for (int i = 0; i < mainCount; ++i)
            {
                mainArray[i] = other.mainArray[i]; // Assuming Models::Talk has a proper copy assignment
            }

            for (int i = 0; i < workCount; ++i)
            {
                workArray[i] = other.workArray[i];
            }

            return *this;
        }
    }
}
