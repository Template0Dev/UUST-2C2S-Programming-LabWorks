#include "search_result.h"
#include <iomanip>

std::ostream& operator <<(std::ostream& os, const SEARCHRESULT& result)
{
    os << "| " << std::setw(24) << std::left << result.filename
        << "| " << std::setw(10) << std::left << result.extension
        << "| " << std::setw(27) << std::left << result.path
        << "| " << std::setw(11) << std::left << result.creation_date
        << "| " << std::setw(9) << std::left << result.creation_time << "|"
        << std::endl;

    return os;
}
