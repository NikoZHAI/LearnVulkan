cmake_minimum_required(VERSION 3.02)

PROJECT(Tera C CXX)

Message(STATUS "------------------------------")
Message(STATUS "     Building Tera Library    ")

if(NOT (CMAKE_SIZEOF_VOID_P EQUAL 8))
    message( FATAL_ERROR "64-bit builds are mandatory for this framework" )
endif()

set(GLFW_PATH $ENV{GLFW_HOME})
set(POCO_PATH $ENV{POCO_HOME})


message(STATUS "GLFW_PATH: ${GLFW_PATH}")

# always
FIND_PACKAGE(Threads REQUIRED)
find_library(glfw3
    NAMES glfw3 HINTS ${GLFW_PATH}/lib
)
find_library(PocoFoundation
    NAMES PocoFoundation HINTS ${POCO_PATH}/lib
)
find_library(PocoUtil
    NAMES PocoUtil HINTS ${POCO_PATH}/lib
)


message(STATUS "POCO_PATH: ${POCO_PATH}")
message(STATUS "PocoFoundation: ${PocoFoundation}")
message(STATUS "PocoUtil: ${PocoUtil}")
message(STATUS "glfw3: ${glfw3}")


if(NOT MSVC)
	# set(CMAKE_C_FLAGS )
	set(CMAKE_C_FLAGS_DEBUG "-Og -D_DEBUG -g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	# set(CMAKE_CXX_FLAGS "-Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "-Og -D_DEBUG -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()


# glob sources
set(CMAKE_SOURCE_DIR ./src)
set(CORE_DIR ${CMAKE_SOURCE_DIR}/Core)
file(GLOB CORE_SOURCES ${CORE_DIR}/*.cpp ${CORE_DIR}/*.c ${CORE_DIR}/*.hpp ${CORE_DIR}/*.h)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# library name
set(library_name "tera")


# add Tera library
add_library(tera STATIC
    ${CORE_SOURCES}
)
set_target_properties(tera
    PROPERTIES LINKER_LANGUAGE CXX
)

target_link_libraries(tera PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}  # -lpthread -lm
    ${CMAKE_DL_LIBS} # for vulkan.c.o
    ${PLATFORM_LIBRARIES}
    ${glfw3}
    ${PocoFoundation}
    ${PocoUtil}
    X11
)

target_include_directories(tera
    PUBLIC ${GLFW_PATH}/include
    ${POCO_PATH}/include
    # ${POCO_PATH}/Foundation/include
    # ${POCO_PATH}/Util/include
)

# install rules
INSTALL(TARGETS tera
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

# install private headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/ # source directory
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/tera # target directory
    FILES_MATCHING # install only matched files
    PATTERN "*.h" PATTERN "*.hpp" # select header files
)

set_target_properties(tera PROPERTIES OUTPUT_NAME ${library_name})
message(STATUS "Tera library name: ${library_name}")


##########################################################################################
## Project Macros                                                                     ####
##########################################################################################
add_compile_definitions(
	POCO_STATIC
)
