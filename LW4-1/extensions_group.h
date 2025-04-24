#ifndef EXTENSIONS_GROUP_H
#define EXTENSIONS_GROUP_H

#include <string>

class EXTENSIONGROUP {
public:
    std::string extension;
    int count;

    EXTENSIONGROUP(const std::string& ext = "", int c = 0) : extension(ext), count(c) {}
};

#endif
