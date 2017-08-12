#include "..\Include\Component\Script\Script.h"
#include "..\Include\ScriptingSystem\ScriptingSystem.h"

Script::Script() : Component(), is_ticking_(false)
{

}

void Script::SetTicking(bool value)
{
    is_ticking_ = value;
    if (is_ticking_) {
        ScriptingSystem::Instance().RegisterTicker(this);
    }
    else {
        ScriptingSystem::Instance().UnregisterTicker(this);
    }
}

void Script::RegisterStart()
{
    ScriptingSystem::Instance().RegisterStarter(this);
}