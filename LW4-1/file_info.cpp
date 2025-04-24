#include "file_info.h"
#include "utils.h"
#include <array>
#include <iomanip>

std::istream& operator >>(std::istream& is, FILEINFO& fi) {
    std::string line;
    std::getline(is, line);

    if (line.find('+') != std::string::npos || line.find('|') == std::string::npos) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::array<std::string, 6> fields;
    int fieldIndex = 0;
    size_t start = 0;

    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '|') {
            if (fieldIndex > 0 && fieldIndex <= 6) {
                std::string field = line.substr(start, i - start);
                trim(field);

                fields[fieldIndex - 1] = field;
            }
            start = i + 1;
            ++fieldIndex;
        }
    }

    fi.directory = fields[0];
    fi.filename = fields[1];
    fi.extension = fields[2];

    return is;
}

std::ostream& operator <<(std::ostream& out, const FILEINFO& fi) {
    out << std::setw(18) << std::left << fi.directory
        << "| " << std::setw(18) << fi.filename
        << "| " << std::setw(10) << fi.extension;

    return out;
}
