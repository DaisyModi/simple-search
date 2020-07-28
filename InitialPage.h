#ifndef INTITIALPAGE_H
#define INTITIALPAGE_H

#include "Headers.h"
#include "Dictionary.h"

class InitialPage
{
public:
    InitialPage(Dictionary dictionary);
    void displayResult(map<int, int> res);
    ~InitialPage();
};

#endif
