#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct{
	char QArr[MAXSIZE];
	int front=0;
	int rear=0;
}QUEUE;

//QUEUE 관련 함수
int isEmpty(QUEUE *q){
	return (q->front==q->rear);
}
int isFull(QUEUE *q){
	return ((q->rear+1)%MAXSIZE==q->front);
}
char enqueue(QUEUE *q, char data){
	if(isFull(q)){
		printf("ADDQUEUE(%c) FAIL. QueueFull\n",data);
		return NULL;
	}
	q->rear=(q->rear+1)%MAXSIZE;
	q->QArr[q->rear]=data;
}
char dequeue(QUEUE *q){
	if(isEmpty(q)){
		printf("DELETEQUEUE() FAIL. QueueEmpty\n");
		return NULL;
	}
	q->front=(q->front+1)%MAXSIZE;
	return q->QArr[q->front];
}


int main(void){
	QUEUE alphabet;
	char enter[MAXSIZE];
	int eind=0;
	char flag='a';
	
	printf("시스템이 시작됩니다.\n");
	
	while(1){
		eind=0;
		printf(">>> ");
		scanf("%s",&enter);
		if(strcmp(enter,"0")==0){
			printf("QUEUE=");
			for(int i=alphabet.front+1; i<alphabet.rear+1; i++){
				printf("%c",alphabet.QArr[i]);
			}
			printf("(%d)\n",alphabet.rear-alphabet.front);
		}
		else if((strcmp(enter,"1")==1)&&(strcmp(enter,"9")==-1)){
			for(int i=0; i<atoi(enter); i++){
				flag=dequeue(&alphabet);
				if(flag==NULL)
					break;
				printf("DELETEQUEUE()=%c, F=%d R=%d\n",flag, alphabet.front, alphabet.rear);
			}
		}
		else{
			while(1){
				char temp=enter[eind++];
				if(temp==NULL)
					break;
				flag=enqueue(&alphabet, temp);
				if(flag==NULL)
					break;
				printf("(SYSTEM) ADDQUEUE(%c), F=%d R=%d\n",temp, alphabet.front, alphabet.rear);
			}
		}
		
		if(flag==NULL)
			break;
	}
}
