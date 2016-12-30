# ***** Variables *****
LIBNAME   = cronologia
#HPP_FILES = $(wildcard $(INCLUDE)/*.hpp)

# ****** Directorios ********
INCLUDE   = include
LIB       = lib
OBJ       = obj
SRC       = src
BIN       = bin
DOC       = doc
TEST      = $(SRC)/test

# ****** Opciones de compilación ********
AR        = ar
CXX       = g++
CXXFLAGS  = -Wall -g -std=c++11 -c -I./$(INCLUDE) -DNDEBUG
LDFLAGS   = -L./$(LIB)
LDLIBS    = -l$(LIBNAME)
RM				= rm -f

# ****** Compilación de módulos **********

.PHONY: all test docs clean mrproper

all: $(BIN)/conecta4 $(BIN)/arboltablero_test

$(BIN)/arboltablero_test: $(OBJ)/arboltablero_test.o $(LIB)/libtablero.a
	$(CXX) -o $(BIN)/arboltablero_test $(OBJ)/arboltablero_test.o -I$(INC) -L$(LIB) -ltablero

$(BIN)/conecta4: $(OBJ)/conecta4.o $(LIB)/libtablero.a $(LIB)/libmando.a
	$(CXX) -o $(BIN)/conecta4 $(OBJ)/conecta4.o -I$(INC) -L$(LIB) -ltablero -lmando

$(OBJ)/conecta4.o: $(SRC)/conecta4.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/conecta4.o $(SRC)/conecta4.cpp -I$(INC)

$(LIB)/libtablero.a: $(OBJ)/tablero.o
	$(AR) $(LIB)/libtablero.a $(OBJ)/tablero.o

$(LIB)/libmando.a: $(OBJ)/mando.o
	$(AR)  $(LIB)/libmando.a $(OBJ)/mando.o

$(OBJ)/tablero.o: $(SRC)/tablero.cpp $(INC)/tablero.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/tablero.o $(SRC)/tablero.cpp -I$(INC)

$(OBJ)/arboltablero_test.o: $(SRC)/arboltablero_test.cpp $(INC)/tablero.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/arboltablero_test.o $(SRC)/arboltablero_test.cpp -I$(INC)

$(OBJ)/mando.o: $(SRC)/mando.cpp $(INC)/mando.h $(INC)/tablero.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/mando.o $(SRC)/mando.cpp -I$(INC)

# ************ Generación de documentación **************
docs:
	@doxygen $(DOC)/doxys/Doxyfile
	@echo "Documentación disponible en $(DOC)/html"

# ************ Limpieza ************

clean:
	-@$(RM) $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~
	@echo "Limpiando..."

mrproper: clean
	-@$(RM) $(BIN)/* $(LIB)/* $(DOC)/html/*
	@echo "Limpieza completada."
