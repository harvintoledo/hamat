/* Archivo instrucciones.l */
%{
#include <stdio.h>
#include "y.tab.h" /* Generado automáticamente por bison */
%}

separador ([ \t""])+
letra [a-zA-Z]
digito [0-9]
identificador {letra}({letra}|{digito})*
constEntera {digito}({digito})*
%%
{separador} {/* omitir los separadores */ }
{constEntera}   { return (CONSTENTERA); }
":="            { return (OPAS); }
"+"             { return (MAS); }
{identificador} { return (IDENTIFICADOR); }
"("             { return (APAR); }
")"             { return (CPAR); }
\n              { return (NL); }
.                ECHO;
%%