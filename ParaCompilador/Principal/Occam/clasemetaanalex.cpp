#include "clasemetaanalex.h"
ClaseMetaAnalex::ClaseMetaAnalex() {
    imPosicionActualCaracter = 0;
    slBuffer = "";
    slAnalisisLexicoResult = "";
    bmImprimeAnalisisLexico = true;
}
InformacionLexema ClaseMetaAnalex::obtenerLexemaInformacion(void) {
    /* indice para el almacenamiento del lexema de cadena */
    int indiceCadenaLexema = 0;
    /* mantiene el lexema actual que se devolverlo */
    InformacionLexema lexemaActual;
    /* estado actual del automata, siempre comienza en INICIO */
    TipoEstado estado = INICIO;
    /* marca para guardar la cadena en buffer */
    int bGuardarEnIdentificador;
    /* mientras el estado del automata no sea HECHO */
    while( estado != HECHO ) {
        char c = obtenerSiguienteCaracter();
        bGuardarEnIdentificador = VERDADERO;
        switch(estado) {
        case INICIO:
            if(c == ';')
            estado = COMENT;
            else if(c == '#') {
                estado = ENDIRECTIVA1;
            }
            else if(c == '%') {
                estado = ENREGISTRO;
                lexemaActual.lexema = TIPO_LEXEMA_REGISTRO;
            }
            else if(c == '$') {
                estado = ENMEMORIA;
                lexemaActual.lexema = TIPO_LEXEMA_MEMORIA;
            }
            else if(c == '!') {
                estado = ENINMEDIATO;
                lexemaActual.lexema = TIPO_LEXEMA_INMEDIATO;
            }
            else if(c == '|') {
                estado = ENSELECCION;
                lexemaActual.lexema = TIPO_LEXEMA_SELECCION;
            }
            else if(isalpha(c))
            estado = ENID;
            else
            /* ignorar espacios en blanco */
            if( c == ' ' || c == '\t' || c == '\n' ) {
                bGuardarEnIdentificador = FALSO;
                switch(c) {
                case ' ':
                    //fprintf(pArchivoDestino, " ");
                    // imprimir espacio en evaluador
                    break;
                case '\t':
                    break;
                case '\n':
                    // fprintf(pArchivoDestino, "<br>\n");
                    // imprimir espacio en evaludador
                    break;
                }
            }
            break;
        case COMENT:
            bGuardarEnIdentificador = FALSO;
            // Salto de linea define fin de comentario despues de un punto y coma
            if( c == '\n' )
            estado = HECHO;
            else
            estado = COMENT;
            //                            fprintf(pArchivoDestino, "%c", c);
            lexemaActual.lexema = TIPO_LEXEMA_COMENTARIO;
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
        } // fin del switch principal para estados
        if( (bGuardarEnIdentificador) && (indiceCadenaLexema <= MAXIMALONGITUDDELEXEMA))
        cadenaDeLexema[indiceCadenaLexema++] = c;
        if( estado == HECHO) {
            cadenaDeLexema[indiceCadenaLexema] = '\0';
            if( lexemaActual.lexema == ID) {
                lexemaActual.lexema = buscarPalabraReservada(cadenaDeLexema);
            }
            if( cadenaDeLexema != NULL || strlen(cadenaDeLexema) != 0) {
                switch( lexemaActual.lexema ) {
                case TIPO_LEXEMA_REGISTRO:
                    strcpy(lexemaActual.informacion, "%");
                    break;
                case TIPO_LEXEMA_MEMORIA:
                    strcpy(lexemaActual.informacion, "$");
                    break;
                case TIPO_LEXEMA_INMEDIATO:
                    strcpy(lexemaActual.informacion, "!");
                    break;
                case TIPO_LEXEMA_SELECCION:
                    strcpy(lexemaActual.informacion, "|");
                    break;
                default:
                    strcpy(lexemaActual.informacion, cadenaDeLexema);
                }
            }
            lexemaActual.lineanumero = lineanumero;
        }
    } // fin del while principal para los estados del automata
    if(bmImprimeAnalisisLexico) {
        // fprintf(pArchivoDestino, "<br>\n");
        imprimirLexema(lexemaActual.lexema, cadenaDeLexema);
        // listaDeAnalisis = construirListaDeAnalisis(lexemaActual.lexema, cadenaDeLexema);
    }
    return lexemaActual;
}
void ClaseMetaAnalex::imprimirLexema(TipoLexema lex, const char *cadena) {
    switch(lex) {
    case TIPO_LEXEMA_REGISTRO:
        //      fprintf(pArchivoDestino, "<span class=\"nohemi-palabrareservada\">%s</span>", cadena);
        break;
    case TIPO_LEXEMA_MEMORIA:
        //      strcpy(lexemaActual.informacion, "$");
        break;
    case TIPO_LEXEMA_INMEDIATO:
        //      strcpy(lexemaActual.informacion, "!");
        break;
    case TIPO_LEXEMA_SELECCION:
        //      strcpy(lexemaActual.informacion, "|");
        break;
    case FINDEARCHIVO:
        //      fprintf(pArchivoDestino, "EOF");
        break;
    case ID:
        //      fprintf(pArchivoDestino, "<span class=\"nohemi-identificador\">%s</span>", cadena);
        break;
    case IDNUM:
        //      fprintf(pArchivoDestino, "<span class=\"nohemi-numero\">%s</span>", cadena);
        break;
    case IDCADENA:
        //      fprintf(pArchivoDestino, "<span class=\"nohemi-cadena\">&quot;%s&quot;</span>", cadena);
        break;
    case ERROR:
        //      fprintf(pArchivoDestino, "ERROR: %s\n", cadena);
        break;
    default:
        //      fprintf(pArchivoDestino, "Lexema DESCONOCIDO: %s\n", cadena);
        ;
    } /* fin del switch */
} /* fin de la funcion imprimirLexema */
char ClaseMetaAnalex::obtenerSiguienteCaracter(void) {
    if(!(lineaposicion < tamAlmacenamiento) ) {
        lineanumero++;
        // Obtener el caracter desde archivo o cadena ya preparada
        //        if( fgets(almacenadorDeLinea, MAXIMALONGITUDDEALAMACENAMIENTO - 1, pArchivoOrigen) ) {
        if( ObtenerCaracter() != '\0' ) {
            // fprintf(pArchivoDestino, "<br>%s",almacenadorDeLinea);
            tamAlmacenamiento = strlen( almacenadorDeLinea);
            lineaposicion = 0;
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
    for( i = 0; i < MAXIMONUMERODEPALABRASRESERVADAS; i++)
    if( !strcmp(s, palabraReservada[i].cad))
    return palabraReservada[i].tok;
    return ID;
} /* fin de la funcion buscarPalabraReservada */
QChar ClaseMetaAnalex::ObtenerCaracter() {
    QChar c;
    c = slBuffer.at(imPosicionActualCaracter);
    imPosicionActualCaracter++;
    if(imPosicionActualCaracter >= slBuffer.length())
    c = '\0';
    return c;
}
