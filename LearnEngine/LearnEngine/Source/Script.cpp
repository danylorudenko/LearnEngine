#include "..\Include\Component\Script\Script.h"
#include "..\Include\ScriptingSystem\ScriptingSystem.h"

Script::Script() : Component(), enable_ticking_(false)
{

}

Script::Script(const Script& rhs) : enable_ticking_(rhs.enable_ticking_)
{

}

Script::Script(Script&& rhs) : enable_ticking_(rhs.enable_ticking_)
{
    rhs.enable_ticking_ = false;
}

Script& Script::operator=(const Script& rhs)
{
    return *this;
}

Script& Script::operator=(Script&& rhs)
{
    enable_ticking_ = rhs.enable_ticking_;
    rhs.enable_ticking_ = false;

    return *this;
}

void Script::RegisterInSystem()
{
    ScriptingSystem::Instance().RegisterTickCallback(this);
    OnRegistered(); 
}

void Script::UnregisterFromSystem()
{
    ScriptingSystem::Instance().UnregisterTickCallback(this);
    OnUnregistered();
}

void Script::SetTicking(bool value)
{
    enable_ticking_ = value;
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