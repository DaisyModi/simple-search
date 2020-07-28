#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
using namespace std;

/* Trie storing the words in the dictionary along with the positions in the files these are present */
const int ALPHABET_SIZE = 255;

// structure of the node in the trie
struct TrieNode {
    bool isEndOfWord;
    //map<int, vector<int>>  fileWithPosition;
    map<int, int>  fileWithCount;
    struct TrieNode* children[ALPHABET_SIZE];
    /*TrieNode() {
     To be done ---------------
     }*/
};


// Defining the Trie class
class Trie
{
private:
    TrieNode *rootNode;
    
public:
    Trie();
//    ~Trie();
    
    struct TrieNode* newNode();
    void insertNode(string dictionaryWord);
    bool searchWord(string wordToSearch);
    map<int, int> findWordDetails (string wordToPrint);
    void insertPosition(string fileWord, int fileIndex, int position);
    void insertDictionaryWords(string pathOfDictionary, string type);
    void insertCountInFiles(map<int,string> listOfFiles, string type);
    void incrementCount(string fileWord, int fileIndex);
    vector<string> findValidWords(string query);
    void findValidWordsHelper(TrieNode* node, string currWord, vector<string>& validWords);
};

#endif
