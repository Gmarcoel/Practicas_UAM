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
	COLOR1 equ 11			; Color blue
	COLOR2 equ 12			; Color red
	XMAX equ 240			; Max x
	YMAX equ 180			; Max y
	p1InitialX equ 50		; Initial X1
	p1InitialY equ 100		; Initial Y1
	p2InitialX equ 200		; Initial X2
	p2InitialY equ 100		; Initial Y2

start: jmp Update
							; Global variables
stable DB "abcdf"
flag DW 0
MODO_VIDEO DB 0				; Saves video mode
posX dw 0					; x pos
posY dw 0					; y pos
counter dw 0				; counter for time
p1x db 0					; blue square x
p1y db 0					; blue square y
p2x db 0					; red square x
p2y db 0					; red square y
old1C dw 2 dup (0)			; old 1Ch interrupt to recover at the end

p1arrayX db 50 dup (0)		; Array of blue x positions
p1arrayY db 50 dup (0)		; Array of blue y positions
p2arrayX db 50 dup (0)		; Array of red x positions
p2arrayY db 50 dup (0)		; Array of red y positions

timer dw 0					; timer for lenght
timer2 dw 0					; timer for speed
lenght dw 0					; lenght
speed dw 18					; speed

blue_win db "Blue wins",13,10,'$'	; Winning text
red_win db "Red wins",13,10,'$'		; Winning text


Interrupt1C PROC FAR			; new int 1Ch process

	inc word ptr [cs:counter]	; adds each tic one to counter global variable
	iret

Interrupt1C ENDP


Update PROC NEAR

		
	mov ax, 0
	mov es, ax
	
		mov ax, es:[1Ch*4]				; Saves in ax 1Ch offset
		mov word ptr old1C, ax			; Moves ax to old1C variable
		mov ax, es:[1Ch*4 + 2]			; Saves in ax 1Ch segment
		mov word ptr old1C + 2, ax		; Moves ax to old1C variable
	
	mov ax, OFFSET Interrupt1C			; Saves new 1Ch offset
	mov bx, cs
	cli
	mov es:[ 1Ch*4 ], ax				; Loads new 1Ch into the interruptor
	mov es:[ 1Ch*4 + 2 ], bx
	sti
	


	mov ax, 0
	mov p1X, p1InitialX					; Initializes coordinates
	mov p1Y, p1InitialY					; Initializes coordinates
	mov p2X, p2InitialX					; Initializes coordinates
	mov p2Y, p2InitialY					; Initializes coordinates
	

	
										; Video mode
	MOV AH,0Fh 							; Asking for video mode
	INT 10h 							; Call to BIOS
	MOV MODO_VIDEO, AL 					; We save the video mode and store it into AL
	mov ah, 00h 						; We set the video mode
	mov al, 0Dh							; 320x200 16 color graphics (VGA)
	int 10h
	
										;Background
	mov ah, 0bh
	mov bh, 00h
	mov bl, 00h							; Sets black
	int 10h
	
	mov bh, p1x							; Initializes coordinates
	mov bl, p1y							; Initializes coordinates
	mov ch, p2x							; Initializes coordinates
	mov cl, p2y							; Initializes coordinates
	
	;jmp no_input
	
next_aux: jmp next						; Jumps to next function

loop_update:							; Saves the keyboard input while waits for counter to reach expected
	;int 1Ch
	mov ax, speed		
	cmp word ptr [cs:counter], ax		; Checks if counter has reached speed variable
		jge next_aux					; Jumps to next "turn"


	mov ah, 01h
	int 16h								; Checks if something is in keyboard
	
	jz loop_update						; Loops until key is pressed

	jmp key								; Jumps if key is pressed



save_pos:								; Saves current position of snake
	push bx
	mov dx, bx
	mov bx, 0
	mov bx, lenght
pos_loop:								; Loops through all the segments of the snake
	cmp bx, 0
		je endpos						; jumps if no more segments
		
	mov ah, p1arrayX[bx-1]				; Saves x of segment bx-1 to ah
	mov p1arrayX[bx], ah				; Loads the saved segment x to the next segment (so it moves like a snake)
	mov al, p1arrayY[bx-1]				; Saves y of segment bx-1 to ah
	mov p1arrayY[bx], al				; Loads the saved segment y to the next segment (so it moves like a snake)
	cmp ax, dx							; Check if red has collision
		je red_wins_aux
	cmp ax, cx							; Check if blue has collision
		je blue_wins_aux
	mov ah, p2arrayX[bx-1]				; Sames as previous but with red snake
	mov p2arrayX[bx], ah
	mov al, p2arrayY[bx-1]
	mov p2arrayY[bx], al
	cmp ax, dx							; Check if red has collision
		je red_wins_aux
	cmp ax, cx							; Check if blue has collision
		je blue_wins_aux
	sub bx, 1							; Goes to next segment
	jmp pos_loop						; Loops until segment 0

red_wins_aux: jmp red_wins
blue_wins_aux: jmp blue_wins
	
endpos:									; Head management function
	pop bx
	mov p1arrayX[0], bh					; Saves blue x
	mov p1arrayY[0], bl					; Saves blue y
	mov p2arrayX[0], ch					; Saves red x
	mov p2arrayY[0], cl					; Saves red y
	
	ret


inc_size:								; Sets timer to 0 and increases size in 1
	mov timer, 0
	inc lenght
	jmp next2							; Jumps back
inc_speed:								; Sets timer of speed to 0 and decreases speed in 2
	mov timer2, 0						; (Speed measures time so this will make it faster, a 10%~11% aprox)
	cmp speed, 2
		je next3
	sub speed, 2
	jmp next3							; Jumps back

next:									; Function that checks the input and process it
	mov word ptr [cs:counter], 0
	
	inc timer 							; Increases the seconds check
	inc timer2							; Increases the speed timer
	cmp timer, 10
		je inc_size						; Checks if it is time to increase the size (lenght)
next2:
	cmp timer2, 15
		je inc_speed					; Checks if it is time to increase the speed (make it faster)
next3:
	call save_pos						; Saves position to snake arrays
	mov p1x, bh							; Save coordinate to variable
	mov p2x, ch							; Save coordinate to variable
	mov p1y, bl							; Save coordinate to variable
	mov p2y, cl							; Save coordinate to variable
	
	push bx
	
										;Video mode
	mov ah, 00h 						; We set the video mode
	mov al, 0Dh 						; 320x200 16 color graphics (VGA)
	int 10h
	
										; Background
	mov ah, 0bh							; This is not completely necessary but just to play safe
	mov bh, 00h
	mov bl, 00h							; To black
	int 10h
	
	pop bx
	
	call draw




no_input:								; If no input snakes go right
	mov bh, p1x
	mov ch, p2x
	add bh, 10
	add ch, 10
	
	cmp bh, XMAX						; Check if limit is reached
		ja red_wins
	cmp ch, XMAX						; Check if limit is reached
		ja blue_wins
	jmp loop_update						; Jumps to loop
	

blue_wins:								; Function if blue wins
	mov ax, 0
	mov es, ax
	
	cli
	mov ax, word ptr old1C				; Restores previous interrupt 1Ch
	mov es:[ 1Ch*4 ], ax
	mov ax, word ptr old1C + 2
	mov es:[ 1Ch*4 + 2 ], ax
	sti
	
	mov ah, 00h 						; Restore the input configuration to video mode
	mov al, MODO_VIDEO ; 
	int 10h
	
	mov dx, offset blue_win				; Prints blue wins text
	mov ah, 9h
	int 21h
	
	MOV AX, 4C00H 						; End of programme
	int 21h
	
red_wins:								; Function if red wins
	mov ax, 0
	mov es, ax
	
	cli
	mov ax, word ptr old1C				; Restores previous interrupt 1Ch
	mov es:[ 1Ch*4 ], ax
	mov ax, word ptr old1C + 2
	mov es:[ 1Ch*4 + 2 ], ax
	sti
	
	mov ah, 00h 						; Restore the input configuration to video mode
	mov al, MODO_VIDEO ; 
	int 10h
	
	mov dx, offset red_win				; Prints red wins text
	mov ah, 9h
	int 21h
	
	MOV AX, 4C00H 						; End of programme
	int 21h

exit:									; Exit function without text
	mov ax, 0
	mov es, ax
	
	cli
	mov ax, word ptr old1C				; Restores previous interrupt 1Ch
	mov es:[ 1Ch*4 ], ax
	mov ax, word ptr old1C + 2
	mov es:[ 1Ch*4 + 2 ], ax
	sti
	
	mov ah, 00h							; Restore the input configuration to video mode
	mov al, MODO_VIDEO ; 
	int 10h
	MOV AX, 4C00H 						; End of programme
	int 21h

key:
	mov ah, 00h
	int 16h								; Returns key pressed ascii in al
	
	cmp al, 'w'							; Check each one of the possible inputs to see if one works
		je w
	cmp al, 'a'							; I commented all this in part b I'm not doing it again it is self explanatory
		je a
	cmp al, 's'
		je s
	cmp al, 'd'
		je d

	cmp al, 'i'
		je i
	cmp al, 'j'
		je j_aux
	cmp al, 'k'
		je k_aux
	cmp al, 'l'
		je l_aux
	
	cmp al, 'q'
		je exit
	jmp loop_update						; Jumps to loop
j_aux: jmp j
k_aux: jmp k
l_aux: jmp l

w:										; w function (again, I explained all this in part b)
	mov bh, p1x	
	mov bl, p1y
	sub bl, 10							; Saves blue snake values into bx and adds the movement of letter w (y+10)
	cmp bl, 0
		je red_wins_aux2				; If limit is reached jumps to winner
	jmp loop_update						; Jumps to loop

a:
	mov bh, p1x							; Same as w but for other letter
	mov bl, p1y
	sub bh, 10
	cmp bh, 0
		je red_wins_aux2
	jmp loop_update

	
s:
	mov bh, p1x							; Same as w but for other letter
	mov bl, p1y
	add bl, 10
	cmp bl, YMAX
		ja red_wins_aux2
	jmp loop_update
	
d:
	mov bh, p1x							; Same as w but for other letter
	mov bl, p1y
	add bh, 10
	cmp bh, XMAX
		ja red_wins_aux2
	jmp loop_update
	
red_wins_aux2: jmp red_wins
	
i:
	mov ch, p2x							; Same as w but for other letter
	mov cl, p2y
	sub cl, 10
	cmp cl, 0
		je blue_wins_aux2				; In this cases if limits are reached blue wins
	jmp loop_update
j:
	mov ch, p2x							; Same as w but for other letter
	mov cl, p2y
	sub ch, 10
	cmp ch, 0
		je blue_wins_aux2
	jmp loop_update
	
k:	
	mov ch, p2x							; Same as w but for other letter
	mov cl, p2y
	add cl, 10
	cmp cl, XMAX
		ja blue_wins_aux2
	jmp loop_update
	
l:
	mov ch, p2x							; Same as w but for other letter
	mov cl, p2y
	add ch, 10
	cmp ch, XMAX
		ja blue_wins_aux2
	jmp loop_update

blue_wins_aux2: jmp blue_wins

	
draw:									; Prints the snakes
	push bx
	mov bx, 0
	mov bx, lenght
draw_loop:								; Goes through all the arrays to print each element
	cmp bx, 0
		jl endraw						; Loops until segment 0 is reached
		
	mov al, p1arrayX[bx]				; Save blue x to al
	mov ah, p1arrayY[bx]				; Save blue y to ah
	int 55h								; Call interrupt 55 to print blue
	mov al, p2arrayX[bx]				; Save red x to al
	mov ah, p2arrayY[bx]				; Save red y to ah
	int 57h 							; Call interrupt 57 to print red
	sub bx, 1							; Goes to next segment
	jmp draw_loop						; Loops
	
endraw:
	pop bx								; pops previously saved bx and returns
	ret


Update ENDP
	
code ENDS
END start
	