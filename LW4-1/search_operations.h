#ifndef SEARCH_OPERATIONS_H
#define SEARCH_OPERATIONS_H

#include "file_structs.h"
#include <ostream>

class SearchOps {
private:
    int& record_count;
    RECORD*& records;

    int search_count;
    RECORD* search_results;

    friend class RequestDistributor;

public:
    SearchOps(RECORD*& recordsRef, int& countRef);
    SearchOps(const SearchOps& other);
    ~SearchOps();

    void searchByFilename();
    void replaceRecordsWithSearchResult();
    void printSearchResults(std::ostream& out);
    void saveSearchResultsToFile();

    void sortByDate();
    void sortByTime();

    friend void executeSearchByFilename(RequestDistributor& distributor);
    friend void executeSortByDate(RequestDistributor& distributor);
    friend void executeSortByTime(RequestDistributor& distributor);
    friend void executeSaveSearchResults(RequestDistributor& distributor);

    SearchOps& operator=(const SearchOps& other);
};

#endif
