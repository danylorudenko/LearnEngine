#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "..\Component.h"

class ScriptingSystem;

// Base class for all scripts in the application.
// Contains callbacks which can be called by the Scripting system.
// Some callbacks must be explicitly told to be called by the Scripting system.
// 
// All callbacks are empy and to be implemented by the inheriting script.
class Script : public Component
{
public:
    Script                                                  ();
    Script                                                  (const Script& rhs);
    Script                                                  (Script&& rhs);

    Script&                     operator=                   (const Script& rhs);
    Script&                     operator=                   (Script&& rhs);

    // Explicit adding OnStart callback to the Scripting system START queue.
    // OnStart will be called on the next iteration.
    void                        RegisterStart               ();

    // Enable\disable ticking of the scirpt.
    // When enabled Tick() will be called every Scripting system iteration.
    void                        SetTicking                  (bool value);

protected:
    // Performs proper registration of script in the scripting system.
    // Registration is performed right after script is attached to the Entity as a component.
    virtual void                RegisterInSystem            () override;

    // Performs proper removal of script from the scripting system.
    // Removals is performed when the Script is removed from Entity manually or when Entity is destroyed.
    virtual void                UnregisterFromSystem        () override;

    // This callback can be called once in the start of Scripting system iteration.
    // To be called this callback must be registered via Script::RegisterStart().
    virtual void                OnStart                     () { };

    // This callback is called right after Script was registered in Scripting system.
    virtual void                OnRegistered                () { };

    // This callback is called right after Script was removed from Scripting system.
    virtual void                OnUnregistered              () { };

    // This callback can be called every Scripting system iteraction, if enabled.
    virtual void                Tick                        () { };

    virtual                     ~Script() = 0 { };

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

#endif