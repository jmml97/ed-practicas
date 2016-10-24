# ****** Directorios ********
INCLUDE   = include
LIB       = lib
OBJ       = obj
SRC       = src
BIN       = bin

# ****** Opciones de compilación ********
AR        = ar
CXX       = g++
CXXFLAGS  = -Wall -g -c -I./$(INCLUDE)
LDFLAGS   = -L./$(LIB)
LDLIBS    = -lcronologia

# ****** Compilación de módulos **********
$(BIN)/pruebaCronologia : $(OBJ)/pruebacronologia.o $(LIB)/libcronologia.a
	$(CXX) $(LDFLAGS)-o $@ $^ $(LDLIBS)

$(LIB)/libcronologia.a : $(OBJ)/eventoHistorico.o $(OBJ)/cronologia.o
	ar rvs $@ $^

$(OBJ)/eventoHistorico.o : $(SRC)/eventoHistorico.cpp $(INCLUDE)/eventoHistorico.hpp
	$(CXX) $(CXXFLAGS) -o $@ $< 

$(OBJ)/cronologia.o : $(SRC)/cronologia.cpp $(INCLUDE)/cronologia.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# *********** Generación de documentación **************
docs:
	@doxygen doc/doxys/Doxyfile
  @echo "Documentación generada en $(DOC)/html"


# ************ Limpieza ************
clean :
	-@rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~
  @echo "Limpiando..."

mrproper : clean
	-@rm $(BIN)/* doc/html/*
  @echo "Limpieza completada." 
