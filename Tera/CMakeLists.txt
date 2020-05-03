cmake_minimum_required(VERSION 3.02)

PROJECT(Tera C CXX)

Message(STATUS "------------------------------")
Message(STATUS "     Building Tera Library    ")

if(NOT (CMAKE_SIZEOF_VOID_P EQUAL 8))
    message( FATAL_ERROR "64-bit builds are mandatory for this framework" )
endif()


# glob sources
set(CMAKE_SOURCE_DIR ./src)
set(CORE_DIR ${CMAKE_SOURCE_DIR}/Core)
file(GLOB CORE_SOURCES ${CORE_DIR}/*.cpp ${CORE_DIR}/*.c ${CORE_DIR}/*.hpp ${CORE_DIR}/*.h)

# library name
set(library_name "tera")


# add Tera library
add_library(tera STATIC
    ${CORE_SOURCES}
)
set_target_properties(tera
    PROPERTIES LINKER_LANGUAGE CXX
)

# glfw
set(glfw3 glfw)

target_link_libraries(tera
    ${PLATFORM_LIBRARIES} ${glfw3} 
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
