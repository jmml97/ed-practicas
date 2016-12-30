#include "tablero.h"
#include <iostream>

using namespace std;

void Tablero::reserve() {
    this->tablero.resize(filas);
    for(int i = 0; i < filas ; i ++){
        this->tablero[i].resize(columnas);
        for(int j = 0; j < columnas; j++)
            this->tablero[i][j] = 0;
    }
}

Tablero::Tablero() : filas(5), columnas(7) {
    turno = 1;
    reserve();
}

Tablero::Tablero(const int filas, const int columnas) :
    filas(filas), columnas(columnas) {
    turno = 1;
    reserve();
}

Tablero::~Tablero() {}

Tablero::Tablero(const Tablero& t) :
    tablero(t.tablero), filas(t.filas), columnas(t.columnas), turno(t.turno) {
}

int Tablero::hayHueco(int pos){
    int i = 0;          // Recorremos la matriz de arriba hacia abajo.
    bool encontrado = false;

    // Comprobamos si la posición no está dentro del tablero.
    if(pos < 0 || pos >= columnas) 
        return -1;
    
    while(i < filas && !encontrado){
        if(this->tablero[i][pos] != 0)
            encontrado = true;
        else
            i++;
    }

    // Si no hay piezas.
    if(!encontrado && i == filas)
        return filas - 1;
    else if(i < filas && i >= 0)
        return i-1;
    else
        return -1;
}

bool Tablero::colocarFicha(int pos) {
    int fila;

    // Comprobamos que hay espacio en la columna.
    fila = hayHueco(pos);
    if(fila != -1){
        this->tablero[fila][pos] = turno;
        return true;
    }
    return false;
}

int Tablero::cambiarTurno(){
    if(turno == 1) turno = 2;
    else turno = 1;
    return turno;
}

void Tablero::SetTablero(vector<vector<int> > tablero) {
    int filas1, filas2, columnas1, columnas2;
    filas1 = GetFilas();
    filas2 = tablero.size();
    columnas1 = GetColumnas();
    columnas2 = tablero[1].size();
    
    // Si tiene la misma dimensión.
    if(filas1 == filas2 && columnas1 == columnas2){
        this->tablero = tablero;
    }
    else{
        cout << "Se han intentado igualar tableros de distintas dimensiones." << endl;
    }
}

Tablero& Tablero::operator=(const Tablero& derecha) {
    // Comprobamos que no se está copiando el mismo objeto.
    if (this == &derecha) 
        return *this; 
    // Asignamos el tablero de la derecha en la igualdad.
    SetTablero(derecha.GetTablero());
    return *this;
}

ostream& operator<<(ostream& os, const Tablero& t) {
    os << t.GetTablero();
    return os;
}

int Tablero::quienGana(){
    int ganador = 0;
    int count = 0;
    int i, j;
    int aux, aux2;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {

            // comprobar columnas
            count = 0;

            for (int k = 0; k < N_FICHAS_GANAR
                    && i + k < filas; k++) {

                if (tablero[i + k][j] != 0) {
                    if (count == 0) {
                        ganador = tablero[i + k][j];
                        aux = i + k;
                        aux2 = j + k;
                        count++;
                    } else {
                        if (ganador == tablero[i + k][j]) {
                            aux = i + k;
                            aux2 = j;
                            count++;
                        } else {
                            count = 0;
                            break;
                        }
                    }
                    if (count == N_FICHAS_GANAR) {
                        return ganador;
                    }
                } else {
                    break;
                }
            }

            // comprobar filas
            count = 0;

            for (int k = 0; k < N_FICHAS_GANAR
                    && j + k < columnas; k++) {

                if (tablero[i][j + k] != 0) {
                    if (count == 0) {
                        ganador = tablero[i][j + k];
                        aux = i + k;
                        aux2 = j + k;
                        count++;
                    } else {
                        if (ganador == tablero[i][j + k]) {
                            aux = i;
                            aux2 = j + k;
                            count++;
                        } else {
                            count = 0;
                            break;
                        }
                    }
                    if (count == N_FICHAS_GANAR) {
                        return ganador;
                    }
                } else {
                    break;
                }
            }

            // comprobar diagonal 1
            count = 0;

            for (int k = 0; k < N_FICHAS_GANAR
                    && i + k < filas
                    && j + k < columnas; k++) {

                if (tablero[i + k][j + k] != 0) {
                    if (count == 0) {
                        ganador = tablero[i + k][j + k];
                        aux = i + k;
                        aux2 = j + k;
                        count++;
                    } else {
                        if (ganador == tablero[i + k][j + k]) {
                            aux = i + k;
                            aux2 = j + k;
                            count++;
                        } else {
                            count = 0;
                            break;
                        }
                    }
                    if (count == N_FICHAS_GANAR) {
                        return ganador;
                    }
                } else {
                    break;
                }
            }

            // comprobar diagonal 2

            count = 0;
            for (int k = 0; k < N_FICHAS_GANAR && i - k >= 0
                    && j + k < columnas; k++) {
                if (tablero[i - k][j + k] != 0) {
                    if (count == 0) {
                        ganador = tablero[i - k][j + k];
                        aux = i - k;
                        aux2 = j + k;
                        count++;
                    } else {
                        if (ganador == tablero[i - k][j + k]) {
                            aux = i - k;
                            aux2 = j + k;
                            count++;
                        } else {
                            count = 0;
                            break;
                        }
                    }
                    if (count == N_FICHAS_GANAR) {
                        return ganador;
                    }
                } else {
                    break;
                }
            }
        }
    }
    return 0;
}
