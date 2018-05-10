# Makefile for customizing C/C++ builds - 138paulmiller 
# Options make [all rebeuild clean test install] 	
# compiler to use
CC = g++

# directory to hold all compiled c/cpp files
OUT = artic

#additional flags to use
CPPFLAGS = -std=c++14 

# directory that contains c/cpp files
SRC_DIR = src
#include directory for additional headers
INC_DIR = inc
# directory that contains temporary object files
OBJ_DIR = obj
# directory that contains test source files
TEST_DIR = test
TEST_OBJ_DIR = test_obj
TEST_OUT = $(OUT)_test

# All objects, creates a list of all potential objects from sources, whether or not compiled yet
# Finds all source files, strips prefix and suffix and renames them as object files
SRC_OBJECTS= $(patsubst %, $(OBJ_DIR)/%.o, \
		$(notdir $(basename \
		$(shell find $(SRC_DIR) -type f -name '*.cpp')))) 	

TEST_OBJECTS= $(patsubst %, $(TEST_OBJ_DIR)/%.o, \
		$(notdir $(basename \
		$(shell find $(TEST_DIR) -type f -name '*.cpp')))) 	


all: $(SRC_OBJECTS)
	$(CC) -o $(OUT) $^ $(CPPFLAGS)

rebuild : clean all
	@echo Rebuild Complete

#If remove fails, contiue
clean:
	@echo rm -r $(OBJ_DIR);
	@if [ -e $(OBJ_DIR) ]; then rm -r $(OBJ_DIR); fi; 
	@echo rm -r $(OUT);
	@if [ -e $(OUT) ]; then rm -r $(OUT); fi;
	@echo rm -r $(TEST_OBJ_DIR); 
	@if [ -e $(TEST_OBJ_DIR) ]; then rm -r $(TEST_OBJ_DIR); fi; 
	@echo rm -r $(TEST_OUT);
	@if [ -e $(TEST_OUT) ]; then rm -r $(TEST_OUT); fi; 
	@echo Cleaned

test: $(TEST_OBJECTS)
	$(CC) -o $(TEST_OUT) $^ $(CPPFLAGS)
	./$(TEST_OUT)

#install:

#usage $(call compile, inc, src, obj, $(flags))
compile = 	\
	@if [ ! -e "$@" ]; then \
	echo "$(CC) -I$(1) $(4) -c $(shell find $(2) -type f -name $(notdir $(basename $@)).cpp) -o $(3)/$(notdir $@);"; \
		$(CC) -I$(1) $(4) \
		-c $(shell find $(2) -type f -name $(notdir $(basename $@)).cpp) \
		-o $(3)/$(notdir $@); \
	fi


#If obj does not exist(not compiled), compile it into build dir 
$(SRC_OBJECTS): $(OBJ_DIR)
	$(call compile, $(INC_DIR), $(SRC_DIR), $(OBJ_DIR), $(CPPFLAGS))
		
#If obj does not exist(not compiled), compile it into build dir 
$(TEST_OBJECTS): $(TEST_OBJ_DIR)
	$(call compile, $(INC_DIR), $(TEST_DIR), $(TEST_OBJ_DIR), $(CPPFLAGS))


# Create build directory for objects files
$(OBJ_DIR):
	@mkdir $@
# Create build directory for objects files
$(TEST_OBJ_DIR):
	@mkdir $@


