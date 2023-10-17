;*********************************************************************
;* 
;*
;* Sistemas Basados en Microprocesador
;* 2020-2021
;* Practica 3a
;* 
;*
;* author: Guillermo Martín-Coello Juárez
;*
;* notas: 
;*********************************************************************/
code SEGMENT
	ASSUME cs: code
	ORG 256
	COLOR1 equ 11	; Color blue
	COLOR2 equ 12	; Color red
	XMAX equ 240	; x limits
	YMAX equ 180	; y limits
	p1InitialX equ 50	; initial coordinates of squares
	p1InitialY equ 100	; initial coordinates of squares
	p2InitialX equ 200	; initial coordinates of squares
	p2InitialY equ 100	; initial coordinates of squares

start: jmp Main

; Global variable
flag DW 0			; flag...
MODO_VIDEO DB 0		; Saves video mode to recover later




Main PROC NEAR
	
	
	; Video mode
	MOV AH,0Fh ; Asking for video mode
	INT 10h ; Call to BIOS
	MOV MODO_VIDEO, AL ; We save the video mode and store it into AL
	mov ah, 00h ; We set the video mode
	mov al, 0Dh ; 320x200 16 color graphics (VGA)
	int 10h
	
	 ;Background
	mov ah, 0bh
	mov bh, 00h
	mov bl, 00h; 0 black 2 
	int 10h

	mov ax, 0
	mov bh, p1InitialX	; Set initial coordinates
	mov bl, p1InitialY	; Set initial coordinates
	mov ch, p2InitialX	; Set initial coordinates
	mov cl, p2InitialY	; Set initial coordinates

looping:


	mov ah, 00h ; We set the video mode (refresh each loop)
	mov al, 0Dh ; 320x200 16 color graphics (VGA)
	int 10h

	mov ah, 01h
	int 16h			; Checks if something is in keyboard
	

	
	jz no_input		; Loops until key is pressed

	jmp key			; Jumps to function when key is pressed


no_input:			; Both squares go left when no input
	add bh, 10
	add ch, 10
	cmp bh, XMAX	; Checks if x1 is bigger than max
		jb check1
	mov bh, XMAX	; If so changes to max
	
check1:
	cmp ch, XMAX	; Checks if x2 is max
		jb check2
	mov ch, XMAX	; If so changes to max
check2:
	jmp draw		; Goes to draw function to print the result
	

	
exit:				; Exit function
	mov ah, 00h ; Restore the input configuration to video mode
	mov al, MODO_VIDEO ; 
	int 10h
	MOV AX, 4C00H 	; End of programme
	int 21h

key:
	mov ah, 00h		
	int 16h			; Returns key pressed ascii in al
	
	cmp al, 'w'		; Cheks if key is expected
		je w
	cmp al, 'a'		; Cheks if key is expected
		je a
	cmp al, 's'		; Cheks if key is expected
		je s
	cmp al, 'd'		; Cheks if key is expected
		je d

	cmp al, 'i'		; Cheks if key is expected
		je i
	cmp al, 'j'		; Cheks if key is expected
		je j
	cmp al, 'k'		; Cheks if key is expected
		je k
	cmp al, 'l'		; Cheks if key is expected
		je l	
	
	cmp al, 'q'		; Cheks if key is expected
		je exit
	jmp looping

w:					; w function
	sub bl, 10		; substracts 10 to y1
	cmp bl, 0
		je min1y	; if max is reached jump
	jmp draw		; Goes to draw function

a:					; a function
	sub bh, 10		; substracts 10 to x1
	cmp bh, 0
		je min1x	; if max is reached jump

	jmp draw		; Goes to draw function
	
s:					; s function
	add bl, 10		; adds 10 to y1
	cmp bl, YMAX
		ja max1y	; if max is reached jump

	jmp draw		; Goes to draw function
	
d:					; d function
	add bh, 10		; adds 10 to x1
	cmp bh, XMAX
		ja max1x	; if max is reached jump
	jmp draw		; Goes to draw function
	

	
i:					; i function
	sub cl, 10		; substracts 10 to y2
	cmp cl, 0
		je min2y	; if max is reached jump
	jmp draw		; Goes to draw function


j:					; j function
	sub ch, 10		; substracts 10 to x2
	cmp ch, 0
		je min2x	; if max is reached jump
	jmp draw		; Goes to draw function
	
k:					; k function
	add cl, 10		; adds 10 to y2
	cmp cl, XMAX
		ja max2y	; if max is reached jump
	jmp draw		; Goes to draw function
	
l:					; l function
	add ch, 10		; adds 10 to x2
	cmp ch, XMAX
		ja max2x	; if max is reached jump
	jmp draw		; Goes to draw function

min1y:				; change coordinates if limit is surpased
	mov bl, 10
	jmp draw


min1x:				; change coordinates if limit is surpased
	mov bh, 10
	jmp draw		; Goes to draw function
max1y:				; change coordinates if limit is surpased
	mov bl, YMAX
	jmp draw		; Goes to draw function
max1x:				; change coordinates if limit is surpased
	mov bh, XMAX
	jmp draw		; Goes to draw function
min2x:				; change coordinates if limit is surpased
	mov ch, 10
	jmp draw		; Goes to draw function

min2y:				; change coordinates if limit is surpased
	mov cl, 10
	jmp draw		; Goes to draw function
max2y:				; change coordinates if limit is surpased
	mov cl, YMAX

	jmp draw		; Goes to draw function
max2x:				; change coordinates if limit is surpased
	mov ch, XMAX
	jmp draw		; Goes to draw function
	
draw:
	mov al, bh
	mov ah, bl
	int 55h			; Calls interrupt 55 with blue square coordinates
	mov al, ch
	mov ah, cl
	int 57h			; Calls interrupt 55 with red square coordinates
	push cx			;saves cx
	
					;Int15H active waiting in milliseconds: 1 millon us = 1 segundo
	MOV     CX, 0Fh ; CX:DX are the waiting time: 1 second = F:4240H
	MOV     DX, 4240h
	MOV     AH, 86H ;int15h with AH=86h to microseconds waiting in CX:DX
	mov al, 0
	INT     15H
	
	pop cx			; recovers cx
	jmp looping		; Jumps to loop

Main ENDP
	
code ENDS
END start
	