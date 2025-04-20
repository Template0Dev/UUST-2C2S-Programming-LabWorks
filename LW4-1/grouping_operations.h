#ifndef GROUPING_OPERATIONS_H
#define GROUPING_OPERATIONS_H

#include "file_structs.h"

class GroupingOps {
private:
    RECORD*& records;
    int& record_count;

    EXTENSIONGROUP* groups;
    int group_count;

    void getUniqueExtensions();

public:
    GroupingOps(RECORD*& recs, int& count);
    GroupingOps(const GroupingOps& other);
    ~GroupingOps();

    void groupByExtension();
    void sortByExtensionFrequency();

    void printGrouped(std::ostream& out);
    void saveGroupedToFile();

    friend void executeGroup(class RequestDistributor&);

    GroupingOps& operator=(const GroupingOps& other);
};

#endif
