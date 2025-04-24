#include "record.h"
#include <iomanip>

std::ostream& operator <<(std::ostream& out, const RECORD& rec) {
    out << "| " << rec.file
        << "| " << std::setw(15) << rec.creation_date
        << "| " << std::setw(10) << rec.creation_time
        << "| " << std::setw(18) << rec.attributes << " |"
        << std::endl;

    return out;
}
