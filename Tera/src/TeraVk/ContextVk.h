#pragma once
#ifndef TERA_CONTEXT_VK_INCLUDED
#define TERA_CONTEXT_VK_INCLUDED


#include <vulkan/vulkan_core.h>

#include <vector>

namespace tera
{


class ContextVk
{
public:
    /**
     * @brief Physical device information collection
     * 
     */
    class PhysicalDeviceInfo
    {
    public:
        VkPhysicalDeviceMemoryProperties        memoryProperties        = {};
        std::vector<VkQueueFamilyProperties>    queueProperties         = {};
        VkPhysicalDeviceFeatures                features10              = {};
        VkPhysicalDeviceVulkan11Features        features11              = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES };
        VkPhysicalDeviceVulkan12Features        features12              = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };

        VkPhysicalDeviceProperties              properties10            = {};
        VkPhysicalDeviceVulkan11Properties      properties11            = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES };
        VkPhysicalDeviceVulkan12Properties      properties12            = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES };
    };


    /**
     * @brief Vulkan queue wrapper
     * 
     */
    class Queue
    {
    public:
        uint32_t                                familyIndex             = ~0u;
        VkQueue                                 queue                   = VK_NULL_HANDLE;

    public:
        operator VkQueue() const                { return queue; }
        operator uint32_t() const               { return familyIndex; }
    };



public:
    ContextVk();
    ~ContextVk();

    bool init();
    void deinit();
    bool initInstance();
    bool initDevice();

    std::vector<int>                                getCompatibleDevices();
    std::vector<VkPhysicalDevice>                   getPhysicalDevices();
    std::vector<VkPhysicalDeviceGroupProperties>    getPhysicalDeviceGroups();
    std::vector<VkExtensionProperties>              getInstanceExtensions();
    std::vector<VkLayerProperties>                  getInstanceLayers();
    std::vector<VkExtensionProperties>              getDeviceExtensions(VkPhysicalDevice physicalDevice);
    
    bool hasMandatoryExtensions(VkPhysicalDevice physicalDevice, const ContextCreateInfo& info, bool bVerbose);
    bool setGTCQueueWithPresent(VkSurfaceKHR surface);
    uint32_t getQueueFamily(VkQueueFlags flagsSupported, VkQueueFlags flagsDisabled = 0, VkSurfaceKHR surface = VK_NULL_HANDLE);
    bool hasDeviceExtension(const char* name) const;


protected:
    void initDebugReport();

    VkResult fillFilteredNameArray(
        std::vector<const char*>&               used,
        const std::vector<VkLayerProperties>&   properties,
        const ContextCreateInfo::EntryArray&    requested
    );
    
    VkResult fillFilteredNameArray(
        std::vector<const char*>&                   used,
        const std::vector<VkExtensionProperties>&   properties,
        const ContextCreateInfo::EntryArray&        requested,
        std::vector<void*>&                         featureStructs
    );
    
    bool checkEntryArray(
        const std::vector<VkExtensionProperties>& properties,
        const ContextCreateInfo::EntryArray& requested,
        bool bVerbose
    );
    
    static void initPhysicalInfo(
        PhysicalDeviceInfo&     info,
        VkPhysicalDevice        physicalDevice, 
        uint32_t                versionMajor, 
        uint32_t                versionMinor
    );


public:
    VkInstance                                  m_instance              = VK_NULL_HANDLE;
    VkDevice                                    m_device                = VK_NULL_HANDLE;
    VkPhysicalDevice                            m_physicalDevice        = VK_NULL_HANDLE;
    PhysicalDeviceInfo                          m_physicalDeviceInfo    {};

    Queue                                       m_queueGTC              {}; // for Graphics/Compute/Transfer (must exist)
    Queue                                       m_queueT                {}; // for pure async Transfer Queue (can exist, only contains transfer nothing else)
    Queue                                       m_queueC                {}; // for async Compute (can exist, may contain other non-graphics support)


protected:
    std::vector<const char*>                    m_instanceLayersEnabled;
    std::vector<const char*>                    m_instanceExtensionsEnabled;
    std::vector<const char*>                    m_deviceExtensionsEnabled;
};

    
}


#endif
