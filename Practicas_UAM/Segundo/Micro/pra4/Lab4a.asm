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
	COLOR1 equ 11
	COLOR2 equ 12

start: jmp Main
; Global variable
stable DB "abcdf"
flag DW 0
MODO_VIDEO DB 0
posX dw 0
posY dw 0
counter db 0
statusY db "Program is installed",13,10,'$'
statusN db "Program is not installed",13,10,'$'
author db "Author: Guillermo Martin-Coello Juarez",13,10,'$'
instructions db "run with /I to install driver or /U to uninstall",13,10,'$'


; INTERRUPT55 PROC FAR
Interrupt55 PROC FAR	;Interrupt 55 process (prints a blue square of size 10 in (al,ah)) 
	push bp	; save bp
	;mov bp, sp
	push ax bx cx dx si di
	
	
;	1. Get the video mode and check if it is correct (320x200)
;	NO MORE VIDEO HERE SINCE EXERCISE 2


;	2. Read the positions (X,Y) from the registers AH, AL
	mov byte ptr posX, al
	mov byte ptr posY, ah
	mov cx, posX	; x
	mov dx, posY	; y

;	3. Print a square 10x10 in blue.
		push si
		push di
		
		mov SI, 10
		mov DI, 10

	looping:				; loop for each line

		mov ah, 0Ch 		; draw
		mov bh, 00			; page
		mov al, COLOR1		; color


		inc cx				; inc x
		

		int 10h				; print interrupt
		
		sub si, 1			; A loop for printing self explanatory
		cmp si, 0
			jne looping
		sub di, 1
		sub cx, 10
		inc dx
		mov si, 10
		cmp di, 0
			jne looping


		pop di
		pop si

		pop di si dx cx bx ax	
		pop bp
		iret
	
Interrupt55 ENDP

Interrupt57 PROC FAR	;Interrupt 57 process (prints a red square of size 10 in (al,ah)) 
	push bp	; save bp
	;mov bp, sp
	push ax bx cx dx si di
	
;	1. Get the video mode and check if it is correct (320x200)
;	(Not anymore)
	
;	2. Read the positions (X,Y) from the registers AH, AL
	mov byte ptr posX, al
	mov byte ptr posY, ah
	mov cx, posX	; x
	mov dx, posY	; y


;	3. Print a square 10x10 in blue.
		push si
		push di
		
		mov SI, 10
		mov DI, 10

	looping2:				; again, a loop for printing each pixel of the square

		mov ah, 0Ch 		; draw
		mov bh, 00			; page
		mov al, COLOR2		; color


		inc cx				; inc x
		

		int 10h
		
		sub si, 1
		cmp si, 0
			jne looping2	; Im not commenting that much because at this point this is obvious
		sub di, 1
		sub cx, 10
		inc dx
		mov si, 10
		cmp di, 0
			jne looping2


		pop di
		pop si
		
		pop di si dx cx bx ax	
		pop bp
		iret
	
Interrupt57 ENDP


Installer PROC NEAR					; Installer of the interrupts
	push bp
	push ax bx dx
	
	mov ax, 0
	mov es, ax
	mov ax, OFFSET Interrupt55		; Takes the function offset to ax
	mov bx, cs						; Takes the code segment to cs
	cli
	mov es:[ 55h*4 ], ax			; Copies to offset of the interrupt
	mov es:[ 55h*4 + 2 ], bx		; Copies to segment of the interrupt
	sti
	
	mov ax, 0
	mov es, ax
	mov ax, OFFSET Interrupt57		; Same with the interrupt 57
	mov bx, cs
	cli
	mov es:[ 57h*4 ], ax
	mov es:[ 57h*4 + 2 ], bx
	sti

	
	mov dx, OFFSET Installer
	int 27h 						; terminate and stay resident

	
	pop dx bx ax
	pop bp
	ret
	
Installer ENDP
	
Uninstaller PROC NEAR
	push ax bx cx ds es
	mov cx, 0 
	mov ds, cx 					; Segment of interrupt vectors
	mov es, ds:[ 55h*4+2 ] 		; Read ISR segment
	mov bx, es:[ 2Ch ] 			; Read segment of environment from ISR’s PSP.
	mov ah, 49h
	int 21h 					; Release ISR segment (es)
	mov es, bx
	int 21h 					; Release segment of environment variables of ISR
								; Set vector of interrupt 40 to zero
	cli
	mov ds:[ 55h*4 ], cx 		; cx = 0
	mov ds:[ 55h*4+2 ], cx
	sti
	
	mov cx, 0 
	mov ds, cx 					; Segment of interrupt vectors
	mov es, ds:[ 57h*4+2 ] 		; Read ISR segment
	mov bx, es:[ 2Ch ] 			; Read segment of environment from ISR’s PSP.
	mov ah, 49h
	int 21h 					; Release ISR segment (es)
	mov es, bx
	int 21h 					; Release segment of environment variables of ISR
								; Set vector of interrupt 40 to zero
	cli
	mov ds:[ 57h*4 ], cx 		; cx = 0
	mov ds:[ 57h*4+2 ], cx
	sti
	
	pop es ds cx bx ax
	ret
Uninstaller ENDP

Main PROC NEAR
	

	mov dl, ds:[80h]				; Checks number of arguments and saves to dl
	cmp dl, 0						; Goes to check function if 0 arguments
		je check
	cmp dl, 3						; Goes to argument function if 3 arguments
		je argument
	jmp check						; Jumps to check
	
argument:
	mov dl, byte ptr cs:[81h]		; Checks first argument
	cmp dl, ' '						; If not goes to check
		jne check
	mov dl, byte ptr  cs:[82h]		; Checks second argument
	cmp dl, '/'						; If not goes to check
		jne check
	mov dl, byte ptr  cs:[83h]		; Checks third argument
	cmp dl, 'I'						; If not /I installs
		je i
	cmp dl, 'U'						; If /U then uninstalls
		je u
		
	jmp check

i:
	call Installer					; Calls installer
	jmp ending
u:
	call Uninstaller				; Calls uninstaller
	jmp ending

	
check:								; Function that checks if drivers are installed
	mov ax, 0
	mov es, ax
	mov cx, 0
	mov cx, es:[55h * 4]			; Checks if installed
	cmp cx, 0
		je notIns
	jmp yesIns

yesIns:								; Function that shows information about installation through terminal
	mov dx, offset statusY			; Int 21h with ah 9 to print to terminal
	mov ah, 9h
	int 21h
	jmp desc
notIns:								; Function that shows information about installation through terminal
	mov dx, offset statusN			; Drivers not installed text
	mov ah, 9h						; Int 21h with ah 9 to print to terminal
	int 21h
	jmp desc
	
	
desc:								; Function to print author and instructions

	mov dx, offset author			; Author name offset
	mov ah, 9h						; Int 21h with ah 9 to print to terminal
	int 21h
	mov dx, offset instructions		; Instructions offset
	mov ah, 9h
	int 21h							; Int 21h with ah 9 to print to terminal
	
ending:
	MOV AX, 4C00H 					; End of the program
	int 21h
	
	

Main ENDP
	
code ENDS
END start
	