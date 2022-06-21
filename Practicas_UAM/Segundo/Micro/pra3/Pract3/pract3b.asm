;*********************************************************************
;* 
;*
;* Sistemas Basados en Microprocesador
;* 2020-2021
;* Practica 3a
;* 
;*
;* author: 
;*
;* notas: ejemplo vacío
;*********************************************************************/

; DEFINICION DEL SEGMENTO DE CODIGO COMO PUBLICO
_TEXT SEGMENT BYTE PUBLIC 'CODE'
    ASSUME CS:_TEXT

	; COMIENZO DEL PROCEDIMIENTO PRINCIPAL
	_MAIN PROC 
		;COMIENZO DEL PROGRAMA 
		PUBLIC _drawPixelsList	
			   _MODO_VIDEO DB 0
		
	_MAIN ENDP 

	_drawPixelsList proc far ; 06 int numPixels 08 char bgcolout 10 long waitingTime 14 int pixelList_x 18 int pixelList_y 22 char pixelList_colour
		push bp	; save bp
		mov bp, sp
		
		; We use 10h interruption to enter in video mode
		MOV AH,0Fh ; Asking for video mode
		INT 10h ; Call to BIOS
		MOV _MODO_VIDEO,AL ; We save the video mode and store it into AL
		
		mov ah, 00h ; We set the video mode
		mov al, 12h ; 640x480 16 color graphics (VGA)
		int 10h
		
		; We set the background colour to the one chosen
		mov ah, 0bh
		mov bh, 00h
		mov bl, [bp + 08]
		int 10h
		
		; Here the loop starts
		mov SI, [bp + 06]
		LOOPING:
		
			sub SI, 1
		
			;Int10H draw pixel --> AH=0Ch 	AL = Colour, BH = PageNumber, CX = x, DX = y
			mov ah, 0Ch 
			
			mov DI, [bp + 22]
			add DI, SI
			mov ES, [bp + 24]
			mov al, ES:[DI] ; color
			
			mov bh, 00
		
			mov DI, [bp + 14]
			add DI, SI
			mov ES, [bp + 16]
			mov cx, ES:[DI] ; x


			mov DI, [bp + 18]
			add DI, SI
			mov ES, [bp + 20]
			mov dx, ES:[DI] ; y
			
			;add dx, SI ; adds vector distance to requested point times 2
		
			int 10h
		
			cmp SI, 0
				jge LOOPING
		
		;Int15H active waiting in milliseconds: 1 millon us = 1 segundo
		MOV     CX, [bp+12] ; CX:DX are the waiting time: 1 second = F:4240H --> 3 seconds 2D:C6C0h
		MOV     DX, [bp+10]
		MOV     AH, 86H ;int15h with AH=86h to microseconds waiting in CX:DX
		INT     15H


		mov ah, 00h ; Restore the input configuration to video mode
		mov al, _MODO_VIDEO ; 
		int 10h

		
		pop bp
		
		mov ax, 0
	
		ret
	_drawPixelsList endp

	
_TEXT ENDS 
END