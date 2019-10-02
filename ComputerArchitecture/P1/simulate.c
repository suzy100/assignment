/* LC-2K Instruction-level simulator */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000
typedef struct stateStruct {
	int pc;
	int mem[NUMMEMORY];
	int reg[NUMREGS];
	int numMemory;
} stateType;

void printState(stateType *);
int convertNum(int);

int
main(int argc, char *argv[])
{
	char line[MAXLINELENGTH];
	stateType state;
	FILE *filePtr;
	int insnum = 0;

	if (argc != 2) {
		printf("error: usage: %s <machine-code file>\n", argv[0]);
		exit(1);
	}
	filePtr = fopen(argv[1], "r");
	if (filePtr == NULL) {
		printf("error: can't open file %s", argv[1]);
		perror("fopen");
		exit(1);
	}
	/* read in the entire machine-code file into memory */
	for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++) {
		if (sscanf(line, "%d", state.mem+state.numMemory) != 1) {
			printf("error in reading address %d\n", state.numMemory);
			exit(1);
		}
		printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
	}

	state.pc = 0;

	for (int i=0; i<NUMREGS; i++) {
		state.reg[i] = 0;
	}

	while (1){
		printState(&state);

		int opcode = state.mem[state.pc]>>22;
		int temp = state.mem[state.pc]>>19;
		int regA = temp - (opcode<<3);
		int regB = (state.mem[state.pc]>>16) - (temp<<3);
		temp = state.mem[state.pc]>>3;
		int destReg = state.mem[state.pc] - (temp<<3);
		temp = state.mem[state.pc]>>16;
		int offset = convertNum(state.mem[state.pc] - (temp<<16));

		state.pc += 1;
		insnum += 1;

		switch(opcode) {
		// R-type
			/* add */
			case 0 :
				state.reg[destReg] = state.reg[regA] + state.reg[regB];
				break;

			/* nor */
			case 1 :
				state.reg[destReg] = ~(state.reg[regA] | state.reg[regB]);
				break;

		// I-type
			/* lw */
			case 2 :
				offset += state.reg[regA];
				state.reg[regB] = state.mem[offset];
				break;

			/* sw */
			case 3 :
				offset += state.reg[regA];
				state.mem[offset] = state.reg[regB];
				break;

			/* beq */
			case 4 :
				if (state.reg[regA] == state.reg[regB]) {
					state.pc = state.pc+offset;
				}
				break;

		// J-type
			/* jalr */
			case 5 :
				state.reg[regB] = state.pc;
				state.pc = state.reg[regA];
				break;

		// O-type
			/* halt */
			case 6 :
				printf("machine halted\ntotal of %d instructions executed\nfinal state of machine:\n", insnum);
				printState(&state);
				exit(0);

			/* noop */
			case 7 :
				/* Do nothing */
				break;

			default :
				printf("Unrecognized\n");
				exit(1);
		}

	}
	return(0);
}

void
printState(stateType *statePtr)
{
	int i;
	printf("\n@@@\nstate:\n");
	printf("\tpc %d\n", statePtr->pc);
	printf("\tmemory:\n");
	for (i=0; i<statePtr->numMemory; i++) {
		printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
	}
	printf("\tregisters:\n");
	for (i=0; i<NUMREGS; i++) {
		printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
	}
	printf("end state\n");
}

int
convertNum(int num)
{
/* convert a 16-bit number into a 32-bit Linux integer */
	if (num & (1<<15) ) {
		num -= (1<<16);
	}
	return(num);
} 