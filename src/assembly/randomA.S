.section .text # The function format
.globl randomA # The name of the function
.type randomA, @function # the function format
randomA: #label
	# Linear congruential generator(LCG)
	# Hull–Dobell Theorem
	li a1, 217672
	# M = 217672 = 2*2*2*7*13*13*23
	li a2, 4187
	# A = 4187 = 2*7*13*23+1
	li a3, 3135
	# C = 3135 = 3*5*11*19
	mul a0, a0, a2
	# A*N_i
	add a0, a0, a3
	# A*N_i + C
	rem a0, a0, a1
	# N_o = (A*N_i + C)%M
	ret
