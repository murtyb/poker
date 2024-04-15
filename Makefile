CXX = g++
LINKER = $(CXX) -o
PROGNAME = poker
MAIN_SRC_DIR = src
MAIN_INC_DIR = include
SRC_DIRS := $(wildcard $(MAIN_SRC_DIR)/*)
INC_DIRS := $(wildcard $(MAIN_INC_DIR)/*)
OBJ_DIR = obj
DEP_DIR = dep
BIN_DIR = bin
DEP_FLAGS = -MP -MT $@ -MMD -MF $(DEP_DIR)/$*.d
CXXFLAGS := -std=c++17 -g -O0 -c $(foreach D,$(INC_DIRS),-I$(D))

SRCS = $(foreach D,$(SRC_DIRS),$(wildcard $(D)/*.cpp))
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
DEPS = $(patsubst %.cpp,$(DEP_DIR)/%.d,$(notdir $(SRCS)))

all: $(PROGNAME)

run: $(PROGNAME)
	.\$(BIN_DIR)\$(PROGNAME).exe

$(PROGNAME): $(OBJS)
	$(LINKER) $(BIN_DIR)/$@ $^ 

$(OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/*/%.cpp $(DEP_DIR)/%.d | $(DEP_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(DEP_FLAGS)

$(DEPS):

clean:
	del $(OBJ_DIR)\*.o $(DEP_DIR)\*.d $(BIN_DIR)\poker.exe

-include $(DEPS)