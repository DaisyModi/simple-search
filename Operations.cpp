//
//  LogicalOperators.cpp
//  Search_CPP1_5
//
//  Created by Jatin Tayal on 28/07/19.
//  Copyright © 2019 Adobe. All rights reserved.
//

#include "Operations.h"
#include "Dictionary.h"
#include <iostream>
#include <string>
#include <fstream>

extern Dictionary dictionary;
extern int totalIndexedFiles;
extern map<int, string> globalfileIndex;



map<int, int> Operations::operationAND(map<int, int> param1, map<int, int> param2) {
    map<int, int> solution;
    //int numOfFiles = ?
    for(int i =0;i<totalIndexedFiles; i++){
        int firstFileOccurence = 0;
        int secondFileOccurence = 0;
        if(param1.find(i) != param1.end()){
            firstFileOccurence = param1[i];
        }
        if(param2.find(i) != param2.end()){
            secondFileOccurence = param2[i];
        }
        solution[i] = firstFileOccurence <= secondFileOccurence ? firstFileOccurence : secondFileOccurence;
    }
    return solution;
}


map<int, int> Operations::operationOR(map<int, int> param1, map<int, int> param2) {
    map<int, int> solution;
    //int numOfFiles = ?
    for(int i =0;i<totalIndexedFiles; i++){
        int firstFileOccurence = 0;
        int secondFileOccurence = 0;
        if(param1.find(i) != param1.end()){
            firstFileOccurence = param1[i];
        }
        if(param2.find(i) != param2.end()){
            secondFileOccurence = param2[i];
        }
        solution[i] = firstFileOccurence >= secondFileOccurence ? firstFileOccurence : secondFileOccurence;
    }
    return solution;
}

map<int, int> Operations::operationSUM(map<int, int> param1, map<int, int> param2) {
    map<int, int> solution;
    for(int i =0;i<totalIndexedFiles; i++){
        int firstFileOccurence = 0;
        int secondFileOccurence = 0;
        if(param1.find(i) != param1.end()){
            firstFileOccurence = param1[i];
        }
        if(param2.find(i) != param2.end()){
            secondFileOccurence = param2[i];
        }
        solution[i] = firstFileOccurence + secondFileOccurence ;
    }
    return solution;
}


map<int, int>  Operations::performWordQuery(string queryString, string type){
    if(type == "normal")
        return dictionary.normalTrie.findWordDetails(queryString);
    else
        return dictionary.reverseTrie.findWordDetails(queryString);
}

int  Operations::findOccurencesOfPhraseInFile(int fileIndex, string phrase){
    int count = 0;
    ifstream ifs(globalfileIndex[fileIndex]);
    string fileContent( (std::istreambuf_iterator<char>(ifs) ),
                            (std::istreambuf_iterator<char>()) );

    size_t pos = fileContent.find(phrase);
    
    // Repeat till end is reached
    while( pos != std::string::npos){
        count++;
        pos = fileContent.find(phrase, pos + phrase.size());
    }
    return count;
}


map<int, int>  Operations::performPhraseQuery(string queryString){
    map<int, int> res;
    string trimmedPhrase = queryString.substr(1, queryString.length()-2);
    string firstWord = "";
    for(int j=0; j < trimmedPhrase.length(); j++){
        if(trimmedPhrase[j] == ' '){
            if(firstWord != ""){
                break;
            }
        }
        else{
            firstWord += trimmedPhrase[j];
        }
    }
//    debug(trimmedPhrase);
    if(firstWord != ""){
        map<int,int > filesInfo =  dictionary.normalTrie.findWordDetails(firstWord); // finding list of files in which first word appears
        map<int, int>::iterator it = filesInfo.begin();
        while (it != filesInfo.end()) {
            res[it->first] = findOccurencesOfPhraseInFile(it->first, trimmedPhrase);
            it++;
        }
    }
    return  res;
}

map<int, int>  Operations::performStemmingQuery(string queryString, string type){
    map<int,int> res;
    res.clear();
    if(type == "normal"){
        string trimmedQuery = queryString.substr(0, queryString.length()-1);
        vector<string>validWords =  dictionary.normalTrie.findValidWords(trimmedQuery);
        
        for(int i=0; i<validWords.size(); i++)
            res = operationSUM(res, performWordQuery(validWords[i], "normal"));
    }
    else{
        reverse(queryString.begin(), queryString.end() );
        string trimmedQuery = queryString.substr(0, queryString.length()-1);
        vector<string>validWords =  dictionary.reverseTrie.findValidWords(trimmedQuery);
        for(int i=0; i<validWords.size(); i++)
            res = operationSUM(res, performWordQuery(validWords[i], "reverse"));
    }
    return res;
}




































