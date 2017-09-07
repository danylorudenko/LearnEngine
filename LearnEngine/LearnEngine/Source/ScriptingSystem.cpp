#include <algorithm>

#include <Engine\ScriptingSystem\ScriptingSystem.h>

namespace Engine
{

ScriptingSystem::ScriptingSystem()
{

}

void ScriptingSystem::Iterate()
{
    FlushStartQueue();
    TickAll();
}

void ScriptingSystem::TickAll()
{
    int count = static_cast<int>(ticking_scripts_.size());
    for (int i = 0; i < count; i++)
    {
        // Nice syntax.
        (ticking_scripts_[i]->*s_tick_callback_)();
    }
}

void ScriptingSystem::RegisterStarter(Script* script)
{
    start_queue_.push(script);
}

void ScriptingSystem::FlushStartQueue()
{
    while (!start_queue_.empty()) {
        auto starter = start_queue_.front();
        
        (starter->*s_start_callback_)();
        
        start_queue_.pop();
    }
}

void ScriptingSystem::RegisterTicker(Script* script)
{
    ticking_scripts_.push_back(script);
}

void ScriptingSystem::UnregisterTicker(Script* script)
{
    std::remove_if(ticking_scripts_.begin(), ticking_scripts_.end(), 
        [script](Script* candidate) {
        return candidate == script;
    });
}

} // namespace Engine