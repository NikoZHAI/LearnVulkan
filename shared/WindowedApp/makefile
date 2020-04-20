# @author:
#	huanyu <huanyu.zhai@outlook.com>
#=========================================================================================

TAR_NAME            := libwindowed_app

# compilers
CC 					:= gcc
CXX 				:= g++
AR					:= ar
# D-debug  R-release
BUILD_TYPE 			:= R
# STATIC-static linking  SHARED-shared orbject
LINK_TYPE 			:= STATIC
# build directory
BUILD_DIR			:= build
# install directory
INST_DIR 			:= lib
# source directory
SRC_DIR				:= src
#=========================================================================================

# resolve header files
HEADER_C			:= $(shell find $(SRC_DIR) -name *.h)
HEADER_CXX			:= $(shell find $(SRC_DIR) -name *.hpp)
# resolve source files
SRC_C				:= $(shell find $(SRC_DIR) -name *.c)
SRC_CXX				:= $(shell find $(SRC_DIR) -name *.cpp)
# generate objects files
OBJ_C				:= $(SRC_C:%.c=%.o)
OBJ_CXX				:= $(SRC_CXX:%.cpp=%.o)
#=========================================================================================

# default gcc flags
CFLAGS				:= -I$(SRC_DIR) -c -std=c11 -Wall
CXXFLAGS			:= -I$(SRC_DIR) -c -std=c++11 -Wall

# set flags for link type
ifeq ($(LINK_TYPE),SHARED)
	LINK_SHARED		:= true
	CFLAGS 			+= -fPIC
	CXXFLAGS 		+= -fPIC
	LDFLAGS			:= -shared
	LD				:= $(CXX)
else ifeq ($(LINK_TYPE),STATIC)
	ARFLAGS			:= cvsr
else
	$(error error LINK_TYPE($(LINK_TYPE)))
endif

# set flags for build type
ifeq ($(BUILD_TYPE),D)
	CFLAGS			+= -D_DEBUG -Og -g
	CXXFLAGS		+= -D_DEBUG -Og -g
else ifeq ($(BUILD_TYPE),R)
	CFLAGS			+= -DNDEBUG -O2
	CXXFLAGS		+= -DNDEBUG -O2
	LD				+= -lto
else
	$(error error BUILD_TYPE($(BUILD_TYPE)))
endif
#=========================================================================================

# globbing targets
build_path			:= $(BUILD_DIR)/
install_path		:= $(INST_DIR)/
install_lib_path	:= $(join $(install_path),lib/)
install_inc_path	:= $(join $(install_path),include/)
target_file_name	:= $(addsuffix $(if $(LINK_SHARED),.so,.a),$(TAR_NAME))
TARGET_BUILD		:= $(addprefix $(build_path),$(target_file_name))
TARGET_INSTALL		:= $(addprefix $(install_lib_path),$(target_file_name))
# bind output objects to BUILD_DIR
bind_build_dir		:= $(addprefix $(build_path),$(notdir $(fname)))
OBJS				:= $(foreach fname,$(OBJ_C) $(OBJ_CXX),$(bind_build_dir))
#=========================================================================================

# recipes
all: $(TARGET_BUILD)
.PHONY: all install

$(OBJ_C): %.o: %.c
	$(CC) $(CFLAGS) $< -o $(addprefix $(build_path),$(@F))

$(OBJ_CXX): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $(addprefix $(build_path),$(@F))

$(OBJS): $(OBJ_C) $(OBJ_CXX)

ifeq ($(LINK_SHARED),true)
$(TARGET_BUILD): $(OBJS)
	@mkdir -p $(build_path)
	$(LD) $(LDFLAGS) $^ -o $@
else
$(TARGET_BUILD): $(OBJS)
	@mkdir -p $(build_path)
	$(AR) $(ARFLAGS) $@ $^
endif

install: $(TARGET_BUILD) $(TARGET_HEADERS_C) $(TARGET_HEADERS_CXX)
	@mkdir -p $(install_path) $(install_lib_path)
	@cp $(TARGET_BUILD) $(TARGET_INSTALL)

$(HEADERS_C): %.h
	@mkdir -p $(install_path) $(install_inc_path)
	@cp $^ $(install_inc_path)

vpath %.h $(SRC_DIR)

$(HEADERS_CXX): %.hpp
	@mkdir -p $(install_path) $(install_inc_path)
	@cp $^ $(install_inc_path)

vpath %.hpp $(SRC_DIR)
