#include "clasemetaanalex.h"

ClaseMetaAnalex::ClaseMetaAnalex() {

}

InformacionLexema ClaseMetaAnalex::obtenerLexemaInformacion(void) {
    /* indice para el almacenamiento del lexema de cadena */
    int indiceCadenaLexema = 0;

    /* mantiene el lexema actual que se devolverïo */
    InformacionLexema lexemaActual;
    /* estado actual del automata, siempre comienza en INICIO */
    eTipoEstado estado = TIPO_ESTADO_INICIO;

    /* marca para guardar la cadena en buffer */
    int bGuardarEnIdentificador;

    /* mientras el estado del autïomata no sea HECHO */
    while( estado != TIPO_ESTADO_HECHO) {

    }
}

char ClaseMetaAnalex::obtenerSiguienteCaracter(void) {
    if(!(lineaposicion < tamAlmacenamiento) ) {
        lineanumero++;
        if( fgets(almacenadorDeLinea, MAXIMALONGITUDDEALAMACENAMIENTO-1, pArchivoOrigen) ) {
            // fprintf(pArchivoDestino, "<br>%s",almacenadorDeLinea);
            tamAlmacenamiento = strlen( almacenadorDeLinea);
            lineaposicion=0;
            return almacenadorDeLinea[lineaposicion++];
        }
        else
        return EOF;
    }
    else
    return almacenadorDeLinea[lineaposicion++];

} /* fin de la funcion obtenerSiguienteCaracter */


void ClaseMetaAnalex::deshacerCaracter(void) {
    lineaposicion--;
}

char ClaseMetaAnalex::bSiguienteCaracter(void) {
    char c;
    lineaposicion++;
}

TipoLexema ClaseMetaAnalex::buscarPalabraReservada(char *s) {
    int i;

    for(i=0; i < MAXIMONUMERODEPALABRASRESERVADAS; i++)
    if( !strcmp(s, palabraReservada[i].cad))
    return palabraReservada[i].tok;

    return ID;
} /* fin de la funcion buscarPalabraReservada */
