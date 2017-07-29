#include "..\Include\Component\Script\Script.h"
#include "..\Include\ScriptingSystem\ScriptingSystem.h"

Script::Script() : Component(), is_ticking_(false)
{

}

Script::Script(const Script& rhs) : is_ticking_(rhs.is_ticking_)
{

}

Script::Script(Script&& rhs) : is_ticking_(rhs.is_ticking_)
{
    rhs.is_ticking_ = false;
}

Script& Script::operator=(const Script& rhs)
{
    return *this;
}

Script& Script::operator=(Script&& rhs)
{
    is_ticking_ = rhs.is_ticking_;
    rhs.is_ticking_ = false;

    return *this;
}

void Script::RegisterInSystem()
{
    OnRegistered(); 
}

void Script::UnregisterFromSystem()
{
    OnUnregistered();
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

void Script::OnRegistered()
{
    // Is up to inheriting users to implement it.
}

void Script::OnUnregistered()
{
    // Is up to inheriting users to implement it.
}

void Script::Tick()
{
    // Is up to inheriting users to implement it.
}