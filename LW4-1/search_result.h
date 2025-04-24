#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <string>

struct SEARCHRESULT {
    std::string filename;
    std::string extension;
    std::string path;
    std::string creation_date;
    std::string creation_time;

    SEARCHRESULT() = default;
    SEARCHRESULT(const std::string& fn, const std::string& ext, const std::string& p, const std::string& date, const std::string& time) : filename(fn), extension(ext), path(p), creation_date(date), creation_time(time) {}
};

#endif
