;--------------------------------------------------------------------------------
;|  Federico E. Gómez Suárez      ID 115443					|
;|  Proyecto de Arquitectura Comparada IS					|
;|										|
;|  Programa que implementa el juego "words" en el cual				|
;|  una palabra va descendiendo dentro de una caja y debe de			|
;|  escribirse antes de que alcance el final de la caja.			|
;|										|
;|  Interrupciones utilizadas:							|
;|	-Interruption 10H							|
;|		-service 00h - Cambia el modo de video				|
;|		-service 02h - Cambia la posición del puntero			|
;|		-service 06h - Scroll de pantalla (limpiar pantalla)		|
;|		-Service 08h - Lee carácter de posición del cursor		|
;|		-Service 09h - Escribe caractér en pantalla			|
;|	-Interruption 16h							|		
;|		-service 00h - Lee del keybord buffer un caractér		|
;|		-service 01h - Indica el status del keybord buffer		|
;|		-service 05h - Introduce un caractér en el keyboard buffer	|
;|	-Interruption 21h							|
;|		-service 01h - Obtiene un caractér del teclado con eco		|
;|		-service 09h - Imprime una cadena de caractéres			|
;|		-service 0Ah - Lee una cadena de caractéres del teclado		|
;|		-service 4ch - Regresa a MS-DOS					|
;--------------------------------------------------------------------------------



;--------------------------------------------------------------------------------
;			Data		Segment
;--------------------------------------------------------------------------------
dataseg segment 'data'

;----------------------------------
; Palabras a escribir en el juego
;----------------------------------
worting db "append         ","$"
	db "beggar         ","$"
	db "sandpaper      ","$"
	db "raider         ","$"
	db "comments       ","$"
	db "magazine       ","$"
	db "cancelation    ","$"
	db "programming    ","$"
	db "promise        ","$"
	db "perennial      ","$"
	db "parlament      ","$"
	db "interesting    ","$"
	db "successfully   ","$"
	db "information    ","$"
	db "mississippi    ","$"
	db "excecution     ","$"
	db "police         ","$"
	db "inhibition     ","$"
	db "astounding     ","$"
	db "extravagant    ","$"
	db "unrevocable    ","$"
	db "michaelangelo  ","$"
	db "sarajevo       ","$"
	db "restaurant     ","$"
	db "espaguetti     ","$"
	db "souvenir       ","$"
	db "animation      ","$"
	db "airlines       ","$"
	db "streams        ","$"
	db "executives     ","$"

;--------------------------
; Cadenas para la interface
;--------------------------
gameover db "Game OVer","$"
titleline db "~~~~~~~~~~","$"
titles db "Words Game","$"
askname db "What's your name? ","$"
player db "player:","$"
scoreboard db "score: ","$"
message db "    Press enter to start, any other key to exit","$"
tellword db "> ","$"


yourname db 9, ?, 9 dup(" "),"$"	; Nombre del jugador
erase db "                  ","$"	; Cadena para eliminar una cadena en la pantalla.
Randseed dw ?				; Semilla para Random
number db 7, ?,7 dup("0"),"$"		; Representación en cadena de un número
posit db ?				; posición del cursor
score dw ?				; score actual
Speed		DW 0			; nivel de velocidad de caída
curword dw ?				; palabra actual a escribir
contword db ?				; contador de palabras escritas para cambio de velocidad
cursx db ?				; renglón cursor de escritura
cursy db ?				; columna cursor de escritura
downer dw ?				; almacena temporalmente el valor de cx
actcx dw ?				; almacena temporalmente el valor de cx (segundo valor)

comp1 db ?				; letra para comparar leída de la posición de escritura
comp2 db ?				; letra para comparar leída de la palabra a escribir
char1 db ?				; almacena temporalmente el valor de ax
written db ?				; indica el total de letras escritas.
setcolor db ?				; Byte de formato para escribir caractéres
cursorx1 db ?				; Renglón de esquina superior derecha para rectángulo
cursory1 db ?				; Columna de esquina superior derecha para rectángulo
cursorx2 dw ?				; Renglón de esquina inferior izquierda para rectángulo
cursory2 dw ?				; Columna de esquina inferior izquierda para rectángulo
chartowrite db ?			; Caractér a escribir en pantalla

dataseg ends

;--------------------------------------------------------------------------------
;--------------------------------------------------------------------------------

stackseg segment stack
stackseg ends

;--------------------------------------------------------------------------------
;			Code		Segment
;--------------------------------------------------------------------------------
codeseg segment 'code'

;programa principal
programa proc far
	assume cs:codeseg,ds:dataseg,ss:stackseg
	
	push ds                 ;salva direcc. del segmento de PSP
        mov ax,0                ;limpia AX para regreso a DOS
        push ax                 ;salva desplaz. direcc. de regreso
        mov ax,dataseg          ;segmento de datos en DS
        mov ds,ax               ;inicializa DS
	mov score,0		;inicia el score
	mov speed,0FFFFh	;inicia la velocidad mínima
	call Randomize		;Instala la semilla para el random
	call interface		;Dibuja la intercace
	mov ah,01h
	int 21h			
	cmp AL,13
	mov contword,0
	jz game			;Lee un caractér del teclado. Si es CR, inicia el juego
Salida: mov dh,24
	mov dl,0
	call cursor     
	ret                ;salida para programa (.COM)
game:	call play
	ret

;fin de programa principal	
programa endp

;------------------------------------------