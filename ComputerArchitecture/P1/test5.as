	lw 0 0 zero
	lw 0 1 zero
	lw 0 2 neg1
	lw 0 3 num
st	add	1 3 1
	add	3 2 3
	beq	3 0	done
	beq 0 0 st
done	halt
zero	.fill	0
neg1	.fill	-1
num		.fill 	5
