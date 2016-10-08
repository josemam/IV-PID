CXX = g++
CHARSET = UTF-8
# If Windows, sets the Western Europe charset
ifdef SystemRoot 		
	CHARSET = CP850
endif

CXXFLAGS = -O3 -m32 -static -s -Wall -Iinclude -flto -fexec-charset=$(CHARSET)
OBJ = obj
SRC = src

all: iv-pid_eng iv-pid_esp

$(OBJ):
	mkdir $@

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

iv-pid_%: $(OBJ)/iv-pid.o $(OBJ)/io.o $(OBJ)/func.o $(OBJ)/strings_%.o
	$(CXX) $(CXXFLAGS) $^ -o $@
