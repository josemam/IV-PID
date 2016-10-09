CXX = g++
VERSION = v0.1.0
CHARSET = UTF-8
PROGRAM_NAME = IV⇆\ PID
# If Windows, sets the Western Europe charset
ifdef SystemRoot 		
	CHARSET = CP850
	PROGRAM_NAME = IV-PID
endif

CXXFLAGS = -O3 -m32 -static -s -Wall -Iinclude -flto
STRINGSFLAGS = -fexec-charset=$(CHARSET)
IOFLAGS = $(STRINGFLAGS) -DPROGRAM_NAME=\"$(PROGRAM_NAME)\" -DVERSION=\"$(VERSION)\"
OBJ = obj
SRC = src
.INTERMEDIATE: $(OBJ)/io.o

all: iv-pid_eng iv-pid_esp

$(OBJ):
	mkdir $@

$(OBJ)/strings%.o: $(SRC)/strings%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(STRINGSFLAGS) -c $< -o $@

$(OBJ)/io.o: $(SRC)/io.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(IOFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

iv-pid_%: $(OBJ)/iv-pid.o $(OBJ)/io.o $(OBJ)/func.o $(OBJ)/strings_%.o
	$(CXX) $(CXXFLAGS) $^ -o $@
