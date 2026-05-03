#pragma once
#include "Action.h"
#include <string>
using namespace std;

class LoadGridAction :
    public Action
{
private:
    string filename;
public:
    LoadGridAction(ApplicationManager* pApp);

    // Gets filename from user
    virtual bool ReadActionParameters();

    // Reads file and populates Grid
    virtual void Execute(); 

    virtual ~LoadGridAction();
};

