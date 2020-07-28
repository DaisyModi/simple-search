#include "Headers.h"
#include "Dictionary.h"
#include "QueryParser.h"

extern Dictionary dictionary;


QueryParser::QueryParser() {
    
}

QueryParser::~QueryParser() {
    
}

vector<pair<string, int>> QueryParser::getTaggedQuery() {
    return taggedQuery;
}




bool QueryParser::validateQuery(string query) {
    taggedQuery.clear();
    unsigned long len = query.length(), flag = 0;
    string tmp = "";
    
    if (len == 0){ //query is empty
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (query[i] == '"') {
            if (flag == 0) { // starting quotes
                flag = 1;
                tmp += query[i];
                
            }
            else { // ending quotes
                flag = 0;
                tmp += query[i];
                if (tmp.length() != 0){
                    taggedQuery.push_back(make_pair(tmp, findTag(tmp)));
                }
                tmp = "";
            }
        }
        
        else if (flag == 1) { // still inside quotes
            tmp += query[i];
        }
        
        else {
            if (query[i] == ' ') {
                if (tmp.length() != 0)
                    taggedQuery.push_back(make_pair(tmp, findTag(tmp)));
                tmp = "";
            }
            else {
                tmp += query[i];
            }
        }
    }
    
    if (flag == 1){// no matching end quote found
        return false;
    }
    
    if(tmp != "")
        taggedQuery.push_back(make_pair(tmp, findTag(tmp)));
    
    
    unsigned long entityLength = taggedQuery.size();
    if (entityLength % 2 == 0){ // even number of entities
        return false;
    }
    
    int flag2 = 1;
    for (int i = 1; i < entityLength; i += 2) {
        string entity = taggedQuery[i].first, tmp = "";
        
        for (int j = 0; j < entity.length(); j++)
            tmp += tolower(entity[j]);
        
        if (tmp != "and" && tmp != "or")
            flag2 = 0;
    }
    if (flag2 == 0){ // no logical operator between two entities
        return false;
    }
    
    
    /*--------------Checking each token from trie whether it is valid or not------------------------*/
    
    for(int i=0; i<taggedQuery.size(); i+=2){
        
        if(taggedQuery[i].second == 0){ //word
            if(! dictionary.normalTrie.searchWord(taggedQuery[i].first) )
                return false;
        }
        
        
        if(taggedQuery[i].second == 1){ //phrase
            string phrase = taggedQuery[i].first;
            string trimmedPhrase = phrase.substr(1, phrase.length()-2);
            //debug(trimmedPhrase);
            string tmp = "";
            for(int j=0; j < trimmedPhrase.length(); j++){
                if(trimmedPhrase[j] == ' '){
                    if(tmp != ""){
                        if(!dictionary.normalTrie.searchWord(tmp))
                            return false;
                        tmp = "";
                    }
                }
                else{
                    tmp += trimmedPhrase[j];
                }
            }
            
            if(tmp != ""){
                if(!dictionary.normalTrie.searchWord(tmp))
                    return false;
            }
        }
        
    }
    
    return true;
}


/*
 tag = 0 : word
 tag = 1 : phrase
 tag = 2 : stemming start
 tag = 3 : stemming end
 */
int QueryParser::findTag(string input) {
    unsigned long len = input.length();
    if (input[0] == '"')
        return 1;
    if (input[0] == '*')
        return 2;
    if (input[len - 1] == '*')
        return 3;
    return 0;
}




bool QueryParser::assignTagsToQuery(string query) {
    taggedQuery.clear();
    return validateQuery(query);
}
