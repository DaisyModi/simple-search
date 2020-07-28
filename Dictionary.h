#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Headers.h"
#include "Trie.h"

//using recursive_directory_iterator = boost::filesystem::recursive_directory_iterator; // mac
using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator; // WINDOWS

// Defining the PathHandling class
class Dictionary
{
private:
    // user getter setter here after defining tries as private attributes ???
    
public:
    Trie normalTrie;
    Trie reverseTrie;
    
    Dictionary(string wordsFilePath);
    ~Dictionary();
};

#endif
