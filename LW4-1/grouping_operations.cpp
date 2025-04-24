#include "grouping_operations.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

GroupingOps::GroupingOps(RECORD*& recs, int& count) : records(recs), record_count(count), groups(nullptr), group_count(0) { }
GroupingOps::GroupingOps(const GroupingOps& other) : records(other.records), record_count(other.record_count), group_count(other.group_count) {
    groups = new EXTENSIONGROUP[group_count];
    for (int i = 0; i < group_count; ++i) {
        groups[i] = other.groups[i];
    }
}
GroupingOps::~GroupingOps() {
    delete[] groups;
}

void GroupingOps::getUniqueExtensions() {
    delete[] groups;
    groups = new EXTENSIONGROUP[record_count];
    group_count = 0;

    for (int i = 0; i < record_count; ++i) {
        string ext = records[i].file.extension;
        bool found = false;
        for (int j = 0; j < group_count; ++j) {
            if (groups[j].extension == ext) {
                groups[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            groups[group_count++] = EXTENSIONGROUP(ext, 1);
        }
    }
}

void GroupingOps::groupByExtension() {
    getUniqueExtensions();
}

#pragma region Область: Вывод сгруппированных данных.

void GroupingOps::printResults(std::ostream& out) {
    printResultsTableHeader(out);
    printResultsTableBody(out);
    printResultsTableFooter(out);
}

void GroupingOps::printResultsTableHeader(std::ostream& out) const {
    out << "+----------------+------------+" << std::endl;
    out << "| Расширение     | Кол-во     |" << std::endl;
    out << "+----------------+------------+" << std::endl;
}

void GroupingOps::printResultsTableBody(std::ostream& out) const {
    for (int i = 0; i < group_count; ++i) {
        out << groups[i];
    }
}

void GroupingOps::printResultsTableFooter(std::ostream& out) const {
    out << "+----------------+------------+" << std::endl;
}
#pragma endregion


void GroupingOps::saveGroupedToFile() {
    string filename;
    cout << "Введите имя файла для сохранения группировки: ";
    cin >> filename;

    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Ошибка при открытии файла.\n";
        return;
    }

    printResults(out);
    cout << "Результаты сохранены в файл: " << filename << endl;
}

void GroupingOps::sortByExtensionFrequency() {
    for (int i = 0; i < record_count - 1; ++i) {
        int freq_i = 0;
        for (int a = 0; a < record_count; ++a)
            if (records[a].file.extension == records[i].file.extension) freq_i++;

        for (int j = i + 1; j < record_count; ++j) {
            int freq_j = 0;
            for (int b = 0; b < record_count; ++b)
                if (records[b].file.extension == records[j].file.extension) freq_j++;

            if (freq_i < freq_j) {
                RECORD temp = records[i];
                records[i] = records[j];
                records[j] = temp;

                freq_i = freq_j;
            }
        }
    }
    cout << "Сортировка по частоте расширений выполнена.\n";
}

GroupingOps& GroupingOps::operator=(const GroupingOps& other) {
    if (this == &other) return *this;

    records = other.records;
    record_count = other.record_count;
    group_count = other.group_count;
    groups = new EXTENSIONGROUP[group_count];
    for (int i = 0; i < group_count; ++i) {
        groups[i] = other.groups[i];
    }

    return *this;
}
