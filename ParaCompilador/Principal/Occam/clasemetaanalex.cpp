#include "clasemetaanalex.h"
ClaseMetaAnalex::ClaseMetaAnalex() {
}
InformacionLexema ClaseMetaAnalex::obtenerLexemaInformacion(void) {
    /* indice para el almacenamiento del lexema de cadena */
    int indiceCadenaLexema = 0;
    /* mantiene el lexema actual que se devolverïo */
    InformacionLexema lexemaActual;
    /* estado actual del automata, siempre comienza en INICIO */
    TipoEstado estado = INICIO;
    /* marca para guardar la cadena en buffer */
    int bGuardarEnIdentificador;
    /* mientras el estado del autïomata no sea HECHO */
    while( estado != HECHO ) {
        char c = obtenerSiguienteCaracter();
        bGuardarEnIdentificador = VERDADERO;
        switch(estado) {
        case INICIO:
            if(c == ';')
            estado = COMENT;
            else if(c == '#')
                estado = ENDIRECTIVA1;
            else if(isalpha(c))
                estado = ENID;

            break;
        case COMENT:
            bGuardarEnIdentificador = FALSO;
            // Salto de linea define fin de comentario despues de un punto y coma
            if( c == '\n' )
            estado = HECHO;
            else
            estado = COMENT;
            //                            fprintf(pArchivoDestino, "%c", c);
            break;
        case ENDIRECTIVA1:
            if(isalpha(c))
                estado = ENDIRECTIVA2;
            break;
        case ENDIRECTIVA2:
            if(isalnum(c))
                estado = ENDIRECTIVA2;
            else
                estado = HECHO;
            break;
        case ENID:
            if(isalnum(c))
                estado = ENID;
            else
                estado = HECHO;
            break;
        case HECHO:
            break;
        default:
            break;
        }
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
