#include "search_operations.h"
#include "request_distributor.h"
#include "basic_operations.h"
#include <iostream>
#include <string>

using namespace std;

SearchOps::SearchOps(RECORD*& recordsRef, int& countRef) : records(recordsRef), record_count(countRef) {}

void SearchOps::searchByFilename() {
    string target;
    cout << "Введите имя файла для поиска: ";
    cin >> target;

    RECORD* results = new RECORD[record_count];
    int found = 0;

    for (int i = 0; i < record_count; ++i) {
        if (records[i].file.filename.find(target) == 0) {
            results[found++] = records[i];
        }
    }

    if (found == 0) {
        cout << "Файлы с указанным именем не найдены." << endl;
        delete[] results;
        return;
    }
    else {
        cout << "Результаты поиска:\n";
        BasicOps(results, found).displayRecords();
    }

    char confirmation;
    cout << "Заменить текущие записи результатами поиска (Y/N)? ";
    cin >> confirmation;
    if (confirmation == 'Y' || confirmation == 'y') {
        delete[] records;

        records = results;
        record_count = found;

        cout << "Результаты поиска были установлены как текущие записи." << endl;
    }
    else {
        delete[] results;
    }
}

void SearchOps::sortByDate() {
    for (int i = 0; i < record_count - 1; ++i) {
        for (int j = i + 1; j < record_count; ++j) {
            if (records[i].creation_date > records[j].creation_date) {
                RECORD temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
    cout << "Сортировка по дате завершена." << endl;
}

void SearchOps::sortByTime() {
    for (int i = 0; i < record_count - 1; ++i) {
        for (int j = i + 1; j < record_count; ++j) {
            if (records[i].creation_time > records[j].creation_time) {
                RECORD temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
    cout << "Сортировка по времени завершена." << endl;
}

void SearchOps::saveSearchResultsToFile() {
    BasicOps(records, record_count).saveToFile();
}

// === Friend Access Points ===

void executeSearchByFilename(RequestDistributor& distributor) {
    SearchOps search(distributor.records, distributor.record_count);
    search.searchByFilename();
}

void executeSortByDate(RequestDistributor& distributor) {
    SearchOps search(distributor.records, distributor.record_count);
    search.sortByDate();
}

void executeSortByTime(RequestDistributor& distributor) {
    SearchOps search(distributor.records, distributor.record_count);
    search.sortByTime();
}

void executeSaveSearchResults(RequestDistributor& distributor) {
    SearchOps search(distributor.records, distributor.record_count);
    search.saveSearchResultsToFile();
}
