#include "extensions_group.h"
#include <iomanip>

std::ostream& operator <<(std::ostream& os, const EXTENSIONGROUP& group) {
    os << "| " << std::setw(15) << std::left << group.extension
        << "| " << std::setw(11) << std::left << group.count << "|" 
        << std::endl;

    return os;
}
