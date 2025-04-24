#include "utils.h"

void trim(std::string& s) {
    size_t start = 0;
    while (start < s.length() && (s[start] == ' ' || s[start] == '\t')) ++start;

    size_t end = s.length();
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t')) --end;

    s = s.substr(start, end - start);
}
