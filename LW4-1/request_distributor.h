#ifndef REQUEST_DISTRIBUTOR_H
#define REQUEST_DISTRIBUTOR_H

#include "record.h"

class RequestDistributor {
public:
    const int initial_records_count = 8;

    int record_count;
    RECORD* records;

private:
    friend class BasicOps;
    friend class GroupingOps;
    friend class SearchOps;

    void printBasicMenu() const;
    void printGroupMenu() const;
    void printSearchMenu() const;

public:
    RequestDistributor();
    ~RequestDistributor();
    void loadMockData();

    void getRequest(int choice);
    friend void executeOperation(RequestDistributor& dist);
    friend void executeGroup(RequestDistributor& dist);
    friend void executeSearch(RequestDistributor& dist);
};

#endif
