# @author:
#	huanyu <huanyu.zhai@outlook.com>
#=========================================================================================

TARGET_NAME         := libwindowed_app

# compilers
CC 					:= gcc
CXX 				:= g++
AR					:= ar
# verbosity
VERBOSE				:= 1
# D-debug  R-release
BUILD_TYPE 			:= R
# STATIC-static linking  SHARED-shared orbject
LINK_TYPE 			:= STATIC
# project directory
PROJ_DIR			:= $(realpath $(CURDIR))
# build directory
BUILD_DIR			:= $(PROJ_DIR)/build
# install directory
INST_DIR 			:= $(PROJ_DIR)/$(TARGET_NAME)
# source directory
SRC_DIR				:= $(PROJ_DIR)/src
# set vpath
VPATH 				 = $(SRC_DIR)
#=========================================================================================

# resolve header files
HEADER_C			:= $(shell find $(SRC_DIR) -name *.h)
HEADER_CXX			:= $(shell find $(SRC_DIR) -name *.hpp)
# resolve source files
SRC_C				:= $(shell find $(SRC_DIR) -name *.c)
SRC_CXX				:= $(shell find $(SRC_DIR) -name *.cpp)
# generate objects files
OBJ_C				:= $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_C:.c=.o))
OBJ_CXX				:= $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_CXX:.cpp=.o))
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
target_file_name	:= $(addsuffix $(if $(LINK_SHARED),.so,.a),$(TARGET_NAME))
TARGET_BUILD		:= $(addprefix $(build_path),$(target_file_name))
TARGET_INSTALL		:= $(addprefix $(install_lib_path),$(target_file_name))
# bind output objects to BUILD_DIR
bind_build_dir		:= $(addprefix $(build_path),$(notdir $(fname)))
OBJS				:= $(foreach fname,$(OBJ_C) $(OBJ_CXX),$(bind_build_dir))
#=========================================================================================
# misc
RMDIR				:= rm -rf
MKDIR				:= mkdir -p
# remove space after separator
SEP					:=/
PSEP 				:= $(strip $(SEP))
# hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),1)
    HIDE 			:=  
else
    HIDE 			:= @
endif
# define our rule generation function
define generate_c_rules
$(1)/%.o: %.c
	@echo building $$@...
	$(HIDE)$(CC) $(CFLAGS) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<)
endef
define generate_cxx_rules
$(1)/%.o: %.cpp
	@echo building $$@...
	$(HIDE)$(CXX) $(CXXFLAGS) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<)
endef
#=========================================================================================

# recipes
all: directories $(TARGET_BUILD)
.PHONY: all directories

ifeq ($(LINK_SHARED),true)
$(TARGET_BUILD): $(OBJ_C) $(OBJ_CXX)
	@mkdir -p $(build_path)
	$(LD) $(LDFLAGS) $^ -o $@
else
$(TARGET_BUILD): $(OBJ_C) $(OBJ_CXX)
	@mkdir -p $(build_path)
	$(AR) $(ARFLAGS) $@ $^
endif

# generate rules for each object
$(foreach build_dir,$(BUILD_DIR),$(eval $(call generate_c_rules, $(build_dir))))
$(foreach build_dir,$(BUILD_DIR),$(eval $(call generate_cxx_rules, $(build_dir))))

directories: 
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILD_DIR))

# install: $(TARGET_BUILD) $(TARGET_HEADERS_C) $(TARGET_HEADERS_CXX)
# 	@mkdir -p $(install_path) $(install_lib_path)
# 	@cp $(TARGET_BUILD) $(TARGET_INSTALL)

# $(HEADERS_C): %.h
# 	@mkdir -p $(install_path) $(install_inc_path)
# 	@cp $^ $(install_inc_path)

# vpath %.h $(SRC_DIR)

# $(HEADERS_CXX): %.hpp
# 	@mkdir -p $(install_path) $(install_inc_path)
# 	@cp $^ $(install_inc_path)

# vpath %.hpp $(SRC_DIR)
