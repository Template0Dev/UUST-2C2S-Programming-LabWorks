#ifndef FILE_STRUCTS_H
#define FILE_STRUCTS_H

#include <string>

struct FILEINFO {
    std::string directory;
    std::string filename;
    std::string extension;
};

struct RECORD {
    FILEINFO file;
    std::string creation_date;
    std::string creation_time;
    std::string attributes;
};

class EXTENSIONGROUP {
public:
    std::string extension;
    int count;
};

#endif
