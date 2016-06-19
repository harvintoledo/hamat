#ifndef NODOARBOL_H
#define NODOARBOL_H

class NodoArbol
{
public:
    NodoArbol();
    /* indice 0 para el nodo del test */
    /* indice 1 puede servir para la rama sino del lenguaje */
    struct NodoArbol *hijo[MAXNUMHIJOS];
    struct NodoArbol *hijoextra; /* hijo extra para informacion */
    struct NodoArbol *siguiente; /* para crear un arbol que tenga varias variables o varias funciones */

    int lineanumero; /* cada nodo mantiene informacion de la linea correspondiente al codigo */

    NodoDescendiente nododescendiente;
    ExpType type; /* para la verficacion del tipo de expresiones */
    char nombre[256];

    union
    {
        TipoArbolSentencia tipoArbolSentencia;
        TipoArbolExpresion tipoArbolExpresion;
    } descendiente;

    union
    {
        TipoLexema tipoLexemaOperador;
        int val;
        char *nombre;
    } atributo;

    double valor;
};

#endif // NODOARBOL_H
