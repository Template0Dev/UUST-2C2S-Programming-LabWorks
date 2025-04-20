#include "request_distributor.h"
#include "basic_operations.h"
#include "grouping_operations.h"
#include "search_operations.h"
#include <iostream>

using namespace std;

RequestDistributor::RequestDistributor() : record_count(0), records(new RECORD[record_count+1]) {}

RequestDistributor::~RequestDistributor() {
    delete[] records;
}

void RequestDistributor::loadMockData() {
    record_count = 5;
    records = new RECORD[record_count] {
        {{"C:/Docs", "report", "txt"}, "2023-04-01", "12:00", "r"},
        {{"C:/Pics", "vacation", "jpg"}, "2022-12-01", "10:15", "rw"},
        {{"D:/Music", "song", "mp3"}, "2021-08-23", "14:30", "r"},
        {{"C:/Docs", "summary", "txt"}, "2023-01-01", "09:00", "rw"},
        {{"D:/Music", "album", "mp3"}, "2021-08-24", "08:00", "r"}
    };
}

void RequestDistributor::getRequest(int choice) {
    switch (choice) {
        case 1:
            executeOperation(*this); break;
        case 2:
            executeGroup(*this); break;
        case 3:
            executeSearch(*this); break;

        default:
            break;
    }
}

void executeOperation(RequestDistributor& dist) {
    BasicOps bops(dist.records, dist.record_count);

    int choice;
    dist.printBasicMenu();
    cin >> choice;

    switch (choice) {
        case 1: bops.loadFromFile(); break;
        case 2: bops.saveToFile(); break;
        case 3: bops.addRecord(); break;
        case 4: bops.deleteRecord(); break;
        case 5: bops.displayRecords(); break;
        case 6: bops.sortByAttribute(); break;
        case 7: bops.sortAlphabetically(); break;
        case 8: {
            cout << "Текущий объект:\n";
            bops.displayRecords();

            cout << "\nКопия объекта:\n";
            BasicOps(bops).displayRecords();

            break;
        }
        case 9: {
            // BasicOps не имеет стандартного конструктора, поэтому инициализацию необходимо проводить при объявлении.
            BasicOps bopsB = bops;
            BasicOps bopsA = bops;
            // А это специально для Хасанова, потому что он требует подобную строчку кода.
            bopsB = bopsA = bops;

            cout << "Копия B:\n";
            bopsB.displayRecords();

            cout << "\nКопия A:\n";
            bopsA.displayRecords();

            cout << "\nОснова:\n";
            bops.displayRecords();

            break;
        }

        default: std::cout << "Неизвестная операция.\n"; break;
    }
}

void RequestDistributor::printBasicMenu() const {
    cout << "1. Загрузить из файла\n";
    cout << "2. Сохранить в файл\n";
    cout << "3. Добавить запись\n";
    cout << "4. Удалить запись\n";
    cout << "5. Вывести записи\n";
    cout << "6. Отсортировать по атрибутам\n";
    cout << "7. Отсортировать по алфавиту\n";
    cout << "8. Проверка конструктора копирования\n";
    cout << "9. Проверка оператора присваивания\n";

    cout << "\nВыбор: ";
}

void executeGroup(RequestDistributor& dist) {
    GroupingOps gops(dist.records, dist.record_count);

    int choice;
    dist.printGroupMenu();
    cin >> choice;

    switch (choice) {
        case 1: gops.groupByExtension(); break;
        case 2: gops.groupByExtension(); gops.sortByExtensionFrequency(); break;
        case 3: {
            gops.groupByExtension();

            cout << "Текущий объект:\n";
            gops.printGroupMenu();

            break;
        }
        case 4: {
            break;
        }

        default: cout << "Неверный выбор.\n"; break;
    }

    char confirmation;
    cout << "Сохранить в файл (Y/N)? ";
    cin >> confirmation;
    if (confirmation == 'Y' || confirmation == 'y') {
        gops.saveGroupedToFile();
    }
}

void RequestDistributor::printGroupMenu() const {
    cout << "1. Простая группировка по расширению\n";
    cout << "2. Группировать и сортировать по частоте расширений\n";
    cout << "3. Проверка конструктора копирования (простая группировка)\n";
    cout << "4. Проверка оператора присваивания (простая группировка)\n";

    cout << "\nВыбор: ";
}

void executeSearch(RequestDistributor& dist) {
    SearchOps sops(dist.records, dist.record_count);

    int choice;
    dist.printSearchMenu();
    cin >> choice;

    switch (choice) {
        case 1: sops.searchByFilename(); break;
        case 2: sops.searchByFilename(); sops.sortByDate(); break;
        case 3: sops.searchByFilename(); sops.sortByTime(); break;

        default: cout << "Неверный выбор.\n"; break;
    }

    char confirmation;
    cout << "Сохранить в файл (Y/N)? ";
    cin >> confirmation;
    if (confirmation == 'Y' || confirmation == 'y') {
        sops.saveSearchResultsToFile();
    }
}

void RequestDistributor::printSearchMenu() const {
    cout << "1. Поиск по названию\n";
    cout << "2. Поиск и сортировка по дате создания\n";
    cout << "3. Поиск и сортировка по времени создания\n";
    cout << "4. Проверка конструктора копирования\n";
    cout << "5. Проверка оператора присваивания\n";

    cout << "\nВыбор: ";
}
