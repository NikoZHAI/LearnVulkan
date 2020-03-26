#huanyu
#=============================================================================================
# general settings

VK_ROOT         := $(shell echo ${VULKAN_SDK})
GLFW_ROOT       := $(shell echo ${GLFW_PATH})

PROJECT_ROOT    := .
SOURCE_DIR      := $(PROJECT_ROOT)/Source
SOURCE_DIR      := $(PROJECT_ROOT)/Source
INCLUDE_DIR     := $(SOURCE_DIR)
TEST_DIR        := $(PROJECT_ROOT)/Test

# built results dirs
BUILD_DIR       := $(PROJECT_ROOT)/build
DIR_BUILT_INC   := $(BUILD_DIR)/include
DIR_BUILT_LIB   := $(BUILD_DIR)/lib
DIR_BUILT_BIN   := $(BUILD_DIR)/bin
DIR_BUILT_TEST  := $(BUILD_DIR)/test

# D-debug    R-release    P-profile
BUILD_TYPE := D

# compilers
CC        := gcc
CXX       := g++
LD        := $(CXX)

#=============================================================================================
# compilation flags

CCFLAGS   := -I$(INCLUDE_DIR) -I$(VK_ROOT)/include -I$(GLFW_ROOT)/include -std=c99 -c -Wall
CXXFLAGS  := -I$(INCLUDE_DIR) -I$(VK_ROOT)/include -I$(GLFW_ROOT)/include -std=c++11 -c -Wall
LDFLAGS   := -L$(VK_ROOT)/lib -lvulkan -lpthread -L$(GLFW_ROOT)/lib 

#=============================================================================================
# file globing

# srcs objects
SRC_C     := $(shell find $(SOURCE_DIR) -name *.c)
SRC_CPP   := $(shell find $(SOURCE_DIR) -name *.cpp)
OBJ_C     := $(SRC_C:%.c=%.o)
OBJ_CPP   := $(SRC_CPP:%.cpp=%.o)

#=============================================================================================
# additional compilation flags

ifeq ($(BUILD_TYPE), D)
    CCFLAGS  += -D_DEBUG -g
    CXXFLAGS += -D_DEBUG -g
else ifeq ($(BUILD_TYPE), R)
    CCFLAGS  += -DNDEBUG -O2
    CXXFLAGS += -DNDEBUG -O2
	LDFLAGS  += -lto
else ifeq ($(BUILD_TYPE), P)
    CCFLAGS  += -g -pg -O2
    CXXFLAGS += -g -pg -O2
	LDFLAGS  += -g -pg
else
    $(error error BUILD_TYPE($(BUILD_TYPE)))
endif

#=============================================================================================
# object library rules

$(OBJ_C): %.o: %.c
	$(CC) $(CCFLAGS) $< -o $@

$(OBJ_CPP): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

#=============================================================================================
# program driver rules

# TODO

#=============================================================================================
# test driver rules

# 1. integration test
integration_test_src := $(TEST_DIR)/integration_test/main.cpp
integration_test_obj := $(integration_test_src:%.cpp=%.o)
$(integration_test_obj): $(integration_test_src)
	$(CXX) -o $@ $(CXXFLAGS) $^
integration_test: $(OBJ_C) $(OBJ_CPP) $(integration_test_obj)
	$(LD) -o $(DIR_BUILT_TEST)/$@ $^ $(LDFLAGS)

#=============================================================================================


all_tests_obj := $(integration_test_obj)

clean:
	-rm -rf $(OBJ_C) $(OBJ_CPP) $(all_tests_obj) $(DIR_BUILT_TEST)/** $(DIR_BUILT_LIB)/** $(DIR_BUILT_INC)/**

clean_lib_objs:
	-rm -rf $(OBJ_C) $(OBJ_CPP) $(all_tests_obj)
