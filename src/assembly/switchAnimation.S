.section .text # The function format
.globl switchAnimation # The name of the function
.type switchAnimation, @function # the function format
switchAnimation: #label
	addi sp,sp,-12 #move sp
	sw ra,8(sp) # save ra
	addi t0,x0,80 #i=80
Loop1Head:
	addi t1,x0,160 #end = 160
	bge t0,t1,Loop1End #for i in 80:160
	mv a0,t0 #a0=i
	mv a1,x0 #a1=0
	mv a2,a0 #a2=i
	mv a3,t0 #a3=80
	li a4,0xFFFF #a4=White
	
	sw t0,0(sp) # save t0
	jal LCD_DrawLine #LCD_DrawLine(i, 0, i, 80, WHITE);
	lw t0,0(sp) #load t0
	
	addi a0,x0,159 #a0=159
	sub a0,a0,t0 #a0=159-i
	mv a1,x0 #a1=0
	mv a2,a0 #a2=159-i
	mv a3,t0 #a3=80
	li a4,0xFFFF #a4=White
	
	jal LCD_DrawLine #LCD_DrawLine(159 - i, 0, 159 - i, 80, WHITE);
	lw t0,0(sp) #load t0
	
	addi t0,t0,1 #i++
	j Loop1Head
Loop1End:

	mv t2,x0 #int animation_interval = 0;
	addi t0,x0,80 #i=80
Loop2Head:
	addi t1,x0,160 #end = 160
	bge t0,t1,Loop2End #for i in 80:160
	
	# the if part;
	addi t1,t0,-80 #t1=i-80
	addi t3,x0,8 #t3=8
	rem t1,t1,t3 #t1=(i-80)%8
	bnez t1,EndIf
	addi t2,t2,1 #++animation_interval;
EndIf:
	
	sw t2,4(sp) # save t2
	sw t0,0(sp) # save t0
	
	mv a0,t0 #a0=i
	mv a1,x0 #a1=0
	mv a2,a0 #a2=i
	mv a3,t0 #a3=80
	mv a4,x0 #a4=Black
	
	
	jal LCD_DrawLine #LCD_DrawLine(i, 0, i, 80, BLACK);
	lw t0,0(sp) #load t0
	
	addi a0,x0,159 #a0=159
	sub a0,a0,t0 #a0=159-i
	mv a1,x0 #a1=0
	mv a2,a0 #a2=159-i
	mv a3,t0 #a3=80
	mv a4,x0 #a4=BLACK
	
	jal LCD_DrawLine #LCD_DrawLine(159 - i, 0, 159 - i, 80, BLACK);
	
	lw a0,4(sp) #a0=animation_interval
	jal delay_1ms #delay_1ms(animation_interval)
	
	lw t2,4(sp) #load t2
	lw t0,0(sp) #load t0
	addi t0,t0,1 #i++
	j Loop2Head
Loop2End:	
	lw ra,8(sp) #load ra
	addi sp,sp,12 #move sp
	ret
