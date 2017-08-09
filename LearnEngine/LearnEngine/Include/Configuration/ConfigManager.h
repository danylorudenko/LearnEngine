#ifndef __CONFIG_MANAGER_H__
#define __CONFIG_MANAGER_H__

#include "..\Util\ControlledSingleton.h"

enum class RendererType {
    Forward,
    Deferred
};

class ConfigManager : ControlledSingleton<ConfigManager>
{
public:
    void            SetDefaultRenderer          (RendererType type);
    void            SetGLVersion                (const char* version_string);
};

#endif