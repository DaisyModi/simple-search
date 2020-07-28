#include "Headers.h"
#include "Trie.h"
#include "Dictionary.h"
#include "InitialPage.h"

using namespace std;

//string wordsListPath = "/Users/jtayal/Desktop/words-original.txt";
string wordsListPath = "words.txt";
Dictionary dictionary(wordsListPath);


// /Users/jtayal/Desktop/text-files
int main() {
	
    InitialPage initialPage(dictionary);
    return 0;
}
