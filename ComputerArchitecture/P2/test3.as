	lw	0	0	start
	lw	0	1	num			// hazard
	lw	0	2	neg1
	add	0	0	3
loop	add 3	0	4		// forwarding
	add	0	3	3
	add 1	2	1
	beq	0	1	loop		// branch
end	sw	0	4	result
	halt
start	.fill	1	
num	.fill	10
neg1	.fill	-1
result	.fill	0
