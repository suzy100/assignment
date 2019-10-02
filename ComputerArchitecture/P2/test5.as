	lw	0	1	five
	lw	1	2	3			// hazard
	nor	2	1	3			// hazard
start	add	1	2	1
	beq	0	1	start		// branch
	noop
	halt
five	.fill	5
neg1	.fill	-1
stAddr	.fill	start
