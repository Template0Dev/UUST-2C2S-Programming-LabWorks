#ifndef SEARCH_OPERATIONS_H
#define SEARCH_OPERATIONS_H

#include "file_structs.h"

class SearchOps {
private:
    RECORD*& records;
    int& record_count;

    friend class RequestDistributor;

public:
    SearchOps(RECORD*& recordsRef, int& countRef);

    void searchByFilename();
    void sortByDate();
    void sortByTime();
    void saveSearchResultsToFile();

    friend void executeSearchByFilename(RequestDistributor& distributor);
    friend void executeSortByDate(RequestDistributor& distributor);
    friend void executeSortByTime(RequestDistributor& distributor);
    friend void executeSaveSearchResults(RequestDistributor& distributor);
};

#endif
