# @author:
#	huanyu <huanyu.zhai@outlook.com>
#=========================================================================================

LIBRARY_NAME        := WindowedApp
TARGET_NAME         := libWindowedApp

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

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
target_file_name	:= $(addsuffix $(if $(LINK_SHARED),.so,.a),$(TARGET_NAME))
TARGET_BUILD		:= $(addprefix $(build_path),$(target_file_name))
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
define print_arg
$(1):
	@echo copying $$@:
endef
#=========================================================================================

# recipes
all: directories $(TARGET_BUILD)
.PHONY: all install directories clean uninstall

ifeq ($(LINK_SHARED),true)
$(TARGET_BUILD): $(OBJ_C) $(OBJ_CXX)
	$(HIDE)$(LD) $(LDFLAGS) $^ -o $@
else
$(TARGET_BUILD): $(OBJ_C) $(OBJ_CXX)
	$(HIDE)$(AR) $(ARFLAGS) $@ $^
endif

# generate rules for each object
$(foreach build_dir,$(BUILD_DIR),$(eval $(call generate_c_rules, $(build_dir))))
$(foreach build_dir,$(BUILD_DIR),$(eval $(call generate_cxx_rules, $(build_dir))))


directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILD_DIR))

install: directories $(TARGET_BUILD) install_directories install_headers
	$(HIDE)$(INSTALLD) $(DESTDIR)$(PREFIX)/lib/
	$(INSTALLF) $(TARGET_BUILD) $(DESTDIR)$(PREFIX)/lib/

install_headers:
	for i in $(HEADER_CXX); do \
		$(HIDE)$(INSTALLF) $$i $(DESTDIR)$(PREFIX)/include/$(TARGET_NAME)/$$(realpath --relative-to $(SRC_DIR) $$i); \
	done

install_directories:
	$(HIDE)$(INSTALLD) $(DESTDIR)$(PREFIX)/include/$(TARGET_NAME)/

uninstall:
	$(HIDE)$(RMDIR) $(DESTDIR)$(PREFIX)/lib/$(TARGET_NAME)
	$(HIDE)$(RMDIR) $(DESTDIR)$(PREFIX)/include/$(TARGET_NAME)

clean:
	$(HIDE)$(RMDIR) $(BUILD_DIR)
