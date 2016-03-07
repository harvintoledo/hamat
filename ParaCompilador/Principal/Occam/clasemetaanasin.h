#ifndef CLASEMETAANASIN_H
#define CLASEMETAANASIN_H


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
};

#endif // CLASEMETAANASIN_H
