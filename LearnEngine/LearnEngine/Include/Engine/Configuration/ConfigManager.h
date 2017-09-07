#ifndef __CONFIG_MANAGER_H__
#define __CONFIG_MANAGER_H__

#include <string>
#include <rapidjson\fwd.h>
#include <Engine\Util\ControlledSingleton.h>

namespace Engine
{

class ConfigManager : ControlledSingleton<ConfigManager>
{
public:
    ConfigManager                                       (const ConfigManager& rhs) = delete;
    ConfigManager                                       (ConfigManager&& rhs) = delete;
    ConfigManager&          operator=                   (const ConfigManager& rhs) = delete;
    ConfigManager&          operator=                   (ConfigManager&& rhs) = delete;

    void                    Open                        ();
    void                    Save                        ();
    
    std::string             GetMainConfigValue          (const char* key);
    std::string             SetMainConfigValue          (const char* key, const char* value);

    std::string             GetUserConfigValue          (const char* key);
    std::string             SetUserConfigValue          (const char* key, const char* value);
    

protected:
    ConfigManager                                       (const char* main_config_file_name);

    
protected:
    const std::string&      main_config_file_;

};

} // namespace Engine

#endif