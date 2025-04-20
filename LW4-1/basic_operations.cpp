#include "basic_operations.h"
#include "request_distributor.h"

BasicOps::BasicOps(RECORD*& r, int& rc) : records(r), record_count(rc) {}

void BasicOps::resize() {
    int new_capacity = capacity * 2;
    RECORD* new_records = new RECORD[new_capacity];
    for (int i = 0; i < record_count; i++) {
        new_records[i] = records[i];
    }
    delete[] records;
    records = new_records;
}

bool BasicOps::isOnlyPunctuation(const std::string& str) {
    return std::regex_match(str, std::regex(R"([[:punct:]]+)"));
}

bool BasicOps::validateDate(const std::string& date) {
    return std::regex_match(date, std::regex(R"(\d{2}\.\d{2}\.\d{2})"));
}

bool BasicOps::validateTime(const std::string& time) {
    return std::regex_match(time, std::regex(R"(\d{2}:\d{2})"));
}

void BasicOps::loadFromFile() {
    std::string filename;
    std::cout << "Введите имя файла для загрузки: ";
    std::cin >> filename;
    if (isOnlyPunctuation(filename)) {
        std::cout << "Ошибка: имя файла не может состоять только из знаков препинания.\n";
        return;
    }
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::ofstream newFile(filename);
        newFile.close();
        std::cout << "Файл не найден. Создан новый файл: " << filename << '\n';
        return;
    }
    record_count = 0;
    std::string header;
    std::getline(file, header);
    while (!file.eof()) {
        if (record_count == capacity) resize();
        file >> records[record_count].file.directory
            >> records[record_count].file.filename
            >> records[record_count].file.extension
            >> records[record_count].creation_date
            >> records[record_count].creation_time
            >> records[record_count].attributes;
        if (!file.fail()) record_count++;
    }
    file.close();
    std::cout << "Данные загружены из файла: " << filename << '\n';
}

void BasicOps::saveToFile() {
    std::string filename;
    std::cout << "Введите имя файла для сохранения: ";
    std::cin >> filename;
    if (isOnlyPunctuation(filename)) {
        std::cout << "Ошибка: имя файла не может состоять только из знаков препинания.\n";
        return;
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << filename << '\n';
        return;
    }
    file << std::setw(18) << std::left << "Каталог"
        << std::setw(18) << "Имя файла"
        << std::setw(10) << "Расширение"
        << std::setw(15) << "Дата"
        << std::setw(10) << "Время"
        << std::setw(18) << "Атрибуты" << '\n';

    for (int i = 0; i < record_count; i++) {
        file << std::setw(18) << std::left << records[i].file.directory
            << std::setw(18) << records[i].file.filename
            << std::setw(10) << records[i].file.extension
            << std::setw(15) << records[i].creation_date
            << std::setw(10) << records[i].creation_time
            << std::setw(18) << records[i].attributes << '\n';
    }
    file.close();
    std::cout << "Данные сохранены в файл: " << filename << '\n';
}

void BasicOps::addRecord() {
    if (record_count == capacity) resize();
    RECORD r;
    std::cout << "Каталог: "; std::cin >> r.file.directory;
    std::cout << "Имя файла: "; std::cin >> r.file.filename;
    std::cout << "Расширение: "; std::cin >> r.file.extension;
    do {
        std::cout << "Дата (дд.мм.гг): ";
        std::cin >> r.creation_date;
    } while (!validateDate(r.creation_date));
    do {
        std::cout << "Время (чч:мм): ";
        std::cin >> r.creation_time;
    } while (!validateTime(r.creation_time));
    std::cout << "Атрибуты: "; std::cin >> r.attributes;

    records[record_count++] = r;
}

void BasicOps::deleteRecord() {
    std::string filename;
    std::cout << "Введите имя файла для удаления: ";
    std::cin >> filename;
    if (isOnlyPunctuation(filename)) {
        std::cout << "Ошибка: имя файла не может состоять только из знаков препинания.\n";
        return;
    }
    for (int i = 0; i < record_count; ++i) {
        if (records[i].file.filename == filename) {
            char confirm;
            std::cout << "Точно удалить? (y/n): ";
            std::cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < record_count - 1; j++) {
                    records[j] = records[j + 1];
                }
                record_count--;
                std::cout << "Запись удалена.\n";
            }
            else {
                std::cout << "Удаление отменено.\n";
            }
            return;
        }
    }
    std::cout << "Файл не найден.\n";
}

void BasicOps::displayRecords() {
    std::cout << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+\n";
    std::cout << "| " << std::setw(18) << std::left << "Каталог"
        << "| " << std::setw(18) << "Имя файла"
        << "| " << std::setw(10) << "Расширение"
        << "| " << std::setw(15) << "Дата"
        << "| " << std::setw(10) << "Время"
        << "| " << std::setw(18) << "Атрибуты" << " |\n";
    std::cout << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+\n";
    for (int i = 0; i < record_count; ++i) {
        std::cout << "| " << std::setw(18) << std::left << records[i].file.directory
            << "| " << std::setw(18) << records[i].file.filename
            << "| " << std::setw(10) << records[i].file.extension
            << "| " << std::setw(15) << records[i].creation_date
            << "| " << std::setw(10) << records[i].creation_time
            << "| " << std::setw(18) << records[i].attributes << " |\n";
    }
    std::cout << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+\n";
}

void BasicOps::sortByAttribute() {
    for (int i = 0; i < record_count - 1; ++i) {
        for (int j = 0; j < record_count - i - 1; ++j) {
            if (records[j].attributes > records[j + 1].attributes) {
                RECORD temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

void BasicOps::sortAlphabetically() {
    for (int i = 0; i < record_count - 1; ++i) {
        for (int j = 0; j < record_count - i - 1; ++j) {
            std::string a = records[j].file.directory + records[j].file.filename + records[j].file.extension;
            std::string b = records[j + 1].file.directory + records[j + 1].file.filename + records[j + 1].file.extension;
            if (a > b) {
                RECORD temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

void executeBasicOperation(int choice, RequestDistributor& distributor) {
    BasicOps ops(distributor.records, distributor.record_count);
    switch (choice) {
        case 1: ops.loadFromFile(); break;
        case 2: ops.saveToFile(); break;
        case 3: ops.addRecord(); break;
        case 4: ops.deleteRecord(); break;
        case 5: ops.displayRecords(); break;
        case 6: ops.sortByAttribute(); break;
        case 7: ops.sortAlphabetically(); break;
        default: std::cout << "Неизвестная операция.\n"; break;
    }
}
