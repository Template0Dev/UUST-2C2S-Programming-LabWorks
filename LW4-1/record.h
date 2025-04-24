#ifndef RECORD_H
#define RECORD_H

#include "file_info.h"
#include <string>

struct RECORD {
    FILEINFO file;
    std::string creation_date;
    std::string creation_time;
    std::string attributes;

    friend std::istream& operator >>(std::istream& is, RECORD& rec);
    friend std::ostream& operator <<(std::ostream& out, const RECORD& rec);
};

#endif
