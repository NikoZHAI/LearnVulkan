/// @file Implementation of VkRenderer


#include "VkRenderer.h"
#include "Common/HandleVkError.h"
#include "Common/ErrMsg.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>


#if defined( _WIN32 )
    #include <windows.h>    // for MessageBox()
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


void VkRenderer::DestroyInstance()
{
    vkDestroyInstance( m_instance, nullptr );
    m_instance = nullptr;
}



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
    _device_layers.push_back( "VK_LAYER_LUNARG_threading" );
	_device_layers.push_back( "VK_LAYER_GOOGLE_threading" );
	_device_layers.push_back( "VK_LAYER_LUNARG_draw_state" );
	_device_layers.push_back( "VK_LAYER_LUNARG_image" );
	_device_layers.push_back( "VK_LAYER_LUNARG_mem_tracker" );
	_device_layers.push_back( "VK_LAYER_LUNARG_object_tracker" );
	_device_layers.push_back( "VK_LAYER_LUNARG_param_checker" );
	*/
}
