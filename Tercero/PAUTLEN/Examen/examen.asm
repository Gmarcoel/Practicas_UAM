; escribir_cabecera_data:
segment .data 
; initialised varables
	func_dividir_error0_message db "Division by zero", 10,13,0
	vector_out_of_bounds_message db "Vector index out of bounds", 10,13,0


; escribir_cabecera_bss:
segment .bss 
; uninitalised varables
	__esp resd 1
;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	x
	_x resd 1	; declarar_variable(x, 0, 1):
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	x
;R2:	<declaraciones> ::= <declaracion>

; escribir segmento codigo:
segment .text
	global main
	extern print_int, print_boolean, print_string, print_blank, print_endofline, scan_int, scan_boolean
;R21:	<funciones> ::=

; escribir inicio main:
main:
	mov [__esp], esp
;D:	=
;D:	4
;R105:	<numero> ::= <digito>
;D:	;
;R104:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>

	; escribir operando(nombre=4, es_variable=0):
	mov dword eax, 4
	push dword eax
;R81:	<exp> ::= <constante_entera>

	; asignar(nombre=x,es_variable=0):
	pop dword eax
	mov [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp> 
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	do

; while_inicio(etiqueta=0)
; inicio del while 0:
func_while_inicio0:
;D:	{
;D:	printf
;D:	(
;D:	x
;D:	)

	; escribir operando(nombre=x, es_variable=1):
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;R82:	<exp> ::= ( <exp> )
;D:	;

	; escribir(es_variable=1,tipo=0):
	pop dword eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	do

; while_inicio(etiqueta=1)
; inicio del while 1:
func_while_inicio1:
;D:	{
;D:	printf
;D:	(
;D:	true
;R102:	<constante_logica> ::= true
;R99:	<constante> ::= <constante_logica>

	; escribir operando(nombre=1, es_variable=0):
	mov dword eax, 1
	push dword eax
;R81:	<exp> ::= <constante_entera>
;D:	)
;R82:	<exp> ::= ( <exp> )
;D:	;

	; escribir(es_variable=0,tipo=1):
	call print_boolean
	add esp, 4
	call print_endofline
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	x
;D:	=
;D:	x
;D:	+

	; escribir operando(nombre=x, es_variable=1):
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	1
;R105:	<numero> ::= <digito>
;D:	;
;R104:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>

	; escribir operando(nombre=1, es_variable=0):
	mov dword eax, 1
	push dword eax
;R81:	<exp> ::= <constante_entera>

	; sumar(es_variable_1=1, es_variable_2=0)
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>

	; asignar(nombre=x,es_variable=0):
	pop dword eax
	mov [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp> 
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;D:	while
;D:	(
;D:	(
;D:	x
;D:	<=

	; escribir operando(nombre=x, es_variable=1):
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	5
;R105:	<numero> ::= <digito>
;D:	)
;R104:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>

	; escribir operando(nombre=5, es_variable=0):
	mov dword eax, 5
	push dword eax
;R81:	<exp> ::= <constante_entera>

	; menor igual(es_variable1=1, es_variable2=0, etiqueta=2):
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	cmp eax, ebx
	jle func_menor_igual_true2
	push dword 0
	jmp func_menor_igual_final2
func_menor_igual_true2: 
	push dword 1
func_menor_igual_final2:
;R95:	<comparacion> ::= <exp> <= <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	;

	; while_exp_pila(exp_es_variable=0, etiqueta=1):
	pop eax
	cmp eax, 1
	jne func_while_final1

	; while_fin(etiqueta=1):
	jmp func_while_inicio1
func_while_final1:
;R52:	<bucle>::= do{ <sentencias> } while (<exp>)
;R41:	<bloque> ::= <bucle>
;R33:	<sentencia> ::= <bloque>
;D:	x
;D:	=
;D:	x
;D:	+

	; escribir operando(nombre=x, es_variable=1):
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	1
;R105:	<numero> ::= <digito>
;D:	;
;R104:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>

	; escribir operando(nombre=1, es_variable=0):
	mov dword eax, 1
	push dword eax
;R81:	<exp> ::= <constante_entera>

	; sumar(es_variable_1=1, es_variable_2=0)
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>

	; asignar(nombre=x,es_variable=0):
	pop dword eax
	mov [_x], eax
;R43:	<asignacion> ::= <identificador> = <exp> 
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;D:	while
;D:	(
;D:	(
;D:	x
;D:	<=

	; escribir operando(nombre=x, es_variable=1):
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	6
;R105:	<numero> ::= <digito>
;D:	)
;R104:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>

	; escribir operando(nombre=6, es_variable=0):
	mov dword eax, 6
	push dword eax
;R81:	<exp> ::= <constante_entera>

	; menor igual(es_variable1=1, es_variable2=0, etiqueta=3):
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	cmp eax, ebx
	jle func_menor_igual_true3
	push dword 0
	jmp func_menor_igual_final3
func_menor_igual_true3: 
	push dword 1
func_menor_igual_final3:
;R95:	<comparacion> ::= <exp> <= <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
;D:	;

	; while_exp_pila(exp_es_variable=0, etiqueta=0):
	pop eax
	cmp eax, 1
	jne func_while_final0

	; while_fin(etiqueta=0):
	jmp func_while_inicio0
func_while_final0:
;R52:	<bucle>::= do{ <sentencias> } while (<exp>)
;R41:	<bloque> ::= <bucle>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R1:	<programa> ::= main { <declaraciones> <funciones> <sentencias> }

; escribir fin:
end_prog:
	mov esp, [__esp]
	ret

func_dividir_error0:
	push dword func_dividir_error0_message
	call print_string
	call print_endofline
	add esp, 4
	jmp end_prog

vector_out_of_bounds:
	push dword vector_out_of_bounds_message
	call print_string
	call print_endofline
	add esp, 4
	jmp end_prog
