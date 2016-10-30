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

# ****** Opciones de compilación ********
AR        = ar
CXX       = g++
CXXFLAGS  = -Wall -g -std=c++11 -c -I./$(INCLUDE) -DNDEBUG
LDFLAGS   = -L./$(LIB)
LDLIBS    = -l$(LIBNAME)

# ****** Compilación de módulos **********

.PHONY: all docs clean mrproper

all: $(BIN)/usoCronologia

$(BIN)/usoCronologia : $(OBJ)/usoCronologia.o $(LIB)/lib$(LIBNAME).a
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(LIB)/lib$(LIBNAME).a : $(OBJ)/eventoHistorico.o $(OBJ)/cronologia.o
	ar rvs $@ $^

$(OBJ)/usoCronologia.o : $(SRC)/usoCronologia.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/eventoHistorico.o : $(SRC)/eventoHistorico.cpp $(INCLUDE)/eventoHistorico.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/cronologia.o : $(SRC)/cronologia.cpp $(INCLUDE)/cronologia.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test: $(BIN)/testEvento

# --- Test ---
$(BIN)/testEvento : $(OBJ)/testEvento.o $(OBJ)/eventoHistorico.o
	$(CXX) -o $@ $^

$(OBJ)/testEvento.o : $(SRC)/testEvento.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<



# ************ Generación de documentación **************
docs:
	@doxygen $(DOC)/doxys/Doxyfile
	@echo "Documentación disponible en $(DOC)/html"


# ************ Limpieza ************

clean:
	-@rm -f $(OBJ)/* $(LIB)/* $(SRC)/*~ $(INC)/*~ ./*~
	@echo "Limpiando..."

mrproper: clean
	-@rm -f $(BIN)/* $(DOC)/html/*
	@echo "Limpieza completada."
