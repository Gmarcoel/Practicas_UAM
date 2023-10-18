.data 0
num0: .word 1 # posic 0
num1: .word 2 # posic 4
num2: .word 4 # posic 8 
num3: .word 8 # posic 12 
num4: .word 16 # posic 16 
num5: .word 32 # posic 20


.text 0
main:
  # Load the first registers to use
  lw $t1, 0($zero)   lw $r9, 0($r0)
  lw $t2, 4($zero)  # lw $r10, 4($r0)
  lw $t3, 8($zero)  # lw $r11, 8($r0)

  # R-type + beq comparison
  add $t4, $t3, $t1  #t4 = 4 + 1 = 5
  beq $t4, $t1, salto  # Branch not effective because 4!= 1
  sub $t4, $t4, $t1  #t4 = 5 - 1 = 4
  beq $t4, $t3, salto  # Branch effective because 4 = 4
  addi $t5, 9  # In case it doesn't jump
  addi $t6, 9
  addi $t7, 9
  
salto:
  # Loads + beq comparison
  lw $t5, 8($zero)  # lw $r13, 8($r0)
  beq $t5, $t1, segundoSalto  # Branch not effective because 4 != 1
  lw $t6, 8($zero)  # lw $r14, 8($r0)
  beq $t6, $t3, segundoSalto  # Branch effective because 4 = 4
  addi $t5, 7  # In case it doesn't jump
  addi $t6, 7
  addi $t7, 7
  
# End Jump
segundoSalto:
  addi $t8, 8  # To check that the jump has been made
  addi $t9, 8