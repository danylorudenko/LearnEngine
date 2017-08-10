#include "..\Include\Configuration\ConfigManager.h"

ConfigManager::ConfigManager(const char* main_config_file_name) :
    main_config_file_(main_config_file_)
{

}

void ConfigManager::Open()
{
}

void ConfigManager::Save()
{
}

std::string ConfigManager::GetMainConfigValue(const char * key)
{
    return std::string();
}

std::string ConfigManager::SetMainConfigValue(const char * key, const char * value)
{
    return std::string();
}

std::string ConfigManager::GetUserConfigValue(const char * key)
{
    return std::string();
}

std::string ConfigManager::SetUserConfigValue(const char * key, const char * value)
{
    return std::string();
}
