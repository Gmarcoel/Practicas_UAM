;*********************************************************************
;* 
;*
;* Microprocessor-Based Systems
;* 2020-2021
;* Lab 3a
;* 
;*
;* author: 
;*
;* notes: empty example
;*********************************************************************/

; DEFINITION OF THE CODE SEGMENT AS PUBLIC
_TEXT SEGMENT BYTE PUBLIC 'CODE'
    ASSUME CS:_TEXT
	

	; BEGINNING OF THE MAIN PROCEDURE
	_MAIN PROC 
		;THE PROGRAMME STARTS
		PUBLIC _drawPixel
	PUBLIC _drawSquare
		_MODO_VIDEO DB 0
		
	_MAIN ENDP 

	_drawPixel proc far
		
		; BEGINNING OF THE PROGRAMME
		push bp
		mov bp, sp


		
	
		; We use 10h interrupción to enter in video mode
		MOV AH,0Fh ; Asking for video mode
		INT 10h ; Call to BIOS
		MOV _MODO_VIDEO,AL ; We save the video mode and store it into AL
	
		mov ah, 00h ; We set the video mode
		mov al, 12h ; 640x480 16 color graphics (VGA)
		int 10h
		
		; We set the background colour to green 0010b
		mov ah, 0bh
		mov bh, 00h
		mov bl, 00h; 0 black 2 ; green
		 int 10h
		
		;Int10H draw pixel --> AH=0Ch 	AL = Colour, BH = PageNumber, CX = x, DX = y
		mov ah, 0Ch
		mov al, [bp + 6]
		mov bh, 00
		mov cx, [bp + 8]
		mov dx, [bp + 10]
		int 10h
		
		; Read from the stack the value for the colour
		;mov al, 0Fh ; white colour 1111b
		;mov bh, 00h ; page number (keep it always to zero)
		;mov cx,320 ; X position
		;mov dx,240 ; Y position
	
		;Int15H active waiting in milliseconds: 1 millon us = 1 segundo
		MOV     CX, 2Dh ; CX:DX are the waiting time: 1 second = F:4240H --> 3 seconds 2D:C6C0h
		MOV     DX, 0C6C0h
		MOV     AH, 86H ;int15h with AH=86h to microseconds waiting in CX:DX
		INT     15H


		mov ah, 00h ; Restore the input configuration to video mode
		mov al, _MODO_VIDEO ; 
		int 10h

		
		pop bp
		
		mov ax, 0
	
		ret
	_drawPixel endp
		_drawSquare proc far
			
		; BEGINNING OF THE PROGRAMME
		push bp
		mov bp, sp

		; We use 10h interrupción to enter in video mode
		MOV AH,0Fh ; Asking for video mode
		INT 10h ; Call to BIOS
		MOV _MODO_VIDEO,AL ; We save the video mode and store it into AL
	
		mov ah, 00h ; We set the video mode
		mov al, 12h ; 640x480 16 color graphics (VGA)
		int 10h
		
		; We set the background colour to green 0010b
		mov ah, 0bh
		mov bh, 00h
		mov bl, 00h; 0 black 2 ; green
		 int 10h
		
		;Int10H draw pixel --> AH=0Ch 	AL = Colour, BH = PageNumber, CX = x, DX = y
		;unsigned char pintaCuadrado (unsigned char color = 6, int tam = 8,int x = 10,int y = 12)
		mov si, [bp + 8]
		mov di, [bp + 8]
		looping:
		mov ah, 0Ch
		mov al, [bp + 6]
		mov bh, 00
		mov cx, [bp + 10]
		add cx, si
		mov dx, [bp + 12]
		add dx, di
		int 10h
		
		sub si,1
		cmp si, 0
			jg looping
		mov si, [bp + 8]
		sub di,1
		cmp di, 0
			jg looping
		
		
		; Read from the stack the value for the colour
		;mov al, 0Fh ; white colour 1111b
		;mov bh, 00h ; page number (keep it always to zero)
		;mov cx,320 ; X position
		;mov dx,240 ; Y position
	
		;Int15H active waiting in milliseconds: 1 millon us = 1 segundo
		MOV     CX, 2Dh ; CX:DX are the waiting time: 1 second = F:4240H --> 3 seconds 2D:C6C0h
		MOV     DX, 0C6C0h
		MOV     AH, 86H ;int15h with AH=86h to microseconds waiting in CX:DX
		INT     15H


		mov ah, 00h ; Restore the input configuration to video mode
		mov al, _MODO_VIDEO ; 
		int 10h

		

		pop bp
		
		mov ax, 0
		int 21h
	
		ret

	_drawSquare endp

	
_TEXT ENDS 
END