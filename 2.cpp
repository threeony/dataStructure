#include <stdio.h>
#define STACKSIZE 10

typedef struct{
	int stackArr[STACKSIZE]={0};
	int top=0;
}STACK;

//STACK ���� �Լ�
/*STACK* Create(void){
	STACK* temp;
	temp=malloc(sizeof(STACK));
	temp->top=0;
	return temp;
}*/
int isEmpty(STACK stack){
	if(stack.top==0)
		return 1;
	else
		return 0;
} 
int isFull(STACK stack){
	if(stack.top==STACKSIZE)
		return 1;
	else
		return 0;
}
void Push(STACK* stack, int data){
	if(isFull(*stack)==1)
		return;
	stack->stackArr[stack->top++]=data;
	//printf("STACK[top]: %d TOP: %d\n", stack->stackArr[stack->top], stack->top);
	return;
}
int Pop(STACK* stack){
	if(isEmpty(*stack)==1)
		return -1;
	return stack->stackArr[--stack->top];
}
int indexOf(int find, STACK stack){
	if(isEmpty(stack)==1)
		return -1;
		
	for(int i=stack.top-1; i>=0; i--){
		if(stack.stackArr[i]==find)
			return i;
	}
	
	return -1;
}

//main ���� �Լ�
int enter(int* standby){
	char temp[STACKSIZE];
	int index=0;
	
	gets(temp);
	
	while(1){
		if(temp[index]=='\0')
			break;
		
		standby[index]=temp[index]-'0';
		index++;
	}
	
	return index;
}

void twoStack(int* standby, int n){		//����ڰ� ������ �� �� ����� ��� 
	STACK stack1, stack2;
	int order;					//in�� ���� 
	int time=0;					//Ƚ���� ���� ����
	int out=1;					//���� ������ ���� ��ȣ�� ����ϴ� ����
	int search1, search2;		//����1�� ����2�� ���� ������ ������ �ִ��� Ž���ϴ� ����
	int data;					//push, pop ������
	
	for(int i=0; i<n; i++){
		int index=0;
		order=standby[i];
		printf("%02d: IN(%d)\n", ++time, order);		//1. IN 
		
		if(order==out){
			printf("%02d: OUT(%d)\n", ++time, out); out++;
			//printf("out= %d\n", out);
			index=1;
		}

		while(1){
			//printf("out= %d\n", out);
			search1=indexOf(out, stack1);
			search2=indexOf(out, stack2);
			//printf("SEARCH: %d %d\n", search1, search2);
			if(search1==-1&&search2==-1)
				break;
			else{
			if(search1!=-1){
				while(stack1.top-1!=search1){		//�ش� ������ ���� ������ pop, �ٸ� ���ÿ� �ֱ� 
					data=Pop(&stack1);
					printf("%02d: POP(1)\n", ++time);
					Push(&stack2, data);
					printf("%02d: PUSH(2, %d)\n", ++time, data);
				}
					data=Pop(&stack1);		//�ش� ������ ������ out 
					printf("%02d: POP(1)\n", ++time);
					printf("%02d: OUT(%d)\n", time++, out);	out++;
			}
			else if(search2!=-1){
				while(stack2.top-1!=search2){
					data=Pop(&stack2);
						printf("%02d: POP(2)\n", ++time);
						Push(&stack1, data);
						printf("%02d: PUSH(1, %d)\n", ++time, data);
					
					}
				data=Pop(&stack2);
				printf("%02d: POP(2)\n", ++time);
				printf("%02d: OUT(%d)\n", ++time, out);	out++;
			}
			}
		}
		
		if(index==1)
			continue;
		
		//push
		int low, high, mid;		//stack1�� ������->low, stack2�� ū ��->high
		if(isEmpty(stack1)==1&&isEmpty(stack2)==1){
			low=out; high=n;
		}
		else if(isEmpty(stack1)==1&&isEmpty(stack2)==0){
			if(stack2.stackArr[stack2.top-1]<order){
				Push(&stack1, order);
				printf("%02d: PUSH(1, %d)\n", ++time, order);
				continue;
			}
			else{
				low=out; high=stack2.stackArr[stack2.top-1];
			}
		}
		else if(isEmpty(stack1)==0&&isEmpty(stack2)==1){
			if(stack1.stackArr[stack1.top-1]<order){
				Push(&stack2, order);
				printf("%02d: PUSH(2, %d)\n", ++time, order);
				continue;
			}
			else{
				low=stack1.stackArr[stack1.top-1]; high=n;
			}
		}
		else{
			low=stack1.stackArr[stack1.top-1];
			high=stack2.stackArr[stack2.top-1];
		}
		mid=(low+high)/2;
		//printf("  low: %d high: %d \n", low, high);
		if(order<=mid){
			Push(&stack1, order);
			printf("%02d: PUSH(1, %d)\n", ++time, order);
		}
		else{
			Push(&stack2, order);
			printf("%02d: PUSH(2, %d)\n", ++time, order);
		}
	}
	printf("����(�� %dȸ)", time);
}

void threeStack(int* standby, int n){		//����ڰ� ������ �� �� ����� ��� 
	STACK stack1, stack2, stack3;
	int order;					//in�� ���� 
	int time=0;					//Ƚ���� ���� ����
	int out=1;					//���� ������ ���� ��ȣ�� ����ϴ� ����
	int search1, search2, search3;		//����1�� ����2�� ���� ������ ������ �ִ��� Ž���ϴ� ����
	int data;					//push, pop ������
	
	for(int i=0; i<n; i++){
		int index=0;
		order=standby[i];
		printf("%02d: IN(%d)\n", ++time, order);		//1. IN 
		
		if(order==out){
			printf("%02d: OUT(%d)\n", ++time, out); out++;
			//printf("out= %d\n", out);
			index=1;
		}

		while(1){
			//printf("out= %d\n", out);
			search1=indexOf(out, stack1);
			search2=indexOf(out, stack2);
			search3=indexOf(out, stack3);
			//printf("SEARCH: %d %d\n", search1, search2);
			if(search1==-1&&search2==-1&&search3==-1)
				break;
			else{
			if(search1!=-1){
				while(stack1.top-1!=search1){		//�ش� ������ ���� ������ pop, �ٸ� ���ÿ� �ֱ� 
					data=Pop(&stack1);
					printf("%02d: POP(1)\n", ++time);
					Push(&stack2, data);
					printf("%02d: PUSH(2, %d)\n", ++time, data);
				}
					data=Pop(&stack1);		//�ش� ������ ������ out 
					printf("%02d: POP(1)\n", ++time);
					printf("%02d: OUT(%d)\n", time++, out);	out++;
			}
			else if(search2!=-1){
				while(stack2.top-1!=search2){
					data=Pop(&stack2);
						printf("%02d: POP(2)\n", ++time);
						if(data<n/2){
							Push(&stack1, data);
							printf("%02d: PUSH(1, %d)\n", ++time, data);
						}
						else{
							Push(&stack3, data);
							printf("%02d: PUSH(3, %d)\n", ++time, data);
						}
					}
				data=Pop(&stack2);
				printf("%02d: POP(2)\n", ++time);
				printf("%02d: OUT(%d)\n", ++time, out);	out++;
			}
			else if(search3!=-1){
				while(stack3.top-1!=search3){
						data=Pop(&stack3);
						printf("%02d: POP(3)\n", ++time);
						if(isEmpty(stack1)==1){
							Push(&stack1, data);
							printf("%02d: PUSH(1, %d)\n", ++time, data);
						}
						else{
							Push(&stack2, data);
							printf("%02d: PUSH(2, %d)\n", ++time, data);
						}
					}
				data=Pop(&stack3);
				printf("%02d: POP(3)\n", ++time);
				printf("%02d: OUT(%d)\n", ++time, out);	out++;
			}
			}
		}
		
		if(index==1)			//out�� ������ push���� �ʱ� ���� 
			continue;
		
		//push
		int low, mid, high;		//stack1�� ������->low, stack2�� ū ��->high 
		//printf("STACK1EMPTY: %d STACK2EMPTY: %d\n", ise1, ise2);
		if(isEmpty(stack1)==1&&isEmpty(stack2)==1){
			low=out; high=n;
		}
		else if(isEmpty(stack1)==1&&isEmpty(stack2)==0){
			if(stack2.stackArr[stack2.top-1]<order){
				Push(&stack1, order);
				printf("%02d: PUSH(1, %d)\n", ++time, order);
				continue;
			}
			else{
				low=out; high=stack2.stackArr[stack2.top-1];
			}
		}
		else if(isEmpty(stack1)==0&&isEmpty(stack2)==1){
			if(stack1.stackArr[stack1.top-1]<order){
				Push(&stack2, order);
				printf("%02d: PUSH(2, %d)\n", ++time, order);
				continue;
			}
			else{
				low=stack1.stackArr[stack1.top-1]; high=n;
			}
		}
		else{
			low=stack1.stackArr[stack1.top-1];
			high=stack2.stackArr[stack2.top-1];
			//printf("high: %d low: %d\n", high, low);
			if(high<order){
				if(isEmpty(stack1)==1){
					Push(&stack1, order);
				printf("%02d: PUSH(1, %d)\n", ++time, order);
				continue;
				}
				else if(isEmpty(stack2)==1){
					Push(&stack2, order);
				printf("%02d: PUSH(2, %d)\n", ++time, order);
				continue;
				}
				else{
					Push(&stack3, order);
					printf("%02d: PUSH(3, %d)\n", ++time, order);
					continue;
				}
			}
		}
		mid=(low+high)/2;
		//printf("  low: %d high: %d \n", low, high);
		if(order<mid){
			Push(&stack1, order);
			printf("%02d: PUSH(1, %d)\n", ++time, order);
		}
		else if(order>mid){
			Push(&stack2, order);
			printf("%02d: PUSH(2, %d)\n", ++time, order);
		}
		else{
			Push(&stack3, order);
			printf("%02d: PUSH(3, %d)\n", ++time, order);
		}
	}
	printf("����(�� %dȸ)", time);
}

int main(void){
	int stackNum;
	int standby[STACKSIZE];
	int n;
	
	printf("������ ����: ");
	scanf("%d", &stackNum);
	getchar();		//enter�� ������ ����
	printf("���� ��ȣ �Է�: ");
	n=enter(standby);
	if(stackNum==2){
		twoStack(standby, n);
	}
	else if(stackNum==3){
		threeStack(standby, n);
	}
}
