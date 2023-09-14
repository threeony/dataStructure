#include <stdio.h>
#include <string.h>

#define MAX_NUM 48406
#define TABLE_SIZE 11213
#define TABLE_WIDTH 5

typedef struct {
	char word[20];
	char mean[51];
}VOCAB;

VOCAB htable[TABLE_SIZE][TABLE_WIDTH];

void init_table(void) {
	int i, j;
	for (i = 0; i < TABLE_SIZE; i++) {
		for (j = 0; j < TABLE_WIDTH; j++) {
			strcpy(htable[i][j].word, "a");
		}
	}
}

int hash_function(char* word) {
	int hashvalue = 1;
	for (int repeat = 0; repeat < 3; repeat++) {
		for (int i = 0; i < strlen(word); i++) {
			hashvalue = hashvalue * word[i] + 311;
			if (hashvalue > TABLE_SIZE)	hashvalue = hashvalue % TABLE_SIZE;
		}
	}
	return hashvalue;
}


int main(void) {
	FILE* fp;
	char str[100];
	int ind = 0;
	VOCAB temp;
	int hashindex;
	int f;

	char tmp[20];
	int findhash;
	int t;
	
	init_table();

	fp = fopen("randdict.txt", "r");

	while (1) {
		fgets(str, 100, fp);
		char* ptr = strtok(str, ":");
		strcpy(temp.word, ptr);
		ptr = strtok(NULL, "\n");
		strcpy(temp.mean, ptr);

		hashindex = hash_function(temp.word);

		for (f = 0; f < TABLE_WIDTH; f++) {
			if (strcmp(htable[hashindex][f].word, "a") == 0) {
				strcpy(htable[hashindex][f].word, temp.word);
				strcpy(htable[hashindex][f].mean, temp.mean);
				//printf("%d %s %d %d\n", ind, temp.word, hashindex, f);
				break;
			}
		}
		if (f >= TABLE_WIDTH) {
			while (1) {
				hashindex++;
				for (f = 0; f < TABLE_WIDTH; f++) {
					if (strcmp(htable[hashindex][f].word, "a") == 0) {
						strcpy(htable[hashindex][f].word, temp.word);
						strcpy(htable[hashindex][f].mean, temp.mean);
						//printf("%d %s %s %d %d\n", ind, temp.word, htable[hashindex][f].mean, hashindex, f);
						break;
					}
				} break;
			}
		}

		ind++;
		if (ind == MAX_NUM) break;
	}

	fclose(fp);

	while (1) {
		int findcount = 1;
		printf(">>");
		scanf("%s", &tmp);
		strcat(tmp, " ");
		
		findhash = hash_function(tmp);
		for (t = 0; t < TABLE_WIDTH; t++) {
			if (strcmp(htable[findhash][t].word, tmp) == 0) {
				printf("%s (%d회 검색)\n", htable[findhash][t].mean, findcount);
				break;
			}
			else {
				findcount+=1;
			}
		}
		if (t >= TABLE_WIDTH) {
			while (1) {
				findhash++;
				for (t = 0; t < TABLE_WIDTH; t++) {
					if (strcmp(htable[findhash][t].word, tmp) == 0) {
						printf("%s (%d회 검색)\n", htable[findhash][t].mean, findcount);
						break;
					}
					else {
						findcount+=1;
					}
				}break;
			}
		}
	}
}
