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

    EXTENSIONGROUP(const std::string& ext = "", int c = 0) : extension(ext), count(c) { }
};

struct SEARCHRESULT {
    std::string filename;
    std::string extension;
    std::string path;
    std::string creation_date;
    std::string creation_time;

    SEARCHRESULT() = default;

    SEARCHRESULT(const std::string& fn, const std::string& ext, const std::string& p, const std::string& date, const std::string& time) : filename(fn), extension(ext), path(p), creation_date(date), creation_time(time) { }
};

#endif
