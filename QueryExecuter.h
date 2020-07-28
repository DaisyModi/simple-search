#ifndef QUERYEXECUTER_H
#define INTITIALPAGE_H

#include "Headers.h"

class QueryExecuter
{
    vector<pair<string, int>> query;
public:
    QueryExecuter(vector<pair<string, int>> query);
    map<int,int>performQueryAccToTag(pair<string , int> query);
    map<int, int> executeQuery();
};

#endif
