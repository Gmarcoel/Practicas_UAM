# This is a comment
all: ALUMNO.exe

ALUMNO.exe: alumno.obj
	tlink /v alumno

ALUMNO.obj: ALUMNO.asm
	tasm /zi alumno.asm ,, alumno.lst
