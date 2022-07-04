.section .text # The function format
.globl drawEnemy_cactus_0 # The name of the function
.type drawEnemy_cactus_0, @function # the function format
drawEnemy_cactus_0: #label
	addi sp,sp,-16 #move sp
	sw a0,0(sp) #x1
	sw a1,4(sp) #y1
	sw a2,8(sp) #color
	sw ra,12(sp) #save ra
	
	#a0=x1
	#a1=y1
	mv a4,a2 #a4=color
	mv a2,a0 #a2=x1
	addi a3,a1,16 #a3=y1+16
	jal LCD_DrawLine #LCD_DrawLine(x1, y1, x1, y1+16, color);
	
	lw a0,0(sp) #a0=x1
	addi a0,a0,1 #a0=x1+1
	lw a1,4(sp) #a1=y1
	mv a2,a0 #a2=x1+1
	addi a3,a1,16 #a3=y1+16
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 1, y1, x1 + 1, y1+16, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,2 #a0=x1+2
	lw a1,4(sp) #a1=y1
	addi a1,a1,8 #a1=y1+8
	mv a2,a0 #a2=x1+2
	addi a3,a1,1 #a3=y1+9
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 2, y1 + 8, x1 + 2, y1 + 9, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,3 #a0=x1+3
	lw a1,4(sp) #a1=y1
	addi a1,a1,2 #a1=y1+2
	addi a2,a0,-1 #a2=x1+2
	addi a3,a1,6 #a3=y1+8
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 3, y1 + 2, x1 + 2, y1 + 8, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-2 #a0=x1-2
	lw a1,4(sp) #a1=y1
	addi a1,a1,9 #a1=y1+9
	mv a2,a0 #a2=x1-2
	addi a3,a1,1 #a3=y1+10
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 2, y1 + 9, x1 - 2, y1 + 10, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-1 #a0=x1-1
	lw a1,4(sp) #a1=y1
	addi a1,a1,9 #a1=y1+9
	mv a2,a0 #a2=x1-1
	addi a3,a1,1 #a3=y1+10
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 1, y1 + 9, x1 - 1, y1 + 10, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-3 #a0=x1-3
	lw a1,4(sp) #a1=y1
	addi a1,a1,4 #a1=y1+4
	mv a2,a0 #a2=x1-3
	addi a3,a1,5 #a3=y1+9
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 3, y1 + 4, x1 - 3, y1 + 9, color);
	
	lw ra,12(sp) #load ra
	addi sp,sp,16 #move sp
	ret
