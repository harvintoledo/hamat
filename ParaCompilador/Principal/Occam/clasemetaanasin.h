#ifndef CLASEMETAANASIN_H
#define CLASEMETAANASIN_H
#include "nodoarbol.h"

class ClaseMetaAnaSin
{
public:
    ClaseMetaAnaSin();
    // Resultado de análisis, correcto = "true", incorrecto = "false"
    bool isGood() {
        return bmGood;
    }

    // Variable booleana para indicar que analisis sintáctico está correcto
    bool bmGood;
    NodoArbol *analizarSintaxis( NodoListaLexema *listaLex );
};

#endif // CLASEMETAANASIN_H
