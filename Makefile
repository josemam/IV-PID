CXX = g++
CXXFLAGS = -O3 -m32 -static -s -Wall -Iinclude
OBJ = obj/
SRC = src/

all: iv-pid_eng iv-pid_esp

$(OBJ)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

iv-pid_%: $(OBJ)iv-pid.o $(OBJ)io.o $(OBJ)func.o $(OBJ)strings_%.o
	$(CXX) $(CXXFLAGS) $^ -o $@
