/* LC-2K Instruction-level simulator */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINELENGTH 1000
#define NUMMEMORY 65536 /* maximum number of data words in memory */
#define NUMREGS 8 /* number of machine registers */
#define ADD 0
#define NOR 1
#define LW 2
#define SW 3
#define BEQ 4
#define JALR 5 /* JALR will not implemented for this project */
#define HALT 6
#define NOOP 7
#define NOOPINSTRUCTION 0x1c00000

typedef struct IFIDStruct {
    int instr;
    int pcPlus1;
} IFIDType;

typedef struct IDEXStruct {
    int instr;
    int pcPlus1;
    int readRegA;
    int readRegB;
    int offset;
} IDEXType;

typedef struct EXMEMStruct {
    int instr;
    int branchTarget;
    int aluResult;
    int readRegB;
} EXMEMType;

typedef struct MEMWBStruct {
    int instr;
    int writeData;
} MEMWBType;

typedef struct WBENDStruct {
    int instr;
    int writeData;
} WBENDType;

typedef struct stateStruct {
    int pc;
    int instrMem[NUMMEMORY];
    int dataMem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
    IFIDType IFID;
    IDEXType IDEX;
    EXMEMType EXMEM;
    MEMWBType MEMWB;
    WBENDType WBEND;
    int cycles; /* number of cycles run so far */
} stateType;

int convertNum(int num);
void printState(stateType *statePtr);
int field0(int instruction);
int field1(int instruction);
int field2(int instruction);
int opcode(int instruction);
int hazard(stateType *state);
void printInstruction(int instr);

int
main(int argc, char *argv[])
{
	char line[MAXLINELENGTH];
	stateType state;
	stateType newState;
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
		if (sscanf(line, "%d", state.instrMem+state.numMemory) != 1) {
			printf("error in reading address %d\n", state.numMemory);
			exit(1);
		}
		if (sscanf(line, "%d", state.dataMem+state.numMemory) != 1) {
			printf("error in reading address %d\n", state.numMemory);
			exit(1);
		}
		printf("memory[%d]=%d\n", state.numMemory, state.instrMem[state.numMemory]);
	}

	state.pc = 0;
	state.cycles = 0;

	for (int i=0; i<NUMREGS; i++) {
		state.reg[i] = 0;
	}

	state.IFID.instr = state.IDEX.instr = state.EXMEM.instr = state.MEMWB.instr = state.WBEND.instr = NOOPINSTRUCTION;

	/* this is run() */
	while (1)
    {
        printState(&state);

        /* check for halt */
        if (opcode(state.MEMWB.instr) == HALT) {
            printf("machine halted\n");
            printf("total of %d cycles executed\n", state.cycles);
            exit(0);
        }

        newState = state;
        newState.cycles++;

        /* --------------------- IF stage --------------------- */
        newState.IFID.instr = state.instrMem[state.pc];
        newState.pc = state.pc + 1;
        newState.IFID.pcPlus1 = state.pc + 1;

        /* --------------------- ID stage --------------------- */
        if (hazard(&state)) {
        	newState.IFID.instr = state.IFID.instr;
        	newState.pc = state.pc;
        	newState.IFID.pcPlus1 = state.pc;

        	newState.IDEX.instr = NOOPINSTRUCTION;
        	newState.IDEX.pcPlus1 = 0;
        	newState.IDEX.readRegA = newState.IDEX.readRegB = 0;
        	newState.IDEX.offset = 0;
        }
        else {
        	newState.IDEX.instr = state.IFID.instr;
	        newState.IDEX.pcPlus1 = state.IFID.pcPlus1;
	        newState.IDEX.readRegA = state.reg[field0(state.IFID.instr)];
	        newState.IDEX.readRegB = state.reg[field1(state.IFID.instr)];
	        newState.IDEX.offset = convertNum(field2(state.IFID.instr));
	    }

        /* --------------------- EX stage --------------------- */
        newState.EXMEM.instr = state.IDEX.instr;
        newState.EXMEM.branchTarget = state.IDEX.pcPlus1 + state.IDEX.offset;
        int regA = state.IDEX.readRegA;
        int regB = state.IDEX.readRegB;
        int c_opcode = opcode(state.IDEX.instr);
        int p_opcode = opcode(state.EXMEM.instr);
        int pp_opcode = opcode(state.MEMWB.instr);
        int ppp_opcode = opcode(state.WBEND.instr);

        if (ppp_opcode == LW) {
        	if (regA == field1(state.WBEND.instr)) regA = state.WBEND.writeData;
        	if (regB == field1(state.WBEND.instr)) regB = state.WBEND.writeData;
        }
        else if (ppp_opcode==ADD || ppp_opcode==NOR) {
        	if (regA == field2(state.WBEND.instr)) regA = state.WBEND.writeData;
        	if (regB == field2(state.WBEND.instr)) regB = state.WBEND.writeData;
        }

        if (pp_opcode == LW) {
        	if (regA == field1(state.MEMWB.instr)) regA = state.MEMWB.writeData;
        	if (regB == field1(state.MEMWB.instr)) regB = state.MEMWB.writeData;
        }
        else if (pp_opcode==ADD || pp_opcode==NOR) {
        	if (regA == field2(state.MEMWB.instr)) regA = state.MEMWB.writeData;
        	if (regB == field2(state.MEMWB.instr)) regB = state.MEMWB.writeData;
        }

        if(p_opcode==ADD || p_opcode==NOR) {
        	if (regA == field2(state.EXMEM.instr)) regA = state.EXMEM.aluResult;
        	if (regB == field2(state.EXMEM.instr)) regB = state.EXMEM.aluResult;
        }

        switch(c_opcode) {
			/* add */
			case ADD:
				newState.EXMEM.aluResult = regA + regB;
				break;

			/* nor */
			case NOR:
				newState.EXMEM.aluResult = ~(regA | regB);
				break;

			/* lw */
			case LW:
				newState.EXMEM.aluResult = regA + state.IDEX.offset;
				break;

			/* sw */
			case SW:
				newState.EXMEM.aluResult = regA + state.IDEX.offset;
				break;

			/* beq */
			case BEQ:
				newState.EXMEM.aluResult = regA - regB;
				break;
/*
			case JALR:
				break;
*/
			case HALT:
				break;

			/* noop */
			case NOOP:
				/* Do nothing */
				break;

			default:
				printf("Unrecognized operation.\n");
				exit(1);
		}
        newState.EXMEM.readRegB = regB;

        /* --------------------- MEM stage --------------------- */
        newState.MEMWB.instr = state.EXMEM.instr;
        switch(opcode(state.EXMEM.instr)) {
        	case ADD:
        		newState.MEMWB.writeData = state.EXMEM.aluResult;
				break;

			case NOR:
				newState.MEMWB.writeData = state.EXMEM.aluResult;
				break;

			case LW:
				newState.MEMWB.writeData = state.dataMem[state.EXMEM.aluResult];
				break;

			case SW:
				newState.dataMem[state.EXMEM.aluResult] = state.EXMEM.readRegB;
				break;

			case BEQ:
				if (state.EXMEM.aluResult == 0) {
					newState.pc = state.EXMEM.branchTarget;
					newState.IDEX.instr = newState.EXMEM.instr = NOOPINSTRUCTION;
				}
				break;

			case HALT:
				break;

			case NOOP:
				break;

			default:
				printf("Unrecognized operation.\n");
				exit(1);
		}

        /* --------------------- WB stage --------------------- */
        newState.WBEND.instr = state.MEMWB.instr;
        newState.WBEND.writeData = state.MEMWB.writeData;
        int temp = state.MEMWB.instr>>3;
		int destReg = state.MEMWB.instr - (temp<<3);
        
        switch(opcode(state.MEMWB.instr)) {
			case ADD:
				newState.reg[destReg] = state.MEMWB.writeData;
				break;

			case NOR:
				newState.reg[destReg] = state.MEMWB.writeData;
				break;

			case LW:
				newState.reg[field1(state.MEMWB.instr)] = state.MEMWB.writeData;
				break;

			case SW:
				break;

			case BEQ:
				break;

			case HALT:
				printf("HALT error.\n");
				break;

			case NOOP:
				break;

			default:
				printf("Unrecognized operation.\n");
				exit(1);
		}

        /* this is the last statement before end of the loop.
        It marks the end of the cycle and updates the
        current state with the values calculated in this cycle */
        state = newState;
    }
}

int
convertNum(int num)
{
	/* convert a 16-bit number into a 32-bit Linux integer */
	if (num & (1<<15) ) {
		num -= (1<<16);
	}
	return num;
}

void
printState(stateType *statePtr)
{
	int i;
	printf("\n@@@\nstate before cycle %d starts\n", statePtr->cycles);
	printf("\tpc %d\n", statePtr->pc);
	printf("\tdata memory:\n");
	for (i=0; i<statePtr->numMemory; i++) {
		printf("\t\tdataMem[ %d ] %d\n", i, statePtr->dataMem[i]);
	}
	printf("\tregisters:\n");
	for (i=0; i<NUMREGS; i++) {
		printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
	}
	printf("\tIFID:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->IFID.instr);
	printf("\t\tpcPlus1 %d\n", statePtr->IFID.pcPlus1);
	printf("\tIDEX:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->IDEX.instr);
	printf("\t\tpcPlus1 %d\n", statePtr->IDEX.pcPlus1);
	printf("\t\treadRegA %d\n", statePtr->IDEX.readRegA);
	printf("\t\treadRegB %d\n", statePtr->IDEX.readRegB);
	printf("\t\toffset %d\n", statePtr->IDEX.offset);
	printf("\tEXMEM:\n"); printf("\t\tinstruction ");
	printInstruction(statePtr->EXMEM.instr);
	printf("\t\tbranchTarget %d\n", statePtr->EXMEM.branchTarget);
	printf("\t\taluResult %d\n", statePtr->EXMEM.aluResult);
	printf("\t\treadRegB %d\n", statePtr->EXMEM.readRegB);
	printf("\tMEMWB:\n"); printf("\t\tinstruction ");
	printInstruction(statePtr->MEMWB.instr);
	printf("\t\twriteData %d\n", statePtr->MEMWB.writeData);
	printf("\tWBEND:\n");
	printf("\t\tinstruction ");
	printInstruction(statePtr->WBEND.instr);
	printf("\t\twriteData %d\n", statePtr->WBEND.writeData);
}

int
field0(int instruction) {
	return( (instruction>>19) & 0x7);
}

int
field1(int instruction) {
	return( (instruction>>16) & 0x7);
}

int
field2(int instruction) {
	return(instruction & 0xFFFF);
}

int
opcode(int instruction) {
	return(instruction>>22);
}

int
hazard(stateType *state)
{
	if (opcode(state->IDEX.instr) == LW) {
		int reg = field1(state->IDEX.instr);
		int regA = field0(state->IFID.instr);
		int regB = field1(state->IFID.instr);
    	int c_opcode = opcode(state->IFID.instr);
    	if ((c_opcode==LW || c_opcode==SW) && reg==regA) return 1;
    	if (c_opcode==ADD || c_opcode==NOR || c_opcode==BEQ)
    		if (reg==regA || reg==regB) return 1;
    }
    return 0;
}

void
printInstruction(int instr)
{
	char opcodeString[10];
	if (opcode(instr) == ADD) {
		strcpy(opcodeString, "add");
	}
	else if (opcode(instr) == NOR) {
		strcpy(opcodeString, "nor");
	}
	else if (opcode(instr) == LW) {
		strcpy(opcodeString, "lw");
	}
	else if (opcode(instr) == SW) {
		strcpy(opcodeString, "sw");
	}
	else if (opcode(instr) == BEQ) {
		strcpy(opcodeString, "beq");
	}
	else if (opcode(instr) == JALR) {
		strcpy(opcodeString, "jalr");
	}
	else if (opcode(instr) == HALT) {
		strcpy(opcodeString, "halt");
	}
	else if (opcode(instr) == NOOP) {
		strcpy(opcodeString, "noop");
	}
	else {
		strcpy(opcodeString, "data");
	}

	printf("%s %d %d %d\n", opcodeString, field0(instr), field1(instr),  field2(instr));
}