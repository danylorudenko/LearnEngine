#ifndef __SCRIPRING_SYSTEM_H__
#define __SCRIPTING_SYSTEM_H__

#include <vector>

#include "..\Util\Singletone.h"
#include "..\Component\Script\Script.h"

class ScriptingSystem : public Singletone<ScriptingSystem>
{
    using TickCallback                                  = void(Script::*)();
    using TickCallbackList                              = std::vector<Script*>;

public:
    ScriptingSystem                                     ();
    ScriptingSystem                                     (const ScriptingSystem& rhs) = delete;
    ScriptingSystem                                     (ScriptingSystem&& rhs) = delete;

    ScriptingSystem             operator=               (const ScriptingSystem& rhs) = delete;
    ScriptingSystem             operator=               (ScriptingSystem&& rhs) = delete;

public:
    void                        Iterate                 ();

    void                        RegisterTickCallback    (Script* script);
    void                        UnregisterTickCallback  (Script* script);
    

protected:
    void                        TickAll                 ();

protected:
    TickCallbackList            ticking_scripts_;
};

#endif