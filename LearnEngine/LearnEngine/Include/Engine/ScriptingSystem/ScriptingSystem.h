#ifndef __SCRIPRING_SYSTEM_H__
#define __SCRIPTING_SYSTEM_H__

#include <vector>
#include <queue>

#include <Engine\Util\ControlledSingleton.h>
#include <Engine\Component\Script\Script.h>

namespace Engine
{

// System responsible for maintaining Script components to trigger custom Entity behaviour.
class ScriptingSystem : public ControlledSingleton<ScriptingSystem>
{
    using StartCallback                                     = void(Script::*)();
    using StartCallbackQueue                                = std::queue<Script*>;

    using TickCallback                                      = void(Script::*)();
    using TickCallbackList                                  = std::vector<Script*>;

public:
    ScriptingSystem                                         ();
    ScriptingSystem                                         (const ScriptingSystem& rhs) = delete;
    ScriptingSystem                                         (ScriptingSystem&& rhs) = delete;

    ScriptingSystem                 operator=               (const ScriptingSystem& rhs) = delete;
    ScriptingSystem                 operator=               (ScriptingSystem&& rhs) = delete;

public:
    // Aggregator for whole iteration of the Scripting system.
    void                            Iterate                 ();

    // Register script to the Start queue.
    void                            RegisterStarter         (Script* script);

    // Register script for ticking.
    void                            RegisterTicker          (Script* script);

    // Unregister script from ticking.
    void                            UnregisterTicker        (Script* script);
    

protected:
    // Unwinding Start queue and calling all OnStart callbacks in it.
    void                            FlushStartQueue         ();

    // Trigger Tick callback on every ticking script.
    void                            TickAll                 ();

    static constexpr TickCallback   s_tick_callback_        = ScriptingSystemCallbackAttorney::s_standard_tick_callback;
    static constexpr StartCallback  s_start_callback_       = ScriptingSystemCallbackAttorney::s_standard_start_callback;

protected:
    StartCallbackQueue              start_queue_;
    TickCallbackList                ticking_scripts_;
};

} // namespace Engine

#endif