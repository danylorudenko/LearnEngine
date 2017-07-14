#include <algorithm>
#include "..\Include\ScriptingSystem\ScriptingSystem.h"

ScriptingSystem::ScriptingSystem()
{

}

void ScriptingSystem::Iterate()
{
    TickAll();
}

void ScriptingSystem::TickAll()
{
    int count = ticking_scripts_.size();
    for (int i = 0; i < count; i++)
    {
        // Nice syntax.
        (ticking_scripts_[i]->*s_tick_callback_)();
    }
}

void ScriptingSystem::RegisterTickCallback(Script* script)
{
    ticking_scripts_.push_back(script);
}

void ScriptingSystem::UnregisterTickCallback(Script* script)
{
    std::remove_if(ticking_scripts_.begin(), ticking_scripts_.end(), 
        [script](Script* candidate) {
        return candidate == script;
    });
}