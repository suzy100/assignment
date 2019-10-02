	lw 0 1 five	
	lw 1 2 3
start nor 1 2 1
	beq 0 1 2
	beq 0 0 start
	noop
done halt
five .fill 5
five .fill 8
stAddr .fill start
