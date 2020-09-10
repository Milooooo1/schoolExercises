CXX := g++
COMPILER_OPTIONS = -Wall -Wextra -Werror -O2

EXECUTABLE = ai
SRC_FILES := $(wildcard ./*.cpp)
OBJ_FILES := $(patsubst %.cpp, %.o, $(SRC_FILES))

INCLUDE = -I ../../include/

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $^ -c -o $@ $(INCLUDE) $(COMPILER_OPTIONS)

clean:
	rm $(OBJ_FILES) $(EXECUTABLE)
