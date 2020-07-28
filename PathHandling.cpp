#include "Headers.h"
#include "PathHandling.h"

using namespace std;
//namespace fs = boost::filesystem;
namespace fs = std::experimental::filesystem;

map<int, string> globalfileIndex;


int totalIndexedFiles;

// default constructor
PathHandling::PathHandling() {
};

// default destructor
PathHandling::~PathHandling() {
    
};

bool PathHandling::checkPathValidity(string path) {
    bool validity = false;
    try {
        if (fs::exists(path))
            validity = true;
    }
    catch (fs::filesystem_error& e) {
        cout << "Error: " << e.code().message() << endl;
    }
    return path_is_valid = validity;
}

bool PathHandling::setCurrentPath(string path) {
    if (checkPathValidity(path)) {
        current_path = path;
		return true;
    }
	else {
		return false;
	}
}

void PathHandling::printFilesIndex() {
    if (files_index.size() == 0) {
        cout << "No files have been indexed yet." << endl;
        return;
    }
    cout << "Files which are indexed are :" << endl;
    map<int, string>::iterator it = files_index.begin();
    while (it != files_index.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }
}

void PathHandling::buildFilesIndex() {
//    cout << current_path << endl;
    files_index.clear();
    if (path_is_valid == true)
    {
        int index_num = 0;
        try
        {
            if (fs::is_regular_file(current_path))
            {
                files_index[index_num++] = current_path;
                cout << current_path << "has been indexed." << endl;
                return;
            }
            for (const auto& dirEntry : recursive_directory_iterator(current_path)) {
                if (fs::is_regular_file(dirEntry)) {
                    cout << dirEntry.path().string() << endl;
                    files_index[index_num++] = dirEntry.path().string();
                }
            }
            totalIndexedFiles = index_num;
            globalfileIndex = files_index;
        }
        catch (const std::system_error& e) {
            std::cout << "System Error :" << e.code() << " Message:" << e.what() << '\n';
        }
        catch (fs::filesystem_error& e)
        {
            cout << "Error: " << e.code().message() << endl;
        }
    }
}
