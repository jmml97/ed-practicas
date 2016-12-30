#ifndef __ArbolGeneral_h__
#define __ArbolGeneral_h__

#include <cassert>
#include <algorithm>
#include <queue>
#include <string>
#include <string.h>

using namespace std;

/**
   @brief T.D.A. ArbolGeneral
   
   \b Definición:
   Una instancia \e a del tipo de dato abstracto ArbolGeneral sobre un dominio 
   \e Tbase se puede construir como
   
   - Un objeto vacío (árbol vacío) si no contiene ningún elemento. 
   Lo denotamos {}.
   - Un árbol que contiene un elemento destacado, el nodo raíz, con un valor 
   \e e en el dominio \e Tbase (denominado \e etiqueta), y \e k subárboles 
   \f$(T_1, \ldots, T_k)\f$ del T.D.A. ArbolGeneral sobre \e Tbase.
    
   Se establece una relación \e padre-hijomasalaizquierda-hermanoaladerecha 
   entre cada nodo y los nodos raíz  de los subárboles (si los hubiera) que 
   cuelgan de él.  
   
   Para poder usar el tipo de dato ArbolGeneral se debe incluir el fichero
   
   <tt>\#include ArbolGeneral.h</tt>
   
   El espacio requerido para el almacenamiento es O(n), donde n es el número de
   nodos del árbol.
   
   @author Luis Baca Ruiz.
   @date Diciembre de 2011
*/

template <class Tbase>
class ArbolGeneral{
 /**
  * @brief repConjunto Rep del TDA ArbolGeneral
  *
  * |b Invariante de la representación
  *
  * Sea \e T un Árbol General sobre el tipo \e Tbase. Entonces el
  * invariante de la representación es
  *
  * Si \e T es vacío, entonces T.laraiz vale 0.
  * Si no:
  * - T.laraiz->padre = 0 y
  * - \f$ \forall \f$ n nodo de \e T, n->izqda \f$ \neq \f$ n->drch y
  * - \f$ \forall \f$ n, m nodos de \e T, si n->izqda = m, entonces
  * m->padre = n y
  * - Número de elementos = número elementos de  la raiz, donde
  * N(n) = 1 + N(n->izqda) + (N->drcha),
  * con N(0) = 0.
  *
  * \b Función de abstracción
  *
  * Sea @e T un Árbol General sobre el tipo @e Tbase. Entonces, si lo denotamos
  * también Árbol(T.laraiz), es decir, como el árbol que cuelga de su raíz,
  * entonces este árbol del conjunto de valores en la representación se aplica
  * al árbol.
  *
  * { T.laraiz->etiqueta, {Arbol(T.laraiz->izqda)}, {Arbol(T.laraiz->drcha)} }
  *
  * donde {0} es el árbol vacío.
  */

  private:
    /**
      *@brief nodo
      *
      * En cada  estructura \e nodo se almacena una etiqueta del árbol, que se 
      * implementa como un conjunto de nodos enlazados según la relación 
      * padre-hijo más a la izquierda-hermano derecha.
      */
    struct nodo {
      /**
        *@brief Elemento almacenado
        *
        * En este campo se almacena la etiqueta que corresponde a este nodo.
        */
      Tbase etiqueta;
      
      /**
        * @brief Puntero al hijo más a la izquierda
        *
        * En este campo se almacena un puntero al nodo raíz del subárbol más a 
        * la izquierda, o el valor 0 si no tiene.
        */
      nodo *izqda;
      
      /**
        * @brief Puntero al hermano derecho
        *
        * En este campo se almacena un puntero al nodo raíz del subárbol 
        * hermano derecho, o el valor 0 si no tiene.
        */
      nodo *drcha;

      /**
        * @brief Puntero al padre
        *
        * En este campo se almacena un puntero al nodo padre, o el valor 0 si 
        * es la raíz.
        */
       nodo *padre;
       /**
        * @brief Constructor.
        * Crea un nodo vacio.
        */
       nodo(){ padre = drcha = izqda = 0; }
       /**
        * @brief Constructor con parametros.
        * @param e elemento que se le va a asignar.
        * Crea un nodo a con un elemento.
        */
       nodo(const Tbase & elemento){padre = drcha = izqda = 0; etiqueta = elemento;}
    };
    
    /**
      * @brief Puntero a la raíz.
      *
      * Este miembro es un puntero al primer nodo, que corresponde a la raíz 
      * del árbol. Vale 0 sin el árbol es vacío.
      */
    struct nodo *laraiz;
    
    /**
      * @brief Destruye el subárbol
      * @param n Nodo a destruir, junto con sus descendientes
      *
      * Libera los recursos que ocupan \e n y sus descendientes.
      */
    void destruir(nodo * n);
    
    /**
      * @brief Copia un subárbol
      * @param dest Referencia al puntero del que cuelga la copia
      * @param orig Puntero a la raíz del subárbol a copiar
      *
      * Hace una copia de todo el subárbol que cuelga de \e orig en el puntero
      * \e dest. Es importante ver que en \e dest->padre (si existe) no se 
      * asigna ningún valor, pues no se conoce.
      */
    void copiar(nodo *& dest, nodo * orig);
      
    /**
      * @brief Cuenta el número de nodos
      * @param n Nodo del que cuelga el subárbol de nodos a contabilizar.
      *
      * Cuenta cuántos nodos cuelgan de \e n, incluido éste.
      */
    int contar(const nodo * n) const;

    /**
     * @brief Cuenta el número de hijos.
     * @param n: Nodo padre del que cuelgan los hijos.
     * @return Número de hijos que tiene ese nodo.
     */
    int contar_Hijos(nodo * n) const;
    
    /**
      * @brief Comprueba igualdad de dos subárboles
      * @param n1 Primer subárbol a comparar
      * @param n2 Segundo subárbol a comparar
      *
      * Comprueba si son iguales los subárboles que cuelgan de \e n1 y \e n2. 
      * Para ello deberán tener los mismos nodos en las mismas posiciones y 
      * con las mismas etiquetas.
      */
    bool soniguales(const nodo * n1, const nodo * n2) const;
    
    /**
      * @brief Escribe un subárbol
      * @param out Stream de salida donde escribir
      * @param nod Nodo del que cuelga el subárbol a escribir
      *
      * Escribe en el flujo de salida todos los nodos del subárbol que cuelga 
      * del nodo \e nod siguiendo un recorrido en preorden. La forma de 
      * impresión de cada nodo es:
      *
      * - Si el nodo es nulo, imprime el carácter 'x'.
      * - Si el nodo no es nulo, imprime el carácter 'n' seguido de un 
      * espacio, al que sigue la impresión de la etiqueta
      */
    void escribe_arbol(std::ostream& out, nodo * nod) const;
    
    /**
      * @brief Lee un subárbol
      * @param in Stream de entrada desde el que leer
      * @param nod Referencia al nodo que contendrá el subárbol leído
      *
      * Lee del flujo de entrada \e in los elementos de un árbol según el 
      * formato que se presenta en la función de escritura.
      *
      * @see escribe_arbol
      */
    void lee_arbol(std::istream& in, nodo *& nod);
      
  public:
    /**
      * @brief Tipo Nodo
      * 
      * Este tipo nos permite manejar cada uno de los nodos del árbol. Los 
      * valores que tomará serán tantos como nodos en el árbol (para poder 
      * referirse a cada uno de ellos) y además un valor destacado
      * \e nulo (0), que indica que no se refiere a ninguno de ellos.
      *
      * Una variable \e n de este tipo se declara
      *
      * <tt>ArbolGeneral::Nodo n;</tt>
      *
      * Las operaciones válidas sobre el tipo nodo son:
      *
      * - Operador de Asignación (=).
      * - Operador de comprobación de igualdad (==).
      * - Operador de comprobación de desigualdad (!=).
      */
    typedef struct nodo * Nodo;


    /**
      * @brief Constructor por defecto
      *
      * Reserva los recursos e inicializa el árbol a vacío {}. La operación se
      * realiza en tiempo O(1).
      */
    ArbolGeneral();
    
    /**
      * @brief Constructor de raíz
      * @param e Etiqueta de la raíz
      *
      * Reserva los recursos e inicializa el árbol con un único nodo raíz que 
      * tiene la etiqueta \e e, es decir, el árbol {e, {}, {}}. La operación 
      * se realiza en tiempo O(1).
      */
    ArbolGeneral(const Tbase& e);
    
    /**
      * @brief Constructor de copias
      * @param v ArbolGeneral a copiar
      *
      * Construye el árbol duplicando el contenido de \e v en el árbol 
      * receptor.
      * La operación se realiza en tiempo O(n), donde \e n es el número
      * de elementos de \e v.
      */
    ArbolGeneral (const ArbolGeneral<Tbase>& v);

    /**
      * @brief Destructor
      *
      * Libera los recursos ocupados por el árbol receptor. La operación se 
      * realiza en tiempo O(n), donde n es el número de elementos del árbol 
      * receptor.
      */
    ~ArbolGeneral();
    
    /**
      * @brief Operador de asignación
      * @param v ArbolGeneral a copiar
      * @return Referencia al árbol receptor.
      *
      * Asigna el valor del árbol duplicando el contenido de \e v en el árbol 
      * receptor.
      * La operación se realiza en tiempo O(n), donde \e n es el número de 
      * elementos de \e v.
      */
    ArbolGeneral<Tbase>& operator = (const ArbolGeneral<Tbase> &v);
    
    /**
      * @brief Asignar nodo raíz
      * @param e Etiqueta a asignar al nodo raíz
      *
      * Vacía el árbol receptor y le asigna como valor el árbol de un único 
      * nodo cuya etiqueta es \e e.
      */
    void AsignaRaiz(const Tbase& e);
    
    /**
      * @brief Raíz del árbol
      * @return Nodo raíz del árbol receptor
      *
      * Devuelve el nodo raíz, que es 0 (nulo) si el árbol está vacío.
      * La operación se realiza en tiempo O(1).
      */
    Nodo raiz() const;
    
    /**
      * @brief Hijo más a la izquierda
      * @param n Nodo del que se quiere obtener el hijo más a la izquierda.
      * @pre \e n no es nulo
      * @return Nodo hijo más a la izquierda
      *
      * Devuelve el nodo hijo más a la izquierda de \e n, que valdrá 0 (nulo) 
      * si no tiene hijo más a la izquierda.
      * La operación se realiza en tiempo O(1).
      */
    Nodo hijomasizquierda(const Nodo n) const;
    
    /**
      * @brief Hermano derecha
      * @param n Nodo del que se quiere obtener el hermano a la derecha.
      * @pre \e n no es nulo
      * @return Nodo hermano a la derecha
      *
      * Devuelve el nodo hermano a la derecha de \e n, que valdrá 0 (nulo) 
      * si no tiene hermano a la derecha.
      * La operación se realiza en tiempo O(1).
      */
    Nodo hermanoderecha(const Nodo n) const;
    
    /**
      * @brief Nodo padre
      * @param n Nodo del que se quiere obtener el padre.
      * @pre \e n no es nulo
      * @return Nodo padre
      *
      * Devuelve el nodo padre de \e n, que valdrá 0 (nulo) si es la raíz.
      * La operación se realiza en tiempo O(1).
      */
    Nodo padre(const Nodo n) const;
    
    /**
      * @brief Etiqueta de un nodo
      * @param n Nodo en el que se encuentra el elemento.
      * @pre \e n no es nulo
      * @return Referencia al elemento del nodo \e n
      *
      * Devuelve una referencia al elemento del nodo \e n y por tanto se puede 
      * modificiar o usar el valor.
      * La operación se realiza en tiempo O(1).
      */
    Tbase& etiqueta(const Nodo n);
    
    /**
      * @brief Etiqueta de un nodo
      * @param n Nodo en el que se encuentra el elemento.
      * @pre \e n no es nulo
      * @return Referencia constante al elemento del nodo \e n.
      *
      * Devuelve una referencia al elemento del nodo \e n. Es constante y por 
      * tanto no se puede modificiar el valor.
      * La operación se realiza en tiempo O(1).
      */
    const Tbase& etiqueta(const Nodo n) const;
    
    /**
      * @brief Copia subárbol
      * @param orig Árbol desde el que se va a copiar una rama
      * @param nod Nodo raíz del subárbol que se copia. 
      * @pre \e nod es un nodo del árbol \e orig y no es nulo
      *
      * El árbol receptor acaba con un valor copia del subárbol que cuelga del 
      * nodo \e nod en el árbol \e orig. La operación se realiza en tiempo
      * O(n), donde \e n es el número de nodos del subárbol copiado.
      */
    void asignar_subarbol(const ArbolGeneral<Tbase>& orig, const Nodo nod);
    
    /**
      * @brief Podar subárbol hijo más a la izquierda
      * @param n Nodo al que se le podará la rama hijo más a la izquierda. 
      * @param dest Árbol que recibe la rama cortada
      * @pre \e n no es nulo y es un nodo válido del árbol receptor.
      *
      * Asigna un nuevo valor al árbol \e dest, con todos los elementos del 
      * subárbol izquierdo del nodo \e n en el árbol receptor. Éste se queda 
      * sin dichos nodos.
      *  La operación se realiza en tiempo O(1).
      */
    void podar_hijomasizquierda(Nodo n, ArbolGeneral<Tbase>& dest);
    
    /**
      * @brief Podar subárbol hermano derecha
      * @param n Nodo al que se le podará la rama hermano derecha. 
      * @param dest Árbol que recibe la rama cortada
      * @pre \e n no es nulo y es un nodo válido del árbol receptor.
      *
      * Asigna un nuevo valor al árbol \e dest, con todos los elementos del 
      * subárbol hermano derecho del nodo \e n en el árbol receptor. Éste se 
      * queda sin dichos nodos.
      * La operación se realiza en tiempo O(1).
      */
    void podar_hermanoderecha(Nodo n, ArbolGeneral<Tbase>& dest);
    
    /**
      * @brief Insertar subárbol hijo más a la izquierda
      * @param n: Nodo al que se insertará el árbol \e rama como hijo más a la 
      * izquierda.
      * @param rama Árbol que se insertará como hijo más a la izquierda.
      * @pre \e n no es nulo y es un nodo válido del árbol receptor
      *
      * El árbol \e rama se inserta como hijo más a la izquierda del nodo \e n
      * del árbol receptor. El árbol \e rama queda vacío y los nodos que 
      * estaban en el subárbol hijo más a la izquierda de \e n se desplazan a 
      * la derecha, de forma que el anterior hijo más a la izquierda pasa a ser
      * el hermano a la derecha del nuevo hijo más a la izquierda.
      */
    void insertar_hijomasizquierda(Nodo n, ArbolGeneral<Tbase>& rama);

    /**
      * @brief Insertar subárbol hermano derecha
      * @param n Nodo al que se insertará el árbol \e rama como hermano a la 
      * derecha. 
      * @param rama Árbol que se insertará como hermano derecho.
      * @pre \e n no es nulo y es un nodo válido del árbol receptor
      *
      * El árbol \e rama se inserta como hermano derecho del nodo \e n del 
      * árbol receptor. El árbol \e rama queda vacío y los nodos que estaban a 
      * la derecha del nodo \e n pasan a la derecha del nuevo nodo.
      */
    void insertar_hermanoderecha(Nodo n, ArbolGeneral<Tbase>& rama);
    
    /**
      * @brief Borra todos los elementos
      *
      * Borra todos los elementos del árbol receptor. Cuando termina, el árbol
      * está vacía. La operación se realiza en tiempo O(n), donde \e n es el 
      * número de elementos del árbol receptor.
      */
    void clear();
    
    /**
      * @brief Número de elementos
      * @return El número de elementos del árbol receptor.
      *
      * La operación se realiza en tiempo O(n).
      * @see contar
      */
    int size() const;
    
    /**
      * @brief Vacío
      * @return Devuelve \e true si el número de elementos del árbol receptor 
      * es cero, \e false en caso contrario.
      *
      * La operación se realiza en tiempo O(1).
      */
    bool empty() const;

    /**
     * @brief Altura de un nodo.
     * @param t: Nodo que se calculará la altura.
     * @return Devuelve la altura de un nodo.
     */
    int altura(Nodo t) const;

    /**
     * @brief Arbol reflejado.
     * @param t: Nodo a partir del cual se hará su reflejado.
     */
    void reflejado(Nodo t);
    
    /**
      * @brief Operador de comparación (igualdad)
      * @param v ArbolGeneral con el que se desea comparar.
      * @return Devuelve \e true si el árbol receptor tiene los mismos
      * elementos y en el mismo orden, \e false en caso contrario.
      *
      * La operación se realiza en tiempo O(n).
      * @see soniguales
      */
    bool operator == (const ArbolGeneral<Tbase>& v) const;
    
    /**
      * @brief Operador de comparación (diferencia)
      * @param v ArbolGeneral con el que se desea comparar.
      * @return Devuelve \e true si el árbol receptor no tiene los mismos 
      * elementos y en el mismo orden, \e false en caso contrario.
      *
      * La operación se realiza en tiempo O(n).
      */
    bool operator != (const ArbolGeneral<Tbase>& v) const;

    /**
     * @brief Crea un arbol a partir de sus tres recorridos.
     * @param preorden: Recorrido en preorden.
     * @param inorden: Recorrido en inorden.
     * @param postorden: Recorrido en postorden.
     * @param nuevo: Árbol que vamos a crear.
     * @return Devuelve un arbol cuyos recorridos son esos tres.
     *
     * Dados tres recorridos exite tan solo 1 árbol que concuerda
     * con esos tres recorridos.
     */
    void recuperar_arbol(string preorden, string inorden, string postorden, Nodo nuevo);
      
    /**
      * @brief Operador de extracción de flujo
      * @param in Stream de entrada
      * @param v Árbol que leer
      * @return Referencia al stream de entrada
      *
      * Lee de \e in un árbol y lo almacena en \e v. El formato aceptado para
      * la lectura se puede consultar en la función de salida.
      * @see lee_arbol
      */
    template<class T>
    friend std::istream& operator>>(std::istream& in, ArbolGeneral<T>& v);
    /**
      * @brief Operador de inserción en flujo
      * @param out Stream de salida
      * @param v Árbol que escribir
      * @return Referencia al stream de salida
      *
      * Escribe en la salida todos los nodos del árbol \e v siguiendo un 
      * recorrido en preorden. La forma de impresión de cada nodo es:
      *
      * - Si el nodo es nulo, imprime el carácter 'x'.
      * - Si el nodo no es nulo, imprime el carácter 'n' seguido de un 
      * espacio, al que sigue la impresión de la etiqueta.
      *
      * @see escribe_arbol
      */
    template<class T>
    friend ostream& operator << (ostream& out, const ArbolGeneral<T>& v);


/* ________________________________________________ */
/*|                                                |*/
/*|             CLASE PREORDEN_ITERADOR            |*/
/*|________________________________________________|*/

    class preorden_iterador{
    private:
        Nodo p;
    public:
        /**
         * @brief Constructor por defecto.
         */
        preorden_iterador()
                :p(0)
        {   }
        /**
         * @brief Constructor con nodo.
         * @param n: nodo que se va a copiar.
         */
        preorden_iterador(const Nodo &n)
                 :p(n)
        {   }
        /**
         * @brief Constructor de copia.
         * @param i: iterador que se va a copiar.
         */
        preorden_iterador(const preorden_iterador &i)
                :p(i.p)
        {   }
        /**
         * @brief Acceso a la información del nodo.
         */
        const Tbase& operator*() const{
            assert(p!=0);
            return p->etiqueta;
        }
        Tbase& operator *(){
            assert(p!=0);
            return p->etiqueta;
        }
        /**
         * @brief Operación de igualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son iguales false en caso contrario.
         */
        bool operator==(const preorden_iterador &n){
            return p == n.p;
        }
        /**
         * @brief Operación de desigualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son distintos false en caso contrario.
         */
        bool operator!=(const preorden_iterador &n){
            return p!=n.p;
        }
        /**
         * @brief Nodo del padre.
         * @return Devuelve un nodo apuntando al padre.
         */
        preorden_iterador padre(){
            if(p->padre != 0)
                return preorden_iterador(p->padre);
            else
                return preorden_iterador();
        }
        /**
         * @brief Nodo del hijo.
         * @return devuelve un nodo apuntando al hijo más a la izquierda.
         */
        preorden_iterador izquierda(){
            if(p->izqda != 0)
                return preorden_iterador(p->izqda);
            else
                return preorden_iterador();
        }
        /**
         * @brief Nodo del hermano.
         * @return devuelve un nodo apuntando al hermano de la derecha.
         */
        preorden_iterador hermano(){
            if(p->drcha != 0)
                return preorden_iterador(p->drcha);
            else
                return preorden_iterador();
        }
        /**
         * @brief Informa de si es nulo.
         * @return true si es nulo, false en otro caso.
         */
        bool nulo(){
            return p == 0;
        }
        /**
         * @brief Siguiente elemento.
         * @return Devuelve un iterador al siguiente elemento en preorden.
         */
        preorden_iterador& operator++();

        /**
         * @brief Anterior elemento.
         * @return Devuelv un iterador al elemento anterior en preorden.
         */
        preorden_iterador& operator--();

        friend class ArbolGeneral;
        friend class reverse_preorden_iterador;
    };
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*~~ Funciones BEGIN y END para preorden_iterador ~~*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /**
     * @brief Comienzo de un iterador preorden_iterador
     * @return un iterador de tipo preorden apuntando a la raiz.
     */
    preorden_iterador beginpreorden() const;
    /**
     * @brief Final de un iterador preorden_iterador
     * @return un iterador de tipo preorden_iterador apuntando al final.
     */
    preorden_iterador endpreorden() const;
    /**
     * @brief Recorrido en preorden.
     * @doc Muestra el recorrido del árbol en preorden
     *      usando iteradores.
     */
    void recorrer_preorden() const;
    /**
     * @brief Recorrido en preorden.
     * @param t: Nodo a partir del cual se va a hacer el recorrido.
     * @doc Muestra el el recorrido del árbol en preorden
     *      sin usar iteradores. De forma iterativa.
     */
    void recorrer_preorden2(Nodo t)const;

    /**
     * @brief Recorrido en preorden al reves.
     * @doc Muestra el recorrido del árbol en preorden, pero
     *      al reves. Utilizando iteradores preorden.
     */
    void recorrer_preorden_al_reves() const;


    /* ________________________________________________ */
    /*|                                                |*/
    /*|         CLASE REVERSE_PREORDEN_ITERADOR        |*/
    /*|________________________________________________|*/

    class reverse_preorden_iterador{
    private:
        Nodo p;
    public:
        /**
         * @brief Constructor por defecto.
         */
        reverse_preorden_iterador()
                :p(0)
        {   }
        /**
         * @brief Constructor con nodo.
         * @param n: nodo que se va a copiar.
         */
        reverse_preorden_iterador(const Nodo &n)
                 :p(n)
        {   }
        /**
         * @brief Constructor de copia.
         * @param i: iterador que se va a copiar.
         */
        reverse_preorden_iterador(const reverse_preorden_iterador &i)
                :p(i.p)
        {   }
        /**
         * @brief Acceso a la información del nodo.
         */
        const Tbase& operator*() const{
            assert(p!=0);
            return p->etiqueta;
        }
        Tbase& operator *(){
            assert(p!=0);
            return p->etiqueta;
        }
        /**
         * @brief Operación de igualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son iguales false en caso contrario.
         */
        bool operator==(const reverse_preorden_iterador &n){
            return p == n.p;
        }
        /**
         * @brief Operación de desigualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son distintos false en caso contrario.
         */
        bool operator!=(const reverse_preorden_iterador &n){
            return p!=n.p;
        }
        /**
         * @brief Nodo del padre.
         * @return Devuelve un nodo apuntando al padre.
         */
        reverse_preorden_iterador padre(){
            if(p->padre != 0)
                return reverse_preorden_iterador(p->padre);
            else
                return reverse_preorden_iterador();
        }
        /**
         * @brief Nodo del hijo.
         * @return devuelve un nodo apuntando al hijo más a la izquierda.
         */
        reverse_preorden_iterador izquierda(){
            if(p->izqda != 0)
                return reverse_preorden_iterador(p->izqda);
            else
                return reverse_preorden_iterador();
        }
        /**
         * @brief Nodo del hermano.
         * @return devuelve un nodo apuntando al hermano de la derecha.
         */
        reverse_preorden_iterador hermano(){
            if(p->drcha != 0)
                return reverse_preorden_iterador(p->drcha);
            else
                return reverse_preorden_iterador();
        }
        /**
         * @brief Informa de si es nulo.
         * @return true si es nulo, false en otro caso.
         */
        bool nulo(){
            return p == 0;
        }
        /**
         * @brief Siguiente elemento.
         * @return Devuelve un iterador al siguiente elemento en preorden inverso.
         */
        reverse_preorden_iterador& operator++();

        /**
         * @brief Anterior elemento.
         * @return Devuelv un iterador al elemento anterior en preorden inverso.
         */
        reverse_preorden_iterador& operator--();

        friend class ArbolGeneral;
        friend class preorden_iterador;
    };

    /**
     * @brief Comienzo de un iterador reverse_preorden_iterador
     * @return un iterador de tipo reverse_preorden apuntando al penultimo elemento.
     */
    reverse_preorden_iterador beginreverse_preorden() const;
    /**
     * @brief Final de un iterador reverse_preorden_iterador
     * @return un iterador de tipo preorden_iterador apuntando al primer elemento.
     */
    reverse_preorden_iterador endreverse_preorden() const;
    /**
     * @brief Recorrido en preorden invertido.
     * @doc Muestra el recorrido del árbol en preorden invertido
     *      usando iteradores.
     */
    void recorrer_reverse_preorden() const;

    /**
     * @brief Recorrido en preorden invertido, al reves.
     * @doc Recorrido en preorden normal.
     */

    void recorrer_reverse_preorden_al_reves() const;


    /* ________________________________________________ */
    /*|                                                |*/
    /*|             CLASE INORDEN_ITERADOR             |*/
    /*|________________________________________________|*/

    class inorden_iterador{
    private:
        Nodo p;
    public:
        /**
         * @brief Constructor por defecto.
         */
        inorden_iterador()
                :p(0)
        {   }
        /**
         * @brief Constructor con nodo.
         * @param n: nodo fuente.
         */
        inorden_iterador(const Nodo & n)
                :p(n)
        {   }
        /**
         * @brief Constructor de copia.
         * @param n: nodo fuente.
         */
        inorden_iterador(const inorden_iterador &n)
                :p(n.p)
        {   }
        /**
         * @brief Acceso a la información del nodo.
         */
        const Tbase& operator*()const{
            assert(p!=0);
            return p->etiqueta;
        }
        Tbase& operator*(){
            assert(p!=0);
            return p->etiqueta;
        }
        /**
         * @brief Operación de igualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son iguales false en caso opuesto.
         */
        bool operator ==(const inorden_iterador &n){
            return p == n.p;
        }
        /**
         * @brief Operación de desigualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son desiguales false en caso contrario.
         */
        bool operator!=(const inorden_iterador &n){
            return p != n.p;
        }
        /**
         * @brief Nodo del padre.
         * @return devuelve un nodo apuntando al padre.
         */
        inorden_iterador padre(){
            if(p->padre != 0)
                return inorden_iterador(p->padre);
            else
                return inorden_iterador();
        }
        /**
         * @brief Nodo hijo.
         * @return devuelve un nodo apuntando al hijo más a la izquierda.
         */
        inorden_iterador izquierda(){
            if(p->izqda != 0)
                return inorden_iterador(p->izqda);
            else
                return inorden_iterador();
        }
        /**
         * @brief Nodo hermano.
         * @return Devuelve un nodo apuntando al hermano derecha.
         */
        inorden_iterador derecha(){
            if(p->drcha != 0)
                return inorden_iterador(p->drcha);
            else
                return inorden_iterador();
        }
        /**
         * @brief Dice si un nodo es nulo.
         * @return true si es nulo, false en caso contrario.
         */
        bool nulo(){
            return p == 0;
        }
        /**
         * @brief Siguiente elemento.
         * @return Devuelve un iterador en inorden al siguiente elemento.
         */
        inorden_iterador &operator++();
        friend class ArbolGeneral;
    };
    /**
     * @brief Comienzo de un iterador inorden_iterador
     * @return un iterador de tipo inorden apuntando a la raiz.
     */
    inorden_iterador begininorden() const;

    /**
     * @brief Final de un iterador inorden_iterador.
     * @return Un iterador de tipo inorden apuntando al final.
     */
    inorden_iterador endinorden() const;
    
    /**
     * @brief Recorrido en inorden.
     * @doc Muestra el árbol recorriendolo en inorden
     *      usando iteradores.
     */
    void recorrer_inorden() const;

    /**
     * @brief Recorrido en inorden.
     * @param t: Nodo a partir del cual se hará el recorrido.
     * @doc Muestra el árbol recorriendolo en inorden
     *      sin usar iteradores.
     */
    void recorrer_inorden2(Nodo t)const;

    /* ________________________________________________ */
    /*|                                                |*/
    /*|           CLASE POSTORDEN_ITERADOR             |*/
    /*|________________________________________________|*/

    class postorden_iterador{
    private:
        Nodo p;
        /**
         * @brief Constructor por defecto.
         */
        postorden_iterador()
                :p(0)
        {   }
        /**
         * @brief Constructor con nodo.
         * @param n: nodo fuente.
         */
        postorden_iterador(const Nodo & n)
                :p(n)
        {   }
        /**
         * @brief Constructor de copia.
         * @param n: nodo fuente.
         */
        postorden_iterador(const postorden_iterador &n)
                :p(n.p)
        {   }
        /**
         * @brief Acceso a la información del nodo.
         */
        const Tbase& operator*()const{
            assert(p!=0);
            return p->etiqueta;
        }
        Tbase& operator*(){
            assert(p!=0);
            return p->etiqueta;
        }
        /**
         * @brief Operación de igualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son iguales false en caso opuesto.
         */
        bool operator ==(const postorden_iterador &n){
            return p == n.p;
        }
        /**
         * @brief Operación de desigualdad entre dos posiciones.
         * @param n: nodo con el que se compara.
         * @return true si son desiguales false en caso contrario.
         */
        bool operator!=(const postorden_iterador &n){
            return p != n.p;
        }
        /**
         * @brief Nodo del padre.
         * @return devuelve un nodo apuntando al padre.
         */
        postorden_iterador padre(){
            if(p->padre != 0)
                return postorden_iterador(p->padre);
            else
                return postorden_iterador();
        }
        /**
         * @brief Nodo hijo.
         * @return devuelve un nodo apuntando al hijo más a la izquierda.
         */
        postorden_iterador izquierda(){
            if(p->izqda != 0)
                return postorden_iterador(p->izqda);
            else
                return postorden_iterador();
        }
        /**
         * @brief Nodo hermano.
         * @return Devuelve un nodo apuntando al hermano derecha.
         */
        postorden_iterador derecha(){
            if(p->drcha != 0)
                return postorden_iterador(p->drcha);
            else
                return postorden_iterador();
        }
        /**
         * @brief Dice si un nodo es nulo.
         * @return true si es nulo, false en caso contrario.
         */
        bool nulo(){
            return p == 0;
        }
        /**
         * @brief Siguiente elemento en postorden.
         * @return Devuelve un iterador al siguiente elemento en postorden.
         */
        postorden_iterador &operator++();
        
        friend class ArbolGeneral;
    };

    /**
     * @brief Primer elemento en postorden.
     * @return Devuelve un iterador al primer elemento en
     *         postorden.
     */
    postorden_iterador beginpostorden() const;

    /**
     * @brief Último elmento.
     * @return Devuelve un iterador al último elemento en
     *         postorden.
     */
    postorden_iterador endpostorden() const;

    /**
     * @brief Recorrido en postorden.
     * @doc Recorre el árbol en postorden. Desde la raíz.
     */
    void recorrer_postorden() const;
    /**
     * @brief Recorrido postorden.
     * @param t: Nodo a partir del cual se va a hacer el recorrido.
     * @doc Muestra el recorrido en postorden sin iteradores.
     */
    void recorrer_postorden2(Nodo t) const;

    /**
     * @brief Recorrido por niveles.
     * @param t: Nodo a partir del cual se va a hacer el recorrido.
     * @doc Muestra el recorrido por niveles del Árbol.
     */
    void recorrer_por_niveles(Nodo t) const;
};



/*____________________________________________________________ */
/*____________________________________________________________ */
//               FUNCIONES PRIVADAS
/*____________________________________________________________ */
/*____________________________________________________________ */

template <class Tbase>
void ArbolGeneral <Tbase>::destruir (nodo * n){
    if(n != 0){                                     //Si no es nulo.
        Nodo t, aux;

        t = n->izqda;                               //Vamos recorriendo los hijos
        while( t !=0 ){                             // izquierda.
            aux = t;                                //Y ahora nos encargamos de los
            t = t->drcha;                           // hermanos.
            destruir(aux);
        }
        delete n;
    }
}

/*____________________________________________________________ */

template <class Tbase>
void ArbolGeneral<Tbase>::copiar(nodo * & dest, nodo * orig){
    if(orig != 0){                                  //Nos aseguramos de que tenga algo.
        if(dest->izqda != 0)                        //Si tiene cosas las borramos.
            destruir(dest->izqda);
        dest->izqda = new nodo(orig->etiqueta);     //Copiamos etiqueta.
        
        copiar(dest->izqda, orig->izqda);           //Copiamos hijos.
        if(dest->izqda != 0)
            dest->izqda->padre = dest;              //Copiamos su padre,

        if(orig->drcha != 0){                       //Nos aseguramos que tiene hermanos.
            dest->drcha = new nodo(orig->drcha->etiqueta);
            
            copiar(dest->drcha, orig->drcha);       //Copiamos hermanos.
            if(dest->drcha != 0)
                dest->drcha->padre = dest;          //Copiamos el padre.
        }
    }
}

/*____________________________________________________________ */

template <class Tbase>
int ArbolGeneral<Tbase>::contar(const nodo * n) const{
    int numero_nodos = 0;
    if(n != 0){
        numero_nodos ++;                            //Contamos el nodo en el que estamos,
        numero_nodos += contar(n->izqda);           // cada uno de los que cuelcan de él,
        numero_nodos += contar(n->drcha);           // y finalmente sus hermanos.
    }
    return numero_nodos;
}

template <class Tbase>
int ArbolGeneral<Tbase>::contar_Hijos(nodo * n) const{
    int num_hijos = 0;
    nodo * p = n;
    if(p->izqda != 0){                              //Si tiene hijos.
        for(p = p->izqda; p != 0; p = p->drcha)
            num_hijos++;

    }
    return num_hijos;
}

/*____________________________________________________________ */

template <class Tbase>
bool ArbolGeneral<Tbase>::soniguales(const nodo * n1,const nodo * n2) const{
    if( (n1 == 0) && (n2 == 0) )                    //Si los dos son nulos.
        return true;
    else{
        if( (n1 == 0) || (n2 == 0) )                //Si uno de ellos es nulo y el otro no.
            return false;
        if(n1->etiqueta != n2->etiqueta)            //Si tienen distintas etiquetas.
            return false;
        else
            return soniguales(n1->izqda, n2->izqda) && soniguales(n1->drcha, n2->drcha);
    }
}

/*____________________________________________________________ */

template <class Tbase>
void ArbolGeneral<Tbase>::lee_arbol(std::istream& in, Nodo & nod){
    char c;
    Nodo aux;
    in >> c; //= in.get(); Esto se traga como carácter el ENTER (\n) Y no me interesa.
    if(in){
        if(c == 'x')                                //Final de rama.
            nod = 0;
        else{
            if(c == 'n'){                           //Nuevo nodo.
                Tbase e;
                in >> e;
                nod = new nodo(e);
                lee_arbol(in, nod->izqda);          //Vamos introduciendo en preorden.
                if(nod->izqda != 0)
                    nod->izqda->padre = nod;        //Le decimos quién es su padre.

                if(nod != raiz())                   //La raiz que no tiene hermanos.
                    lee_arbol(in, nod->drcha);

                if(nod->izqda != 0){
                    aux = nod->izqda->drcha;
                    while(aux != 0){
                        aux->padre = nod; //Tienen el mismo padre.
                        aux = aux->drcha;
                    }
                }
            }
        }
    }
}

/*____________________________________________________________ */

template <class Tbase>
void ArbolGeneral<Tbase>::escribe_arbol(std::ostream& out, Nodo nod) const{
    if(nod == 0)
        out << 'x';                                 //Final de rama.
    else{
        out << "n " << nod->etiqueta << " ";               //Nuevo nodo.
        escribe_arbol(out, nod->izqda);             //Vamos a sus hijos,
        escribe_arbol(out, nod->drcha);             // y luego a sus hermanos.
    }

}

/*____________________________________________________________ */
/*____________________________________________________________ */
//               FUNCIONES PUBLICAS
/*____________________________________________________________ */
/*____________________________________________________________ */


template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(){
    laraiz = new nodo;                              //Nuevo nodo vacío.
}

template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(const Tbase& e){
    laraiz = new nodo(e);                           //Un solo nodo con una etiqueta.
}
    
template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral (const ArbolGeneral<Tbase>& v){
    if(v.laraiz == 0)                               //Si el nodo apunta a null.
        laraiz = 0;
    else                                            //Sino,
        copiar(laraiz, v.laraiz);                   // copiamos todo a partir de él.
}
    
template <class Tbase>
ArbolGeneral<Tbase>::~ArbolGeneral(){
    destruir(laraiz);                               //Borramos desde la raiz.
}
    
template <class Tbase>
ArbolGeneral<Tbase>& 
ArbolGeneral<Tbase>::operator = (const ArbolGeneral<Tbase> &v){
    if(this != &v){                                 //Nos aseguramos de que no sea el mismo árbol.
        destruir(laraiz);                           //Borramos y copiamos.
        copiar(laraiz, v.laraiz);
    }
}
    
template <class Tbase>
void ArbolGeneral<Tbase>::AsignaRaiz(const Tbase& e){
    destruir(laraiz);                               //Borramos.
    laraiz = new nodo(e);                           //Y asignamos el elemento a la raiz.
}
    
template <class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::raiz() const{
    return laraiz;                                  //Devolvemos el puntero al nodo raiz.
}
    
template <class Tbase>
typename ArbolGeneral<Tbase>::
Nodo ArbolGeneral<Tbase>::hijomasizquierda(const Nodo n) const{
    return n->izqda;                                //Devolvemos el puntero al nodo hijo izquierda.
}
    
template <class Tbase>
typename ArbolGeneral<Tbase>::
Nodo ArbolGeneral<Tbase>::hermanoderecha(const Nodo n) const{
    return n->drcha;                                //Devolvemos el puntero al nodo hermano.
}
    
template <class Tbase>
typename ArbolGeneral<Tbase>::
Nodo ArbolGeneral<Tbase>::padre(const Nodo n) const{
    return n->padre;                                //Devolvemos el puntero al nodo padre.
}
    
template <class Tbase>
Tbase& ArbolGeneral<Tbase>::etiqueta(const Nodo n){
    return n->etiqueta;                             //Devolvemos la etiqueta.
}
    
template <class Tbase>
const Tbase& ArbolGeneral<Tbase>::etiqueta(const Nodo n) const{
    return n->etiqueta;                             //Devolvemos la etiquetas.
}

template <class Tbase>
void ArbolGeneral<Tbase>::
asignar_subarbol(const ArbolGeneral<Tbase>& orig, const Nodo nod){
    if(this != &nod){                               //Nos aseguramos que no vamos a copiar el mismo árbol.
        destruir(laraiz);                           //Borramos desde la raiz, lo que teníamos.
        copiar(laraiz, nod);                        //Copiamos el subárbol.
        laraiz->drcha = 0;
        laraiz->padre = 0;
    }
}
    
template <class Tbase>
void ArbolGeneral<Tbase>::
podar_hijomasizquierda(Nodo n, ArbolGeneral<Tbase>& dest){
    destruir(dest.laraiz);                          //Si tiene algo lo borramos.
    if(n->izqda != 0){
        dest.laraiz = n->izqda;                     //Ubicamos en dest lo que queremos podar.
        if(n->izqda != 0)
            n->izqda = n->izqda->drcha;             //Reestructuramos el árbol.

        dest.laraiz->drcha = 0;
        dest.laraiz->padre = 0;
    }
}
    
template <class Tbase>
void ArbolGeneral<Tbase>::
podar_hermanoderecha(Nodo n, ArbolGeneral<Tbase>& dest){
    destruir(dest.laraiz);                          //Eliminamos lo que teníamos si hubiese algo.
    dest.laraiz = n->drcha;                         //Lo colocamos en su lugar.
    n->drcha = n->drcha->drcha;                     //Su hermano ahora será (si tiene) el hermano de este.
    dest.laraiz->padre = 0;                         //Sin padre.
    dest.laraiz->drcha = 0;                         //Sin hermanos.
}
    
template <class Tbase>
void ArbolGeneral<Tbase>::
insertar_hijomasizquierda(Nodo n, ArbolGeneral<Tbase>& rama){
    Nodo aux = n->izqda;                            //Señalamos al futuro hermano derecha.
    n->izqda = rama.laraiz;                         //Ponemos en su sitio la rama que queríamos.
    n->izqda->padre = n;                            //Su padre ahora es el nodo n.
    n->izqda->drcha = aux;                          //Y ponemos a su hermano en su sitio.

    rama.laraiz = 0;                                //Y la rama queda vacía.
}
    
template <class Tbase>
void ArbolGeneral<Tbase>::
insertar_hermanoderecha(Nodo n, ArbolGeneral<Tbase>& rama){
    Nodo aux = n->drcha;                            //Para no perder a su hermano.
    n->drcha = rama.laraiz;
    n->drcha->padre = n->padre;                     //Asignamos el mismo padre.
    n->drcha->drcha = aux;                          //Y el antiguo hermano de 'n'.

    rama.laraiz = 0;                                //Rama queda vacía.
}
    
template <class Tbase>
void ArbolGeneral<Tbase>::clear(){
    destruir(laraiz);
    laraiz = 0;
}
    
template <class Tbase>
int ArbolGeneral<Tbase>::size() const{
    return contar(laraiz);                          //Contamos el número de nodos.
}
    
template <class Tbase>
bool ArbolGeneral<Tbase>::empty() const{
    return laraiz == 0;                               //Vemos si la raíz vale 0.
}

template <class Tbase>
int ArbolGeneral<Tbase>::altura(Nodo t) const{
    int h = 0;
    int max = 0;
    int tmp = 0;
    Nodo p(t);
    if(p->izqda != 0){                              //Si hay hijo.
        ++h;                                        //Aumenta en altura.
        for(p = p->izqda; p != 0; p = p->drcha){    //Ahora de las alturas de los hijos,
            tmp = altura(p);                        // buscamos al que tenga una altura
            if(max < tmp)                           // mayor y con esa nos quedamos.
                max = tmp;
        }
        return max + h;                             //La altura será la suma de la más grande +1 puesto que tiene hijos.
    }
    else                                            //Si no tiene hijos.
        return 0;                                   //No tiene altura.
}

template <class Tbase>
void ArbolGeneral<Tbase>::reflejado(Nodo t){
    int num_hijos = contar_Hijos(t);
    ArbolGeneral<Tbase> aux;

    if(num_hijos > 1){                              //Si hay más de 1 hijo se puede permutar.
        Nodo hijo_izqda = t->izqda;                 //Este deberá estar a la derecha del todo.
        reflejado(hijo_izqda);                      //Reflejamos al que se va a estar moviendo.
        while(hijo_izqda->drcha != 0){              //Mientras tenga hermanos.
            podar_hermanoderecha(hijo_izqda, aux);  //Podamos sus hermanos.
            reflejado(aux.laraiz);                  //Reflejamos al resto.
            insertar_hijomasizquierda(t, aux);      //Ahora mi padre tiene un nuevo hijo más a la izquierda.
        }
    }
}
    
template <class Tbase>
bool ArbolGeneral<Tbase>::operator == (const ArbolGeneral<Tbase>& v) const{
    return soniguales(this->laraiz, v.laraiz);     //Comparamos desde la raíz.
}
    
template <class Tbase>
bool ArbolGeneral<Tbase>::operator != (const ArbolGeneral<Tbase>& v) const{
    return !(*this == v);                           
}

template <class Tbase>
void ArbolGeneral<Tbase>::recuperar_arbol(string preorden, string inorden, string postorden, Nodo nuevo){
    if(preorden[0] == postorden[postorden.size()-1]){       //Si el primer elemento en preorden es el último en postorden. Subárbol del que cuelga el resto.
        string preorden_izqda, inorden_izqda, postorden_izqda;
        string preorden_drcha, inorden_drcha, postorden_drcha;
        if(nuevo == 0)
            nuevo = new nodo(preorden[0]);
        else
            nuevo->etiqueta = preorden[0];                  //Creamos la raiz.

        inorden_izqda = inorden;
        inorden_drcha = inorden;
        while(inorden_izqda[inorden_izqda.size()-1] != preorden[0])
            inorden_izqda.erase(inorden_izqda.end()-1);     //Quitamos el resto de elementos.
        inorden_izqda.erase(inorden_izqda.end()-1);         //Borramos el primer elemento en preorden.
        while(inorden_drcha[0] != preorden[0])
            inorden_drcha.erase(inorden_drcha.begin());
        inorden_drcha.erase(inorden_drcha.begin());         //Borramos el primer elemento en preorden.

        postorden_izqda = postorden;
        postorden_drcha = postorden;
        while(postorden_izqda.size() != inorden_izqda.size())
            postorden_izqda.erase(postorden_izqda.end()-1);
        postorden_drcha.erase(postorden_drcha.end()-1);     //Borramos el primer elemento en preorden.
        while(postorden_drcha.size() != inorden_drcha.size())
            postorden_drcha.erase(postorden_drcha.begin());

        preorden_izqda = preorden_drcha = preorden;
        preorden_izqda.erase(preorden_izqda.begin());       //Borramos la raiz. (Ya la hemos puesto).
        while(preorden_izqda.size() != inorden_izqda.size())
            preorden_izqda.erase(preorden_izqda.end()-1);   //Borramos el resto de elementos.
        while(preorden_drcha.size() != inorden_drcha.size())
            preorden_drcha.erase(preorden_drcha.begin());
            
        if(preorden_izqda.size() != 0 && postorden_izqda.size() != 0 && inorden_izqda.size() != 0){
            nuevo->izqda = new nodo;
            recuperar_arbol(preorden_izqda, inorden_izqda, postorden_izqda, nuevo->izqda);
            if(nuevo->izqda != 0)
                nuevo->izqda->padre = nuevo;
        }
        if(preorden_drcha.size() != 0 && postorden_drcha.size() != 0 && inorden_drcha.size() != 0){
            nuevo->izqda->drcha = new nodo;
            recuperar_arbol(preorden_drcha, inorden_drcha, postorden_drcha, nuevo->izqda->drcha);
            typename ArbolGeneral<Tbase>::Nodo n = nuevo->izqda;
            while(n != 0){                                  //Decimos a cada hijo quién es su padre.
                n->padre = nuevo;
                n = n->drcha;
            }
        }
    }
    else{                                                   //Tenemos un recorrido donde hay un subarbol independiente.
                                                            // esto quiere decir que la raiz tiene hermanos.
        string preorden_izqda, inorden_izqda, postorden_izqda;
        string preorden_drcha, inorden_drcha, postorden_drcha;

        postorden_izqda = postorden_drcha = postorden;
        while(postorden_izqda[postorden_izqda.size()-1] != preorden[0])
            postorden_izqda.erase(postorden_izqda.end()-1); //Borramos el subarbol independiente.
        while(postorden_drcha.size() != (postorden.size()-postorden_izqda.size()) )
            postorden_drcha.erase(postorden_drcha.begin()); //El resto de elementos estará en la parte que queda.

        preorden_izqda = preorden_drcha = preorden;
        while(preorden_izqda.size() != postorden_izqda.size())
            preorden_izqda.erase(preorden_izqda.end()-1);
        while(preorden_drcha.size() != postorden_drcha.size())
            preorden_drcha.erase(preorden_drcha.begin()-1);

        inorden_izqda = inorden_drcha = inorden;
        while(inorden_izqda.size() != preorden_izqda.size())//Habrá los mismos elementos, obviamente.
            inorden_izqda.erase(inorden_izqda.end()-1);
        while(inorden_drcha.size() != preorden_drcha.size())
            inorden_drcha.erase(inorden_drcha.begin());     //Dejamos a la derecha el resto de elementos.

        if(preorden_izqda.size() != 0 && postorden_izqda.size() != 0 && inorden_izqda.size() != 0){
            recuperar_arbol(preorden_izqda, inorden_izqda, postorden_izqda, nuevo);
        }
        if(preorden_drcha.size() != 0 && postorden_drcha.size() != 0 && inorden_drcha.size() != 0){
            nuevo->drcha = new nodo;
            recuperar_arbol(preorden_drcha, inorden_drcha, postorden_drcha, nuevo->drcha);
        }
    }
    laraiz = nuevo;
}
    
template<class T>
istream& operator >> (istream& in, ArbolGeneral<T>& v){
    v.lee_arbol(in, v.laraiz);
    return in;
}
    
template<class Tbase>
ostream& operator << (ostream& out, const ArbolGeneral<Tbase>& v){
    v.escribe_arbol(out, v.laraiz);
    return out;
}


/*---------------------------------------------------------*/
/*----------------------Operators ++-----------------------*/
/*---------------------------------------------------------*/
template<class Tbase>
typename ArbolGeneral<Tbase>::preorden_iterador & ArbolGeneral<Tbase>::preorden_iterador::operator ++(){
    if(p == 0)
        return *this;
    if(p->izqda != 0)                               //Le toca al hijo más a la izquierda.
        p = p->izqda;
    else if(p->drcha != 0)                          //Le toca a su hermano.
        p = p->drcha;
    else{                                           //Subimos mientras no haya heramanos a la derecha.
        while((p->padre != 0)
                && ( p->padre->drcha == 0))
            p = p->padre;
        if(p->padre == 0)                           //Si es la raiz hemos acabado.
            p = 0;
        else
            p = p->padre->drcha;
    }
    return *this;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::reverse_preorden_iterador&
ArbolGeneral<Tbase>::reverse_preorden_iterador::operator ++(){
    typename ArbolGeneral<Tbase>::preorden_iterador it(p);
    --it;
    p = it.p;
    
    return *this;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::inorden_iterador & ArbolGeneral<Tbase>::inorden_iterador::operator ++(){
    if(p == 0)
        return *this;

    if((p->izqda != 0) && p->izqda->drcha != 0){    //Si tengo hijos y más de uno.
            p = p->izqda->drcha;                    //Le toca al hijo que esté a la derecha.
            while(p->izqda != 0)
                 p = p->izqda;
    }
    else if((p->padre != 0) && p->padre->izqda == p){//Si soy hijo más a la izquierda y no tengo hijos.
        p = p->padre;                               //Le toca a mi padre.
    }
    else{                                           //Si no tengo hijos, y no soy hijo más a la izquierda.
        if(p->drcha != 0){                          //Si tengo hermanos.
            p = p->drcha;                           //Le toca al descendiente más a la izquierda de mi hermano.
            while(p->izqda != 0)
                p = p->izqda;
        }
        else{                                       //No tengo hermanos ni hijos.
            while((p->padre != 0)                   //Busco a mi ancestro del cual yo sea
                    && (p->padre->izqda != p)){     // su hijo más a la izquierda,
                if(p->padre->drcha != 0){           // o tenga hermanos.
                    p = p->padre->drcha;
                    while(p->izqda != 0)
                        p = p->izqda;
                    return *this;
                }
                p = p->padre;                       //Subimos la rama.
            }
            p = p->padre;                           //Le tocaría al padre.
        }
    }
    return *this;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::postorden_iterador& ArbolGeneral<Tbase>::postorden_iterador::operator ++(){
    if(p->drcha != 0){                                  //Si tengo a alguien a la derecha.
        p = p->drcha;                                   //Vamos al descendiente más que esté
        while(p->izqda != 0)                            // más a la izquierda.
            p = p->izqda;
    }
    else{                                               //Si no tengo hermanos.
        if(p->padre != 0)                               //Si tengo padre.
            p = p->padre;                               //Le toca a él.
        else
            p = 0;                                      //No tengo padre, hemos acabado.
    }
    return *this;
}

/************************Operador--**********************/
template<class Tbase>
typename ArbolGeneral<Tbase>::preorden_iterador& ArbolGeneral<Tbase>::preorden_iterador::operator --(){
    if(p == 0)
        return *this;                          //<---------------------------------????Cómo recuperamos el árbol, ¿cómo sabemos cual es el árbol??
    else{
        if(p->padre != 0){                          //Si tengo padre.
            typename ArbolGeneral<Tbase>::preorden_iterador sig(p->padre);
            typename ArbolGeneral<Tbase>::preorden_iterador it(p->padre);
            while(++sig != p){                      //Ahora me busco.
                ++it;                               //Le tocará al penúltimo.
            }
            p = it.p;
            return *this;
        }
        else{                                       //Estamos en la raíz.
            p = 0;
            return *this;
        }
    }
}

template <class Tbase>
typename ArbolGeneral<Tbase>::reverse_preorden_iterador&
ArbolGeneral<Tbase>::reverse_preorden_iterador::operator --(){
    typename ArbolGeneral<Tbase>::preorden_iterador it(p);
    ++it;
    p = it.p;
    return *this;
}

template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_preorden_al_reves() const{
    typename ArbolGeneral<Tbase>::preorden_iterador it;
    typename ArbolGeneral<Tbase>::preorden_iterador sig;
    it  = beginpreorden();
    sig = beginpreorden();
    while(++sig != endpreorden())                       //Buscamos el penúltimo.
        ++it;
    for( ; it != beginpreorden(); --it)
        cout << *it << " ";
    cout << *it;
}

template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_reverse_preorden_al_reves() const{
    typename ArbolGeneral<Tbase>::reverse_preorden_iterador it;
    for(it = endreverse_preorden(); it != beginreverse_preorden(); --it)
        cout << *it << " ";
    cout << *it;
}
/************************************************************/
/*----------------------Recorridos--------------------------*/
/************************************************************/
template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_preorden() const{
    typename ArbolGeneral<Tbase>::preorden_iterador it;
    for(it = beginpreorden(); it != endpreorden(); ++it)
        cout << *it << " ";
}
template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_preorden2(Nodo t) const{
    if(t != 0){
        cout << t->etiqueta << " ";
        for(Nodo aux = t->izqda; aux != 0; aux = aux->drcha)
            recorrer_preorden2(aux);
    }
}

template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_reverse_preorden() const{
    typename ArbolGeneral<Tbase>::reverse_preorden_iterador it;
    for(it = beginreverse_preorden(); it != endreverse_preorden(); ++it)
        cout << *it << " ";
    cout << *it;                                        //Imprimimos el último.
}

template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_inorden() const{
    typename ArbolGeneral<Tbase>::inorden_iterador it;
    for(it = begininorden(); it != endinorden(); ++it)
        cout << *it << " ";
}
template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_inorden2(Nodo t) const{
    if(t != 0){
        Nodo aux = t->izqda;
        if(aux != 0){
            recorrer_inorden2(aux);
            aux = aux->drcha;
        }
        cout << t->etiqueta << " ";
        while(aux != 0){
            recorrer_inorden2(aux);
            aux = aux->drcha;
        }
    }
}

template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_postorden() const{
    typename ArbolGeneral<Tbase>::postorden_iterador it;
    for(it = beginpostorden(); it != endpostorden(); ++it)
        cout << *it << " ";
}
template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_postorden2(Nodo t) const{
    if(t != 0){
        for(Nodo aux = t->izqda; aux != 0; aux = aux->drcha)
            recorrer_postorden2(aux);
        cout << t->etiqueta << " "; 
    }
}

template<class Tbase>
void ArbolGeneral<Tbase>::recorrer_por_niveles(Nodo t) const{
    if(t != 0){
        queue<Nodo> cola;
        cola.push(t);
        while(!cola.empty()){
            Nodo aux;
            aux = cola.front();
            cola.pop();
            cout << aux->etiqueta << " ";
            for(aux = aux->izqda; aux != 0; aux = aux->drcha)
                cola.push(aux);
        }
    }
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~Funciones BEGIN y END~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template<class Tbase>
typename ArbolGeneral<Tbase>::preorden_iterador ArbolGeneral<Tbase>::beginpreorden() const{
    typename ArbolGeneral<Tbase>::preorden_iterador nuevo(laraiz);
    return nuevo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::preorden_iterador ArbolGeneral<Tbase>::endpreorden() const{
    typename ArbolGeneral<Tbase>::preorden_iterador nuevo(0);
    return nuevo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::reverse_preorden_iterador ArbolGeneral<Tbase>::beginreverse_preorden() const{
    typename ArbolGeneral<Tbase>::preorden_iterador it;
    typename ArbolGeneral<Tbase>::preorden_iterador sig;
    it  = beginpreorden();
    sig = beginpreorden();
    while(++sig != endpreorden())                           //Buscamos el penúltimo elemento.
        ++it;
    return ArbolGeneral<Tbase>::reverse_preorden_iterador(it.p);
}

template<class Tbase>
typename ArbolGeneral<Tbase>::reverse_preorden_iterador ArbolGeneral<Tbase>::endreverse_preorden() const{
    return ArbolGeneral<Tbase>::reverse_preorden_iterador(beginpreorden().p);//El último es el primero en preorden.
}

template<class Tbase>
typename ArbolGeneral<Tbase>::inorden_iterador ArbolGeneral<Tbase>::begininorden() const{
    Nodo n = laraiz;
    if(n != 0)
        while(n->izqda != 0)                                //El primero será aquél
            n = n->izqda;                                   // hijo que esté más a la
    typename ArbolGeneral<Tbase>::inorden_iterador nuevo(n);// izquierda.
    return nuevo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::inorden_iterador ArbolGeneral<Tbase>::endinorden() const{
    typename ArbolGeneral<Tbase>::inorden_iterador nuevo(0);
    return nuevo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::postorden_iterador ArbolGeneral<Tbase>::beginpostorden() const{
    Nodo n = laraiz;

    while(n->izqda != 0)                                    //El primero será el que esté más
        n = n->izqda;                                       // a la izquierda.
    typename ArbolGeneral<Tbase>::postorden_iterador nuevo(n);
    return nuevo;
}

template<class Tbase>
typename ArbolGeneral<Tbase>::postorden_iterador ArbolGeneral<Tbase>::endpostorden() const{
    typename ArbolGeneral<Tbase>::postorden_iterador nuevo(0);
    return nuevo;
}


#endif
