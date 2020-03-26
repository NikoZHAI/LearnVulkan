/// @file Implementation of VkRenderer


#include "VkRenderer.h"
#include "Common/HandleVkError.h"
#include "Common/ErrMsg.h"

#include <vulkan/vulkan.h>

#include <vector>
#include <string>
#include <iostream>
#include <sstream>


#if defined( _WIN32 )
    #include <windows.h>    // MessageBox()
#endif


/**
 * @brief Construct a new Vk Renderer:: Vk Renderer object
 * 
 */
VkRenderer::VkRenderer( const VkApplicationInfo *app_info )
{
    SetupDebug();
    InitInstance( app_info );
    InitDebugInfo();
    InitDevice();
}


/**
 * @brief Destroy the Vk Renderer:: Vk Renderer object
 * 
 */
VkRenderer::~VkRenderer()
{
    DestroyDevice();
    DestroyDebugInfo();
    DestroyInstance();
}


/////////////////////////////////////////////
//          getters and setters          ////
/////////////////////////////////////////////

/**
 * @brief Get the Instance object
 * 
 * @return VkInstance 
 */
VkInstance VkRenderer::GetInstance() const
{ return m_instance; }


/**
 * @brief Get the Gpu object
 * 
 * @return VkPhysicalDevice 
 */
VkPhysicalDevice VkRenderer::GetGpu() const
{ return m_gpu; }


/**
 * @brief Get the Device object
 * 
 * @return VkDevice 
 */
VkDevice VkRenderer::GetDevice() const
{ return m_device; }


/**
 * @brief Get the Gpu Props object
 * 
 * @return const VkPhysicalDeviceProperties* 
 */
const VkPhysicalDeviceProperties* VkRenderer::GetGpuProps() const
{ return &m_gpu_props;}


/**
 * @brief Number of Vulkan instance layers
 * 
 * @return std::size_t 
 */
std::size_t VkRenderer::VkLayerCount() const
{ return m_instance_layers.size(); }


/**
 * @brief Vulkan instance layer names
 * 
 * @return const char* 
 */
const char* const* VkRenderer::VkLayerNames() const
{ return m_instance_layers.empty()? nullptr : m_instance_layers.data(); }


/**
 * @brief Number of Vulkan extensions
 * 
 * @return std::size_t 
 */
std::size_t VkRenderer::VkExtensionCount() const
{ return m_instance_layers.size(); }


/**
 * @brief Vulkan instance layer extension names
 * 
 * @return const char* 
 */
const char* const * VkRenderer::VkExtensionNames() const
{ return m_instance_extensions.empty()? nullptr : m_instance_extensions.data(); }



/////////////////////////////////////////////
//            Renderer Instance          ////
/////////////////////////////////////////////


/**
 * @brief Initialize a Vulkan instance associated with this VkRenderer
 * 
 */
void VkRenderer::InitInstance( const VkApplicationInfo *app_info )
{
    VkInstanceCreateInfo instance_create_info {};
    instance_create_info.sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pApplicationInfo           = app_info;
    instance_create_info.enabledLayerCount          = this->VkLayerCount();
    instance_create_info.ppEnabledLayerNames        = this->VkLayerNames();
    instance_create_info.enabledExtensionCount      = this->VkExtensionCount();
    instance_create_info.ppEnabledExtensionNames    = this->VkExtensionNames();

    // pNext points to instance
    instance_create_info.pNext                      = &m_debug_callback_create_info;

    HandleVkError( vkCreateInstance( &instance_create_info, nullptr, &m_instance ) );
}


/**
 * @brief Destroy initiated Vulkan instances
 * 
 */
void VkRenderer::DestroyInstance()
{
    vkDestroyInstance( m_instance, nullptr );
    m_instance = VK_NULL_HANDLE;
}


/**
 * @brief Initiate Vulkan devices
 * 
 */
void VkRenderer::InitDevice()
{
    // Fetch and enumerate gpu information
    {
        uint32_t gpu_count = 0u;
        vkEnumeratePhysicalDevices( m_instance, &gpu_count, nullptr );
        if ( !gpu_count )
        {
            ErrMsg( "Fatal: No Vulkan compatible device found" );
        }

        std::vector<VkPhysicalDevice> gpu_list( gpu_count );
        vkEnumeratePhysicalDevices( m_instance, &gpu_count, gpu_list.data() );
        m_gpu = gpu_list.front();
        vkGetPhysicalDeviceProperties( m_gpu, &m_gpu_props );
    }

    // Query device Families, find the best graphic device
    // TODO:
    //      + Add multi-device support
    //      + If have multiple devices, sort the gpu list by their computational power
    {
        uint32_t family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties( m_gpu, &family_count, nullptr );
        std::vector<VkQueueFamilyProperties> family_property_list( family_count );
        vkGetPhysicalDeviceQueueFamilyProperties( m_gpu, &family_count, family_property_list.data() );

        bool found = false;
        for ( uint32_t i=0u; i<family_count; ++i )
        {
            if ( family_property_list[i].queueFlags & VK_QUEUE_GRAPHICS_BIT )
            {
                found = true;
                m_graphics_family_index = i;
                break;
            }
        }
        if ( !found )
            ErrMsg( "Fatal: No graphic device found" );
    }

    // Initiate, enumerate and fetch Vulkan instance layer information
    {
        uint32_t layer_count = 0u;
        vkEnumerateInstanceLayerProperties( &layer_count, nullptr );
        std::vector<VkLayerProperties> layer_props_list( layer_count );
        vkEnumerateInstanceLayerProperties( &layer_count, layer_props_list.data() );
        
        // TODO use a logger
        std::cout << "Device Layers: \n";
        for ( auto &&layer : layer_props_list )
        {
            std::cout << "  " << layer.layerName << "\t\t | " << layer.description << std::endl;
        }
        std::cout << std::endl;
    }

    // Initiate, enumerate and fetch Vulkan device layer information
    {
        uint32_t layer_count = 0u;
        vkEnumerateDeviceLayerProperties( m_gpu, &layer_count, nullptr );
        std::vector<VkLayerProperties> layer_props_list( layer_count );
        vkEnumerateDeviceLayerProperties( m_gpu, &layer_count, layer_props_list.data() );
        std::cout << "Device Layer: \n";
        for ( auto &&layer : layer_props_list )
        {
            std::cout << "  " << layer.layerName << "\t\t | " << layer.description << std::endl;
        }
        std::cout << std::endl;
    }

    // Load coefficients of devices
    // TODO:
    //      + Add multiple device support
    float queue_priorities[] { 1.f };

    // Assign create info for Vulkan device queues
    // TODO:
    //      + Add multiple device support
    VkDeviceQueueCreateInfo device_queue_create_info {};
    device_queue_create_info.sType              = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    device_queue_create_info.queueFamilyIndex   = m_graphics_family_index;
    device_queue_create_info.queueCount         = 1u;
    device_queue_create_info.pQueuePriorities   = queue_priorities;

    // Assign create info for VkRenderer visible devices
    VkDeviceCreateInfo device_create_info {};
    device_create_info.sType                    = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount     = 1u;
    device_create_info.pQueueCreateInfos        = &device_queue_create_info;
//  device_create_info.enabledLayerCount        = m_device_layers.size();
//  device_create_info.ppEnabledLayerNames      = m_device_layers.data();
    device_create_info.enabledExtensionCount    = m_device_extensions.size();
    device_create_info.ppEnabledExtensionNames  = m_device_extensions.data();

    // Finally create Vulkan devices for VkRenderer
    HandleVkError( vkCreateDevice( m_gpu, &device_create_info, nullptr, &m_device ) );
}


/**
 * @brief Destroy Vulkan devices
 * 
 */
void VkRenderer::DestroyDevice()
{
    vkDestroyDevice( m_device, nullptr );
    m_device = VK_NULL_HANDLE;
}


/**
 * @brief The Vulkan debug info callback
 * 
 */
VKAPI_ATTR VkBool32 VKAPI_CALL
VulkanDebugCallback(
	VkDebugReportFlagsEXT		flags,
	VkDebugReportObjectTypeEXT	obj_type,
	uint64_t					src_obj,
	size_t						location,
	int32_t						msg_code,
	const char *				layer_prefix,
	const char *				msg,
	void *						user_data
	)
{
	std::ostringstream stream;
	stream << "VKDBG: ";
	if( flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT ) {
		stream << "INFO: ";
	}
	if( flags & VK_DEBUG_REPORT_WARNING_BIT_EXT ) {
		stream << "WARNING: ";
	}
	if( flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT ) {
		stream << "PERFORMANCE: ";
	}
	if( flags & VK_DEBUG_REPORT_ERROR_BIT_EXT ) {
		stream << "ERROR: ";
	}
	if( flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT ) {
		stream << "DEBUG: ";
	}
	stream << "@[" << layer_prefix << "]: ";
	stream << msg << std::endl;
	std::cout << stream.str();

#if defined( _WIN32 )
	if( flags & VK_DEBUG_REPORT_ERROR_BIT_EXT ) {
		MessageBox( nullptr, stream.str().c_str(), "Vulkan Error!", 0 );
	}
#endif

	return false;
}


/**
 * @brief Setup vulkan debug info
 * 
 */
void VkRenderer::SetupDebug()
{
    m_debug_callback_create_info.sType              = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    m_debug_callback_create_info.pfnCallback        = VulkanDebugCallback;
    m_debug_callback_create_info.flags              = \
//      VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
        VK_DEBUG_REPORT_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_ERROR_BIT_EXT |
//      VK_DEBUG_REPORT_DEBUG_BIT_EXT |
        0;
    
    m_instance_layers.push_back( "VK_LAYER_LUNARG_standard_validation" );
	/*
	m_instance_layers.push_back( "VK_LAYER_LUNARG_threading" );
	m_instance_layers.push_back( "VK_LAYER_GOOGLE_threading" );
	m_instance_layers.push_back( "VK_LAYER_LUNARG_draw_state" );
	m_instance_layers.push_back( "VK_LAYER_LUNARG_image" );
	m_instance_layers.push_back( "VK_LAYER_LUNARG_mem_tracker" );
	m_instance_layers.push_back( "VK_LAYER_LUNARG_object_tracker" );
	m_instance_layers.push_back( "VK_LAYER_LUNARG_param_checker" );
	*/
	m_instance_extensions.push_back( VK_EXT_DEBUG_REPORT_EXTENSION_NAME );

	/*
    m_device_layers.push_back( "VK_LAYER_LUNARG_threading" );
	m_device_layers.push_back( "VK_LAYER_GOOGLE_threading" );
	m_device_layers.push_back( "VK_LAYER_LUNARG_draw_state" );
	m_device_layers.push_back( "VK_LAYER_LUNARG_image" );
	m_device_layers.push_back( "VK_LAYER_LUNARG_mem_tracker" );
	m_device_layers.push_back( "VK_LAYER_LUNARG_object_tracker" );
	m_device_layers.push_back( "VK_LAYER_LUNARG_param_checker" );
	*/
}


/**
 * @brief Initialize Vulkan debug info
 * 
 */
void VkRenderer::InitDebugInfo()
{
    // fetch function pointers
	m_fvkCreateDebugReportCallbackEXT	= (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr( m_instance, "vkCreateDebugReportCallbackEXT" );
	m_fvkDestroyDebugReportCallbackEXT	= (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr( m_instance, "vkDestroyDebugReportCallbackEXT" );

    if ( nullptr == m_fvkCreateDebugReportCallbackEXT || nullptr == m_fvkDestroyDebugReportCallbackEXT )
        ErrMsg( "Vulkan Runtime Error: Unable to fetch debug function pointers." );
    
    m_fvkCreateDebugReportCallbackEXT( m_instance, &m_debug_callback_create_info, nullptr, &m_debug_report );
}


/**
 * @brief Destroy Vulkan debug info
 * 
 */
void VkRenderer::DestroyDebugInfo()
{
    m_fvkDestroyDebugReportCallbackEXT( m_instance, m_debug_report, nullptr );
    m_debug_report = VK_NULL_HANDLE;
}
