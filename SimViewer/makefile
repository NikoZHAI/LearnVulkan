# @author:
#	huanyu <huanyu.zhai@outlook.com>
#=========================================================================================

TARGET_NAME			:= SimViewer

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

# libraries
WINDOWED_APP_HOME	:= ../shared/WindowedApp

# compilers
CC 					:= gcc
CXX 				:= g++
LD					:= $(CXX)
# verbosity
VERBOSE				:= 1
# D-debug  R-release
BUILD_TYPE 			:= R
# project directory
PROJ_DIR			:= $(realpath $(CURDIR))
# build directory
BUILD_DIR			:= $(PROJ_DIR)/bin
# source directory
SRC_DIR				:= $(PROJ_DIR)/src
# set vpath
VPATH 				:= $(SRC_DIR)
#=========================================================================================

# resolve header files
HEADER_C			:= $(shell find $(SRC_DIR) -name '*.h')
HEADER_CXX			:= $(shell find $(SRC_DIR) -name '*.hpp')
# resolve source files
SRC_C				:= $(shell find $(SRC_DIR) -name '*.c')
SRC_CXX				:= $(shell find $(SRC_DIR) -name '*.cpp')
# generate objects files
OBJ_C				:= $(SRC_C:.c=.o)
OBJ_CXX				:= $(SRC_CXX:.cpp=.o)
#=========================================================================================

# default gcc flags
CFLAGS				:= -I$(SRC_DIR) -I$(WINDOWED_APP_HOME)/include -c -std=c11 -Wall
CXXFLAGS			:= -I$(SRC_DIR) -I$(WINDOWED_APP_HOME)/include -c -std=c++11 -Wall
LDFLAGS				:= -L$(WINDOWED_APP_HOME)/lib -l:libWindowedApp.a

# set flags for build type
ifeq ($(BUILD_TYPE),D)
	CFLAGS			+= -D_DEBUG -Og -g
	CXXFLAGS		+= -D_DEBUG -Og -g
else ifeq ($(BUILD_TYPE),R)
	CFLAGS			+= -DNDEBUG -O2
	CXXFLAGS		+= -DNDEBUG -O2
	# LDFLAGS     	+= 
else
	$(error error BUILD_TYPE($(BUILD_TYPE)))
endif


#=========================================================================================

# globbing targets
build_path			:= $(BUILD_DIR)/
target_file_name	:= $(TARGET_NAME)
TARGET_BUILD		:= $(addprefix $(build_path),$(target_file_name))
TARGET_INST_DIR		:= $(DESTDIR)$(PREFIX)/$(TARGET_NAME)
BINS_INST_DIR		:= $(TARGET_INST_DIR)/bin
#=========================================================================================
# misc
RMDIR				:= rm -rf
MKDIR				:= mkdir -p
CP					:= cp -rf
INSTALLD		    := install -d
INSTALLF		    := install -m 644
# remove space after separator
SEP					:=/
PSEP 				:= $(strip $(SEP))
# hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),1)
    HIDE 			:=  
else
    HIDE 			:= @
endif
define print_arg
$(1):
	@echo copying $$@:
endef
#=========================================================================================

# recipes
all: directories dependencies $(TARGET_BUILD)
.PHONY: all install directories clean uninstall

dependencies: ../Tera
	for i in $^; do \
		$(MAKE) -C $$i install PREFIX=../shared BUILD_TYPE=$(BUILD_TYPE); \
	done

main.o: main.cpp
	$(HIDE)$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ_C): %.o : %.c
	$(HIDE)$(CC) $(CFLAGS) -o $@ $<

$(OBJ_CXX): %.o : %.cpp
	$(HIDE)$(CXX) $(CXXFLAGS) -o $@ $<

$(TARGET_BUILD): $(OBJ_C) $(OBJ_CXX) main.o
	$(HIDE)$(LD) $^ $(LDFLAGS) -o $@


directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILD_DIR))

install: directories $(TARGET_BUILD)
	$(HIDE)$(INSTALLD) $(BINS_INST_DIR)
	$(INSTALLF) $(TARGET_BUILD) $(BINS_INST_DIR)

uninstall:
	$(HIDE)$(RMDIR) $(BINS_INST_DIR)/$(TARGET_BUILD)

clean:
	$(HIDE)$(RMDIR) $(OBJ_C) $(OBJ_CXX) main.o
