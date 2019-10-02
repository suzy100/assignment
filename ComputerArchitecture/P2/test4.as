	lw	0	0	one
	lw	0	1	A 			// hazard
	add	0	1	2			// hazard
	add	2	2	3			// forwarding
	nor	1	3	4			// forwarding
	add	4	4	5			// forwarding
	noop
	halt
one	.fill	1
A	.fill	10
