# ***** Variables *****
LIBNAME   = cronologia
HPP_FILES = $(wildcard $(INCLUDE)/*.hpp)

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
CXXFLAGS  = -Wall -g -std=c++11 -c -I./$(INCLUDE) #-DNDEBUG
LDFLAGS   = -L./$(LIB)
LDLIBS    = -l$(LIBNAME)
RM				= rm -f

# ****** Compilación de módulos **********

.PHONY: all test docs clean mrproper

all: $(BIN)/union_cronologia $(BIN)/estadistica_eventos $(BIN)/filtrado_palabra_clave $(BIN)/filtrado_intervalo

# --- Ejecutables ---
$(BIN)/% : $(OBJ)/%.o $(LIB)/lib$(LIBNAME).a
	$(CXX) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(OBJ)/union_cronologia.o : $(SRC)/union_cronologia.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/estadistica_eventos.o : $(SRC)/estadistica_eventos.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/filtrado_palabra_clave.o : $(SRC)/filtrado_palabra_clave.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/filtrado_intervalo.o : $(SRC)/filtrado_intervalo.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

# --- Librería ---
$(LIB)/lib$(LIBNAME).a : $(OBJ)/evento_historico.o $(OBJ)/cronologia.o
	ar rvs $@ $?

$(OBJ)/evento_historico.o : $(SRC)/evento_historico.cpp $(INCLUDE)/evento_historico.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/cronologia.o : $(SRC)/cronologia.cpp $(INCLUDE)/cronologia.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# --- Test ---
test: $(BIN)/test_*

$(BIN)/test_%: $(OBJ)/test_%.o $(OBJ)/%.o
	$(CXX) -o $@ $^

$(BIN)/test_cronologia: $(OBJ)/evento_historico.o 

$(OBJ)/test_%.o: $(TEST)/test_%.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

.PRECIOUS: $(OBJ)/test_%.o

# ************ Generación de documentación **************
docs:
	@doxygen $(DOC)/doxys/Doxyfile
	@echo "Documentación disponible en $(DOC)/html"

# ************ Limpieza ************

clean:
	-@rm -f $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~
	@echo "Limpiando..."

mrproper: clean
	-@rm -f $(BIN)/* $(LIB)/* $(DOC)/html/*
	@echo "Limpieza completada."
