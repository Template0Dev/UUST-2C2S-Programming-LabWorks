#include "search_operations.h"
#include "request_distributor.h"
#include "basic_operations.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

SearchOps::SearchOps(RECORD*& recordsRef, int& countRef) : record_count(countRef), records(recordsRef), search_count(0), search_results(nullptr) {}
SearchOps::SearchOps(const SearchOps& other) : record_count(other.record_count), records(other.records),  search_count(other.search_count), search_results(other.search_results) {
    search_results = new RECORD[search_count];
    for (int i = 0; i < search_count; ++i) {
        search_results[i] = other.search_results[i];
    }
}
SearchOps::~SearchOps() {
    delete[] search_results;
}

void SearchOps::searchByFilename() {
    string target;
    cout << "Введите имя файла для поиска: ";
    cin >> target;

    search_results = new RECORD[record_count];
    search_count = 0;

    for (int i = 0; i < record_count; ++i) {
        if (records[i].file.filename.find(target) == 0) {
            auto cr = records[i];
            auto newRecord = new RECORD;
            newRecord->attributes = cr.attributes;
            newRecord->creation_date = cr.creation_date;
            newRecord->creation_time = cr.creation_time;
            newRecord->file = cr.file;

            search_results[search_count++] = *newRecord;
        }
    }

    if (search_count == 0) {
        cout << "Файлы с указанным именем не найдены." << endl;
        delete[] search_results;
        search_results = nullptr;
        return;
    }
}

void SearchOps::printSearchResults(ostream& out) {
    if (!search_results || search_count == 0) {
        out << "Нет доступных результатов для отображения.\n";
        return;
    }

    BasicOps(search_results, search_count).displayRecords();
}

void SearchOps::saveSearchResultsToFile() {
    if (!search_results || search_count == 0) {
        cout << "Нет результатов для сохранения.\n";
        return;
    }

    BasicOps(search_results, search_count).saveToFile();
}

void SearchOps::replaceRecordsWithSearchResult()
{
    char confirmation;
    cout << "Заменить текущие записи результатами поиска (Y/N)? ";
    cin >> confirmation;
    if (confirmation == 'Y' || confirmation == 'y') {
        delete[] records;
        records = new RECORD[search_count];
        for (int i = 0; i < search_count; ++i)
            records[i] = search_results[i];
        record_count = search_count;

        cout << "Результаты поиска были установлены как текущие записи." << endl;

        delete[] search_results;
        search_results = nullptr;
        search_count = 0;
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

#pragma region Область: Дружественные функции.

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
#pragma endregion

SearchOps& SearchOps::operator=(const SearchOps& other) {
    if (this == &other) return *this;

    records = other.records;
    record_count = other.record_count;
    search_count = other.search_count;
    search_results = new RECORD[search_count];
    for (int i = 0; i < search_count; ++i) {
        search_results[i] = other.search_results[i];
    }

    return *this;
}
