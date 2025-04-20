#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <windows.h>
#include <regex>
#include <limits>

using namespace std;

struct FILE_INFO {
    string directory;
    string filename;
    string extension;
};

struct RECORD {
    FILE_INFO file;
    string creation_date;
    string creation_time;
    string attributes;
};

class FileManager {
private:
    RECORD* records;
    int record_count;
    int capacity;

    void resize() {
        int new_capacity = capacity * 2;
        RECORD* new_records = new RECORD[new_capacity];
        for (int i = 0; i < record_count; i++) {
            new_records[i] = records[i];
        }
        delete[] records;
        records = new_records;
        capacity = new_capacity;
    }

public:
    // Конструктор по умолчанию
    FileManager() {
        capacity = 10;
        record_count = 0;
        records = new RECORD[capacity];
    }

    // Конструктор копирования
    FileManager(const FileManager& other) {
        capacity = other.capacity;
        record_count = other.record_count;
        records = new RECORD[capacity];
        for (int i = 0; i < record_count; i++) {
            records[i] = other.records[i];
        }
    }

    // Оператор присваивания
    FileManager& operator=(const FileManager& other) {
        if (this == &other)
            return *this;
        delete[] records;
        capacity = other.capacity;
        record_count = other.record_count;
        records = new RECORD[capacity];
        for (int i = 0; i < record_count; i++) {
            records[i] = other.records[i];
        }
        return *this;
    }

    // Оператор сравнения: объекты равны, если содержат одинаковое число записей и каждая запись совпадает
    bool operator==(const FileManager& other) const {
        if (record_count != other.record_count)
            return false;
        for (int i = 0; i < record_count; i++) {
            if (records[i].file.directory != other.records[i].file.directory ||
                records[i].file.filename != other.records[i].file.filename ||
                records[i].file.extension != other.records[i].file.extension ||
                records[i].creation_date != other.records[i].creation_date ||
                records[i].creation_time != other.records[i].creation_time ||
                records[i].attributes != other.records[i].attributes) {
                return false;
            }
        }
        return true;
    }

    // Оператор вывода на терминал (friend-функция)
    friend ostream& operator<<(ostream& os, const FileManager& fm);

    ~FileManager() {
        delete[] records;
    }

    bool isOnlyPunctuation(const string& str) {
        return regex_match(str, regex(R"([[:punct:]]+)"));
    }

    void loadFromFile() {
        string filename;
        cout << "Введите имя файла для загрузки: ";
        cin >> filename;
        if (isOnlyPunctuation(filename)) {
            cout << "Ошибка: имя файла не может состоять только из знаков препинания." << endl;
            return;
        }
        ifstream file(filename);
        if (!file.is_open()) {
            ofstream newFile(filename);
            newFile.close();
            cout << "Файл не найден. Создан новый файл: " << filename << endl;
            return;
        }
        record_count = 0;
        while (!file.eof()) {
            if (record_count == capacity) {
                resize();
            }
            string line;
            getline(file, line);  // Пропускаем заголовок
            file >> records[record_count].file.directory
                >> records[record_count].file.filename
                >> records[record_count].file.extension
                >> records[record_count].creation_date
                >> records[record_count].creation_time
                >> records[record_count].attributes;
            if (!file.fail()) {
                record_count++;
            }
        }
        file.close();
        cout << "Данные загружены из файла: " << filename << endl;
    }
    void saveToFile() {
        string filename;
        cout << "Введите имя файла для сохранения: ";
        cin >> filename;
        if (isOnlyPunctuation(filename)) {
            cout << "Ошибка: имя файла не может состоять только из знаков препинания." << endl;
            return;
        }
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл " << filename << endl;
            return;
        }
        // Заголовок таблицы
        file << setw(18) << left << "Каталог"
            << setw(18) << "Имя файла"
            << setw(10) << "Расширение"
            << setw(15) << "Дата"
            << setw(10) << "Время"
            << setw(18) << "Атрибуты" << endl;
        // Запись данных
        for (int i = 0; i < record_count; i++) {
            file << setw(18) << left << records[i].file.directory
                << setw(18) << records[i].file.filename
                << setw(10) << records[i].file.extension
                << setw(15) << records[i].creation_date
                << setw(10) << records[i].creation_time
                << setw(18) << records[i].attributes
                << endl;
        }
        file.close();
        cout << "Данные сохранены в файл: " << filename << endl;
    }

    void addRecord(const RECORD& rec) {
        if (record_count == capacity) {
            resize();
        }
        records[record_count++] = rec;
    }

    void deleteRecord(const string& filename) {
        if (isOnlyPunctuation(filename)) {
            cout << "Ошибка: имя файла не может состоять только из знаков препинания." << endl;
            return;
        }
        for (int i = 0; i < record_count; i++) {
            if (records[i].file.filename == filename) {
                char confirmation;
                cout << "Точно ли вы хотите удалить эту запись? (y/n): ";
                cin >> confirmation;
                if (confirmation == 'y' || confirmation == 'Y') {
                    for (int j = i; j < record_count - 1; j++) {
                        records[j] = records[j + 1];
                    }
                    record_count--;
                    cout << "Запись удалена." << endl;
                    return;
                }
                else {
                    cout << "Удаление отменено." << endl;
                    return;
                }
            }
        }
        cout << "Файл не найден." << endl;
    }

    void displayRecords() {
        system("cls");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        // Заголовок таблицы
        cout << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+" << endl;
        cout << "| " << setw(18) << left << "Каталог"
            << "| " << setw(18) << "Имя файла"
            << "| " << setw(10) << "Расширение"
            << "| " << setw(15) << "Дата"
            << "| " << setw(10) << "Время"
            << "| " << setw(18) << "Атрибуты"
            << " |" << endl;
        cout << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+" << endl;
        // Вывод данных
        for (int i = 0; i < record_count; i++) {
            cout << "| " << setw(18) << left << records[i].file.directory
                << "| " << setw(18) << records[i].file.filename
                << "| " << setw(10) << records[i].file.extension
                << "| " << setw(15) << records[i].creation_date
                << "| " << setw(10) << records[i].creation_time
                << "| " << setw(18) << records[i].attributes
                << " |" << endl;
        }
        cout << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+" << endl;
    }

    void sortByAttribute() {
        sort(records, records + record_count, [](const RECORD& a, const RECORD& b) {
            return tie(a.attributes, a.file.filename, a.file.extension) < tie(b.attributes, b.file.filename, b.file.extension);
            });
    }
    void sortAlphabetically() {
        sort(records, records + record_count, [](const RECORD& a, const RECORD& b) {
            return tie(a.file.directory, a.file.filename, a.file.extension) < tie(b.file.directory, b.file.filename, b.file.extension);
            });
    }

    void sortByDateTime() {
        sort(records, records + record_count, [](const RECORD& a, const RECORD& b) {
            return tie(a.creation_date, a.creation_time) < tie(b.creation_date, b.creation_time);
            });
    }

    bool validateDate(const string& date) {
        regex datePattern(R"(\d{2}.\d{2}.\d{2})");
        return regex_match(date, datePattern);
    }

    bool validateTime(const string& time) {
        regex timePattern(R"(\d{2}:\d{2})");
        return regex_match(time, timePattern);
    }
};

// Оператор вывода на терминал
ostream& operator<<(ostream& os, const FileManager& fm) {
    os << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+\n";
    os << "| " << setw(18) << left << "Каталог"
        << "| " << setw(18) << "Имя файла"
        << "| " << setw(10) << "Расширение"
        << "| " << setw(15) << "Дата"
        << "| " << setw(10) << "Время"
        << "| " << setw(18) << "Атрибуты"
        << " |\n";
    os << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+\n";
    for (int i = 0; i < fm.record_count; i++) {
        os << "| " << setw(18) << left << fm.records[i].file.directory
            << "| " << setw(18) << fm.records[i].file.filename
            << "| " << setw(10) << fm.records[i].file.extension
            << "| " << setw(15) << fm.records[i].creation_date
            << "| " << setw(10) << fm.records[i].creation_time
            << "| " << setw(18) << fm.records[i].attributes
            << " |\n";
    }
    os << "+-------------------+-------------------+-----------+----------------+-----------+--------------------+\n";
    return os;
}

int mainDev() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    FileManager manager;

    while (true) {
        cout << "\nМеню:\n"
            << "1. Загрузка из файла\n"
            << "2. Сохранение результатов в файле\n"
            << "3. Добавление записи\n"
            << "4. Удаление записи\n"
            << "5. Вывод данных на экран\n"
            << "6. Сортировка по атрибуту\n"
            << "7. Алфавитная сортировка\n"
            << "8. Сортировка по дате и времени\n"
            << "9. Проверка конструктора копирования\n"
            << "10. Перегрузка сравнения\n"
            << "11. Перегрузка присваивания\n"
            << "12. Выход\n";

        int choice;
        cout << "Выберите действие (1-12): ";
        while (!(cin >> choice) || choice < 1 || choice > 12) {
            cout << "Ошибка: введите число от 1 до 12.\n";
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }

        switch (choice) {
            case 1:
                manager.loadFromFile();
                break;
            case 2:
                manager.saveToFile();
                break;
            case 3: {
                RECORD rec;
                cout << "Введите каталог: ";
                cin >> rec.file.directory;
                cout << "Введите имя файла: ";
                cin >> rec.file.filename;
                if (manager.isOnlyPunctuation(rec.file.filename)) {
                    cout << "Ошибка: имя файла не может состоять только из знаков препинания.\n";
                    break;
                }
                cout << "Введите расширение файла: ";
                cin >> rec.file.extension;
                manager.addRecord(rec);
                do {
                    cout << "Введите дату (ГГ.ММ.ДД): ";
                    cin >> rec.creation_date;
                } while (!manager.validateDate(rec.creation_date));
                do {
                    cout << "Введите время (ЧЧ:ММ): ";
                    cin >> rec.creation_time;
                } while (!manager.validateTime(rec.creation_time));
                cout << "Введите атрибуты: ";
                cin >> rec.attributes;
                manager.addRecord(rec);
                break;
            }
            case 4: {
                string fname;
                cout << "Введите имя файла для удаления: ";
                cin >> fname;
                manager.deleteRecord(fname);
                break;
            }
            case 5:
                manager.displayRecords();
                break;
            case 6:
                manager.sortByAttribute();
                break;
            case 7:
                manager.sortAlphabetically();
                break;
            case 8:
                manager.sortByDateTime();
                break;
            case 9: {
                cout << "Оригинальные данные:\n" << manager;
                FileManager copyManager = manager;
                cout << "Данные копии (конструктор копирования):\n" << copyManager;
                break;
            }
            case 10: {
                // Демонстрация перегрузки оператора сравнения
                FileManager copyManager(manager);
                FileManager assignedManager;
                assignedManager = manager;
                cout << "Оригинальные данные:\n" << manager;
                cout << "Данные копии (конструктор копирования):\n" << copyManager;
                cout << "Данные, созданные оператором присваивания:\n" << assignedManager;
                cout << "\nСравнение оригинала с копией (конструктор копирования): "
                    << ((manager == copyManager) ? "Равны" : "Не равны") << endl;
                cout << "Сравнение оригинала с объектом, созданным оператором присваивания: "
                    << ((manager == assignedManager) ? "Равны" : "Не равны") << endl;
                break;
            }
            case 11: {
                // Демонстрация перегрузки оператора присваивания
                FileManager assignedManager;
                assignedManager = manager; // первое присваивание из оригинала
                FileManager secondAssignedManager;
                secondAssignedManager = assignedManager; // второе присваивание из первого присваивания
                cout << "Оригинальные данные:\n" << manager;
                cout << "Данные, созданные оператором присваивания (1-е присваивание):\n" << assignedManager;
                cout << "Данные, созданные оператором присваивания (2-е присваивание из первого):\n" << secondAssignedManager;
                break;
            }
            case 12:
                return 0;
        }
    }
}