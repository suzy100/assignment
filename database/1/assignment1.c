#include <stdio.h>
#include <string.h>

typedef struct Person
{
	char	name[30];
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
		printf("111111\n");
		while (!feof(pFile)) {
			pStr = fgets(strTmp, sizeof(strTmp), pFile);

			if (colCnt >= 1) {
				if (pStr == NULL) break;
				sscanf(pStr, "%[^','],%s", &person[cnt].name, &person[cnt].p_number);
				cnt++;
			}

			else colCnt++;
		}

		fclose(pFile);

	}

	else if ( (pFile = fopen("contact.csv", "r")) != NULL ) {
		printf("22222\n");
		while (!feof(pFile)) {
			pStr = fgets(strTmp, sizeof(strTmp), pFile);

			if (colCnt >= 1) {
				if (pStr == NULL) break;
				sscanf(pStr, "%[^','],%s", &person[cnt].name, &person[cnt].p_number);
				cnt++;
			}

			else colCnt++;
		}

		fclose(pFile);

		printf("%s, %s\n", person[0].name, person[0].p_number);
	}

	else {
		printf("Cannot find data.\n");
	}
	// if (pFile != NULL) {
	// 	while (!feof(pFile)) {

	// 	}
	// }

	if ((pFile = fopen("2017029752_백승수.csv", "w")) != NULL) {
		printf("success\n");
		for (int i = 0; i < cnt; i++) {
			char buffer[50];
            memset(buffer, '\0', sizeof(char)*50);
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

	while (1) {
		printf("Choose number what you want to do.\n");
		printf("0. Exit\n");
		printf("1. Search\n");
		printf("2. Insert\n");
		printf("3. Modify\n");
		printf("4. Delete\n");

		scanf("%d", &command); 

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
				printf("Sorry. Maybe wrong command.\nPlease insert number 0~4.\n");
				break;
		}

		//pFile = fopen("2017029752_.csv", "w");
		//fclose(pFile);

		if (command == 2 || command == 3 || command == 4) {
			if ((pFile = fopen("2017029752_백승수.csv", "w")) != NULL) {
				printf("success\n");
				for (int i = 0; i < cnt; i++) {
					char buffer[50];
                    memset(buffer, '\0', sizeof(char)*50);
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
	
	char input[30];
	scanf("%s", input);

	int r_index = 0;
	int c = 0;
	
	int len = strlen(input);
	for (int i = 0; i < cnt; i++) {
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

	/*
	printf("Do you want to Modify or Delete?\n");
	printf("1. Modify\n");
	printf("2. Delete\n");
	printf("3. No thanks (Back to main menu)\n");
	scanf("%d", &command);

	switch (command) {
		int index;
		case 1:
			while (1) {
				printf("Modify what? Choose index.\n");
				scanf("%d", &index);
				if (index < 0 || index >= c) {
					printf("Invalid index.\n");
				}
				else break;
			}
			modify(person, ii[index]);
			printf("Modified.\n");
			break;

		case 2:
			while (1) {
				printf("Delete what? Choose index.\n");
				scanf("%d", &index);
				if (index < 0 || index >= c) {
					printf("Invalid index.\n");
				}
				else break;
			}
			delete(person, ii[index]);
			printf("Deleted.\n");
			break;

		case 3:
			return;

		default:
			printf("Wrong command. Back to main menu.\n");
			break;
	}

	*/

	return;
}

void insert(Person *person) {
	printf("<Insert Mode>\n");
	printf("name: ");
	scanf("%s", &person[cnt].name);
	printf("phone number: ");
	scanf("%s", &person[cnt].p_number);
	cnt++;
	return;
}

void modify(Person *person) {
	printf("Modify what? Give me the name: ");

	char input[30];
	scanf("%s", input);

	int r_index = 0;
	int c = 0;

	for (int i = 0; i < cnt; i++) {
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

	int index;
	while (1) {
		printf("Modify what? Choose index.\n");
		scanf("%d", &index);
		if (index < 0 || index >= c) {
			printf("Invalid index.\n");
		}
		else break;
	}
	index = ii[index];
	printf("<Modify Mode>\n");
	printf("Modify (1)name or (2)phone number?\n");
	int ans;
	while (1) {
		scanf("%d",&ans);
		switch (ans) {
		case 1:
			printf("name: ");
			scanf("%s", &person[index].name);
			return;
		case 2:
			printf("phone number: ");
			scanf("%s", &person[index].p_number);
			return;
		default:
			printf("Wrong command. Choose 1 or 2\n");
		}
	}
}

void delete(Person *person) {
	printf("Delete what? Give me the name: ");

	char input[30];
	scanf("%s", input);

	int r_index = 0;
	int c = 0;

	for (int i = 0; i < cnt; i++) {
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

	int index;
	while (1) {
		printf("Delete what? Choose index.\n");
		scanf("%d", &index);
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
