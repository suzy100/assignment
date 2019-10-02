	lw	0	2	mcand
	lw	0	3	mplier
	lw 	0	4	current
	lw 	0	5	bound
loop	nor	3	3	3
	nor	4	4	4
	nor	3	4	6
	nor	3	3	3
	nor	4	4	4
	beq	0	6	here
	add	2	1	1
here	add	4	4	4
	add	2	2	2
	beq	4	5	done
	beq	0	0	loop
done	halt
mcand	.fill	32766
mplier	.fill	10383
current	.fill	1
bound	.fill	32768
