#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <string>

struct FILEINFO {
    std::string directory;
    std::string filename;
    std::string extension;

    friend std::ostream& operator <<(std::ostream& out, const FILEINFO& fi);
};

#endif
