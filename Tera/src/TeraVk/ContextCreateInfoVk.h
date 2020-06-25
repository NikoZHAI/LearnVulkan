#pragma once
#ifndef TERA_CONTEXT_CREATEINFO_VK_INCLUDED
#define TERA_CONTEXT_CREATEINFO_VK_INCLUDED


#include <cstdint>
#include <string>
#include <vector>


class ContextCreateInfoVk
{
public:
    class Entry
    {
    public:
        bool            optional    = false;
        uint32_t        version     = 0;
        void*           pFeature    = nullptr;
        std::string     name        = "";
    };

    using EntryArr = std::vector<Entry>;


public:
    bool        useDeviceGroups             = false;    // use device groups
    bool        vkUseRBA                    = false;    // flag for Vulkan's Robust Buffer Access, disabled by default due to performance issues
    bool        verboseCompatibleDevices    = true;     // flag for printing vulkan-compatible devices info
    bool        verboseUsed                 = true;     // flag for printing used vulkan layers
    bool        verboseAvailable            = true;     // flag for printing available vulkan layers
    uint32_t    vkCompatibleDeviceIndex     = 0u;       // which compatible device or device group to pick, only used by All-in-one Context::init(...)
    int         apiVersionMajor             = 1;
    int         apiVersionMinor             = 1;

    // instance properties
    std::string engineName                  = "";
    std::string appName                     = "";

    EntryArr    instanceLayers;
    EntryArr    instanceExtensions;
    EntryArr    deviceExtensions;
    void*       deviceCreateInfoExt         = nullptr;


public:
    ContextCreateInfoVk(const std::string& engineName_, const std::string& appName_, bool useValidation = true);
    void setVersion(int major, int minor);
    void addInstanceLayer(const std::string& name, bool optional = false);
    void addInstanceExtension(const std::string& name, bool optional = false);
    void addDeviceExtension(const std::string& name, bool optional = false, void* pFeature = nullptr, uint32_t version = 0);
    void removeInstanceLayer(const std::string& name);
    void removeInstanceExtension(const std::string& name);
    void removeDeviceExtension(const std::string& name);
};



#endif
