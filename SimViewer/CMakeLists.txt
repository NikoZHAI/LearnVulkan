cmake_minimum_required(VERSION 3.02)

PROJECT(SimViewer C CXX)

Message(STATUS "------------------------------")
Message(STATUS "      Building SimViewer      ")


set(GLFW_PATH $ENV{GLFW_HOME})
set(POCO_PATH $ENV{POCO_HOME})

# always
FIND_PACKAGE(Threads REQUIRED)

find_library(glfw3 NAMES
    glfw3 HINTS ${GLFW_PATH}/lib
)
find_library(PocoFoundation
    NAMES PocoFoundation HINTS ${POCO_PATH}/lib
)
find_library(PocoUtil
    NAMES PocoUtil HINTS ${POCO_PATH}/lib
)
find_library(tera
    NAMES tera HINTS ${TERA_HOME}/lib
)


message(STATUS "tera: ${tera}")
message(STATUS "PocoFoundation: ${PocoFoundation}")
message(STATUS "PocoUtil: ${PocoUtil}")
message(STATUS "glfw3: ${glfw3}")


if(NOT MSVC)
	# set(CMAKE_C_FLAGS "-Wall")
	set(CMAKE_C_FLAGS_DEBUG "-Og -D_DEBUG -g")
	set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
	# set(CMAKE_CXX_FLAGS "-Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "-Og -D_DEBUG -g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

if(NOT (CMAKE_SIZEOF_VOID_P EQUAL 8))
    message( FATAL_ERROR "64-bit builds are mandatory for this framework" )
endif()

# glob sources
set(SRC_DIR src)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)
file(GLOB_RECURSE HEADERS ${SRC_DIR}/*.hpp ${SRC_DIR}/*.h)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# library name
set(bin_name "SimViewer")


# add Tera library
add_executable(SimViewer
    ${SOURCES} ${HEADERS}
)
target_include_directories(SimViewer PUBLIC
    ${TERA_HOME}/include
    ${GLFW_PATH}/include
    ${POCO_PATH}/include
    # ${POCO_PATH}/Foundation/include
    # ${POCO_PATH}/Util/include
)

set_target_properties(SimViewer
    PROPERTIES LINKER_LANGUAGE CXX
)

if (NOT MSVC)
    target_link_options(SimViewer PRIVATE -lpthread)
endif()

target_link_libraries(SimViewer PUBLIC
    ${tera}
    ${glfw3}
    ${PocoFoundation}
    ${PocoUtil}
    X11
    ${PLATFORM_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}  # -lpthread -lm
    ${CMAKE_DL_LIBS} # for vulkan.c.o
)

# install rules
INSTALL(TARGETS SimViewer
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)


set_target_properties(SimViewer PROPERTIES OUTPUT_NAME ${bin_name})
message(STATUS "target name: ${bin_name}")


add_compile_definitions(
    POCO_STATIC
)
