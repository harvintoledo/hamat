;******************************************************
;***   Proyecto Emulador de procesadores            ***
;***   Integrantes                                  ***
;***   Jorge Potosme                                ***
;***   Harvin Toledo                                ***
;***   Fecha: Sabado 30 de enero de 2016            ***
;***   Universidad Nacional de Ingeniería UNI       ***
;******************************************************
MOV reg1, 117
MOV reg2, 400
MOV reg3, reg2
MOV reg4, reg1
ADD reg1, reg2
MOV reg1, 5
MOV reg2, 7
MUL reg2, reg1
INC reg1
INC reg2
INC reg3
INC reg4
AND reg1, reg2
OR reg3, reg4
SHL reg1, 3
SHL reg2, 2
SHR reg1, 3
SHR reg2, 2
PUSH reg1
PUSH reg2
PUSH reg3
PUSH reg4
POP reg1
POP reg2
POP reg3
POP reg4
