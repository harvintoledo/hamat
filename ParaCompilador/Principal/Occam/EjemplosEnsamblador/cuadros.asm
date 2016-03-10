; Programa que dibuja una linea cruzada

pila segment stack
   dw 32H dup(?)
pila ends

datos segment 'data'
  mode db 18 ;640x480
  lineacolor db 1
  lineatamano dw 470
  vertical dw 470
  horizontal dw 620
  lineat dw 620
  linearen_inicio dw 0
  lineacol_inicio dw 1
  duracion dw 117

   tiempo dw 43
   lcolor db 4
   tiempoo dw 35
   time dw 37
   tiempof dw 15
   diez dw 10
   
   tamanouh dw 30
   tamanouv dw 40   
   tamanodiag dw 16
   tamanouvdiag dw 9
   colorletra db 11

  ;Algunos mensajes para nuestro programa
  MensajeInicia  db "ESTE PROGRAMA DIBUJA FIGURAS CON MOVIMIENTO","$"
  orden db "Teclee cualquier tecla para iniciar","$"
  mensaje db "Teclee cualquier tecla para finalizar"

  MensajeFin  db "FIN DE PROGRAMA","$"
datos ends

texto segment 'code'
     Assume CS:texto, DS:datos, SS:pila

inicio:
  
   dibujalinea:
        push ds
        mov ax,0
        push ax
        mov ax,datos
        mov ds,ax
        
   
           
        
  ;dibuja el laberinto
        
        mov ah,00h
        mov al,mode
        int 10h
        call u
        call d
        call l
        call a
        call guion
        call p
        
        call mensajeinicio
        call mensajeorden
        
        call leellave    

        mov ah,0ch
        mov al,lineacolor
        mov dx,linearen_inicio
        mov cx,lineacol_inicio
        mov bx,0
        mov SI,lineatamano
        mov ah,12
        call lineava
        mov SI,lineat
        call lineahd
        mov SI,lineatamano
        call lineavat
        mov SI,lineat
        dec SI
        dec SI
        call lineahr
        call ciclo
        inc lineacolor
        mov al,lineacolor
        mov dx,linearen_inicio
        mov cx,lineacol_inicio
        mov bx,0
        mov vertical,470
        mov horizontal,620
        mov duracion,117

        call ciclo
        call cambio
        call u
        call d
        call l
        call a
        call guion
        call p
        call ordenfin              
        call mensajefinal 
 
        call leellave
        call fin

    lineava:
         push ax
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         pop  ax
         inc  dx        ;apunta al siguiente renglon del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  lineava
         ret

    lineahd:
         push ax
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         pop  ax
         inc  cx        ;apunta a la siguiente columna del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  lineahd
         ret
    
    lineavat:
         push ax
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         pop  ax
         dec  dx        ;apunta al siguiente renglon del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  lineavat
         ret

    lineahr:
         push ax
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         pop  ax
         dec  cx        ;apunta a la siguiente columna del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  lineahr
         ret

    ciclo:
          call decremento
          mov SI,vertical
          call lineava
          mov SI,horizontal
          call lineahd
          mov SI,vertical
          dec SI
          dec SI
          dec vertical
          dec vertical
          call lineavat
          mov SI,horizontal
          dec SI
          dec SI
          call lineahr
          dec duracion
          jnz ciclo
          ret
    
    decremento:
          dec vertical
          dec vertical
          dec horizontal
          dec horizontal
          dec horizontal
          dec horizontal
          ret
    
     
    leellave:
    mov ah,00h
    int 16h
    ret

    fin:
     mov ah,00h
     mov al,03h
     int 10h
     mov ah,04ch
     mov al,00h
     int 21h
     ret

modotexto:
    mov ah,00h
    mov al,3h
    int 10h
    ret

; ESTA RUTINA ESCRIBE EL MENSAJE INICIAL
mensajeinicio:
          mov si,0
          mov dh, 12    ;renglon o y's
          mov dl, 16    ;columna
          
  rutina: 
          call cursor
          mov al,offset MensajeInicia[si]
          call letrascolor
          inc si
          inc dl
          dec tiempo
          jnz rutina
     	  ret

letrascolor: mov bh,0
             mov bl,lcolor
             mov cx,1
             mov ah, 9h
             int 10h
             ret

; ESTA RUTINA UBICA EL CURSOR
Cursor:      mov bh,0            ;pagina #0
             mov ah,2            ;func. de ubicacion
             int 10h
             ret


; DESPLEGANDO LA ORDEN
 mensajeorden:
          mov si,0
          mov dh, 13    ;renglon o y's
          mov dl, 25    ;columna
           
  rutinao: 
          call cursor
          mov al,offset orden[si]
          mov lcolor,1
          call letrascolor
          inc si
          inc dl
          dec tiempoo
          jnz rutinao
          ret

; DESPLEGANDO LA ORDEN
 ordenfin:
          mov si,0
          mov dh, 13    ;renglon o y's
          mov dl, 25    ;columna
           
  rutino: 
          call cursor
          mov al,offset mensaje[si]
          mov lcolor,1
          call letrascolor
          inc si
          inc dl
          dec time
          jnz rutino
          ret

; ESTA RUTINA ESCRIBE EL MENSAJE FINAL

mensajefinal:
          mov si,0
          mov dh, 14    ;renglon o y's
          mov dl, 31    ;columna
       
  rutinaf: 
          call cursor
          mov al,offset MensajeFin[si]
          mov lcolor, 6
          call letrascolor
          inc si
          inc dl
          dec tiempof
          jnz rutinaf
     	  ret

  cambio:
        inc lineacolor
        mov al,lineacolor
        mov dx,linearen_inicio
        mov cx,lineacol_inicio
        mov bx,0
        mov vertical,470
        mov horizontal,620
        mov duracion,117

        call ciclo
        dec diez
        jnz cambio
        ret

   u:
        mov ah,0ch       
        mov bx,0
        mov dx,10
        mov cx,220     
        mov al, colorletra
        mov si, tamanouv
        call rectav
        mov si, tamanouh
        call rectah
        mov si, tamanouv
        call rectava
        ret
    
   d:
        mov ah,0ch       
        mov bx,0
        mov dx,10
        mov cx,270     
        mov al, colorletra
        mov si, tamanouv
        call rectav
        mov si, tamanodiag
        call rectadiag
        mov si, tamanouvdiag
        call rectava
        mov si, tamanodiag
        call rectadiaga
        ret
   
   l:
        mov ah,0ch       
        mov bx,0
        mov dx,10
        mov cx,300     
        mov al, colorletra
        mov si, tamanouv
        call rectav
        mov si, tamanouh
        call rectah
        ret

    a:
        mov ah,0ch       
        mov bx,0
        mov dx,50
        mov cx,345     
        mov al, colorletra
        mov si, tamanouv
        call rectava
        mov si, tamanouh
        call rectah
        mov si, tamanouv
        call rectav
        mov dx,30
        mov cx,345  
        mov si, tamanouh
        call rectah
        ret
    
 guion:
        mov ah,0ch       
        mov bx,0
        mov dx,30
        mov cx,390  
        mov si, 20
        call rectah
        ret

     p:
        mov ah,0ch       
        mov bx,0
        mov dx,50
        mov cx,420     
        mov al, colorletra
        mov si, tamanouv
        call rectava
        mov si, tamanouh
        call rectah
        mov si, 20
        call rectav
        mov dx,30
        mov cx,420  
        mov si, tamanouh
        call rectah
        ret

  rectadiag:
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         inc  cx        ;apunta a la siguiente columna del pixel de la linea
         dec  dx        ;apunta al siguiente renglon del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  rectadiag
         ret

  
  rectadiaga:
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         dec  cx        ;apunta a la siguiente columna del pixel de la linea
         dec  dx        ;apunta al siguiente renglon del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  rectadiaga
         ret



  rectav:
         
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         inc  dx        ;apunta al siguiente renglon del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  rectav
         ret
    
   rectava:
         ;push ax
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         dec  dx        ;apunta al siguiente renglon del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  rectava
         ret

  rectah:
         push bx
         push CX
         push DX
         push SI
         int  10h       ;video BIOS call
         pop  SI
         pop  dx
         pop  cx
         pop  bx
         inc  cx        ;apunta a la siguiente columna del pixel de la linea
         dec  SI        ;ajusta el contador del tamaño de la linea 
         jnz  rectah
         ret

   

       



       
texto ends
end inicio