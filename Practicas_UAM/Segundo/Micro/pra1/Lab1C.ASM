;************************************************************************** 
; MBS 2021. BASIC STRUCTURE OF AN ASSEMBLER PROGRAMME 
;************************************************************************** 
; DATA SEGMENT DEFINITION 
DATA SEGMENT 
;-- fill with the requested data 
	BOOKMARK DB ?
	DRINK DW 0CAFEH
	TABLE200 DB 200 DUP (0)
	TOTALERROR1 DB "This  programme  always  crashes"
	
DATA ENDS 
;************************************************************************** 
; STACK SEGMENT DEFINITION 
STACKSEG SEGMENT STACK "STACK" 
	DB 40H DUP (0) ; initialization example, 64 bytes initialize to 0 
STACKSEG ENDS 
;************************************************************************** 
; EXTRA SEGMENT DEFINITION  
EXTRA SEGMENT 
	RESULT DW 0,0 ; initialization example. 2 WORDS (4 BYTES) 
EXTRA ENDS 
;*********************************	***************************************** 
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
	MOV SP, 64 
	; LOAD A STACK POINTER WITH THE HIGHEST VALUE 
	; END OF INITIALIZATIONS 
	; BEGINNING OF THE PROGRAMME 
	; -- fill with the requested instructions. 
	MOV AL, TOTALERROR1[2]
	MOV TABLE200[63H], AH
	
	MOV AX, DRINK
	MOV TABLE200[23H], AL
	MOV TABLE200[24H], AH
	
	MOV BOOKMARK, AH
	
	; END OF THE PROGRAMME 
	MOV AX, 4C00H 
	INT 21H 
BEGIN ENDP 
; END OF THE CODE SEGMENT 
CODE ENDS 
; END OF THE PROGRAMME POINTING OUT WHERE THE EXECUTION BEGINS 
END BEGIN 	