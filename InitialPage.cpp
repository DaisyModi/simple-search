#include "Headers.h"
#include "InitialPage.h"
#include "QueryParser.h"
#include "PathHandling.h"
#include "QueryExecuter.h"
#include "Collation.h"



extern map<int, string> globalfileIndex;
extern int totalIndexedFiles;
extern Collation collation;

void InitialPage::displayResult(map<int, int> res){
	cout << "The final result of given query is: \n" << endl;
    
    int totalOccurences = 0;
    for(int i=0 ; i<totalIndexedFiles ; i++){
        cout<<"File : "<<globalfileIndex[i]<<"\t\tOccurence : "<< res[i] << endl;
        totalOccurences += res[i];
    }
    
    cout <<"\t\t\t\tTotal Occurences : "<<totalOccurences<<endl;
    
}


InitialPage::InitialPage(Dictionary dictionary) {
    
    
    string directoryPath;
    PathHandling pathHandler;
	int path_valid_flag = 0;
	do {
		if (path_valid_flag)
			cout << "You entered invalid path\n";
		cout << "\nGive the valid directory where you want to search: ";
		cin >> directoryPath;
		cin.ignore();
		path_valid_flag = 1;
	} while (!pathHandler.setCurrentPath(directoryPath));

	cout << "Starting indexing of files." << endl;
	pathHandler.buildFilesIndex();
    dictionary.normalTrie.insertCountInFiles(pathHandler.files_index, "normal");
    dictionary.reverseTrie.insertCountInFiles(pathHandler.files_index, "reverse");
    
    int option = 1;
    while (option != 3)
    {
        cout << "\n\nChoose an Option:" << endl;
        cout << "1. Autocomplete" << endl;
        cout << "2. Search" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your Choice : ";
        cin >> option;
        cin.ignore();
        if (cin.fail()|| option < 1 || option>3)
        {
            cout << "Invalid Input" << endl;
            continue;
        }
        switch (option)
        {
            case 1:
            {
                
                cout << "Enter the keyword  : ";
                string keyword;
                cin >> keyword;
                cin.ignore();
                vector<string>validWords =  dictionary.normalTrie.findValidWords(keyword);
                
                if(validWords.size() == 0){
                    cout << "No valid words start with the given keyword" <<endl;
                    break;
                }
                else{
                    cout << "Words which start with "<<keyword<<" are:"<<endl;
                    int totalWords = (int)validWords.size();
                    
                    int i, limit = 10;
                    for( i = 0; i < min(limit, (int)validWords.size()); i++){
                        cout<<i+1<<": "<<validWords[i]<<endl;
                    }
                    
                    totalWords -= 10;
                    limit += 10;
                    
                    int flag = 0;
                    while(totalWords > 0){
                        cout << "\nChoose an Option:" << endl;
                        cout << "1. See more valid words" << endl;
                        cout << "2. Go to main menu" << endl;
                        cout << "3. Exit" << endl;
                        cout << "Enter your Choice : ";
                        
                        int choice;
                        cin >> choice;
                        cin.ignore();
                        if(choice == 1){
                            for(; i < min(limit, (int)validWords.size() ); i++){
                                cout<<i+1<<": "<<validWords[i]<<endl;
                            }
                            totalWords -= 10;
                            limit+=10;
                        }
                        else if(choice == 2){
                            flag = 2;
                            break;
                        }
                        else{
                            flag = 3;
                            break;
                        }
                    }
                    
                    if(flag == 0){
                        cout << "No more valid words to show "<<endl;
                        option = 1;
                        break;
                    }
                    else if(flag == 2){
                        option = 1;
                        break;
                    }
                    else{
                        option = 3;
                        break;
                    }
                }
            }
            case 2:
            {
                cout << "\nEnter the query : " ;
                string query;
                getline(cin, query);
                
                QueryParser queryParser;
                if (queryParser.assignTagsToQuery(query)) {
                    
					if (queryParser.getTaggedQuery().size() > 1) {
						int collationType;
						cout << "\nChoose an Option:" << endl;
						cout << "1. Horizontal Collation" << endl;
						cout << "2. Vertical Collation" << endl;
						cout << "Enter your Choice : ";
						cin >> collationType;
						collation.setCollationType(collationType);
					}
					else
						collation.setCollationType(0);
					
                    QueryExecuter queryExecuter(queryParser.getTaggedQuery());
                    map<int, int > res = queryExecuter.executeQuery();
                    displayResult(res);
                }
                else {
                    cout << "You entered invalid query." << endl;
                }
				break;
            }
            case 3:
                
            default:
                break;
        }
    }
}

InitialPage::~InitialPage() {
    
}
