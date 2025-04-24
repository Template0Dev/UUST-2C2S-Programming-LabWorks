#include "CLIController.h"
#include "DialogController.h"
#include "CopyConstructorsTester.h"
#include "AssignmentOperatorsTester.h"
#include "Talk.h"
#include "Utils.h"
#include <iostream>
#include <string>


namespace LW6
{
	namespace Controllers
	{
		namespace Views
		{

#pragma region Region: Constructors.

			CLIController::CLIController()
			{
				processingRepo = Repos::GeneralDataRepo();

				mainArray = new Models::Talk[INIT_SIZE];
				workArray = new Models::Talk[INIT_SIZE];
			}

			CLIController::CLIController(const CLIController& other) : processingRepo(other.processingRepo), mainCount(other.mainCount), workCount(other.workCount)
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
#pragma endregion

#pragma region Region: Main Functions.

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
							executeBasicOperation(*this, choice, "");
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
							executeBasicOperation(*this, choice, "");
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
						{
							executeGeneralOperation(*this, choice);
							break;
						}
						case 110:
						{
							executeBasicOperation(*this, choice, "");
							break;
						}
						case 120:
						{
							executeGroupingOperation(*this, choice);
							break;
						}
						case 130:
						{
							executeSearchingOperation(*this, choice, getPhoneNumber());
							break;
						}

						case 200:
						{
							executeGeneralOperation(*this, choice);
							break;
						}
						case 210:
						{
							executeBasicOperation(*this, choice, "");
							break;
						}
						case 220:
						{
							executeGroupingOperation(*this, choice);
							break;
						}
						case 230:
						{
							executeSearchingOperation(*this, choice, getPhoneNumber());
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

				std::cout << std::endl;
				std::cout << "1. Загрузка данных с клавиатуры" << std::endl;
				std::cout << "2. Загрузка данных из файла" << std::endl;
				std::cout << "3. Сохранение обработки в файл" << std::endl;

				std::cout << std::endl;
				std::cout << "4. Добавление записи" << std::endl;
				std::cout << "5. Удаление записи" << std::endl;
				std::cout << "6. Вывод данных на экран" << std::endl;

				std::cout << std::endl;
				std::cout << "7. Алфавитная сортировка по ФИО (комплексная сортировка с перегрузкой)" << std::endl;
				std::cout << "8. Сортировка по дате разговора" << std::endl;
				std::cout << "9. Сортировка по длительности разговора" << std::endl;

				std::cout << std::endl;
				std::cout << "10. Сброс рабочей копии к исходной" << std::endl;

				std::cout << std::endl;
				std::cout << "20. Группировка по номеру телефона" << std::endl;
				std::cout << "21. Группировка по номеру телефона (сортировка по количеству звонков)" << std::endl;
				std::cout << "22. Группировка по номеру телефона (сортировка по номеру)" << std::endl;

				std::cout << std::endl;
				std::cout << "30. Поиск по номеру телефона" << std::endl;
				std::cout << "31. Поиск по номеру телефона (с сортировкой по дате начала разговора)" << std::endl;
				std::cout << "32. Поиск по номеру телефона (с сортировкой по времени начала разговора)" << std::endl;

				std::cout << std::endl;
				std::cout << "100. Проверка конструктора копирования общего репозитория данных" << std::endl;
				std::cout << "110. Проверка конструктора копирования базового контроллера" << std::endl;
				std::cout << "120. Проверка конструктора копирования контроллера группировки" << std::endl;
				std::cout << "130. Проверка конструктора копирования контроллера поиска" << std::endl;

				std::cout << std::endl;
				std::cout << "200. Проверка перегрузки присваивания общего репозитория данных" << std::endl;
				std::cout << "210. Проверка перегрузки присваивания базового контроллера" << std::endl;
				std::cout << "220. Проверка перегрузки присваивания контроллера группировки" << std::endl;
				std::cout << "230. Проверка перегрузки присваивания контроллера поиска" << std::endl;

				std::cout << std::endl;
				std::cout << "0. Выход" << std::endl;

				std::cout << std::endl;
				std::cout << "Выберите действие: ";
			}

			void executeBasicOperation(CLIController& controller, int operation, const std::string& fileName)
			{
				switch (operation)
				{
					case 1:
					{
						controller.processingRepo.loadFromKeyboard(controller.mainArray, controller.workArray, controller.mainCount, controller.workCount);
						break;
					}
					case 2:
					{
						auto result = controller.processingRepo.loadFromFile(fileName, controller.mainArray, controller.workArray, controller.mainCount, controller.workCount);
						if (result)
							std::cout << "Данные успешно загружены из файла. Общее количество импортированных записей: " << controller.mainCount << "." << std::endl;
						else
							std::cout << "Не удалось загрузить данные." << std::endl;

						break;
					}
					case 3:
					{
						auto result = controller.processingRepo.saveToFile(fileName, controller.workArray, controller.workCount);
						if (result)
							std::cout << "Удалось сохранить данные в файл." << std::endl;
						else
							std::cout << "Ошибка при сохранении файла." << std::endl;

						break;
					}

					case 6:
					{
						controller.processingRepo.displayData(controller.workArray, controller.workCount);
						break;
					}
					case 7:
					{
						controller.processingRepo.sortByName(controller.workArray, controller.workCount);
						std::cout << "Сортировка по ФИО выполнена." << std::endl;

						break;
					}
					case 8:
					{
						controller.processingRepo.sortByDate(controller.workArray, controller.workCount);
						std::cout << "Сортировка по дате разговора выполнена." << std::endl;

						break;
					}
					case 9:
					{
						controller.processingRepo.sortByDuration(controller.workArray, controller.workCount);
						std::cout << "Сортировка по длительности разговора выполнена." << std::endl;

						break;
					}
					case 10:
					{
						controller.processingRepo.resetWorkingArray(controller.mainArray, controller.workArray, controller.mainCount, controller.workCount);
						std::cout << "Рабочая копия сброшена к исходной." << std::endl;

						break;
					}
					case 110:
					{
						Testers::CopyConstructorsTester().testBasicOperationsControllerCopyConstructor(controller.processingRepo.basicOperationsController, controller.workArray, controller.workCount);
						break;
					}
					case 210:
					{
						Testers::AssignmentOperatorsTester().testBasicOperationsControllerAssignmentOperator(controller.processingRepo.basicOperationsController, controller.workArray, controller.workCount);
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
				int groupCount = 0;
				auto* groups = controller.processingRepo.groupByPhone(controller.workArray, controller.workCount, groupCount);

				switch (operation)
				{
					case 20:
					{
						std::cout << "Базовый результат группировки:" << std::endl;
						break;
					}
					case 21:
					{
						controller.processingRepo.sortGroupsByCount(groups, groupCount);
						std::cout << "Группировка по номеру телефона (сортировка по количеству звонков):" << std::endl;

						break;
					}
					case 22:
					{
						controller.processingRepo.sortGroupsByPhone(groups, groupCount);
						std::cout << "Группировка по номеру телефона (сортировка по номеру):" << std::endl;

						break;
					}

					case 120:
					{
						Testers::CopyConstructorsTester().testGroupingOperationsControllerCopyConstructor(controller.processingRepo.groupingOperationsController, controller.workArray, controller.workCount);
						break;
					}
					case 220:
					{
						Testers::AssignmentOperatorsTester().testGroupingOperationsControllerAssignmentOperator(controller.processingRepo.groupingOperationsController, controller.workArray, controller.workCount);
						break;
					}

					default:
					{
						std::cout << "Неверный выбор операции группировки." << std::endl;
						break;
					}
				}
				// Ignore output part if specified operation is testing, because result was already printed.
				if (operation != 110 && operation != 210)
					controller.processingRepo.printGroups(std::cout, groups, groupCount);

				if (DialogController::askConfirmation(std::string("Сохранить результат группировки в файл")))
				{
					auto fileName = DialogController::getFileName();
					controller.processingRepo.saveGroupsToFile(&fileName, groups, groupCount);
				}

				delete[] groups;
			}

			void executeSearchingOperation(CLIController& controller, int operation, const std::string& phoneNumber)
			{
				int matchCount = 0;
				Models::Talk* matches = controller.processingRepo.searchByPhone(controller.workArray, controller.workCount, phoneNumber, matchCount);
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
						controller.processingRepo.sortMatchesByDate(matches, matchCount);
						std::cout << "Поиск по номеру телефона с сортировкой по дате начала разговора:" << std::endl;

						break;
					}
					case 32:
					{
						controller.processingRepo.sortMatchesByTime(matches, matchCount);
						std::cout << "Поиск по номеру телефона с сортировкой по времени начала разговора:" << std::endl;

						break;
					}

					case 130:
					{
						Testers::CopyConstructorsTester().testSearchingOperationsControllerCopyConstructor(controller.processingRepo.searchingOperationsController, controller.workArray, controller.workCount, &phoneNumber);
						break;
					}
					case 230:
					{
						Testers::AssignmentOperatorsTester().testSearchingOperationsControllerAssignmentOperator(controller.processingRepo.searchingOperationsController, controller.workArray, controller.workCount, &phoneNumber);
						break;
					}

					default:
					{
						std::cout << "Неверный выбор операции поиска." << std::endl;
						break;
					}
				}
				// Ignore output part if specified operation is testing, because result was already printed.
				if (operation != 120 && operation != 220)
					controller.processingRepo.displayMatches(matches, matchCount);

				if (DialogController::askConfirmation(std::string("Сохранить результат поиска в файл")))
				{
					auto fileName = DialogController::getFileName();
					controller.processingRepo.saveMatchesToFile(&fileName, matches, matchCount);
				}

				if (DialogController::askConfirmation(std::string("Перезаписать рабочий массив результатами поиска")))
				{
					delete[] controller.workArray;

					controller.workArray = matches;
					controller.workCount = matchCount;
				}
				else
				{
					delete[] matches;
				}
			}

			void executeGeneralOperation(const CLIController& controller, int operation)
			{
				auto phoneNumber = DialogController::getString(std::string("Введите номер телефона для поиска"));
				switch (operation)
				{
					case 100:
					{
						Testers::CopyConstructorsTester().testGeneralDataRepositoryCopyConstructor(controller.processingRepo, controller.workArray, controller.workCount, phoneNumber);
						break;
					}
					case 200:
					{
						Testers::AssignmentOperatorsTester().testGeneralDataRepositoryAssignmentOperator(controller.processingRepo, controller.workArray, controller.workCount, phoneNumber);
						break;
					}

					default:
					{
						std::cout << "Выбрана неправильная операция." << std::endl;
						break;
					}
				}
			}
#pragma endregion

#pragma region Region: Additional Functions.

			bool CLIController::addNewEntrySubFunction()
			{
				Models::Talk newEntry = userGuidedTalkCreation();
				return processingRepo.addRecord(workArray, workCount, newEntry);
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

				return processingRepo.deleteRecord(workArray, workCount, index);
			}
#pragma endregion

#pragma region Region: Operators.

			CLIController& CLIController::operator =(const CLIController& other)
			{
				if (this == &other)
					return *this;

				delete[] mainArray;
				delete[] workArray;

				processingRepo = other.processingRepo;

				mainCount = other.mainCount;
				workCount = other.workCount;

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

				return *this;
			}
#pragma endregion
		}
	}
}
