#pragma once
#ifndef VK_RENDERER_INCLUDED
#define VK_RENDERER_INCLUDED 1


#include <vulkan/vulkan.h>
#include <vector>


/**
 * @brief A basic implementation of a Vulkan-based Renderer
 */
class VkRenderer
{
public:
    // @constructor
    VkRenderer( const VkApplicationInfo *app_info = VK_NULL_HANDLE );

    // @destructor
    ~VkRenderer();

    // set the VkApplicationInfo of the Renderer
    // void SetVkApplicationInfo();


    /**
     * @brief Get the Instance object
     * 
     * @return VkInstance 
     */
    VkInstance GetInstance() const;

    
    /**
     * @brief Get the Gpu object
     * 
     * @return VkPhysicalDevice 
     */
    VkPhysicalDevice GetGpu() const;


    /**
     * @brief Get the Device object
     * 
     * @return VkDevice 
     */
    VkDevice GetDevice() const;


    /**
     * @brief Get the Gpu Props object
     * 
     * @return const VkPhysicalDeviceProperties* 
     */
    const VkPhysicalDeviceProperties* GetGpuProps() const;


    /**
     * @brief Number of Vulkan instance layers
     * 
     * @return std::size_t 
     */
    std::size_t VkLayerCount() const;
    

    /**
     * @brief Vulkan instance layer names
     * 
     * @return const char* 
     */
    const char* const* VkLayerNames() const;


    /**
     * @brief Number of Vulkan extensions
     * 
     * @return std::size_t 
     */
    std::size_t VkExtensionCount() const;


    /**
     * @brief Vulkan instance layer extension names
     * 
     * @return const char* 
     */
    const char* const * VkExtensionNames() const;


protected:

    void InitInstance( const VkApplicationInfo *app_info = VK_NULL_HANDLE );
    void DestroyInstance();

    void InitDevice();
    void DestroyDevice();

    // vulkan debug info
    void SetupDebug();
    void InitDebugInfo();
    void DestroyDebugInfo();


    VkInstance                  m_instance                  = VK_NULL_HANDLE;
    VkPhysicalDevice            m_gpu                       = VK_NULL_HANDLE;
    VkDevice                    m_device                    = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties  m_gpu_props                 = {};

    uint32_t                    m_graphics_family_index     = 0u;

    std::vector<const char*>    m_instance_layers;
    std::vector<const char*>    m_instance_extensions;
    std::vector<const char*>    m_device_extensions;

    // debug info
    VkDebugReportCallbackEXT                m_debug_report                          = VK_NULL_HANDLE;
    VkDebugReportCallbackCreateInfoEXT      m_debug_callback_create_info            = {};
    PFN_vkCreateDebugReportCallbackEXT      m_fvkCreateDebugReportCallbackEXT       = nullptr;
    PFN_vkDestroyDebugReportCallbackEXT     m_fvkDestroyDebugReportCallbackEXT      = nullptr;
};


#endif
