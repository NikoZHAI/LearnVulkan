#include "HandleVkError.h"
#include "ErrMsg.h"

#include <vulkan/vulkan.h>

#include <iostream>
#include <cassert>
#include <sstream>


/**
 * @brief Print out readable Vulkan error type
 * 
 * @param result Result of any Vulkan throwable methods
 */
void HandleVkError( VkResult result )
{
	if( result < 0 )
		return;

	std::stringstream msg{ "Vulkan runtime error: \n\t" };

	switch( result )
	{
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		msg << "VK_ERROR_OUT_OF_HOST_MEMORY" << std::endl;
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		msg << "VK_ERROR_OUT_OF_DEVICE_MEMORY" << std::endl;
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		msg << "VK_ERROR_INITIALIZATION_FAILED" << std::endl;
		break;
	case VK_ERROR_DEVICE_LOST:
		msg << "VK_ERROR_DEVICE_LOST" << std::endl;
		break;
	case VK_ERROR_MEMORY_MAP_FAILED:
		msg << "VK_ERROR_MEMORY_MAP_FAILED" << std::endl;
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		msg << "VK_ERROR_LAYER_NOT_PRESENT" << std::endl;
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		msg << "VK_ERROR_EXTENSION_NOT_PRESENT" << std::endl;
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		msg << "VK_ERROR_FEATURE_NOT_PRESENT" << std::endl;
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		msg << "VK_ERROR_INCOMPATIBLE_DRIVER" << std::endl;
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		msg << "VK_ERROR_TOO_MANY_OBJECTS" << std::endl;
		break;
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		msg << "VK_ERROR_FORMAT_NOT_SUPPORTED" << std::endl;
		break;
	case VK_ERROR_SURFACE_LOST_KHR:
		msg << "VK_ERROR_SURFACE_LOST_KHR" << std::endl;
		break;
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		msg << "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR" << std::endl;
		break;
	case VK_SUBOPTIMAL_KHR:
		msg << "VK_SUBOPTIMAL_KHR" << std::endl;
		break;
	case VK_ERROR_OUT_OF_DATE_KHR:
		msg << "VK_ERROR_OUT_OF_DATE_KHR" << std::endl;
		break;
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		msg << "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR" << std::endl;
		break;
	case VK_ERROR_VALIDATION_FAILED_EXT:
		msg << "VK_ERROR_VALIDATION_FAILED_EXT" << std::endl;
		break;
	default:
		break;
	}

	// throw
	ErrMsg( msg.str() );
}
