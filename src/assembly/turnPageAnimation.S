.section .text # The function format
.globl turnPageAnimation # The name of the function
.type turnPageAnimation, @function # the function format
turnPageAnimation: #label
	addi t0,x0,162 #i=162
	addi sp,sp,-8 #move sp
	sw ra,4(sp)	#save ra
ForHead:
	blt t0,x0,ForEnd #for start
	sw t0,0(sp) #save t0
	
	mv a0,t0 #a0=i
	mv a1,x0 #a1=0
	mv a2,a0 #a2=a1
	addi a3,x0,80 #a3=80
	mv a4,x0 #a4=BLACK
	jal LCD_DrawLine #LCD_DrawLine(i, 0, i, 80, BLACK);
	
	lw a0,0(sp) #a0=i
	addi a0,a0,-1 #a0=i-1
	mv a1,x0 #a1=0
	mv a2,a0 #a2=a1
	addi a3,x0,80 #a3=80
	mv a4,x0 #a4=BLACK
	jal LCD_DrawLine #LCD_DrawLine(i-1, 0, i-1, 80, BLACK);
	
	lw a0,0(sp) #a0=i
	addi a0,a0,-2 #a0=i-2
	mv a1,x0 #a1=0
	mv a2,a0 #a2=a1
	addi a3,x0,80 #a3=80
	li a4,0xFFFF #a4=WHITE
	jal LCD_DrawLine #LCD_DrawLine(i-2, 0, i-2, 80, WHITE)
	
	lw a0,0(sp) #a0=i
	addi a0,a0,-3 #a0=i-3
	mv a1,x0 #a1=0
	mv a2,a0 #a2=a1
	addi a3,x0,80 #a3=80
	li a4,0xFFFF #a4=WHITE
	jal LCD_DrawLine #LCD_DrawLine(i-3, 0, i-3, 80, WHITE);
    
	lw t0,0(sp) #load t0
	addi t0,t0,-2 #i=i-2
	j ForHead #jump to start
ForEnd:
	lw ra,4(sp)	#load ra
	addi sp,sp,8 #move sp
	ret
