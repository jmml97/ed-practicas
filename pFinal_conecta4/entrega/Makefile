# ***** Variables del proyecto *****
LIBNAME = conecta4

# ****** Directorios ********
INC       = include
LIB       = lib
OBJ       = obj
SRC       = src
BIN       = bin
DOC       = doc
TEST      = $(SRC)/test

# ****** Opciones de compilación ********
RM				= rm -rf
AR        = ar
CXX       = g++
CXXFLAGS  = -Wall -g -std=c++11 -c -I./$(INC) -DNDEBUG
LDFLAGS   = -L./$(LIB)
LDLIBS    = -l$(LIBNAME)

# ****** Compilación de módulos **********

.PHONY: all test docs clean mrproper

all: $(BIN)/partida_conecta4

# --- Ejecutables ---
$(BIN)/partida_conecta4: $(OBJ)/partida_conecta4.o $(LIB)/lib$(LIBNAME).a
	$(CXX) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(OBJ)/partida_conecta4.o: $(SRC)/partida_conecta4.cpp $(INC)/conecta4.h $(INC)/mando.h
	$(CXX) $(CXXFLAGS) -o $@ $<

# --- Librería ---
$(LIB)/lib$(LIBNAME).a : $(OBJ)/conecta4.o $(OBJ)/mando.o $(OBJ)/tablero.o
	$(AR) rvs $@ $?

$(OBJ)/conecta4.o: $(SRC)/conecta4.cpp $(INC)/conecta4.h $(INC)/tablero.h $(INC)/arbol_general.h
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/mando.o: $(SRC)/mando.cpp $(INC)/mando.h $(INC)/tablero.h
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/tablero.o: $(SRC)/tablero.cpp $(INC)/tablero.h
	$(CXX) $(CXXFLAGS) -o $@ $<

# --- Test ---
test: $(BIN)/test_arbol_tablero $(BIN)/test_conecta4

$(BIN)/test_arbol_tablero: $(OBJ)/test_arbol_tablero.o $(OBJ)/tablero.o
	$(CXX) -o $@ $^

$(BIN)/test_conecta4: $(OBJ)/test_conecta4.o $(OBJ)/tablero.o $(OBJ)/mando.o
	$(CXX) -o $@ $^

$(OBJ)/test_arbol_tablero.o: $(TEST)/test_arbol_tablero.cpp $(INC)/tablero.h $(INC)/arbol_general.h
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/test_conecta4.o: $(TEST)/test_conecta4.cpp $(INC)/tablero.h $(INC)/mando.h
	$(CXX) $(CXXFLAGS) -o $@ $<

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
