# ***** Variables *****
LIBNAME   = cronologia
RM				= rm -f
HPP_FILES = $(wildcard $(INCLUDE)/*.hpp)

# ****** Directorios ********
INCLUDE   = include
LIB       = lib
OBJ       = obj
SRC       = src
BIN       = bin
DOC       = doc

# ****** Opciones de compilación ********
AR        = ar
CXX       = g++
CXXFLAGS  = -Wall -g -std=c++11 -c -I./$(INCLUDE) #-DNDEBUG
LDFLAGS   = -L./$(LIB)
LDLIBS    = -l$(LIBNAME)

# ****** Compilación de módulos **********

.PHONY: all docs clean mrproper

all: $(BIN)/union_cronologia $(BIN)/uso_cronologia

$(BIN)/uso_cronologia : $(OBJ)/uso_cronologia.o $(LIB)/lib$(LIBNAME).a
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(LIB)/lib$(LIBNAME).a : $(OBJ)/evento_historico.o $(OBJ)/cronologia.o
	ar rvs $@ $^

$(OBJ)/uso_cronologia.o : $(SRC)/uso_cronologia.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/evento_historico.o : $(SRC)/evento_historico.cpp $(INCLUDE)/evento_historico.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/cronologia.o : $(SRC)/cronologia.cpp $(INCLUDE)/cronologia.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<


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
