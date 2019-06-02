# TLM 2019 c++ makefile
#
# build in /src
# place exe in /build
#



FXX = gfortran
CXX = g++
NXX = nvcc -x cu  -arch=sm_30  -rdc=true -lcudadevrt
CFLAGS =  -Wall #Wall: warn all unused variables  -g -O0 `sdl-config --cflags --libs`
LDFLAGS = #-lGL -lGLU -lglut -lpthread  -lSDL_mixer -lGLEW -lcuda
NVFLAGS = -g -G -O0


.SUFFIXES: 

.SUFFIXES:  .cpp .c .cu .o


.c.o:
	echo Compiling C

.cpp.o:
	echo Compiling CPP

.cu.o:
	echo Compiling NVCC

#BUILD_DIR ?= .././build
#ODIR ?= ./
#SRC_DIRS ?= ./

BUILD_DIR ?= ./build
TEST_DIR ?= ./tests
ODIR ?= ./src
SRC_DIRS ?= ./src

EXECUTABLE = solver




OBJECTS = vector.o tests_array.o 




 

$(BUILD_DIR)/solver: 	$(SRC_DIRS)/tests_array.o \
						$(SRC_DIRS)/vector.o
	$(CXX) 	 $(SRC_DIRS)/tests_array.cpp  $(SRC_DIRS)/vector.cpp  -o $(BUILD_DIR)/solver 






# vanilla overloaded array testing:
#$(BUILD_DIR)/tests_array.o: $(TEST_DIR)/tests_array.cpp 
#	$(NXX) -g -c $(TEST_DIR)/tests_array.cpp



# expression template testing:
#$(BUILD_DIR)/tests_etarray.o: $(TEST_DIR)/tests_etarray.cu 
#	$(NXX) -g -c $(TEST_DIR)/tests_etarray.cu

#$(SRC_DIRS)/tests_etarray.cuh



# vanilla overloaded array testing:
# $(BUILD_DIR)/tests_array.o: $(SRC_DIRS)/tests_array.cpp 
# 	$(NXX) -g -c $(SRC_DIRS)/tests_array.cpp


# # expression template testing:
# $(BUILD_DIR)/tests_etarray.o: $(SRC_DIRS)/tests_etarray.cu 
# 	$(NXX) -g -c $(SRC_DIRS)/tests_etarray.cu 





# $(BUILD_DIR)/main.o: 	$(SRC_DIRS)/main.cpp  
# 	$(NXX) -g -c $(SRC_DIRS)/main.cpp







$(OBJECTS): tests_array.o vector.o

.PHONY: clean


clean: 
	-rm -f  \
			$(SRC_DIRS)/*.o  


realclean: 
	-rm -f  \
			$(SRC_DIRS)/*.o  \
			$(BUILD_DIR)/$(EXECUTABLE)