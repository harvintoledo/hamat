#ifndef CLASEMETAANALEX_H
#define CLASEMETAANALEX_H
#include <QString>
#include "claseinformacionlexema.h"
#include "util.h"

class ClaseMetaAnalex {
public:
    ClaseMetaAnalex();
    enum eTipoEstado {
        TIPO_ESTADO_INICIO,
        TIPO_ESTADO_EN_ID,
        TIPO_ESTADO_ENTRADA_COMENT1,
        TIPO_ESTADO_ENTRADA_COMENT2,
        TIPO_ESTADO_HECHO
    };

    enum eTipoLexema {

    };

    // Resultado de análisis, correcto = "true", incorrecto = "false"
    bool isGood() {
        return bmGood;
    }

    QString getInstruccion() {
        return smInstruccion;
    }

    void setInstruccion(QString spInstruccion) {
        smInstruccion = spInstruccion;
    }

    InformacionLexema obtenerLexemaInformacion(void);
    char obtenerSiguienteCaracter(void);
    void deshacerCaracter(void);
    char bSiguienteCaracter(void);
    TipoLexema buscarPalabraReservada(char *s);

    char cadenaDeLexema[MAXIMALONGITUDDELEXEMA+1];
    void setBuffer(QString spBuffer) {
        slBuffer = spBuffer;
    }

    QString getAnalisisLexico() {
        return slAnalisisLexicoResult;
    }

private:
    // Variable booleana para indicar que analisis léxico está correcto
    bool bmGood;
    QString smInstruccion;
    int lineaposicion,
    tamAlmacenamiento,
    lineanumero,
    imPosicionActualCaracter;
    char almacenadorDeLinea[MAXIMALONGITUDDEALAMACENAMIENTO];
    FILE *pArchivoOrigen;
    QString slBuffer,
    slAnalisisLexicoResult;
    QChar ObtenerCaracter();

};

#endif // CLASEMETAANALEX_H
