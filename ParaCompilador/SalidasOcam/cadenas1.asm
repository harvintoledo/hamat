;Definir modelo
.model small
;Definir segmento de pila
.stack
;Definir segmento de datos
.data
mensaje db 10,13, 'CLASE DE ENSAMBLADOR$'
mensaje1 db 10,13,'introduce cadena:$'
cv db 16 dup('$')
cvi db 16 dup('$')
;Definir segmento de codigo
.code
inicio:

mov ax,@data
mov ds,ax
mov es,ax

;desplegar mensages
mov ah,09h
mov dx,offset mensaje
int 21h

;cadena
mov ah,09h
mov dx,offset mensaje1
int 21h

;captura de cadena
mov ah,0ah
mov dx, offset cv
int 21h
cld

mov cx,16
lea si,cv

invertir:
lodsb
mov [di],al
dec di
loop invertir

mov di,cvi

;Imprimir cadena original
mov ah,09h
lea dx,cv
int 21h

;Imprimir cadena invertida
mov ah,09h
lea dx,cvi
int 21h

mov ah,4ch
int 21h