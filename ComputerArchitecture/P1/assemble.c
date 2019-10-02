/* Assembler code for LC-2K */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINELENGTH 1000

struct Instruction
{
	int addr;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH], arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
	
};

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
unsigned count(char *, char *);

int
main(int argc, char *argv[])
{
	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH], arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
	size_t size;
	unsigned cnt = 0;
	char buf[4096];

	if (argc != 3) {
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
		exit(1);
	}

	inFileString = argv[1];
	outFileString = argv[2];
	
	inFilePtr = fopen(inFileString, "r");
	if (inFilePtr == NULL) {
		printf("error in opening %s\n", inFileString);
		exit(1);
	}

	outFilePtr = fopen(outFileString, "w");
	if (outFilePtr == NULL) {
		printf("error in opening %s\n", outFileString);
		exit(1);
	}

    while (!feof(inFilePtr)) {
    	size = fread(buf, 1, sizeof(buf), inFilePtr);
    	cnt += count(buf, buf+size);
    }
    
    struct Instruction ins[cnt];

    int i = 0;
    rewind(inFilePtr);

    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
    	ins[i].addr = i;
    	for (int t=0; t<i; t++) {
    		if (label[0] != '\0' && !strcmp(ins[t].label, label)) {
    			printf("Duplicate label : %s\n", label);
    			exit(1);
    		}
    	}
    	strcpy(ins[i].label, label);
		strcpy(ins[i].opcode, opcode);
		strcpy(ins[i].arg0, arg0);
		strcpy(ins[i].arg1, arg1);
		strcpy(ins[i].arg2, arg2);
    	i += 1;
    }

	for (int k=0; k<cnt; k++) {

        int result = 0;
        int temp;
        int i_arg0, i_arg1, i_arg2;
		int offset = 0;
		int flag = 0;
		int flag1 = 0;

        if (isNumber(ins[k].arg0)) 
        	i_arg0 = atoi(ins[k].arg0);
        else if (ins[k].arg0[0] != '\0') {
        	for (int j=0; j<cnt; j++) {
        		if (!strcmp(ins[j].label, ins[k].arg0)) {
        			i_arg0 = ins[j].addr;
        			flag1 = 1;
        			break;
        		}
        	}
        	if (!flag1) {
        		printf("Undefined label : %s\n", ins[k].arg0);
        		exit(1);
        	}
        }

        if (isNumber(ins[k].arg1))
			i_arg1 = atoi(ins[k].arg1);
        else if (ins[k].arg1[0] != '\0') {
        	for (int j=0; j<cnt; j++) {
        		if (!strcmp(ins[j].label, ins[k].arg1))
        			i_arg1 = ins[j].addr;
        	}
        }

        if (isNumber(ins[k].arg2))
			i_arg2 = atoi(ins[k].arg2);
		else if (ins[k].arg2[0] != '\0') {
        	for (int j=0; j<cnt; j++){
        		if (!strcmp(ins[j].label, ins[k].arg2)) {
        			i_arg2 = ins[j].addr;
        			flag = 1;
        			break;
        		}
        	}
        	if (!flag) {
        		printf("Undefined label : %s\n", ins[k].arg2);
        		exit(1);
        	}
		}

		if (!strcmp(ins[k].opcode, ".fill")) {
			result = i_arg0;
		}

	// R-type
		else if (!strcmp(ins[k].opcode, "add")) {
			/* opcode in binary : 000 = 0 */
			result += i_arg0;
			result = result << 3;
			result += i_arg1;
			result = result << 16;
			result += i_arg2;
		}

		else if (!strcmp(ins[k].opcode, "nor")) {
			/* opcode in binary : 001 = 1 */
			result += 1;
			result = result << 3;
			result += i_arg0;
			result = result << 3;
			result += i_arg1;
			result = result << 16;
			result += i_arg2;
		}

	// I-type
		else if (!strcmp(ins[k].opcode, "lw")) {
			/* opcode in binary : 010 = 2 */
			result += 2;
			result = result << 3;
			result += i_arg0;
			result = result << 3;
			result += i_arg1;
			result = result << 16;
            result += i_arg2;
		}
			
		else if (!strcmp(ins[k].opcode, "sw")) {
			/* opcode in binary : 011 = 3 */
			result += 3;
			result <<= 3;
			result += i_arg0;
			result <<= 3;
			result += i_arg1;
			result <<= 16;
			result += i_arg2;
		}

		else if (!strcmp(ins[k].opcode, "beq")) {
			/* opcode in binary : 100 = 4 */
			result += 4;
			result <<= 3;
			result += i_arg0;
			result <<= 3;
			result += i_arg1;
			result <<= 16;
			if (flag) {
				offset = i_arg2-(ins[k].addr+1);
				if (offset<-32768 || offset>32767) {
					printf("Out of offsetFields %d- line %d\n", offset, ins[k].addr);
					exit(1);
				}
				if (offset<0) {
					offset += 65536;
				}
				result += offset;
			}
			else result += i_arg2;
		}

	// J-type
		else if (!strcmp(ins[k].opcode, "jalr")) {
			/* opcode in binary : 101 = 5 */
			result += 5;
			result <<= 3;
			result += i_arg0;
			result <<= 3;
			result += i_arg1;
			result <<= 16;
		}

	// O-type
		else if (!strcmp(ins[k].opcode, "halt")) {
			/* opcode in binary : 110 = 6 */
			result += 6;
			result <<= 22;
		}

		else if (!strcmp(ins[k].opcode, "noop")) {
			/* opcode in binary : 111 = 7 */
			result += 7;
			result <<= 22;
		}

		else {
			printf("Unrecognized opcode : %s\n", ins[k].opcode);
			exit(1);
		}

        char output[6];

		sprintf(output, "%d\n", result);
        fputs(output, outFilePtr);
	}

	fclose(inFilePtr);
	fclose(outFilePtr);
	return(0);

}	
/*
 * Read and parse a line of the assembly-language file. Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 * 0 if reached end of file
 * 1 if all went well
 *
 * exit(1) if line is too long.
 */
int
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0, char *arg1, char *arg2)
{
	char line[MAXLINELENGTH];
	char *ptr = line;

	/* delete prior values */
	label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

	/* read the line from the assembly-language file */
	if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
		/* reached end of file */
		return(0);
	}

	/* check for line too long (by looking for a \n) */
	if (strchr(line, '\n') == NULL) {
		/* line too long */
		printf("error: line too long\n");
		exit(1);
	}
	
	/* is there a label? */
	ptr = line;
	if (sscanf(ptr, "%[^\t\n\r ]", label)) {
		/* successfully read label; advance pointer over the label */
		ptr += strlen(label);
	}
	/*
	* Parse the rest of the line. Would be nice to have real regular
	* expressions, but scanf will suffice.
	*/
	sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]", opcode, arg0, arg1, arg2);
	return(1);
}

int
isNumber(char *string)
{
	/* return 1 if string is a number */
	int i;
	return((sscanf(string, "%d", &i)) == 1);
}

unsigned
count(char * f, char * end)
{
	unsigned cnt = 0;
	for(; f != end; ++f) {
		if (*f == '\n') {
			cnt++;
		}
	}
	return cnt;
}