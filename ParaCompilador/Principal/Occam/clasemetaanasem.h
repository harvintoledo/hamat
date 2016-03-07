#ifndef CLASEMETAANASEM_H
#define CLASEMETAANASEM_H


class ClaseMetaAnaSem
{
public:
    ClaseMetaAnaSem();
    // Resultado de análisis, correcto = "true", incorrecto = "false"
    bool isGood() {
        return bmGood;
    }

    // Variable booleana para indicar que analisis semántico está correcto
    bool bmGood;
};

#endif // CLASEMETAANASEM_H
