cmake_minimum_required(VERSION 3.02)

PROJECT(SimViewer C CXX)

Message(STATUS "------------------------------")
Message(STATUS "      Building SimViewer      ")


set(GLFW_PATH $ENV{GLFW_HOME})

find_library(glfw3 NAMES glfw3 HINTS ${GLFW_PATH}/lib)
find_library(tera NAMES tera HINTS ${TERA_HOME}/lib)

if(NOT (CMAKE_SIZEOF_VOID_P EQUAL 8))
    message( FATAL_ERROR "64-bit builds are mandatory for this framework" )
endif()

# glob sources
set(SRC_DIR src)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)
file(GLOB_RECURSE HEADERS ${SRC_DIR}/*.hpp ${SRC_DIR}/*.h)


# library name
set(bin_name "SimViewer")


# add Tera library
add_executable(SimViewer
    ${SOURCES} ${HEADERS}
)
target_include_directories(SimViewer PUBLIC ${TERA_HOME}/include ${GLFW_PATH}/include)
set_target_properties(SimViewer
    PROPERTIES LINKER_LANGUAGE CXX
)

target_link_libraries(SimViewer
    ${PLATFORM_LIBRARIES} ${glfw3} ${tera}
)

# install rules
INSTALL(TARGETS SimViewer
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)


set_target_properties(SimViewer PROPERTIES OUTPUT_NAME ${bin_name})
message(STATUS "target name: ${bin_name}")
