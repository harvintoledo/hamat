;Programadores:
; Victor Atomitl García Toral
; Mark Alberto Barreto Valladares
; 15 de marzo de 2004

;constantes de direccion(BIOS key code):
LEFT    EQU     4Bh
RIGHT   EQU     4Dh
UP      EQU     48h
DOWN    EQU     50h

        assume cs:code, ds:data         ; estableciendo direccionamiento
;
data    segment public                  ; comienza data semgent
tecla   dB ?    
fcursor dB ?
ccursor dB ?
simbolo dB 206 
simbolo1 db 001      
tiempo1 dB ?
tiempo2 dB ?
posy	dB 1
cont	dB 0
conti	dB 0
cont1	dB 0
cont2   dB 0
seg1f	dB 0
seg1c	dB 0
seg2f	dB 0
seg2c	dB 0
seg3f	dB 0
seg3c	dB 0
seg4f	dB 0
seg4c	dB 0
seg5f	dB 0
seg5c	dB 0
seg6f	dB 0
seg6c	dB 0
seg7f	dB 0
seg7c	dB 0
seg8f	dB 0
seg8c	dB 0
seg9f	dB 0
seg9c	dB 0
seg10c	dB 0
seg10f	dB 0
seg11f	dB 0
seg11c	dB 0
seg12f	dB 0
seg12c	dB 0
seg13f	dB 0
seg13c	dB 0
seg14f	dB 0
seg14c	dB 0
seg15f	dB 0
seg15c	dB 0
seg16c	dB 0
seg16f	dB 0
seg17c	dB 0
seg17f	dB 0
seg18c	dB 0
seg18f	dB 0
seg19c	dB 0
seg19f	dB 0
seg20c	dB 0
seg20f	dB 0
seg21c	dB 0
seg21f	dB 0
seg22c	dB 0
seg22f	dB 0
seg23c	dB 0
seg23f	dB 0
seg24c	dB 0
seg24f	dB 0
seg25c	dB 0
seg25f	dB 0
seg26c	dB 0
seg26f	dB 0
seg27c	dB 0
seg27f	dB 0
seg28c	dB 0
seg28f	dB 0
seg29c	dB 0
seg29f	dB 0
seg30c	dB 0
seg30f	dB 0

com1f	dB 0
com1c	dB 0
com2f	dB 0
com2c	dB 0
com3f	dB 0
com3c	dB 0
com4f	dB 0
com4c	dB 0
com5f	dB 0
com5c	dB 0
com6f	dB 0
com6c	dB 0
com7f	dB 0
com7c	dB 0
com8f	dB 0
com8c	dB 0
com9f	dB 0
com9c	dB 0
com10f	dB 0
com10c	dB 0
com11f	dB 0
com11c	dB 0
MSG 	DB "Fin del Juego$"
MSG2 	DB "Score: $"
MSG3	DB "espacio - jugar$"
MSG4 	DB "Q para salir.$"
score	dB 0

data    ends                            ; termina data segment

code    segment                         ; comienza code segment
start:
        mov ax, data                    ; configurar data segment como assumed
        mov  ds, ax                      
;     

otravez:

	
	mov cont, 0
	mov cont2,0
	mov score, 0
                             
        ; cambia el modo de video
        mov AH, 00
        mov AL, 03
        int 10h

	;posicion inicial del cursor
	mov AH, 2
        mov DH, 0
        mov DL, 0       
        int 10h	

;marco
	;linea superior
	reg:
	mov ah, 2
        mov dl, 177
        int 21h
	inc cont
	cmp cont, 80
	jne reg

	;posicion inicial del cursor
	mov AH, 2
        mov DH, 24
        mov DL, 0       
        int 10h
	
	mov cont, 0

	;linea inferior
	reg2:
	mov ah, 2
        mov dl, 177
        int 21h
	inc cont
	cmp cont, 79
	jne reg2

	;posicion inicial del cursor
	mov AH, 2
        mov DH, 0
        mov DL, 0       
        int 10h
	
	mov cont, 0

	;linea izquierda

	reg3:
	mov ah, 2
        mov dl, 177
        int 21h
	inc cont
	mov AH, 2
        mov DL, 0
        mov DH, cont
        int 10h
	cmp cont, 24
	jne reg3

	;posicion inicial del cursor
	mov AH, 2
        mov DH, 23
        mov DL, 79      
        int 10h
	
	mov cont, 23

	;linea derecha

	reg4:
	mov ah, 2
        mov dl, 177
        int 21h
	dec cont
	mov AH, 2
        mov DL, 79
        mov DH, cont
        int 10h
	cmp cont, 0
	jne reg4
	
	
	;posicion inicial del cursor
	mov AH, 2
        mov DH, 1
        mov DL, 1       
        int 10h
	jmp ciclo

otravez1:
	jmp otravez

colacomida:	

	mov AH, com10f
	mov AL, com10c
	mov com11f, AH
	mov com11c, AL
	
	mov AH, com9f
	mov AL, com9c
	mov com10f, AH
	mov com10c, AL

	mov AH, com8f
	mov AL, com8c
	mov com9f, AH
	mov com9c, AL

	mov AH, com7f
	mov AL, com7c
	mov com8f, AH
	mov com8c, AL
	
	mov AH, com6f
	mov AL, com6c
	mov com7f, AH
	mov com7c, AL

	mov AH, com5f
	mov AL, com5c
	mov com6f, AH
	mov com6c, AL

	mov AH, com4f
	mov AL, com4c
	mov com5f, AH
	mov com5c, AL
	
	mov AH, com3f
	mov AL, com3c
	mov com4f, AH
	mov com4c, AL

	mov AH, com2f
	mov AL, com2c
	mov com3f, AH
	mov com3c, AL

	mov AH, com1f
	mov AL, com1c
	mov com2f, AH
	mov com2c, AL
	
	mov AH, posy
	mov AL, tiempo2
	mov com1f, AH
	mov com1c, AL

	ret
	


comida:

	mov cont1,0
	mov AH, 2Ch
        int 21h
        mov tiempo2, DL
	add tiempo2,2
	;posicion inicial del cursor
	mov AH, 2
        mov DH, posy
        mov DL, tiempo2      
        int 10h
	mov AH,2
	mov DL,simbolo1	
	int 21h
	call colacomida
	mov AH, 2
        mov DH, fcursor
        mov DL, ccursor      
        int 10h
	cmp posy,24
	jl movimientoComida
	mov posy,1
	inc cont2
	cmp cont2,2
	je fin3
	jmp perate

movimientoComida:

	add posy,4
			
perate: 

	inc cont1
	cmp cont1,50
	je  comida       
        mov AH, 2Ch
        int 21h
        mov tiempo1, DL
        delay:
	mov AH, 2Ch
        int 21h
        cmp DL, tiempo1
        je delay
	ret

checa_t:
	;checa si hay informacion del teclado
        mov AH, 0Bh
        int 21H
        cmp AL, 00h
        jne leer	
	ret

otravez2:
	jmp otravez1

pcursor:
	;buscar posicion del cursor
        mov AH, 3
        mov fcursor, DH
        mov ccursor, DL
        int 10h
	ret
leer:
	;lee del teclado
	mov AH, 8
        int 21h    
        mov tecla, AL
	jmp siguele



fin3:
	;ventana de fin
	mov conti, 9
	volver1:
	mov cont, 0
	;posicion inicial del cursor
	mov AH, 2
        mov DH, conti
        mov DL, 30       
        int 10h
	volver2:
	mov ah, 2
        mov dl, 176
        int 21h
	inc cont	
	cmp cont, 21	
	jne volver2
	inc conti
	cmp conti,16
	jne volver1
	jmp brinco

     otravez3:
	jmp otravez2

	brinco:

	mov AH, 2
        mov DH, 10
        mov DL, 34       
        int 10h

	mov AH, 9 
	mov DX, Offset MSG 
	int 21h 

	mov AH, 2
        mov DH, 11
        mov DL, 34       
        int 10h
		
	mov AH, 9 
	mov DX, Offset MSG2 
	int 21h

	add score, 30h  
	mov AH, 2
        mov dl, score
        int 21h

	mov AH, 2
        mov DH, 13
        mov DL, 33       
        int 10h
		
	mov AH, 9 
	mov DX, Offset MSG3 
	int 21h

	mov AH, 2
        mov DH, 14
        mov DL, 34       
        int 10h
		
	mov AH, 9 
	mov DX, Offset MSG4 
	int 21h

	seguir:
	;lee del teclado
	mov AH, 8
        int 21h    
        mov tecla, AL
	cmp tecla, 20h
	je otravez3
	cmp tecla, 71h
	je fin4	
	jmp seguir

ciclo:  
	call checa_t
	
     siguele:
	
	call pcursor
	


        cmp tecla, LEFT
        je m_left
        cmp tecla, RIGHT
        je m_right
        cmp tecla, UP
        je m_up
        cmp tecla, DOWN
        je m_down
        
        cmp tecla, 71h
        je fin
        jmp ciclo


m_left:
	call perate
	call despseg
	call borrcola
	
        ;imprime el caracter
        mov AH, 2
        mov DL, simbolo
        int 21h         
        ;mover el cursor a la izquierda
	cmp ccursor, 1
	jne dccursor
	mov ccursor, 78
     dccursor:
        dec ccursor
	call contcom	
	mov AH, 2
        mov DH, fcursor
        mov DL, ccursor        
        int 10h
	jmp ciclo

fin4:
	jmp fin
                   
m_right:
	call perate
	call despseg
	call borrcola
	
	mov AH, 2
        mov DL, simbolo
        int 21h
        ;mover el cursor a la derecha
        cmp ccursor, 78
	jne iccursor
	mov ccursor, 0
     iccursor:
        inc ccursor
	call contcom	
        mov AH, 2
        mov DH, fcursor
        mov DL, ccursor
        int 10h
	
	jmp ciclo

fin:
	jmp fin2
m_down:
	jmp m_down2

m_up:
	call perate
	call despseg
	call borrcola
	
        ;dibujar
        mov AH, 2
        mov DL, simbolo
        int 21h        
        ;mover el cursor a hacia arriba
	cmp fcursor, 1
	jne dfcursor
	mov fcursor, 24
     dfcursor:
        dec fcursor
	call contcom	
        mov AH, 2
        mov DL, ccursor
        mov DH, fcursor
        int 10h
        jmp ciclo
        
m_down2:
	call perate
	call despseg
	call borrcola
	
	;call choque
        ;dibujar
        mov AH, 2
        mov DL, simbolo
        int 21h         
        ;mover el cursor a hacia abajo
	cmp fcursor, 23
	jne ifcursor
	mov fcursor, 0
     ifcursor:       
        inc fcursor
	call contcom
        mov AH, 2
        mov DL, ccursor
        mov DH, fcursor
        int 10h
        jmp ciclo

contcom: 

	mov AH, fcursor
	mov AL, ccursor

	cmp com1f, AH
	je co1
	jmp nel1
	co1:
	cmp com1c, AL
	jne nel1
	inc score
	mov com1f, 0
	mov com1c, 0
	nel1:

	cmp com2f, AH
	je co2
	jmp nel2
	co2:
	cmp com2c, AL
	jne nel2
	inc score
	mov com2f, 0
	mov com2c, 0
	nel2:

	cmp com3f, AH
	je co3
	jmp nel3
	co3:
	cmp com3c, AL
	jne nel3
	inc score
	mov com3f, 0
	mov com3c, 0
	nel3:

	cmp com4f, AH
	je co4
	jmp nel4
	co4:
	cmp com4c, AL
	jne nel4
	inc score
	mov com4f, 0
	mov com4c, 0
	nel4:

	cmp com5f, AH
	je co5
	jmp nel5
	co5:
	cmp com5c, AL
	jne nel5
	inc score
	mov com5f, 0
	mov com5c, 0
	nel5:

	cmp com6f, AH
	je co6
	jmp nel6
	co6:
	cmp com6c, AL
	jne nel6
	inc score
	mov com6f, 0
	mov com6c, 0
	nel6:

	cmp com7f, AH
	je co7
	jmp nel7
	co7:
	cmp com7c, AL
	jne nel7
	inc score
	mov com7f, 0
	mov com7c, 0
	nel7:

	cmp com8f, AH
	je co8
	jmp nel8
	co8:
	cmp com8c, AL
	jne nel8
	inc score
	mov com8f, 0
	mov com8c, 0
	nel8:

	cmp com9f, AH
	je co9
	jmp nel9
	co9:
	cmp com9c, AL
	jne nel9
	inc score
	mov com9f, 0
	mov com9c, 0
	nel9:

	cmp com10f, AH
	je co10
	jmp nel10
	co10:
	cmp com10c, AL
	jne nel10
	inc score
	mov com10f, 0
	mov com10c, 0
	nel10:

	cmp com11f, AH
	je co11
	jmp nel11
	co11:
	cmp com11c, AL
	jne nel11
	inc score
	mov com11f, 0
	mov com11c, 0
	nel11:
	ret


despseg:
	
	mov AH, seg29f
	mov AL, seg29c
	mov seg30f, AH
	mov seg30c, AL	

	mov AH, seg28f
	mov AL, seg28c
	mov seg29f, AH
	mov seg29c, AL	

	mov AH, seg27f
	mov AL, seg27c
	mov seg28f, AH
	mov seg28c, AL

	mov AH, seg26f
	mov AL, seg26c
	mov seg27f, AH
	mov seg27c, AL	

	mov AH, seg25f
	mov AL, seg25c
	mov seg26f, AH
	mov seg26c, AL	

	mov AH, seg24f
	mov AL, seg24c
	mov seg25f, AH
	mov seg25c, AL	
	
	mov AH, seg23f
	mov AL, seg23c
	mov seg24f, AH
	mov seg24c, AL	

	mov AH, seg22f
	mov AL, seg22c
	mov seg23f, AH
	mov seg23c, AL	

	mov AH, seg21f
	mov AL, seg21c
	mov seg22f, AH
	mov seg22c, AL	
	
	mov AH, seg20f
	mov AL, seg20c
	mov seg21f, AH
	mov seg21c, AL	
	
	mov AH, seg19f
	mov AL, seg19c
	mov seg20f, AH
	mov seg20c, AL	

	mov AH, seg18f
	mov AL, seg18c
	mov seg19f, AH
	mov seg19c, AL	

	mov AH, seg17f
	mov AL, seg17c
	mov seg18f, AH
	mov seg18c, AL	

	mov AH, seg16f
	mov AL, seg16c
	mov seg17f, AH
	mov seg17c, AL	

	mov AH, seg15f
	mov AL, seg15c
	mov seg16f, AH
	mov seg16c, AL	

	mov AH, seg14f
	mov AL, seg14c
	mov seg15f, AH
	mov seg15c, AL	

	mov AH, seg13f
	mov AL, seg13c
	mov seg14f, AH
	mov seg14c, AL	

	mov AH, seg12f
	mov AL, seg12c
	mov seg13f, AH
	mov seg13c, AL	

	mov AH, seg11f
	mov AL, seg11c
	mov seg12f, AH
	mov seg12c, AL	

	mov AH, seg10f
	mov AL, seg10c
	mov seg11f, AH
	mov seg11c, AL
	
	mov AH, seg9f
	mov AL, seg9c
	mov seg10f, AH
	mov seg10c, AL	

	mov AH, seg8f
	mov AL, seg8c
	mov seg9f, AH
	mov seg9c, AL

	mov AH, seg7f
	mov AL, seg7c
	mov seg8f, AH
	mov seg8c, AL

	mov AH, seg6f
	mov AL, seg6c
	mov seg7f, AH
	mov seg7c, AL

	mov AH, seg5f
	mov AL, seg5c
	mov seg6f, AH
	mov seg6c, AL	

	mov AH, seg4f
	mov AL, seg4c
	mov seg5f, AH
	mov seg5c, AL
	
	mov AH, seg3f
	mov AL, seg3c
	mov seg4f, AH
	mov seg4c, AL
	
	mov AH, seg2f
	mov AL, seg2c
	mov seg3f, AH
	mov seg3c, AL
	
	mov AH, seg1f
	mov AL, seg1c
	mov seg2f, AH
	mov seg2c, AL

	mov AH, fcursor
	mov AL, ccursor
	mov seg1f, AH
	mov seg1c, AL


	ret

borrcola:

	cmp seg30f, 0
	je nada
	cmp seg30c, 0
	je nada
	
	;posicion inicial del cursor
	mov AH, 2
        mov DH, seg30f
        mov DL, seg30c      
        int 10h	
	mov AH, 2
        mov DL, 20h
        int 21h
	
	mov AH, 2
        mov DH, fcursor
        mov DL, ccursor      
        int 10h	
	
nada:
	ret
	
	
	
	
fin2:
        mov  ah, 4Ch                    ; especifica la function de salida del programa
        int  21h                        ; interrupcion de DOS
	ret




code    ends                            ; fin del code segment
;
end     start                           
;