AR = ar
CXX = g++
CXXFLAGS = -Wall -g

OBJ = obj
BIN = bin

all : ordenacion

$(OBJ)/ordenacion.o : ordenacion.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/ordenacion.o ordenacion.cpp

ordenacion : $(OBJ)/ordenacion.o
	$(CXX) -o $(BIN)/ordenacion $(OBJ)/ordenacion.o

clean :
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrpropper : clean
	rm $(BIN)/*
