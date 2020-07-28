#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "Headers.h"

//using recursive_directory_iterator = boost::filesystem::recursive_directory_iterator; // mac
using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator; // WINDOWS

// Defining the PathHandling class
class QueryParser
{
private:
    vector<pair<string, int>> taggedQuery;
    
public:
    
    QueryParser();
    ~QueryParser();
    
    vector<pair<string, int>> getTaggedQuery();
    bool validateQuery(string query);
    int findTag(string token);
    bool assignTagsToQuery(string query);
};

#endif

