AR = ar
CXX = g++
CXXFLAGS = -Wall -g

OBJ = obj
BIN = bin

all : ordenacion

$(OBJ)/ordenacion.o : ordenacion.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/ordenacion.o ordenacion.cpp

$(OBJ)/desconocido.o : desconocido.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/desconocido.o desconocido.cpp

ordenacion : $(OBJ)/ordenacion.o
	$(CXX) -o $(BIN)/ordenacion $(OBJ)/ordenacion.o

clean :
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrpropper : clean
	rm $(BIN)/*
