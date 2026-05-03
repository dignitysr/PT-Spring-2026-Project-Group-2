#pragma once
#include "Action.h"
class SaveGridAction :
    public Action
{
private:
    string filename;

public: 
    //constructor
    SaveGridAction(ApplicationManager* pApp);
    //Reading file name
    virtual bool ReadActionParameters();
    //Executes the saving process
    virtual void Execute();
    // Destructor
    virtual ~SaveGridAction();
};

