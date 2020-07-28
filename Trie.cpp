#include "Headers.h"
#include "Trie.h"
using namespace std;

//Initialization of head node in Constructor
Trie::Trie() {
    rootNode = newNode();
};


//Destructor to deallocate memory
//Trie::~Trie() {
//    delete rootNode;
//};

// creating a new node
struct TrieNode* Trie::newNode() {
    struct TrieNode* node = new TrieNode;
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void Trie::insertNode(string dictionaryWord) {
    struct TrieNode* iteratorNode = rootNode;
    for (int i = 0; i < dictionaryWord.size(); i++) {
        int alphabetIndex = dictionaryWord[i];
        if (iteratorNode->children[alphabetIndex] == NULL)
            iteratorNode->children[alphabetIndex] = newNode();
        iteratorNode = iteratorNode->children[alphabetIndex];
    }
    // marking last character node as the end of word
    iteratorNode->isEndOfWord = true;
}



bool Trie::searchWord(string wordToSearch) {
    struct TrieNode* iteratorNode = rootNode;
    
    for (int i = 0; i < wordToSearch.size(); i++) {
        int alphabetIndex = wordToSearch[i];
        if (iteratorNode->children[alphabetIndex] == NULL) {
            return false;
        }
        iteratorNode = iteratorNode->children[alphabetIndex];
    }
    return (iteratorNode != NULL && iteratorNode->isEndOfWord);
}

map<int, int> Trie::findWordDetails(string wordToPrint) {
    struct TrieNode* iteratorNode = rootNode;
    
//    cout<<"word to search " << wordToPrint << endl;
    map<int,int> res;
    res.clear();
    
    for (int i = 0; i < wordToPrint.size(); i++) {
        int alphabetIndex = wordToPrint[i];
        iteratorNode = iteratorNode->children[alphabetIndex];
    }
    
    if (iteratorNode != NULL && iteratorNode->isEndOfWord) {
       res =  iteratorNode->fileWithCount;
        
//        map<int, int>::iterator it = fileWithCount.begin();
//        cout << "Details for the word " << wordToPrint << "are : " << endl;
//
//        while (it != fileWithCount.end()) {
//            cout << "Printing positions in file no. " << it->first << " with count = " << it->second << endl;
//            //vector<int> listOfPositions = it->second;
//            /*for (int i = 0; i < listOfPositions.size(); i++) {
//             cout << listOfPositions[i] << " ";
//             }*/
//            //cout << endl;
//            it++;
//        }

    }
    return res;
}

void Trie::insertPosition(string fileWord, int fileIndex, int position) {
    struct TrieNode* iteratorNode = rootNode;
    
    for (int i = 0; i < fileWord.size(); i++) {
        int alphabetIndex = fileWord[i];
        if (iteratorNode->children[alphabetIndex] == NULL) {
            return;
        }
        iteratorNode = iteratorNode->children[alphabetIndex];
    }
    if (iteratorNode->isEndOfWord) {
        /*if (iteratorNode->fileWithPosition.find(fileIndex) == iteratorNode->fileWithPosition.end()) {
         iteratorNode->fileWithPosition[fileIndex] = vector<int>();
         }
         iteratorNode->fileWithPosition[fileIndex].push_back(position);*/
    }
}

void Trie::incrementCount(string fileWord, int fileIndex) {
    
    //cout<<"inserting word: "<<fileWord <<" from file:"<< fileIndex << endl;
    struct TrieNode* iteratorNode = rootNode;
    
    for (int i = 0; i < fileWord.size(); i++) {
        int alphabetIndex = fileWord[i];
        if (iteratorNode->children[alphabetIndex] == NULL) {
            return;
        }
        iteratorNode = iteratorNode->children[alphabetIndex];
    }
    if (iteratorNode->isEndOfWord) {
//        cout<<fileWord<<" is inserted succesfully from file:"<< fileIndex << endl;
        if (iteratorNode->fileWithCount.find(fileIndex) == iteratorNode->fileWithCount.end()) {
            iteratorNode->fileWithCount[fileIndex] = 0;
        }
        iteratorNode->fileWithCount[fileIndex]++;
    }
}

void Trie::insertDictionaryWords(string pathOfDictionary, string type) {
    ifstream wordsFile;
    wordsFile.open(pathOfDictionary);
    string word, wordReversed;
    
    // reading the words in the file and inserting
    if (wordsFile.is_open()) {
        while (!wordsFile.eof()) {
            wordsFile >> word;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (type == "normal") {
                insertNode(word);
            }
            else {
                reverse(word.begin(), word.end());
                insertNode(word);
            }
        }
        /*if(type == "normal")
            cout << "\nNormal Trie has been created successfully" << endl;
        else
            cout << "\nReverse Trie has been created successfully" << endl;*/
    }
    else {
        cout << "File not found" << endl;
    }
    wordsFile.close();
}

void Trie::insertCountInFiles(map<int,string> files_index, string type) {
    // Now, traversing the files to check the positions of the dictionary words
    ifstream wordsFile;
    string word;
    
//    cout << "Traversing the files index" << endl;
    map<int, string>::iterator it = files_index.begin();
    while (it != files_index.end()) {
        int fileIndex = it->first;
        string filePath = it->second;
        wordsFile.open(filePath);
        if (wordsFile.is_open()) {
            while (!wordsFile.eof()) {
                wordsFile >> word;
                for (int i = 0; i < word.size(); i++) {
                    if (ispunct(word[i]) && word[i] != '\'' && word[i] != '&' && word[i] != '/')
                    {
                        word.erase(i--, 1);
                    }
                }
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                if (type == "normal") {
                    incrementCount(word, fileIndex);
                }
                else {
                    reverse(word.begin(), word.end());
                    incrementCount(word, fileIndex);
                }
            }
//            cout << "All word positions for file"  << fileIndex << " has been inserted" << endl;
        }
        wordsFile.close();
        it++;
    }
}

void Trie::findValidWordsHelper(TrieNode* node, string currWord, vector<string>& validWords) {
    if (node->isEndOfWord) {
        validWords.push_back(currWord);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            findValidWordsHelper(node->children[i], currWord + (char)i, validWords);
        }
    }
}

vector<string> Trie::findValidWords(string query) {
    vector<string> validWords;
    bool isPresent = true;
    
    struct TrieNode* iteratorNode = rootNode;
    
    for (int i = 0; i < query.size(); i++) {
        int alphabetIndex = query[i];
        if (iteratorNode->children[alphabetIndex] == NULL) {
            isPresent = false;
            break;
        }
        iteratorNode = iteratorNode->children[alphabetIndex];
    }
    
    if (isPresent)
        findValidWordsHelper(iteratorNode, query, validWords);
    
    return validWords;
}
