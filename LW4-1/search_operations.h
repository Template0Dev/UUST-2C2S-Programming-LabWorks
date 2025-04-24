#ifndef SEARCH_OPERATIONS_H
#define SEARCH_OPERATIONS_H

#include "record.h"
#include "search_result.h"

class SearchOps {
private:
    RECORD*& records;
    int& record_count;

    SEARCHRESULT* search_results;
    int search_count;

    friend class RequestDistributor;

public:
    SearchOps(RECORD*& recordsRef, int& countRef);
    ~SearchOps();
    SearchOps(const SearchOps& other);
    SearchOps& operator=(const SearchOps& other);

    void searchByFilename();
    void sortByDate();
    void sortByTime();
    void replaceCurrentArrayWithSearchResults();

    void printResults(std::ostream& os) const;
    void saveSearchResultsToFile() const;

private:
    void clearResults();

    void sortResultsByDate();
    void sortResultsByTime();
};

#endif
