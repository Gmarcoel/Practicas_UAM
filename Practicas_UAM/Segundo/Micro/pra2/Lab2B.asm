;************************************************************************** 
; MBS 2021. LABORATORY ASSIGNMENT 2 
; Author: Guillermo Martín-Coello Juárez
; Group: 2292
; Task: 2A
;************************************************************************** 
; DATA SEGMENT DEFINITION 
DATA SEGMENT 

; VARIABLE DEFINITION
v DB 0
; VECTOR DEFINITION 
vector1 DB 1,2,2,4
vector2 DB 4,2,5,1 
vector3 DB 3,2,4,1 
errorNumDif DB "Duplicated", 13, 10, '$' 
correctOutput DB "Correct",13,10,'$' 
DATA ENDS 
;************************************************************************** 
; STACK SEGMENT DEFINITION 
STACKSEG SEGMENT STACK "STACK" 
DB 40H DUP (0)	; initialization example, 64 bytes initialize to 0 
STACKSEG ENDS 
;************************************************************************** 
; EXTRA SEGMENT DEFINITION  
EXTRA SEGMENT 
RESULT DW 0,0 ; initialization example. 2 WORDS (4 BYTES) 
EXTRA ENDS 
;*************************************************************************
; CODE SEGMENT DEFINITION 
CODE SEGMENT 
ASSUME CS: CODE, DS: DATA, ES: EXTRA, SS: STACKSEG 
; BEGINNING OF MAIN PROCEDURE 
BEGIN PROC 
; INITIALIZE THE SEGMENT REGISTER WITH ITS VALUE  
MOV AX, DATA 
MOV DS, AX 
MOV AX, STACKSEG 
MOV SS, AX 
MOV AX, EXTRA 
MOV ES, AX 
MOV SP, 64  ; LOAD A STACK POINTER WITH THE HIGHEST VALUE 
; END OF INITIALIZATIONS 

; BEGINNING OF THE PROGRAMME 
MOV CX, 0
MOV AX, 0
MOV SI, 0


LOOPING:	;LOOPS EACH ELEMENT OF THE VECTOR AND CALLS TO THE COMPARING FUNCTION
	CMP SI, 4
		JE PRINT_CORRECT
	MOV AL, DS:VECTOR1[BX][SI] ; Moves the chosen element of the vector to the register AL
	JMP COMPARE_FUNCTION	; Calls the compare function

	JMP ENDING

; END OF THE PROGRAMME 
NEXT: ; LOOPS BETWEEN THE DIFFERENT VECTORS AND CALLS THE LOOPING FUNCTION

; Increments bx, which indicates the vector to check 
	INC BX
	INC BX
	INC BX
	INC BX
	
; Compares to check if all vectors are already checked. (Change 3 to the number of vectors)
	CMP BX, 4*3
		JE ENDING
	MOV SI, 0
	JMP LOOPING

ENDING: ; END OF PROGRAM
	MOV DX, 0
	MOV AX, 4C00H 
	INT 21H 
BEGIN ENDP 

; SPACE FOR SUBROUTINES 
COMPARE_FUNCTION:	; COMPARES AN ELEMENT TO CHECK IF IS GOOD
	MOV AH, 0
	CMP AL, VECTOR1[BX][0]
		JE ADD0
RET0:	CMP AL, VECTOR1[BX][1]
			JE ADD1
RET1:	CMP AL, VECTOR1[BX][2]
			JE ADD2
RET2:	CMP AL, VECTOR1[BX][3]
			JE ADD3
RET3:	CMP AH, 1
			JNE FAIL
		INC SI
		JMP LOOPING

ADD0:
	INC AH
	JMP RET0
ADD1:
	INC AH
	JMP RET1
ADD2:
	INC AH
	JMP RET2
ADD3:
	INC AH
	JMP RET3

	
PRINT_CORRECT:	; PRINTS CORRECT IF VECTOR IS CORRECT
	MOV AH,9
	MOV DX, OFFSET correctOutput
	INT 21H
	JMP NEXT
	
FAIL:	; PRINTS FAILURE ARRAY IF THE VECTOR IS NOT CORRECT
 	MOV AH,9
	MOV DX, 0000h
	MOV DX,OFFSET errorNumDif; Write fail
	INT 21H
	JMP NEXT
					


; END OF THE CODE SEGMENT 
CODE ENDS 
; END OF THE PROGRAMME POINTING OUT WHERE THE EXECUTION BEGINS 
END BEGIN