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
CXXFLAGS  = -Wall -g -std=c++11 -I./$(INCLUDE)

# ******* Fuentes y cabeceras ********
SOURCESMAIN = $(addprefix $(SRC)/, use_stack_max.cpp stack_max.cpp)
SOURCES = $(addprefix $(SRC)/, stack_max_list.cpp stack_max_dvector.cpp stack_max_queue.cpp)
SOURCES += $(addprefix $(INCLUDE)/, list.cpp dvector.cpp queue.cpp)
INC = $(addprefix $(INCLUDE)/, stack_max.hpp list.hpp dvector.hpp queue.hpp node.hpp)
INC += $(addprefix $(INCLUDE)/, stack_max_list.hpp stack_max_dvector.hpp stack_max_queue.hpp)

# ****** Compilación de módulos **********

.PHONY: all test docs clean mrproper

all: $(BIN)/use_stack_max

# -- Programa principal (simplificado) --
$(BIN)/use_stack_max: $(INC) $(SOURCES) $(SOURCESMAIN)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCESMAIN)

# --- Test ---
test: $(BIN)/test_%

$(BIN)/test_%: $(OBJ)/test_%.o
	$(CXX) -o $@ $<

$(OBJ)/test_%.o: $(TEST)/test_%.cpp $(INCLUDE)/%.hpp $(INCLUDE)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PRECIOUS: $(OBJ)/test_%.o

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
