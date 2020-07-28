//
//  Collation.cpp
//  Search_CPP1_5
//
//  Created by Jatin Tayal on 29/07/19.
//  Copyright © 2019 Adobe. All rights reserved.
//
#include "Collation.h"
Collation collation;
extern int totalIndexedFiles;
extern map<int, string> globalfileIndex;

void Collation::setCollationType(int type){
    collationType = type;
}

int Collation::getCollationType(){
    return  collationType;
}

int Collation::findWordsOccurenceInFile(int fileIndex, vector<map<int, int> > result, vector<string> tokens){
    int total = 0;
    for(int i =0; i<tokens.size(); i++){
        total += result[i][fileIndex];
        cout<<"\t\t\tQuery String : "<< tokens[i] <<"\t\tOccurence : "<< result[i][fileIndex] << endl;
    }
    return total;
}

void Collation::printHorizontalCollation(map<int,int > res, string queryString){
    cout<<"\t\t\tQuery String : "<< queryString <<endl;
    int totalOccurences = 0;
    for(int i=0 ; i<totalIndexedFiles ; i++){
        cout<<"\t\tFile : "<<globalfileIndex[i]<<"\t\tOccurence : "<< res[i] << endl;
        totalOccurences += res[i];
    }
    
    cout <<"\t\t\t\tTotal Occurences : "<<totalOccurences<<endl;
}

void Collation::printVerticalCollation(vector<map<int, int> > result, vector<string> tokens){
    
    for(int i=0 ; i<totalIndexedFiles ; i++){
        cout<<"\t\tFile : "<<globalfileIndex[i]<<endl;
        int totalOccurences = findWordsOccurenceInFile(i,result, tokens);
        cout<<"\t\tTotal occurence : "<<totalOccurences<<endl;
    }
}
