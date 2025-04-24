#include "record.h"
#include "utils.h"
#include <array>
#include <iomanip>

std::istream& operator>>(std::istream& is, RECORD& rec) {
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

    rec.file.directory = fields[0];
    rec.file.filename = fields[1];
    rec.file.extension = fields[2];
    rec.creation_date = fields[3];
    rec.creation_time = fields[4];
    rec.attributes = fields[5];

    return is;
}

std::ostream& operator <<(std::ostream& out, const RECORD& rec) {
    out << "| " << rec.file
        << "| " << std::setw(15) << rec.creation_date
        << "| " << std::setw(10) << rec.creation_time
        << "| " << std::setw(18) << rec.attributes << " |"
        << std::endl;

    return out;
}
