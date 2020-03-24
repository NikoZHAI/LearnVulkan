
#include "VkRenderer.h"
#include "Common/CreateVkAppInfo.h"

#include <cstdlib>
#include <iostream>

int main()
{
    try
	{
		VkApplicationInfo appInfo = CreateVkAppInfo( "test VkRenderer" );
		VkRenderer r( &appInfo );
    }
	catch (const std::exception& e)
	{
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

	return 0;
}
