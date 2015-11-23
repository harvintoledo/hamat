/* Archivo instrucciones.l */
%{
/* Archivo que genera lex.yy.c */
/* Teoria de Compiladores */
/* Autor Harvin Toledo */
/* harvintoledo@gmail.com */
#include <stdio.h>
#include "y.tab.h" /* Generado automáticamente por bison */

%}
/* Esto indica a Flex que lea sólo un fichero de entrada */
%option noyywrap
separador ([ \t""])+
letra [a-zA-Z]
digito [0-9]
identificador {letra}({letra}|{digito})*
constEntera {digito}({digito})*
constFlotante {digito}\.({digito})*
%%
{separador} {/* omitir los separadores */ }
{constEntera}   {
            printf("Entero reconocido:%s\n", yytext);
          return (CONSTENTERA); }
{constFlotante}    { 
printf("Flotante reconocido:%s\n", yytext);
return (CONSTFLOTANTE); }
":="            { return (OPAS); }
"<"             { return (MENORQUE); }
"<="            { return (MENOROIGUALQUE); }
">"             { return (MAYORQUE); }
">="            { return (MAYOROIGUALQUE); }
"="             { return (IGUAL); }
"+"             { return (MAS); }
"-"             { return (MENOS); }
"*"             { return (POR); }
"/"             { return (ENTRE); }
"^"             { return (POTENCIA); }
{identificador} { return (IDENTIFICADOR); }
"("             { return (APAR); }
")"             { return (CPAR); }
\n              { return (NL); }
.                ECHO;
%%