#include "grouping_operations.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

GroupingOps::GroupingOps(RECORD*& recs, int& count) : records(recs), record_count(count) {}

void GroupingOps::getUniqueExtensions(char**& extensions, int*& counts, int& uniqueCount) {
    uniqueCount = 0;
    extensions = new char* [record_count];
    counts = new int[record_count];

    for (int i = 0; i < record_count; ++i) {
        bool found = false;
        for (int j = 0; j < uniqueCount; ++j) {
            if (records[i].file.extension == extensions[j]) {
                counts[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            extensions[uniqueCount] = new char[records[i].file.extension.length() + 1];
            strcpy(extensions[uniqueCount], records[i].file.extension.c_str());
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }
}

void GroupingOps::groupByExtension() {
    char** extensions;
    int* counts;
    int uniqueCount;

    getUniqueExtensions(extensions, counts, uniqueCount);

    cout << "+----------------+------------+" << endl;
    cout << "| Расширение     | Кол-во     |" << endl;
    cout << "+----------------+------------+" << endl;
    for (int i = 0; i < uniqueCount; ++i) {
        cout << "| " << setw(15) << left << extensions[i]
            << "| " << setw(11) << counts[i] << "|" << endl;
    }
    cout << "+----------------+------------+" << endl;

    for (int i = 0; i < uniqueCount; ++i)
        delete[] extensions[i];
    delete[] extensions;
    delete[] counts;
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

                freq_i = freq_j; // update for new records[i]
            }
        }
    }
    cout << "Сортировка по частоте расширений выполнена.\n";
}

void GroupingOps::saveGroupedToFile() {
    string filename;
    cout << "Введите имя файла для сохранения группировки: ";
    cin >> filename;

    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Ошибка при открытии файла.\n";
        return;
    }

    char** extensions;
    int* counts;
    int uniqueCount;

    getUniqueExtensions(extensions, counts, uniqueCount);

    out << "+----------------+------------+\n";
    out << "| Расширение     | Кол-во     |\n";
    out << "+----------------+------------+\n";
    for (int i = 0; i < uniqueCount; ++i) {
        out << "| " << setw(15) << left << extensions[i]
            << "| " << setw(11) << counts[i] << "|\n";
    }
    out << "+----------------+------------+\n";

    out.close();
    cout << "Результаты сохранены в файл: " << filename << endl;

    for (int i = 0; i < uniqueCount; ++i)
        delete[] extensions[i];
    delete[] extensions;
    delete[] counts;
}
