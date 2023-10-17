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

; DEFINICION DEL SEGMENTO DE CODIGO COMO PUBLICO
_TEXT SEGMENT BYTE PUBLIC 'CODE'
    ASSUME CS:_TEXT

	; COMIENZO DEL PROCEDIMIENTO PRINCIPAL
	_MAIN PROC 
		;COMIENZO DEL PROGRAMA
		muls db 1,2,4,8,5,10,9,7,3,6
		
		PUBLIC _findSubString	
		PUBLIC _bankAccountNumber
		
		
	_MAIN ENDP 

	; findSubString (char* str, char* substr)	; 06 str 08 sub
	_findSubString proc far
		push bp	; save bp
		mov bp, sp
		
		mov cx, 0
		mov si, 0
		mov di, 0
		
		find_lenght:
			les bx, [bp + 06]	; moves the position of the first element of the string to dx
			add bx, si			; adds to dx the counter si
			mov dx, es:[bx]		; finds the element in that position
			cmp dl, 0			; compares if it is the end of the string
				je find_equals
			inc si
			jmp find_lenght
		
		find_equals:
		les bx, [bp + 06]	; moves the position of the first element of the string to dx
		add bx, cx			; adds a counter for the character number
		mov dx, es:[bx] 	; moves to dx the current element 
		
		les bx, [bp + 10]
		mov ax, es:[bx] 	; moves the position of the first element of the substring to ax
		
		cmp al, dl			; compares the current character with the first character of the subarray
			je possible_candidate
			
		cmp cx, si			; compares the length
			jge not_found
		
		inc cx
		jmp find_equals
				
		possible_candidate:
			inc di
			les bx, [bp + 06]	; moves the position of the first element of the string to dx
			add bx, cx			; adds a counter for the character number
			add bx, di			; adds the number of elements already equal
			mov dx, es:[bx] 	; moves to dx the current element 
			
			les bx, [bp + 10]
			add bx, di
			mov ax, es:[bx] 	; moves the position of the "di" element of the substring to ax
			
			cmp al, 0			; check if the substring is over
				je sum
				
			cmp dl, 0			; check if string is over
				je not_found
			
			cmp dl, al			; if equal check the next element
				je possible_candidate
			
			inc cx				; in case they are not equal, inc counter
			mov di, 0			; reset di
			jmp find_equals		; and continue searching
			
		sum:
			
			pop bp
			mov ax, cx
			ret
				
				
		not_found:
			pop bp
			mov ax, -1 ; returns -1 if not found
			ret
			
			
	_findSubString endp
	
;  bankAccountNumber(char * bankAccountNumber);
	_bankAccountNumber proc far
		push bp
		mov bp, sp
		mov si, 0			; initializes a counter
		mov di, 0			; initialize a sum
		
		addition:
			mov ax, 0
			les bx, [bp + 06]	; moves the position of the "si" element of the array to ax
			add bx, si			; adds a counter for the element number
			mov al, es:[bx] 	; moves to dx the current element 			
			sub al, 30h			; converts ascii number to integer

			mul cs:muls[si]	; multiplies by corresponding number of the muls array
			add di, ax			; adds the result to the sum
		
			cmp si, 9
				je modulus
			inc si
			jmp addition
		
		modulus:
			mov ax, di			; moving di to ax to do the division
			mov dx, 0			; cleaning dx so divide doesn't do overflow
			mov cx, 11
			div cx				; divides the sum saved in ax by eleven and the modulus goes to dx
			sub cx, dx			; substracts the modulus to eleven
			
			mov ax, cx
			cmp ax, 10
				je	special_case
			pop bp
			ret
			
		special_case:
			mov ax, 1
			pop bp
			ret
		
	_bankAccountNumber endp

	
_TEXT ENDS 
END