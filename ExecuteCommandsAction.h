#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"  // تأكد من أن الكلاس Player موجود هنا
#include <vector>

class ExecuteCommandsAction : public Action
{
private:
    std::vector<std::string> commands;  // قائمة الأوامر المختارة

public:
    ExecuteCommandsAction(ApplicationManager* pApp);  // المُنشئ
    virtual void Execute();                           // تنفيذ الأوامر
    virtual void ReadActionParameters();
    virtual ~ExecuteCommandsAction();                 // المدمر
};