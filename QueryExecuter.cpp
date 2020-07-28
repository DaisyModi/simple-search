#include "Headers.h"
#include "QueryExecuter.h"
#include "Dictionary.h"
#include "Operations.h"
#include "Collation.h"

extern Dictionary dictionary;
extern int totalIndexedFiles;
extern Collation collation;



QueryExecuter::QueryExecuter(vector<pair<string, int>> queryString) {
    query = queryString;
}


map<int, int>  QueryExecuter::performQueryAccToTag(pair<string , int> query){
    Operations op;
    string queryString = query.first;
    int tag = query.second;
    map<int, int> res;
    res.clear();
    
    if (tag == 0 ) { // word query
        transform(queryString.begin(), queryString.end(), queryString.begin(), ::tolower);
        res = op.performWordQuery(queryString,"normal");
    }
    else if (tag == 1) { // phrase query
        res =  op.performPhraseQuery(queryString);
    }
    else if(tag == 2){ // beginning stemming
        transform(queryString.begin(), queryString.end(), queryString.begin(), ::tolower);
        res =  op.performStemmingQuery(queryString, "reverse");
    }
    else{ // end stemming
        transform(queryString.begin(), queryString.end(), queryString.begin(), ::tolower);
        res =  op.performStemmingQuery(queryString, "normal");
    }
    
    
    return res;
}

map<int, int> QueryExecuter::executeQuery() {
    Operations op;
    map<int, int> res;
    vector<string> tokens;
    vector<map<int, int> > verticalCollation;
    verticalCollation.clear();
    res.clear();

    
    
    if(collation.getCollationType() == 1){
        cout<<"The result for Horizontal collation is:\n";
        res = performQueryAccToTag(query[0]);
		collation.printHorizontalCollation(res, query[0].first);

        for(int i = 2; i < query.size(); i++){
            map<int, int > tmp = performQueryAccToTag(query[i]);
           collation.printHorizontalCollation(tmp,query[i].first);
            
            if(query[i-1].first == "and")
                res = op.operationAND(res, tmp);
            else if(query[i-1].first == "or")
                res = op.operationOR(res, tmp);
        }
    }
    else if(collation.getCollationType() == 2){
        cout<<"The result for Vertical collation is:\n";
        res = performQueryAccToTag(query[0]);
        tokens.push_back(query[0].first);
        verticalCollation.push_back(res);
        for(int i = 2; i < query.size(); i++){
            map<int, int > tmp = performQueryAccToTag(query[i]);
            tokens.push_back(query[i].first);
            verticalCollation.push_back(tmp);
            if(query[i-1].first == "and")
                res = op.operationAND(res, tmp);
            else if(query[i-1].first == "or")
                res = op.operationOR(res, tmp);
        }
        collation.printVerticalCollation(verticalCollation, tokens);
    }
	else { // only one entity
		res = performQueryAccToTag(query[0]);
	}
    return res;
}
