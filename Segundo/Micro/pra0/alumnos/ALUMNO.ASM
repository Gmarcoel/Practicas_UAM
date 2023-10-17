;_Guillermo Martín-Coello Juárez_______________________________________________________
; Data segment definition
DATOS SEGMENT
	CLR_PANT 	DB 	1BH,"[2","J$"
	CUR_MICRO	DB 	1BH,"[4;27fTECNOLOGIA DE COMPUTADORES$"
	PREG_NOM 	DB 	1BH,"[8;1fWRITE YOUR NAME ? $"
	PREG_SEC 	DB 	1BH,"[10;1fWRITE YOUR SECOND NAME ? $"
	PREG_CTR 	DB 	1BH,"[13;1fCOUNTRY NAME ? $"
	NOMBRE		DB 	80 DUP (0)
	NOMBRE2		DB 	80 DUP	(0)
	COUNTRY		DB 	80 DUP	(0)
	TEXTO 		DB 	1BH,"[22;1f","$"
	TEXTO2 		DB 	" ) IS COURSING SECOND COURSE "
			DB 	"OF COMPUTER SCIENCE",13,10,"$"
	TEXTO3		DB 	1BH," (FROM ","$"
DATOS ENDS
;_______________________________________________________________
; Stack segment definition
PILA SEGMENT STACK "STACK"
	DB 40H DUP (0)
PILA ENDS
;_______________________________________________________________
; Code segment definition
CODE SEGMENT
ASSUME CS:CODE,DS:DATOS,SS:PILA
; Main process start
START PROC FAR
;Segment registers initialization
	MOV AX,DATOS
	MOV DS,AX	;End of initialization
	
	MOV AH,9	; Clear screen
	MOV DX, OFFSET CLR_PANT
	INT 21H
	
	MOV DX,OFFSET CUR_MICRO		;Write course
	INT 21H

	MOV DX,OFFSET PREG_NOM		;Show write your name
	INT 21H
                   
	MOV AH,0AH			;Save the name
	MOV DX,OFFSET NOMBRE

	MOV NOMBRE[0],60		;Max characters
	INT 21H
	
;-----------------------------------------------------------------
;-----------------------------------------------------------------

	MOV AH,9					;Move line

	MOV DX,OFFSET PREG_SEC		;Show write your second name
	INT 21H
	
	MOV AH,0AH					;saves second name
	MOV DX,OFFSET NOMBRE2
	
	
	MOV NOMBRE2[0],60			;max number of characters
	INT 21H
	
;-----------------------------------------------------------------
;-----------------------------------------------------------------

	MOV AH,9					;Move line
	
	MOV DX,OFFSET PREG_CTR		;Show write your Country
	INT 21H
	
	MOV AH,0AH			;Saves Country
	MOV DX,OFFSET COUNTRY
	
	
	MOV COUNTRY[0],60		;Max characters
	INT 21H
	
	
;-----------------------------------------------------------------
; printing
;-----------------------------------------------------------------
	MOV AH,9
	MOV DX, OFFSET TEXTO	;Moves to write the name
	INT 21H

moV BX,0
OTRO:
	MOV DL,NOMBRE[BX+2]		;Writes the name
	MOV AH,2
	INT 21H
	
	INC BX
	CMP BL, NOMBRE[1]		;Compare character n
	JNE OTRO
	
	MOV DX,' '				; Write a space between name and last name
	INT 21H
	
	
;-----------------------------------------------------------------
;-----------------------------------------------------------------

	
moV BX,0
SEC:
	MOV DL,NOMBRE2[BX+2]		;Writes last name
	MOV AH,2
	INT 21H
	
	INC BX
	CMP BL, NOMBRE2[1]		;Compare with number of characters
	JNE SEC

	
;-----------------------------------------------------------------
;-----------------------------------------------------------------
	MOV DX,' '		; Writes a space and the From text
	INT 21H
	MOV AH,9
	MOV DX, OFFSET TEXTO3
	INT 21H

moV BX,0
TRD:
	MOV DL,COUNTRY[BX+2]		;Writes the country
	MOV AH,2
	INT 21H
	
	INC BX
	CMP BL, COUNTRY[1]		;Compares with the number of characters
	JNE TRD

	MOV DX, OFFSET TEXTO2		; Writes the end
	MOV AH,9
	INT 21H
	
;-----------------------------------------------------------------
;-----------------------------------------------------------------

	
	MOV AX,4C00H			; End of program
	INT 21H
START ENDP
;FIN DEL SEGMENTO DE CODIGO
CODE ENDS
;FIN DE PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION
END START

