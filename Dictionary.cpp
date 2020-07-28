#include "Headers.h"
#include "Dictionary.h"

Dictionary::Dictionary(string wordsFilePath) {
	cout << "Building tries.....wait for some time. " << endl;
    normalTrie.insertDictionaryWords(wordsFilePath,"normal");
    reverseTrie.insertDictionaryWords(wordsFilePath, "reverse");
}



Dictionary::~Dictionary() {
    
}
