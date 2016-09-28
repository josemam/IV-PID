CXX = g++
CXXFLAGS = -O3 -m32 -static -s -Wall -Iinclude -flto -finput-charset=UTF-8 -fexec-charset=UTF-8
OBJ = obj/
SRC = src/

all: iv-pid_eng iv-pid_esp

$(OBJ)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

iv-pid_%: $(OBJ)iv-pid.o $(OBJ)io.o $(OBJ)func.o $(OBJ)strings_%.o
	$(CXX) $(CXXFLAGS) $^ -o $@
