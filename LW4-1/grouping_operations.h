#ifndef GROUPING_OPERATIONS_H
#define GROUPING_OPERATIONS_H

#include "record.h"
#include "extensions_group.h"

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

    void printResults(std::ostream& out);
    void saveGroupedToFile();

private:
    void printResultsTableHeader(std::ostream& out) const;
    void printResultsTableBody(std::ostream& out) const;
    void printResultsTableFooter(std::ostream& out) const;

public:
    friend void executeGroup(class RequestDistributor&);

    GroupingOps& operator=(const GroupingOps& other);
};

#endif
