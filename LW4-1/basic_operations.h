#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include "file_structs.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>

class BasicOps {
private:
    RECORD*& records;
    int& record_count;
    int capacity;

    void resize();

    bool isOnlyPunctuation(const std::string& str);
    bool validateDate(const std::string& date);
    bool validateTime(const std::string& time);

public:
    BasicOps(RECORD*& r, int& rc);
    BasicOps(const BasicOps& other);
    ~BasicOps();

    void loadFromFile();
    void saveToFile();
    void addRecord();
    void deleteRecord();
    void displayRecords();
    void sortByAttribute();
    void sortAlphabetically();

    BasicOps& operator =(const BasicOps& other);
};

#endif
