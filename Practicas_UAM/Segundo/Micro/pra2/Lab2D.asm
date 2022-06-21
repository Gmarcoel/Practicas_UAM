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
vector1 DB 1,2,3,4
vector2 DB 3,4,1,2 
vector3 DB 2,1,4,3 
vector4 DB 4,3,2,1 
numberASCII DB 8 dup (0), " $"
errorRows DB "INVALID ROWS", 13, 10, '$' 
correctRows DB "VALID ROWS",13,10,'$' 
errorColumns DB "INVALID COLUMNS", 13, 10, '$' 
correctColumns DB "VALID COLUMNS",13,10,'$' 
rc_flag DB 0, 0 ; row column flag to check if rows and columns are ok
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
MOV SI, 0
MOV DI, 1
LOOPING:	;LOOPS EACH ELEMENT OF THE VECTOR AND CALLS TO THE COMPARING FUNCTION
	CMP SI, 4
		JE NEXT ; If all the elements of the vector have been read, it goes to the next vector
	CALL READ	; function to read a vector
	CALL TRANSFORM ; writes the read number into ascii
	CALL ADDSPACE	; adds spaces so the output looks cleaner
	INC SI	; counter that loops through the elements of the vectors
	JMP LOOPING	; jumps to the begining of the loop
	
READ:	; function that reads a vector element
	MOV AX, 0	
	MOV BX, CX
	MOV AL, DS:vector1[BX][SI]
	RET
PRINT :	; funtion that prints a vector (saved in the numberASCII variable)
	MOV BX, CX
	MOV DX, OFFSET numberASCII
	MOV AH, 9h
	INT 21h
	MOV DL, 0Ah
	MOV AH, 02h
	INT 21h
	RET

TRANSFORM: ; function that transforms into ascii
	ADD AX, 30h
	MOV BX, CX
	MOV DS:numberASCII[DI], AL
	INC DI
	RET
ADDSPACE:	; adds spaces to the numberASCII variable to make the output cleaner
	MOV DS:numberASCII[DI], ' '
	INC DI
	RET

NEXT: ; function that goes to the next vector
	CMP CX, 10h
		JGE CHECK_ROWS
	CALL PRINT
	ADD CX, 4
	
	MOV SI, 0
	MOV DI, 1
	JMP LOOPING

FAIL_ROWS:	; prints if rows are invalid
	MOV DX, OFFSET errorRows
	MOV AH, 9h
	INT 21h
	JMP FLAG_CHECK2
CORRECT_ROWS:	; prints if rows are valid
	MOV DX, OFFSET correctRows
	MOV AH, 9h
	INT 21h
	JMP FLAG_CHECK2
FAIL_COLUMNS:	; prints if columns are invalid
	MOV DX, OFFSET errorColumns
	MOV AH, 9h
	INT 21h
	JMP ENDING
CORRECT_COLUMNS:	; prints if columns are valid
	MOV DX, OFFSET correctColumns
	MOV AH, 9h
	INT 21h
	JMP ENDING
FLAG_CHECK:	; checks if row flag is active (in that case rows would be invalid)
	MOV AX, 0
	MOV AL, DS:rc_flag[0]
	CMP AL, 1
		JE FAIL_ROWS
	JMP CORRECT_ROWS
FLAG_CHECK2: ; checks that column flag is active
	MOV AX, 0
	MOV AL, DS:rc_flag[1]
	CMP AL, 1
		JE FAIL_COLUMNS
	JMP CORRECT_COLUMNS

ENDING: ; END OF PROGRAM
	MOV DX, 0
	MOV AX, 4C00H 
	INT 21H 
	
CHECK_ROWS:	; check that both rows and columns work
	MOV BX, 0
	MOV SI, 0
	MOV DI, 0
	MOV CX, 0
ROWS_START:	; used to make a loop for each vector
	CMP BX, 10h
		JGE FLAG_CHECK
	MOV AX, 0
	MOV AL, DS:VECTOR1[BX][SI] ; Moves the chosen element of the vector to the register AL
	
	CMP AL, VECTOR1[BX][0]
		JE ADD0
RET0:	CMP AL, VECTOR1[BX][1] ; this part is for rows
			JE ADD1
RET1:	CMP AL, VECTOR1[BX][2]
			JE ADD2
RET2:	CMP AL, VECTOR1[BX][3]
			JE ADD3
RET3:	CMP AH, 1
			JNE FLAG_ROWS
	CMP AL, 4	; Check if greater than 4
		JG FLAG_ROWS
	CMP AL, 1	; Check if shorter than 1
		JL FLAG_ROWS
RET_ROW: ;return after adding the row flag
	MOV AX, 0
	MOV DX, BX
	MOV BX, CX
	MOV AL, DS:VECTOR1[BX][DI] ; Moves the chosen element of the vector to the register AL
	
		CMP AL, VECTOR1[0][DI]
			JE ADD4
RET4:	CMP AL, VECTOR1[4][DI]
			JE ADD5
RET5:	CMP AL, VECTOR1[8][DI]
			JE ADD6
RET6:	CMP AL, VECTOR1[12][DI]
			JE ADD7
RET7:	CMP AH, 1
			JNE FLAG_COLUMNS
	CMP AL, 4	; Check if greater than 4
		JG FLAG_COLUMNS
	CMP AL, 1	; Check if shorter than 1
		JL FLAG_COLUMNS
RET_COL:	; return to the place after adding the column flag
	MOV CX, BX
	MOV BX, DX
	ADD CX, 4
	INC SI
	CMP SI, 4
		JE END_ROW
	JMP ROWS_START
END_ROW:
	ADD BX, 4
	MOV SI, 0
	INC DI
	MOV CX, 0
	JMP ROWS_START

ADD0:	; This is separated in 7 to jump to different places but is just one function
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
ADD4:	; This is separated in 4 to jump to different places but is just one function
	INC AH
	JMP RET4
ADD5:
	INC AH
	JMP RET5
ADD6:
	INC AH
	JMP RET6
ADD7:
	INC AH
	JMP RET7

	
FLAG_ROWS: ; adds a flag if the rows are invalid so they are printed as invalid later
	MOV DS:rc_flag[0], 1
	jmp RET_ROW
	

FLAG_COLUMNS:	; adds a flag if the columns are invalid so they are printed as invalid later
	MOV DS:rc_flag[1], 1
	JMP RET_COL



BEGIN ENDP 

; END OF THE CODE SEGMENT 
CODE ENDS 
; END OF THE 
 
END BEGIN