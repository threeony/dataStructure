#pragma warning(disable :4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUM 48406

typedef struct {
	char word[20];
	char mean[51];
}VOCAB;

VOCAB dict[MAX_NUM];

typedef struct ListNode{
	VOCAB note;
	struct ListNode* link;
}ListNode;

ListNode* index[8];

ListNode* insert(ListNode* head, ListNode* pre, VOCAB value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->note = value;
	if(head==NULL){
		p->link=head;
		head=p;
	}
	else{
		p->link=pre->link;
		pre->link=p;
	}
	return head;
}
ListNode* search(ListNode* head, char str[]) {
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (strcmp(str, strlwr(p->note.word))==0) {
			return p;
		}
		p = p->link;
	}
	return p;
}
ListNode* compar(ListNode* head, char str[]) {
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->link==NULL){
			return p;
		}
		else if (strcmp(str, strlwr(p->link->note.word))<0) {
			if(p->note.word[0]<'c'&&p->link->note.word[0]=='c')
				index[0]=p->link;
			else if(p->note.word[0]<'f'&&p->link->note.word[0]=='f')
				index[1]=p->link;
			else if(p->note.word[0]<'i'&&p->link->note.word[0]=='i')
				index[2]=p->link;
			else if(p->note.word[0]<'l'&&p->link->note.word[0]=='l')
				index[3]=p->link;
			else if(p->note.word[0]<'o'&&p->link->note.word[0]=='o')
				index[4]=p->link;
			else if(p->note.word[0]<'r'&&p->link->note.word[0]=='r')
				index[5]=p->link;
			else if(p->note.word[0]<'u'&&p->link->note.word[0]=='u')
				index[6]=p->link;
			else if(p->note.word[0]<'x'&&p->link->note.word[0]=='x')
				index[7]=p->link;
			return p;
		}
		p = p->link;
	}
	return p;
}
void printList(ListNode* head){
	for(ListNode* p = head; p != NULL; p = p->link)
		printf("%s:%s\n", p->note.word, p->note.mean);
}
void fin(ListNode* head){
	ListNode* p;
	ListNode* removed;
	p=head;
	for(int i=0; i<MAX_NUM; i++){
		removed=p;
		p=p->link;
		free(removed);
	}
}



int main(void) {
	FILE* fp;
	char str[100];
	int ind=0;
	
	ListNode* head=NULL;
	char tmp[20];
	char meaning[20];
	VOCAB temp;
	ListNode* before;
	ListNode* result;
	ListNode* indexstart;
	
	clock_t start, finish;
	float searchtime;
	
	fp = fopen("randdict.txt", "r");
	
	while(1){
		fgets(str, 100, fp);
		char *ptr = strtok(str, ":");
		strcpy(dict[ind].word,ptr);
		ptr = strtok(NULL, "\n");
		strcpy(dict[ind++].mean,ptr);
		if(ind==MAX_NUM){
			break;
		}
	}
	
	fclose(fp);
	
	for(int i=0; i<MAX_NUM; i++){
		strcpy(tmp,dict[i].word);
		strlwr(tmp);
		before=compar(head, tmp);
		head=insert(head, before, dict[i]);
	}
	//printList(head);
	
	for(int i=0; i<2; i++){
	printf(">>");
	scanf("%s", &tmp);
	strcat(tmp, " ");
	start = clock();
	if(tmp[0]<'c')
		indexstart=head;
	else if(tmp[0]<'f')
		indexstart=index[0];
	else if(tmp[0]<'i')
		indexstart=index[1];
	else if(tmp[0]<'l')
		indexstart=index[2];
	else if(tmp[0]<'o')
		indexstart=index[3];
	else if(tmp[0]<'r')
		indexstart=index[4];
	else if(tmp[0]<'u')
		indexstart=index[5];
	else if(tmp[0]<'x')
		indexstart=index[6];
	else
		indexstart=index[7];
	printf("%p", indexstart);
	result=search(indexstart, strlwr(tmp));
	if(result==NULL){
		printf("찾을 수 없는 단어입니다. 뜻을 추가하세요(추가하지 않으려면 공백)\n");
		getchar();
		printf(">>"); 
		gets(meaning);
		if(strcmp(meaning, " ")!=0){
			strcpy(temp.word, tmp);
			strcpy(temp.mean, meaning);
			before=compar(head, tmp);
			head=insert(head, before, temp);
			printf("%s %s 가 추가되었습니다.\n", temp.word, temp.mean);
		}
	}
	else{
		printf("%s", result->note.mean);
	}
	finish = clock();
	searchtime = (float)(finish - start) / CLOCKS_PER_SEC;
	printf("\nAFTER IMPROVEMENT SEARCHTIME: %.3f", searchtime);
	}
	
	fin(head);
}
