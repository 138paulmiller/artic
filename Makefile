# Makefile for customizing C/C++ builds - 138paulmiller 
# Options make [all rebeuild clean test install] 	
# compiler to use
CC = g++
MAIN = main.cpp
# directory to hold all compiled c/cpp files
#additional flags to use
CPPFLAGS = -std=c++14 
# directory that contains c/cpp files
SRC_DIR = src
#include directory for additional headers
INC_DIR = inc
BUILD_DIR = build
OUT = $(BUILD_DIR)/artic
OBJ_DIR = $(BUILD_DIR)/obj

#testing defs
TEST_DIR = test
TEST_BUILD_DIR = $(TEST_DIR)/build
TEST_OBJ_DIR = $(TEST_BUILD_DIR)/obj
TEST_RULES = test_img test_math

# All objects, creates a list of all potential objects from sources, whether or not compiled yet
# Finds all source files, strips prefix and suffix and renames them as object files
SRC_OBJECTS= $(patsubst %, $(OBJ_DIR)/%.o, \
		$(notdir $(basename \
		$(shell find $(SRC_DIR) -type f -name '*.cpp')))) 	

TEST_OBJECTS= $(patsubst %, $(TEST_OBJ_DIR)/%.o, \
		$(notdir $(basename \
		$(shell find $(SRC_DIR) -not -name $(MAIN) -type f -name '*.cpp')))) 	

.PHONY : $(TEST_RULES)

all: $(SRC_OBJECTS) 
	$(CC) -o $(OUT) $^ $(CPPFLAGS)

rebuild : clean all
	@echo Rebuild Complete

#If remove fails, contiue
clean: clean_test
	@echo rm -r $(BUILD_DIR);
	@if [ -e $(BUILD_DIR) ]; then rm -r $(BUILD_DIR); fi; 
	@echo Cleaned

clean_test:
	@echo rm -r $(TEST_BUILD_DIR); 
	@if [ -e $(TEST_BUILD_DIR) ]; then rm -r $(TEST_BUILD_DIR); fi; 
	@echo Cleaned


$(TEST_RULES): $(TEST_OBJECTS) 
	$(CC) -I$(INC_DIR) $(CPPFLAGS) -c $(TEST_DIR)/$@.cpp -o $(TEST_OBJ_DIR)/$(notdir $@).o 
	$(CC) -o $(TEST_BUILD_DIR)/$@ $(TEST_OBJ_DIR)/$@.o $(TEST_OBJECTS) $(CPPFLAGS)
	./$(TEST_BUILD_DIR)/$@

$(TEST_OBJECTS) : $(TEST_BUILD_DIR) $(TEST_OBJ_DIR)
	$(call compile_test,$(INC_DIR), $(SRC_DIR), $(TEST_OBJ_DIR), $(CPPFLAGS))


#If obj does not exist(not compiled), compile it into build dir 
$(SRC_OBJECTS): $(BUILD_DIR) $(OBJ_DIR)
	$(call compile,$(INC_DIR), $(SRC_DIR), $(OBJ_DIR), $(CPPFLAGS))

# Create build directory if needed
$(BUILD_DIR) $(OBJ_DIR) $(TEST_BUILD_DIR) $(TEST_OBJ_DIR):
	@mkdir $@


#usage $(call compile, inc, src, obj, $(flags))
compile = 	\
	@if [ ! -e "$@" ]; then \
	echo "$(CC) -I$(1) $(4) -c $(shell find $(2) -type f -name $(notdir $(basename $@)).cpp) -o $(3)/$(notdir $@);"; \
		$(CC) -I$(1) $(4) \
		-c $(shell find $(2) -type f -name $(notdir $(basename $@)).cpp) \
		-o $(3)/$(notdir $@); \
	fi

compile_test = 	\
	@if [ ! -e "$@" ]; then \
	echo "$(CC) -I$(1) $(4) -c $(shell find $(2) -type f -name $(notdir $(basename $@)).cpp) -o $(3)/$(notdir $@);"; \
		$(CC) -I$(1) $(4) \
		-c $(shell find $(2) -type f -name $(notdir $(basename $@)).cpp) \
		-o $(3)/$(notdir $@); \
	fi




