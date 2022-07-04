.section .text # The function format
.globl drawEnemy_cactus_1 # The name of the function
.type drawEnemy_cactus_1, @function # the function format
drawEnemy_cactus_1: #label
	addi sp,sp,-16 #move sp
	sw a0,0(sp) #x1
	sw a1,4(sp) #y1
	sw a2,8(sp) #color
	sw ra,12(sp) #save ra
	
	#a0=x1
	#a1=y1
	mv a4,a2 #a4=color
	mv a2,a0 #a2=x1
	addi a3,a1,23 #a3=y1+23
	jal LCD_DrawLine #LCD_DrawLine(x1, y1, x1, y1+23, color);
	
	lw a0,0(sp) #a0=x1
	addi a0,a0,1 #a0=x1+1
	lw a1,4(sp) #a1=y1
	mv a2,a0 #a2=x1+1
	addi a3,a1,23 #a3=y1+23
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 1, y1, x1 + 1, y1+23, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,2 #a0=x1+2
	lw a1,4(sp) #a1=y1
	mv a2,a0 #a2=x1+2
	addi a3,a1,23 #a3=y1+23
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 2, y1, x1 + 2, y1+23, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,3 #a0=x1+3
	lw a1,4(sp) #a1=y1
	mv a2,a0 #a2=x1+3
	addi a3,a1,23 #a3=y1+23
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 3, y1, x1 + 3, y1+23, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,4 #a0=x1+4
	lw a1,4(sp) #a1=y1
	addi a1,a1,16 #a1=y1+16
	mv a2,a0 #a2=x1+4
	addi a3,a1,1 #a3=y1+17
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 4, y1 + 16, x1 + 4, y1 + 17, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,5 #a0=x1+5
	lw a1,4(sp) #a1=y1
	addi a1,a1,16 #a1=y1+16
	mv a2,a0 #a2=x1+5
	addi a3,a1,1 #a3=y1+17
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 5, y1 + 16, x1 + 5, y1 + 17, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,6 #a0=x1+6
	lw a1,4(sp) #a1=y1
	addi a1,a1,9 #a1=y1+9
	mv a2,a0 #a2=x1+6
	addi a3,a1,7 #a3=y1+16
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 6, y1 + 9, x1 + 6, y1 + 16, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,7 #a0=x1+7
	lw a1,4(sp) #a1=y1
	addi a1,a1,9 #a1=y1+9
	mv a2,a0 #a2=x1+7
	addi a3,a1,7 #a3=y1+16
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 + 7, y1 + 9, x1 + 7, y1 + 16, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-1 #a0=x1-1
	lw a1,4(sp) #a1=y1
	addi a1,a1,12 #a1=y1+12
	mv a2,a0 #a2=x1-1
	addi a3,a1,2 #a3=y1+14
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 1, y1 + 12, x1 - 1, y1 + 14, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-2 #a0=x1-2
	lw a1,4(sp) #a1=y1
	addi a1,a1,12 #a1=y1+12
	mv a2,a0 #a2=x1-2
	addi a3,a1,2 #a3=y1+14
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 2, y1 + 12, x1 - 2, y1 + 14, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-3 #a0=x1-3
	lw a1,4(sp) #a1=y1
	addi a1,a1,6 #a1=y1+6
	mv a2,a0 #a2=x1-3
	addi a3,a1,7 #a3=y1+13
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 3, y1 + 6, x1 - 3, y1 + 13, color);
    
    lw a0,0(sp) #a0=x1
	addi a0,a0,-4 #a0=x1-4
	lw a1,4(sp) #a1=y1
	addi a1,a1,6 #a1=y1+6
	mv a2,a0 #a2=x1-4
	addi a3,a1,6 #a3=y1+12
	lw a4,8(sp) #a4=color
    jal LCD_DrawLine #LCD_DrawLine(x1 - 4, y1 + 6, x1 - 4, y1 + 12, color);
	
	lw ra,12(sp) #load ra
	addi sp,sp,16 #move sp
	ret
