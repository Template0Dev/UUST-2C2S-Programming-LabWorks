#include "request_distributor.h"
#include "basic_operations.h"
#include "grouping_operations.h"
#include "search_operations.h"
#include <iostream>

using namespace std;

RequestDistributor::RequestDistributor() : records(nullptr), record_count(0) {}

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
    switch (choice)
    {
        case 1:
            executeGroup(*this); break;
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
    ops.sortByFilename();
}

void executeGroup(RequestDistributor& dist) {
    GroupingOps gops(dist.records, dist.record_count);
    int choice;
    cout << "1. Группировать по расширению\n";
    cout << "2. Группировать и  сортировать по частоте расширений\n";
    cout << "Выбор: ";
    cin >> choice;

    switch (choice) {
        case 1: gops.groupByExtension(); break;
        case 2: gops.groupByExtension(); gops.sortByExtensionFrequency(); break;

        default: cout << "Неверный выбор.\n"; break;
    }

    char confirmation;
    cout << "Сохранить в файл (Y/N)? ";
    cin >> confirmation;
    if (confirmation == 'Y' || confirmation == 'y') {
        gops.saveGroupedToFile();
    }
}

void executeSearch(RequestDistributor& dist) {
    SearchOps sops(dist.records, dist.record_count);
    int choice;
    cout << "1. Поиск по названию\n";
    cout << "2. Поиск и сортировка по дате создания\n";
    cout << "3. Поиск и сортировка по времени создания\n";
    cout << "Выбор: ";
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
