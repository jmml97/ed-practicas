AR = ar
CXX = g++
CXXFLAGS = -Wall -g

OBJ = obj
BIN = bin
SRC = src

all : burbuja binaria burbuja_mejor_caso burbuja_peor_caso burbuja_optimizado burbuja_opt_compilador

$(OBJ)/burbuja.o : $(SRC)/ordenacion.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/burbuja.o $(SRC)/ordenacion.cpp

$(OBJ)/burbuja_opt_compilador.o : $(SRC)/ordenacion.cpp
	$(CXX) -c $(CXXFLAGS) -O3 -o $(OBJ)/burbuja_opt_compilador.o $(SRC)/ordenacion.cpp

$(OBJ)/binaria.o : $(SRC)/ejercicio_desc.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/binaria.o $(SRC)/ejercicio_desc.cpp

$(OBJ)/burbuja_mejor_caso.o : $(SRC)/burbuja_mejor_caso.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/burbuja_mejor_caso.o $(SRC)/burbuja_mejor_caso.cpp

$(OBJ)/burbuja_peor_caso.o : $(SRC)/burbuja_peor_caso.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/burbuja_peor_caso.o $(SRC)/burbuja_peor_caso.cpp

$(OBJ)/burbuja_optimizado.o : $(SRC)/burbuja_optimizado.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)/burbuja_optimizado.o $(SRC)/burbuja_optimizado.cpp

burbuja : $(OBJ)/burbuja.o
	$(CXX) -o $(BIN)/burbuja $(OBJ)/burbuja.o

burbuja_opt_compilador : $(OBJ)/burbuja_opt_compilador.o
	$(CXX) -o $(BIN)/burbuja_opt_compilador $(OBJ)/burbuja_opt_compilador.o

binaria : $(OBJ)/binaria.o
	$(CXX) -o $(BIN)/binaria $(OBJ)/binaria.o

burbuja_mejor_caso : $(OBJ)/burbuja_mejor_caso.o
	$(CXX) -o $(BIN)/burbuja_mejor_caso $(OBJ)/burbuja_mejor_caso.o

burbuja_peor_caso : $(OBJ)/burbuja_peor_caso.o
	$(CXX) -o $(BIN)/burbuja_peor_caso $(OBJ)/burbuja_peor_caso.o

burbuja_optimizado : $(OBJ)/burbuja_optimizado.o
	$(CXX) -o $(BIN)/burbuja_optimizado $(OBJ)/burbuja_optimizado.o

clean :
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrpropper : clean
	rm $(BIN)/*
