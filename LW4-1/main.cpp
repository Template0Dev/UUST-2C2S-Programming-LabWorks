#include <iostream>
#include "request_distributor.h"
#include "grouping_operations.h"

void specifySettings() {
    setlocale(LC_ALL, "RU");
}

RequestDistributor initDistributor() {
    RequestDistributor distributor;

    char confirmation;
    std::cout << "Загрузить тестовые данные (Y/N)? ";
    std::cin >> confirmation;
    if (confirmation == 'Y' || confirmation == 'y')
        distributor.loadMockData();

    return distributor;
}

void printMenu() {
    system("cls");

    std::cout << "Команды:\n";

    std::cout << "1. Базовые операции;\n";
    std::cout << "2. Операции группировки;\n";
    std::cout << "3. Операции поиска;\n";
    std::cout << "0. Выход.\n";

    std::cout << "\nВыбор: ";
}

void startMainWorkCycle(RequestDistributor& distributor)
{
    int choice;
    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
            case 2:
            case 3: distributor.getRequest(choice); break;

            case 0: break;
            default:
                std::cout << "Некорректный выбор.\n";
        }

        system("pause");
    } while (choice != 0);
}

int main() {
    specifySettings();

    RequestDistributor distributor = initDistributor();
    startMainWorkCycle(distributor);

    return 0;
}
