#include <stdio.h>
#include <string.h>

typedef struct Person
{
	char	name[50];
	char	p_number[15];
}Person;

void search(Person*);
void insert(Person*);
void modify(Person*);
void delete(Person*);

FILE *pFile;
int fd;
int command;
char *pStr;
char strTmp[255];
int cnt = 0, colCnt = 0;
int ii[500001];
Person person[500001];

int main()
{
	if ( (pFile = fopen("2017029752_백승수.csv", "r")) != NULL ) {
		while (!feof(pFile)) {
			pStr = fgets(strTmp, sizeof(strTmp), pFile);

			if (pStr == NULL) break;
			sscanf(pStr, "%[^','],%s", person[cnt].name, person[cnt].p_number);
			cnt++;
		}

		fclose(pFile);

	}

	else if ( (pFile = fopen("contact.csv", "r")) != NULL ) {
		while (!feof(pFile)) {
			pStr = fgets(strTmp, sizeof(strTmp), pFile);

			if (pStr == NULL) break;
			sscanf(pStr, "%[^','],%s", person[cnt].name, person[cnt].p_number);
			cnt++;
		}

		fclose(pFile);
	}

	else {
		printf("Cannot find data.\n");
        return -1;
	}

	if ((pFile = fopen("2017029752_백승수.csv", "w")) != NULL) {
		printf("success\n");
		for (int i = 0; i < cnt; i++) {
			char buffer[70];
            memset(buffer, '\0', sizeof(char)*70);
			sprintf(buffer, "%s,%s\n", person[i].name, person[i].p_number);
			int len = strlen(buffer);
			fwrite(buffer, (sizeof(char)) * len, 1, pFile);
		}
		fclose(pFile);
	}
	else {
		printf("Failed to save.\n");
		return -1;
	}

    int flag, com;

	while (1) {
        do {
            flag = 0;
		    printf("Choose number what you want to do.\n");
		    printf("0. Exit\n");
		    printf("1. Search\n");
		    printf("2. Insert\n");
		    printf("3. Modify\n");
		    printf("4. Delete\n");

		    if (!scanf("%d", &command)) {
                printf("Wrong command.\nPlease insert number 0~4.\n");
                flag = 1;
                while(com=getchar() != '\n' && com != EOF);
            }
        } while (flag);

		switch (command) {
			case 0:
				return 0;

			case 1:
				search(person);
				break;

			case 2:
				insert(person);
				printf("Inserted.\n");
				break;

			case 3:
				modify(person);
				printf("Modified.\n");
				break;

			case 4:
				delete(person);
				printf("Deleted.\n");
				break;
			
			default:
				printf("Wrong command. Please insert number 0~4.\n");
				break;
		}

		if (command == 2 || command == 3 || command == 4) {
			if ((pFile = fopen("2017029752_백승수.csv", "w")) != NULL) {
				for (int i = 0; i < cnt; i++) {
					char buffer[70];
                    memset(buffer, '\0', sizeof(char)*70);
					sprintf(buffer, "%s,%s\n", person[i].name, person[i].p_number);
					int len = strlen(buffer);
					fwrite(buffer, (sizeof(char)) * len, 1, pFile);
				}
				fclose(pFile);
			}
			else {
				printf("Failed to save.\n");
				return -1;
			}
		}
		
	}
}

void search(Person *person) {
	printf("Searching: ");
	
	char input[50];
	scanf("%s", input);

	int r_index = 0;
	int c = 0;
	
	int len = strlen(input);
	for (int i = 1; i < cnt; i++) {
		if (strncmp(person[i].name, input, len) == 0) {
			printf("name: %s // phone: %s\n", person[i].name, person[i].p_number);
			ii[r_index] = i;
			r_index++;
			c++;
		}
	}

	if (c == 0) {
		printf("No result.\n");
		return;
	}

	return;
}

void insert(Person *person) {
    char buffer[15];
    int flag;
	printf("<Insert Mode>\n");
	printf("name: ");
	scanf("%s", person[cnt].name);
    while (getchar() != '\n');
    
    do {
        flag = 0;
	    printf("phone number: ");
	    scanf("%[0-9]", buffer);
        while (getchar() != '\n');
        if (!(strlen(buffer) == 11 && buffer[0] == '0' && buffer[1] == '1' && buffer[2] == '0')) {
            flag = 1;
            printf("Phone number should be 010xxxxxxxx (x is number)\n");
        }
    } while (flag);

    strcpy(person[cnt].p_number, buffer);
	cnt++;
	return;
}

void modify(Person *person) {
	printf("Modify what? Give me the exact name: ");

	char input[50];
	scanf("%s", input);

	int r_index = 0;
	int c = 0;

	for (int i = 1; i < cnt; i++) {
		if (strcmp(person[i].name, input) == 0) {
			printf("[%d] name: %s // phone: %s\n", r_index, person[i].name, person[i].p_number);
			ii[r_index] = i;
			r_index++;
			c++;
		}
	}

	if (c == 0) {
		printf("No result.\n");
		return;
	}
    int com, flag;
	int index;
	while (1) {
        do {
            flag = 0;
		    printf("Modify what? Choose index.\n");
		    if (!scanf("%d", &index)) {
                printf("Wrong command. Please insert number.\n");
                flag = 1;
                while (com=getchar() != '\n' && com != EOF);
            }
        } while (flag);

		if (index < 0 || index >= c) {
			printf("Invalid index.\n");
		}
		else break;
	}
	index = ii[index];
	printf("<Modify Mode>\n");
	int ans;
	while (1) {
        do {
            flag = 0;
            
            printf("Modify (1)name or (2)phone number?\n");
            
            if (!scanf("%d",&ans)) {
                printf("Wrong command. Choose 1 or 2\n");
                flag = 1;
                while (com=getchar() != '\n' && com != EOF);
            }
        } while (flag);
        
        char buffer[15];
        int flag;

		switch (ans) {

		case 1:
			printf("name: ");
			scanf("%s", person[index].name);
			return;

		case 2:
			do {
        			flag = 0;
	    			printf("phone number: ");
	    			scanf("%s", buffer);
                    while (getchar() != '\n');
        			if (!(strlen(buffer) == 11 && buffer[0] == '0' && buffer[1] == '1' && buffer[2] == '0')) {
					    flag = 1;
            			printf("Phone number should be 010xxxxxxxx (x is number)\n");
        			}
    		} while (flag);

    		strcpy(person[index].p_number, buffer);
			cnt++;
			return;

		default:
			printf("Wrong command. Choose 1 or 2\n");
		}
	}
}

void delete(Person *person) {
	printf("Delete what? Give me the exact name: ");

	char input[50];
	scanf("%s", input);

	int r_index = 0;
	int c = 0;

	for (int i = 1; i < cnt; i++) {
		if (strcmp(person[i].name, input) == 0) {
			printf("[%d] name: %s // phone: %s\n", r_index, person[i].name, person[i].p_number);
			ii[r_index] = i;
			r_index++;
			c++;
		}
	}

	if (c == 0) {
		printf("No result.\n");
		return;
	}
    int com, flag;
	int index;
	while (1) {
        do {
            flag = 0;
		    printf("Delete what? Choose index.\n");
		    if (!scanf("%d", &index)) {
                printf("Wrong command. Please insert number.\n");
                flag = 1;
                while (com=getchar() != '\n' && com != EOF);
            }
        } while (flag);

		if (index < 0 || index >= c) {
			printf("Invalid index.\n");
		}
		else break;
	}
	index = ii[index];
	strcpy(person[index].name, person[cnt - 1].name);
	strcpy(person[index].p_number, person[index].p_number);
	
	person[cnt - 1].name[0] = '\0';
	person[cnt - 1].p_number[0] = '\0';
	
	cnt--;

	return;
}
