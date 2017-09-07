#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include <Engine\Component\Component.h>
#include <Engine\Component\ComponentFactory.h>

namespace Engine
{

class ScriptingSystem;

// Base class for all scripts in the application.
// Contains callbacks which can be called by the Scripting system.
// Some callbacks must be explicitly told to be called by the Scripting system.
// 
// All callbacks are empy and to be implemented by the inheriting script.
class Script : public Component
{
public:
    Script                                                  (Entity* owner);
    Script                                                  (const Script& rhs) = delete;
    Script                                                  (Script&& rhs) = delete;

    Script&                     operator=                   (const Script& rhs) = delete;
    Script&                     operator=                   (Script&& rhs) = delete;

    // Explicit adding OnStart callback to the Scripting system START queue.
    // OnStart will be called on the next iteration.
    void                        RegisterStart               ();

    // Enable\disable ticking of the scirpt.
    // When enabled Tick() will be called every Scripting system iteration.
    void                        SetTicking                  (bool value);

protected:
    // This callback can be called once in the start of Scripting system iteration.
    // To be called this callback must be registered via Script::RegisterStart().
    virtual void                OnStart                     () { };

    // This callback can be called every Scripting system iteraction, if enabled.
    virtual void                Tick                        () { };

    virtual                     ~Script() = 0;

protected:
    bool                        is_ticking_;

    friend class ScriptingSystemCallbackAttorney;
};

class ScriptingSystemCallbackAttorney
{
    using ScriptingSystemTickCallback                                           = void(Script::*)();
    using ScriptingSystemStartCallback                                          = void(Script::*)();

    static constexpr ScriptingSystemTickCallback    s_standard_tick_callback    = &Script::Tick;
    static constexpr ScriptingSystemStartCallback   s_standard_start_callback   = &Script::OnStart;

    friend ScriptingSystem;
};

} // namespace Engine

#endif