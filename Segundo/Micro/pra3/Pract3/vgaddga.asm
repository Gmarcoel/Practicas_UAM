;******************************************************************************* 
;* VGADDGA.asm
;*
;* Microprocessor-Based Systems
;* 2020-2021
;* Lab 3
;* Case of use of Int10h and Int15h
;*
;* author: David Gonzalez-Arjona
;* Notes: Draw a white pixel in the middle of a green background
;*******************************************************************************

; DATA SEGMENT DEFINITION

DATOS SEGMENT

	MODO_VIDEO DB 0

DATOS ENDS 


; STACK SEGMENT DEFINITION

STACKSEG    SEGMENT STACK "STACK" 
    DB   40H DUP (0) 
STACKSEG ENDS 


; EXTRA SEGMENT DEFINITION 

EXTRA     SEGMENT 
   
   
EXTRA ENDS 


; CODE SEGMENT DEFINITION

CODE    SEGMENT 
    ASSUME CS:CODE, DS:DATOS, ES: EXTRA, SS:PILA 

; BEGINNING OF MAIN PROCEDURE

DDGA PROC 
    ;INITIALIZE THE SEGMENT REGISTER WITH ITS VALUE 
    MOV AX, DATOS 
    MOV DS, AX 

    MOV AX, PILA 
    MOV SS, AX 

    MOV AX, EXTRA 
    MOV ES, AX 

    ; LOAD A STACK POINTER WITH THE HIGHEST VALUE
; END OF INITIALIZATIONS

; BEGINNING OF THE PROGRAMME
    MOV SP, 64 
	
		 ; We use 10h interrupción to enter in video mode
		 MOV AH,0Fh ; Asking for video mode
		 INT 10h ; Call to BIOS
		 MOV MODO_VIDEO,AL ; We save the video mode and store it into AL
	
		 mov ah, 00h ; We set the video mode
		 mov al, 12h ; 640x480 16 color graphics (VGA)
		 int 10h
		 
		 ; We set the background colour to green 0010b
		 mov ah, 0bh
		 mov bh, 00h
		 mov bl, 02h; 0 black 2 ; green
		 int 10h
		
		;Int10H draw pixel --> AH=0Ch 	AL = Colour, BH = PageNumber, CX = x, DX = y
		mov ah, 0Ch
		; Read from the stack the value for the colour
		mov al, 0Fh ; white colour 1111b
		mov bh, 00h ; page number (keep it always to zero)
		mov cx,320 ; X position
		mov dx,240 ; Y position
		int 10h
	
		;Int15H active waiting in milliseconds: 1 millon us = 1 segundo
		MOV     CX, 2Dh ; CX:DX are the waiting time: 1 second = F:4240H --> 3 seconds 2D:C6C0h
		MOV     DX, 0C6C0h
		MOV     AH, 86H ;int15h with AH=86h to microseconds waiting in CX:DX
		INT     15H


		mov ah, 00h ; Restore the input configuration to video mode
		mov al, MODO_VIDEO ; 
		int 10h

		mov ax, 4c00h
		int 21h
		
DDGA ENDP 


; END OF THE CODE SEGMENT
CODE ENDS 
; END OF THE PROGRAMME POINTING OUT WHERE THE EXECUTION BEGINS
END DDGA 