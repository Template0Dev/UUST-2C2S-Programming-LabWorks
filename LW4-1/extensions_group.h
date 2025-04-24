#ifndef EXTENSIONS_GROUP_H
#define EXTENSIONS_GROUP_H

#include <string>
#include <iostream>

class EXTENSIONGROUP {
public:
    std::string extension;
    int count;

    EXTENSIONGROUP(const std::string& ext = "", int c = 0) : extension(ext), count(c) {}

    friend std::ostream& operator <<(std::ostream& os, const EXTENSIONGROUP& group);
};

#endif
