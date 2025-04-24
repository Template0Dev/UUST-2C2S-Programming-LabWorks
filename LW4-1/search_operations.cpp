#include "search_operations.h"
#include "request_distributor.h"
#include "basic_operations.h"
#include <iostream>
#include <fstream>

using namespace std;

#pragma region Область: Конструкторы / Деструкторы.

SearchOps::SearchOps(RECORD*& recordsRef, int& countRef)
	: records(recordsRef), record_count(countRef), search_results(nullptr), search_count(0) {
}

SearchOps::SearchOps(const SearchOps& other)
	: records(other.records), record_count(other.record_count), search_results(nullptr), search_count(other.search_count) {
	if (other.search_count > 0 && other.search_results) {
		search_results = new SEARCHRESULT[search_count];
		for (int i = 0; i < search_count; ++i) {
			search_results[i] = other.search_results[i];
		}
	}
}

SearchOps::~SearchOps() {
	clearResults();
}
#pragma endregion

void SearchOps::clearResults() {
	delete[] search_results;
	search_results = nullptr;
	search_count = 0;
}

void SearchOps::searchByFilename() {
	string target;
	cout << "Введите имя файла для поиска: ";
	cin >> target;

	SEARCHRESULT* temp = new SEARCHRESULT[record_count];
	int found = 0;

	for (int i = 0; i < record_count; ++i) {
		if (records[i].file.filename.find(target) == 0) {
			temp[found++] = SEARCHRESULT(
				records[i].file.filename,
				records[i].file.extension,
				records[i].file.directory,
				records[i].creation_date,
				records[i].creation_time
			);
		}
	}

	if (found == 0) {
		cout << "Файлы с указанным именем не найдены.\n";
		delete[] temp;
		return;
	}

	clearResults();
	search_results = temp;
	search_count = found;
}

void SearchOps::sortByDate() {
	sortResultsByDate();
	cout << "Сортировка результатов поиска по дате завершена.\n";
}

void SearchOps::sortResultsByDate() {
	for (int i = 0; i < search_count - 1; ++i) {
		for (int j = i + 1; j < search_count; ++j) {
			if (search_results[i].creation_date > search_results[j].creation_date) {
				SEARCHRESULT temp = search_results[i];
				search_results[i] = search_results[j];
				search_results[j] = temp;
			}
		}
	}
}

void SearchOps::sortByTime() {
	sortResultsByTime();
	cout << "Сортировка результатов поиска по времени завершена.\n";
}

void SearchOps::sortResultsByTime() {
	for (int i = 0; i < search_count - 1; ++i) {
		for (int j = i + 1; j < search_count; ++j) {
			if (search_results[i].creation_time > search_results[j].creation_time) {
				SEARCHRESULT temp = search_results[i];
				search_results[i] = search_results[j];
				search_results[j] = temp;
			}
		}
	}
}

void SearchOps::replaceCurrentArrayWithSearchResults()
{
	delete[] records;
	records = new RECORD[search_count];
	for (int i = 0; i < search_count; ++i) {
		records[i].file.filename = search_results[i].filename;
		records[i].file.extension = search_results[i].extension;
		records[i].file.directory = search_results[i].path;
		records[i].creation_date = search_results[i].creation_date;
		records[i].creation_time = search_results[i].creation_time;
	}
	record_count = search_count;
	cout << "Результаты поиска были установлены как текущие записи.\n";
}

#pragma region Область: Вывод данных.

void SearchOps::printResults(ostream& os) const { 
	printResultTableHeader(os);
	printResultTableBody(os);
	printResultTableFooter(os);
}

void SearchOps::printResultTableHeader(ostream& os) const {
	os << "+-------------------------+-----------+----------------------------+------------+----------+" << std::endl;
	os << "| Имя файла               | Расшир.   | Путь                       | Дата       | Время    |" << std::endl;
	os << "+-------------------------+-----------+----------------------------+------------+----------+" << std::endl;
}

void SearchOps::printResultTableBody(ostream& os) const {
	for (int i = 0; i < search_count; ++i) {
		os << search_results[i];
	}
}

void SearchOps::printResultTableFooter(ostream& os) const {
	os << "+-------------------------+-----------+----------------------------+------------+----------+" << std::endl;
}
#pragma endregion

void SearchOps::saveSearchResultsToFile() const {
	string filename;
	cout << "Введите имя файла для сохранения результатов поиска: ";
	cin >> filename;

	ofstream out(filename);
	if (!out.is_open()) {
		cout << "Ошибка открытия файла.\n";
		return;
	}

	printResults(out);
	out.close();

	cout << "Результаты поиска сохранены в файл: " << filename << endl;
}

SearchOps& SearchOps::operator=(const SearchOps& other) {
	if (this == &other) return *this;

	clearResults();

	records = other.records;
	record_count = other.record_count;
	search_count = other.search_count;

	if (search_count > 0 && other.search_results) {
		search_results = new SEARCHRESULT[search_count];
		for (int i = 0; i < search_count; ++i) {
			search_results[i] = other.search_results[i];
		}
	}

	return *this;
}
