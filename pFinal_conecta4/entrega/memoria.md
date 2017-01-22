---
title: Estructura de Datos - Práctica final, Conecta4
author: Antonio Coín Castro, Miguel Lentisco Ballesteros y José María Martín Luque.
header-includes:
    - \usepackage{pgfplots}
    - \usepackage{pgfplotstable}
    - \usepackage{graphicx}
    - \usepackage{adjustbox}
    - \usepackage[spanish]{babel}
abstract: En este documento se recogen las consideraciones tomadas en el diseño de la IA de conecta4..
---

### Métrica 4

Bajo esta métrica, el jugador automático insertará la ficha en una columna que tenga hueco, elegida aleatoriamente.

### Métrica 3

Utilizando esta métrica, el jugador automático seguirá los siguientes pasos para elegir la columna en la que insertar:

1. Primero intentará buscar una columna en la que insertando su ficha puede ganar. 
2. En caso de que no exista dicha columna, buscará columnas de tal forma que al insertar su ficha, se generen tableros en los que el jugador humano no pueda ganar en ese turno, insertándola en la primera que cumpla dichas condiciones.
3. Si no existe ninguna columna como la descrita en el paso anterior, el jugador humano podrá ganar sin importar dónde insertemos la ficha, por lo que insertamos la ficha en la primera columna en la que sea posible.

Exploramos un segundo nivel del árbol con el fin de evitar programar una función que compruebe si el jugador humano tiene tres fichas alineadas y un hueco libre donde insertar una cuarta que le haga ganar la partida. Estamos primando la **simplicidad** frente a la **eficiencia**.

### Métrica 2.

En esta métrica, el jugador automático se encarga de asignar a cada subárbol que cuelga de cada uno de los hijos del tablero actual una puntuación. Las puntuaciones se asignan de la siguiente forma:

- Por cada tablero en el que el jugador automático pierde, la puntuación disminuye 2 puntos.
- Por cada tablero en el que el jugador automático empata, la puntuación aumenta 1 punto.
- Por cada tablero en el que el jugador automático gana, la puntuación aumenta 2 puntos.

El jugador automático introducirá la ficha en la columna correspondiente al tablero cuyo subárbol tenga más puntuación.
