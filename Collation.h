//
//  Collation.hpp
//  Search_CPP1_5
//
//  Created by Jatin Tayal on 29/07/19.
//  Copyright © 2019 Adobe. All rights reserved.
//

#ifndef COLLATION_H
#define COLLATION_H

#include "Headers.h"
#include <stdio.h>

//1 - horizontal
//2- vertical

class Collation
{
private:
    int collationType;
public:
    void setCollationType(int type);
    int getCollationType();
    void printHorizontalCollation(map<int, int> result, string queryString);
    void printVerticalCollation(vector<map<int, int> > result, vector<string> tokens);
    int findWordsOccurenceInFile(int fileIndex, vector<map<int, int> > result, vector<string> tokens);

};


#endif /* Collation_hpp */
