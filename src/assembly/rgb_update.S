.section .text # The function format
.globl rgb_update # The name of the function
.type rgb_update, @function # the function format
rgb_update: #label
	lw t0,0(a1)
	# t0 is *stage_t
	lw t2,0(a0)
	# t2 is *color_t
	li t1,1
	beq t0,t1,stage1
	# stage1 is 1
	addi t1,t1,1
	beq t0,t1,stage2
	# stage2 is 2
	addi t1,t1,1
	beq t0,t1,stage3
	# stage3 is 3
	j stageEnd
	# jump out
stage1:
	#stage1
	addi t2,t2,-2047
	j stageEnd
	# jump out
stage2:
	#stage2
	addi t2,t2,63
	j stageEnd
	# jump out
stage3:
	#stage3
	addi t2,t2,1984
stageEnd:
	# the end of the part
	
	# *color_t / 32 == 0
	srli t1,t2,5
	beqz t1,part1
	# (*color_t / 2048 == 0) && (*color_t % 32 == 0)
	srli t1,t2,11
	# t1 = *color_t / 2048
	addi t4,x0,32
	rem t4,t2,t4
	#t4 = *color_t % 32
	add t1,t1,t4
	# and operation
	beqz t1,part2
	# *color_t % 2048 == 0
	li t1,2048
	rem t1,t2,t1
	# t1 = *color_t % 2048
	beqz t1,part3
	j partEnd
	# jump out
part1:
	# *stage_t = 2
    # *color_t = 0b0000000000011111
    addi t0,x0,2
    addi t2,x0,31
	j partEnd
	# jump out
part2:
	# *stage_t = 3
	addi t0,x0,3
	j partEnd
	# jump out
part3:
	# *stage_t = 1
    # *color_t = 0b1111100000000000
	addi t0,x0,1
	li t2,0b1111100000000000
	# jump out
partEnd:
	sw t0,0(a1)
	# stage_t back
	sw t2,0(a0)
	# color_t back
	ret
