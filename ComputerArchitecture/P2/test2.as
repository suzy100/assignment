	lw	0	0	A
	nor	0	1	A 				// hazard
	lw	0	1	B
	lw	0	2	neg1
	add	2	3	4 				// hazard
	add	4	1	4				// forwarding
loop	beq	0	4	9 			// branch
	add	1	6	6
	beq	0	1	loop
	halt
A	.fill   30
B	.fill	20
neg1	.fill	-1
