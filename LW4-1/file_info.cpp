#include "file_info.h"
#include <iomanip>

std::ostream& operator <<(std::ostream& out, const FILEINFO& fi) {
    out << std::setw(18) << std::left << fi.directory
        << "| " << std::setw(18) << fi.filename
        << "| " << std::setw(10) << fi.extension;

    return out;
}
