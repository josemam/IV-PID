CXX = g++
VERSION = v0.1.1
CHARSET = UTF-8
PROGRAM_NAME = IV⇆\ PID
# If Windows, sets the Western Europe charset
ifdef SystemRoot 		
	CHARSET = CP850
	PROGRAM_NAME = IV-PID
endif

CXXFLAGS = -O3 -m32 -static -s -Wall -Iinclude -flto
STRINGSFLAGS = -fexec-charset=$(CHARSET)
IO = cmdline_io
IOFLAGS = $(STRINGFLAGS) -DPROGRAM_NAME=\"$(PROGRAM_NAME)\" -DVERSION=\"$(VERSION)\"
OBJ = obj
SRC = src
.INTERMEDIATE: $(OBJ)/$(IO).o

all: iv-pid_eng iv-pid_esp

$(OBJ):
	mkdir $@

$(OBJ)/strings%.o: $(SRC)/strings%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(STRINGSFLAGS) -c $< -o $@

$(OBJ)/$(IO).o: $(SRC)/$(IO).cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(IOFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

iv-pid_%: $(OBJ)/iv-pid.o $(OBJ)/$(IO).o $(OBJ)/func.o $(OBJ)/strings_%.o
	$(CXX) $(CXXFLAGS) $^ -o $@
