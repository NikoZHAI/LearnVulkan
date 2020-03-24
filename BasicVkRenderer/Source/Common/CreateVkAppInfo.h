#pragma once
#ifndef CREATE_VK_APP_INFO_INCLUDED
#define CREATE_VK_APP_INFO_INCLUDED 1


#include <vulkan/vulkan.h>


VkApplicationInfo
CreateVkAppInfo(
    const char *app_name = "",
    uint32_t app_version = VK_MAKE_VERSION( 0, 1, 0 ),
    const char *engine_name = "",
    uint32_t engine_version = VK_MAKE_VERSION( 0, 1, 0 ),
    uint32_t vk_api_version = VK_API_VERSION_1_2
) {
    VkApplicationInfo info {};
    info.pApplicationName = app_name;
    info.applicationVersion = app_version;
    info.pEngineName = engine_name;
    info.engineVersion = engine_version;
    info.apiVersion = vk_api_version;
    return info;
}


#endif
