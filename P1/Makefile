
SRC = src
INC = include
OBJ = obj
BIN = bin

PRAC = practica1

CXX = g++
CPPFLAGS = -Wall -g -I$(INC) -c
CPPLFLAGS = -Wall -g

LDFLAGS= -lGLU -lGL -lglut

# ************ Compilación completa ************
#~ all: $(BIN)/ocultar $(BIN)/revelar

# ************ Compilación de los binarios ************
#~ ocultar: $(BIN)/ocultar
#~ revelar: $(BIN)/revelar

# ************ Compilación de módulos ************
# compilación de cada .cpp, dependiendo de sí mismo y de su cabecera
# compilación de cada .cpp primario, dependiendo de sí mismo y de los .o requeridos
# enlazado de cada binario, dependiendo del .o primario (y de esta cuelga el resto de dependencias)
# ejemplo:

#~ $(OBJ)/imagenES.o : $(SRC)/imagenES.cpp $(INC)/imagenES.h
#~ 	$(CXX) $(CPPFLAGS) $(SRC)/imagenES.cpp -o $(OBJ)/imagenES.o
#~ $(OBJ)/codificar.o : $(SRC)/codificar.cpp $(INC)/codificar.h
#~ 	$(CXX) $(CPPFLAGS) $(SRC)/codificar.cpp -o $(OBJ)/codificar.o
#~ $(OBJ)/ocultar.o : $(SRC)/ocultar.cpp $(OBJ)/codificar.o $(OBJ)/imagenES.o
#~ 	$(CXX) $(CPPFLAGS) $(SRC)/ocultar.cpp -o $(OBJ)/ocultar.o
#~ $(OBJ)/revelar.o : $(SRC)/revelar.cpp $(OBJ)/codificar.o $(OBJ)/imagenES.o
#~ 	$(CXX) $(CPPFLAGS) $(SRC)/revelar.cpp -o $(OBJ)/revelar.o
#~ $(BIN)/ocultar : $(OBJ)/ocultar.o
#~ 	$(CXX) $(CPPLFLAGS) $(OBJ)/ocultar.o $(OBJ)/codificar.o $(OBJ)/imagenES.o -o $(BIN)/ocultar
#~ $(BIN)/revelar : $(OBJ)/revelar.o
#~ 	$(CXX) $(CPPLFLAGS) $(OBJ)/revelar.o $(OBJ)/codificar.o $(OBJ)/imagenES.o -o $(BIN)/revelar

# default
default: $(BIN)/$(PRAC)

# enlazado del binario final
$(BIN)/$(PRAC): $(OBJ)/$(PRAC).o $(OBJ)/escena.o $(OBJ)/pyramid.o $(OBJ)/prism.o $(OBJ)/model.o
	$(CXX) $(CPPLFLAGS) $^ -o $(BIN)/$(PRAC) $(LDFLAGS)

# compilación de los distintos módulos
$(OBJ)/escena.o: $(SRC)/escena.cc $(INC)/escena.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/model.o: $(SRC)/model.cc $(INC)/model.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pyramid.o: $(SRC)/pyramid.cc $(INC)/pyramid.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/prism.o: $(SRC)/prism.cc $(INC)/prism.h
	$(CXX) $(CPPFLAGS) $< -o $@

# compilación del primario $(PRAC) - MODIFICAR CONFORME SE AVANCE
$(OBJ)/$(PRAC).o: $(SRC)/$(PRAC).cc $(INC)/escena.h
	$(CXX) $(CPPFLAGS) $< -o $@


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/*
