# ****** Directorios ********
INCLUDE   = include
LIB       = lib
OBJ       = obj
SRC       = src
BIN       = bin
DOC       = doc
TEST      = $(SRC)/test

# ****** Opciones de compilación ********
RM        = rm -f
CXX       = g++
CXXFLAGS  = -Wall -g -c -std=c++11 -I./$(INCLUDE)

# ******* Archivos de cabecera
HPP_FILES = $(addprefix $(INCLUDE)/, *)

# ****** Compilación de módulos **********

.PHONY: all docs clean mrproper

all: $(BIN)/use_queue_max

# -- Programa principal --
$(BIN)/use_queue_max: $(OBJ)/use_queue_max.o $(OBJ)/queue_max.o
	$(CXX) -o $@ $^

$(OBJ)/use_queue_max.o: $(SRC)/use_queue_max.cpp $(INCLUDE)/queue_max.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJ)/queue_max.o: $(SRC)/queue_max.cpp $(HPP_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $<

# --- Test ---
$(BIN)/test_stack: $(OBJ)/test_stack.o
	$(CXX) -o $@ $<

$(OBJ)/test_stack.o: $(TEST)/test_stack.cpp $(INCLUDE)/stack.hpp $(INCLUDE)/stack.cpp $(INCLUDE)/node.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# ************ Generación de documentación **************
docs:
	@doxygen $(DOC)/doxys/Doxyfile
	@echo "Documentación disponible en $(DOC)/html"

# ************ Limpieza ************

clean:
	@$(RM) $(OBJ)/* $(SRC)/*~ $(INCLUDE)/*~ ./*~
	@echo "Limpiando..."

mrproper: clean
	@$(RM) $(BIN)/* $(LIB)/* $(DOC)/html/*
	@echo "Limpieza completada."
