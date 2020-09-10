#Opdracht 5 bash
CXX := g++
COMPILER_OPTIONS = -Wall

SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp, %.o, $(SRC_FILES))

INCLUDE = -I ./include/

main: $(OBJ_FILES)
	echo $(OBJ_FILES)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $^ -c -o $@ $(INCLUDE) $(COMPILER_OPTIONS)

clean:
	rm $(OBJ_FILES)