#ifndef GROUPING_OPERATIONS_H
#define GROUPING_OPERATIONS_H

#include "file_structs.h"

class GroupingOps {
private:
    RECORD*& records;
    int& record_count;

    void getUniqueExtensions(char**& extensions, int*& counts, int& uniqueCount);

public:
    GroupingOps(RECORD*& recs, int& count);

    void groupByExtension();
    void sortByExtensionFrequency();
    void saveGroupedToFile();
    friend void executeGroup(class RequestDistributor&);
    void printGroupMenu();
};

#endif
