#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Headers.h"

using namespace std;

/*
 Performs operation on the keyword.
 For OR , AND , DEFAULT
 AND : Maximum intersection between two keywords in a query.
 OR : Minimum Union between two keywords in a query.
 SUM : Addition of occurance of two keywords in a query.
 DEFAULT : OR operation.
 */

class Operations{
    
public:
    //Performs AND of occurance of two keywords in a query.
    map<int, int> operationAND(map<int, int> param1, map<int, int> param2);
    
    //Performs OR of occurance of two keywords in a query.
    map<int, int> operationOR(map<int, int> param1, map<int, int> param2);
    
    //Performs sum operation for stemming query
    map<int, int> operationSUM(map<int, int> param1, map<int, int> param2);
    
    map<int, int> performWordQuery(string queryString, string type);
    map<int, int> performPhraseQuery(string queryString);
    map<int, int> performStemmingQuery(string queryString, string type);
    int findOccurencesOfPhraseInFile(int fileIndex, string phrase);
    
};

#endif
