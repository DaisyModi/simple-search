#ifndef PATHHANDLING_H
#define PATHHANDLING_H

#include "Headers.h"
using namespace std;

//using recursive_directory_iterator = boost::filesystem::recursive_directory_iterator; // mac
using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator; // WINDOWS

// Defining the PathHandling class
class PathHandling
{
private:
    string current_path;   // path storing the files on which searching is to be done
    bool path_is_valid;    // true if path given by the user is valid
    
public:
    map<int, string> files_index; // indexing of the files
    
    PathHandling();
    ~PathHandling();
    
    bool setCurrentPath(string path);
    void buildFilesIndex();
    bool checkPathValidity(string path);
    void printFilesIndex();
};

#endif
