#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"
#include <vector>

class SelectCommandAction : public Action
{
private:
    std::vector<std::string> availableCommands;  
    std::vector<std::string> selectedCommands;   

public:
    SelectCommandAction(ApplicationManager* pApp);  
    virtual void Execute();                         
    virtual void ReadActionParameters();            
    virtual ~SelectCommandAction();                 
};