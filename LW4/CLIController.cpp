#include "CLIController.h"
#include "BasicOperationsController.h"
#include "GroupingController.h"
#include "SearchingController.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <string>


namespace LW4
{
	namespace Controllers
	{
		namespace Views
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
				std::string fileName;
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

					switch (choice)
					{
						case 1:
						{
							executeBasicOperation(*this, choice);
							break;
						}

						case 2:
						{
							std::cout << "Введите имя файла для загрузки: ";
							std::getline(std::cin, fileName);

							executeBasicOperation(*this, choice, fileName);
							break;
						}
						case 3:
						{
							std::cout << "Введите имя файла для сохранения: ";
							std::getline(std::cin, fileName);

							executeBasicOperation(*this, choice, fileName);
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
						case 7: 
						case 8: 
						case 9: 
						case 10:
						{
							executeBasicOperation(*this, choice);
							break;
						}

						case 20:
						case 21:
						case 22:
						{
							std::string phoneNumber;

							executeGroupingOperation(*this, choice);
							break;
						}

						case 30:
						case 31:
						case 32:
						{
							std::string phoneNumber;

							std::cout << "Введите номер телефона для поиска: ";
							std::getline(std::cin, phoneNumber);

							executeSearchingOperation(*this, choice, phoneNumber);
							break;
						}

						case 100: 
						case 200:
						{
							executeBasicOperation(*this, choice);
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

			void executeBasicOperation(CLIController& controller, int operation, const std::string& fileName)
			{
				Data::BasicOperationsController dataController;
				switch (operation)
				{
					case 1:
					{
						dataController.loadFromKeyboard(controller.mainArray, controller.workArray, controller.mainCount, controller.workCount);
						break;
					}
					case 2:
					{
						if (dataController.loadFromFile(fileName, controller.mainArray, controller.workArray, controller.mainCount, controller.workCount))
							std::cout << "Данные успешно загружены из файла. Общее количество импортированных записей: " << controller.mainCount << "." << std::endl;
						else
							std::cout << "Не удалось загрузить данные." << std::endl;

						break;
					}
					case 3:
					{
						if (dataController.saveToFile(fileName, controller.workArray, controller.workCount))
							std::cout << "Удалось сохранить данные в файл." << std::endl;
						else
							std::cout << "Ошибка при сохранении файла." << std::endl;

						break;
					}

					case 6:
					{
						dataController.displayData(controller.workArray, controller.workCount);
						break;
					}
					case 7:
					{
						dataController.sortByName(controller.workArray, controller.workCount);
						std::cout << "Сортировка по ФИО выполнена." << std::endl;

						break;
					}
					case 8:
					{
						dataController.sortByDate(controller.workArray, controller.workCount);
						std::cout << "Сортировка по дате разговора выполнена." << std::endl;

						break;
					}
					case 9:
					{
						dataController.sortByDuration(controller.workArray, controller.workCount);
						std::cout << "Сортировка по длительности разговора выполнена." << std::endl;

						break;
					}
					case 10:
					{
						dataController.resetWorkingArray(controller.mainArray, controller.workArray, controller.mainCount, controller.workCount);
						std::cout << "Рабочая копия сброшена к исходной." << std::endl;

						break;
					}
					case 100:
					{
						auto copiedController = CLIController(controller);

						std::cout << "Текущий объект:" << std::endl;
						dataController.displayData(controller.workArray, controller.workCount);

						std::cout << std::endl << "Скопированный объект:" << std::endl;
						dataController.displayData(copiedController.workArray, copiedController.workCount);

						break;
					}
					case 200:
					{
						auto newController = CLIController();
						newController = controller;

						std::cout << "Текущий объект:" << std::endl;
						dataController.displayData(controller.workArray, controller.workCount);

						std::cout << std::endl << "Присвоенный объект:" << std::endl;
						dataController.displayData(newController.workArray, newController.workCount);

						break;
					}

					default:
					{
						std::cout << "Неверный выбор операции." << std::endl;
						break;
					}
				}
			}

			void executeGroupingOperation(const CLIController& controller, int operation)
			{
				Data::GroupingController groupingController;
				int groupCount = 0;
				auto* groups = groupingController.groupByPhone(controller.workArray, controller.workCount, groupCount);

				switch (operation)
				{
					case 20:
					{
						std::cout << "Базовый результат группировки:" << std::endl;
						break;
					}
					case 21:
					{
						groupingController.sortByTalkCount(groups, groupCount);
						std::cout << "Группировка по номеру телефона (сортировка по количеству звонков):" << std::endl;

						break;
					}
					case 22:
					{
						groupingController.sortByPhoneNumber(groups, groupCount);
						std::cout << "Группировка по номеру телефона (сортировка по номеру):" << std::endl;

						break;
					}
					default:
					{
						std::cout << "Неверный выбор операции группировки." << std::endl;
						break;
					}
				}

				groupingController.printGroupsTable(std::cout, groups, groupCount);

				char confirmation;
				std::cout << "Сохранить результат группировки в файл (Y/N)? ";
				std::cin >> confirmation;
				if (confirmation == 'y' || confirmation == 'Y')
				{
					std::string fileName;
					std::cout << "Введите название файла для сохранения: ";
					std::cin >> fileName;

					auto result = groupingController.saveToFile(fileName, groups, groupCount);
					if (result)
						std::cout << "Файл успешно сохранён." << std::endl;
				}

				delete[] groups;
			}

			void executeSearchingOperation(const CLIController& controller, int operation, const std::string& phoneNumber)
			{
				Data::SearchingController searchingController;
				int matchCount = 0;

				Models::Talk* matches = searchingController.searchByPhoneNumber(controller.workArray, controller.workCount, phoneNumber, matchCount);
				if (matchCount == 0)
				{
					std::cout << "Записей с номером " << phoneNumber << " не найдено." << std::endl;
					return;
				}
				switch (operation)
				{
					case 30:
					{
						std::cout << "Базовый поиск:" << std::endl;
						break;
					}
					case 31:
					{
						searchingController.sortByCallDate(matches, matchCount);
						std::cout << "Поиск по номеру телефона с сортировкой по дате начала разговора:" << std::endl;

						break;
					}
					case 32:
					{
						searchingController.sortByCallTime(matches, matchCount);
						std::cout << "Поиск по номеру телефона с сортировкой по времени начала разговора:" << std::endl;

						break;
					}
					default:
					{
						std::cout << "Неверный выбор операции поиска." << std::endl;
						break;
					}
				}

				Data::BasicOperationsController basicController;
				basicController.displayData(matches, matchCount);

				char confirmation;
				std::cout << "Сохранить результат группировки в файл (Y/N)? ";
				std::cin >> confirmation;
				if (confirmation == 'y' || confirmation == 'Y')
				{
					std::string fileName;
					std::cout << "Введите название файла для сохранения: ";
					std::cin >> fileName;

					auto result = Data::BasicOperationsController().saveToFile(fileName, matches, matchCount);
					if (result)
						std::cout << "Файл успешно сохранён." << std::endl;
				}

				delete[] matches;
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

				std::cout << "20. Группировка по номеру телефона" << std::endl;
				std::cout << "21. Группировка по номеру телефона (сортировка по количеству звонков)" << std::endl;
				std::cout << "22. Группировка по номеру телефона (сортировка по номеру)" << std::endl;

				std::cout << "30. Поиск по номеру телефона" << std::endl;
				std::cout << "31. Поиск по номеру телефона (с сортировкой по дате начала разговора)" << std::endl;
				std::cout << "32. Поиск по номеру телефона (с сортировкой по времени начала разговора)" << std::endl;

				std::cout << "100. Проверка конструктора копирования" << std::endl;
				std::cout << "200. Проверка перегрузки присваивания" << std::endl;

				std::cout << "0. Выход" << std::endl;

				std::cout << std::endl << "Выберите действие: ";
			}

			bool CLIController::addNewEntrySubFunction()
			{
				Models::Talk newEntry = userGuidedTalkCreation();
				return Data::BasicOperationsController().addRecord(newEntry, workArray, workCount);
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

				return Data::BasicOperationsController().deleteRecord(index, workArray, workCount);
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
}
