#ifndef REQUEST_DISTRIBUTOR_H
#define REQUEST_DISTRIBUTOR_H

#include "file_structs.h"

class RequestDistributor {
public:
    RECORD* records;
    int record_count;

private:
    friend class BasicOps;
    friend class GroupingOps;
    friend class SearchOps;

public:
    RequestDistributor();
    ~RequestDistributor();

    void getRequest(int choice);

    void loadMockData();
    friend void executeOperation();
    friend void executeGroup(RequestDistributor& dist);
    friend void executeSearch(RequestDistributor& dist);
};

#endif
