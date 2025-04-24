#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include "record.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>

class BasicOps {
private:
    RECORD*& records;
    int& record_count;
    int capacity;

public:
    BasicOps(RECORD*& r, int& rc);
    BasicOps(const BasicOps& other);
    ~BasicOps();

    void loadFromFile();
    void saveToFile() const;

    void addRecord();
    void deleteRecord();

    void printRecords() const;
    void sortByAttribute();
    void sortAlphabetically();

private:
    void resize();

    bool isOnlyPunctuation(const std::string& str) const;
    bool validateDate(const std::string& date) const;
    bool validateTime(const std::string& time) const;

public:
    BasicOps& operator =(const BasicOps& other);
};

#endif
