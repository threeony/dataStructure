#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 80

typedef struct{
	char stackArr[MAXLINE];
	double stackNum[MAXLINE];
	int top=0;
}STACK;


//STACK ���� �Լ�
int isEmpty(STACK stack){
	if(stack.top==0)
		return 1;
	else
		return 0;
}
int isFull(STACK stack){
	if(stack.top==MAXLINE)
		return 1;
	else
		return 0;
}
void Push(STACK *stack, char data){
	if(isFull(*stack)==1)
		return;
	stack->stackArr[stack->top++]=data;
}
char Pop(STACK *stack){
	if(isEmpty(*stack)==1)
		return -1;
	return stack->stackArr[--stack->top];
}
void PushNum(STACK *stack, double data){
	if(isFull(*stack)==1)
		return;
	stack->stackNum[stack->top++]=data;
}
double PopNum(STACK *stack){
	if(isEmpty(*stack)==1)
		return -1;
	return stack->stackNum[--stack->top];
}

//main ���� �Լ�
int findError(char* formula, char* postfix, int* postin){
	int i=0;
	int ind=0;		//���ڰ� ���� ���� 0; �����ڰ� ���� ���� 1;
	//int bind=0;	//)�� ���;��ϴ� �����̸� 1;
	int point=0;	//�Ҽ��� ������ ���� ����
	
	while(formula[i]!='\0'){
		if(i==0){		//������ �������� ��� 
			if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/'||formula[i]==')'||formula[i]=='.'){
				return i;	//������ �� ������ ��ȯ 
			}
			else{
				ind=1;
			}
		}
		
		if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/'){
			if(ind==0){		//���ڰ� ���� ���ʿ� �����ڰ� ���� ��� 
				return i;
			}
			else{
				ind=0; point=0;	//���ڸ� ���� ���� �Ҽ��� ���� �ʱ�ȭ
				postfix[(*postin)++]=' ';
				postfix[(*postin)++]=formula[i++];
				postfix[(*postin)++]=' ';		//�յڷ� ������ ����-> ���� ���鹮�ڸ� �������� �и��ϱ� ���� 
				continue;
			}
		}
		else if(formula[i]=='('){
			/*bind=1;*/ point=0;
			if(ind==1){
				return i;	//���� �� ���� ��ȣ�� ������ ��� �������� ��ȯ 
			}
			else{
				postfix[(*postin)++]=formula[i++];
				postfix[(*postin)++]=' ';		//�յڷ� ������ ����-> ���� ���鹮�ڸ� �������� �и��ϱ� ���� 
				continue;
			} 
		}
		else if(formula[i]==')'){
			if(ind==0)
				return i;
			point=0; /*bind=0;*/ ind=1;
			postfix[(*postin)++]=' ';
			postfix[(*postin)++]=formula[i++];		//�յڷ� ������ ����-> ���� ���鹮�ڸ� �������� �и��ϱ� ���� 
			continue;
		}
		else if(formula[i]=='.'){
			point++;
			if(formula[i-1]=='+'||formula[i-1]=='-'||formula[i-1]=='*'||formula[i-1]=='/'||formula[i-1]==')'){
				return i;		//������ �ڿ� �Ҽ����� ���� ��� �������� ��ȯ 
			}
			else if(formula[i+1]=='+'||formula[i+1]=='-'||formula[i+1]=='*'||formula[i+1]=='/'||formula[i+1]==')'){
				return i+1;		//�Ҽ��� �ڿ� �ٷ� �����ڰ� ���� ��� �������� ��ȯ 
			}
			else if(point>1){
				return i;		//�Ҽ����� �� �� �̻� ���� ��� �������� ��ȯ 
			}
		}
		else{
			ind=1;
		}
		postfix[(*postin)++]=formula[i++];
	}
	
	if(ind==0||formula[i-1]=='.'){		//�ݴ� ��ȣ�� ���ų�, ������, '.'�� ������ ���������� ��ȯ 
		//printf("\nIND: %d", ind);
		return i-1;
	}
	/*else if(bind=1){
		printf("\nBRACKET: %d", bind);
		return i;
	}*/
	
	return -1;	//������ ������ -1 ��ȯ 
}
int infixTopostfix(char postfix[], char cal[]){
	STACK opt;
	int pind=0;
	int cind=0;
	int bind=0;
	char* ch;
	
	while(postfix[pind]!=NULL){
		*ch=postfix[pind++];
		//printf("%s\n", ch);
		if(strcmp(ch, " ")==0){
			continue;
		}
		else if(strcmp(ch, "+")==0||strcmp(ch, "-")==0){
			while(1){
				if(isEmpty(opt)==1||opt.stackArr[opt.top-1]=='('){
					Push(&opt, *ch);
					strcat(cal, " ");
					//printf("\nSTACK[%d]: %c\n", opt.top, opt.stackArr[opt.top-1]);
					break;
				}
				else{
					*ch=Pop(&opt);
					strcat(cal, " ");
					strcat(cal, ch);
				}
			}
		}
		else if(strcmp(ch, "*")==0||strcmp(ch, "/")==0){
			while(1){
			if(opt.stackArr[opt.top-1]=='*'||opt.stackArr[opt.top-1]=='/'){
				Pop(&opt);
				
				strcat(cal, " ");
				strcat(cal, ch);
			}
			else{
				Push(&opt, *ch);
				strcat(cal, " ");
				//printf("\nSTACK[%d]: %c\n", opt.top, opt.stackArr[opt.top-1]); 
				break;
			}
			}
		}
		else if(strcmp(ch, "(")==0){
			bind=1;
			Push(&opt, *ch);
			//printf("\nSTACK[%d]: %c\n", opt.top, opt.stackArr[opt.top-1]);
		}
		else if(strcmp(ch, ")")==0){
			bind=0;
			strcat(cal, " ");
			while(1){
				*ch=Pop(&opt);
				if(strcmp(ch, "(")==0){
					break;
				}
				strcat(cal, ch);
			}
		}
		else{
			strcat(cal, ch);
		}
	}
	
	while(isEmpty(opt)!=1){
		*ch=Pop(&opt);
		if(ch=="("){
			return 1;
		}
		strcat(cal, " ");
		strcat(cal, ch);
	}
	strcat(cal, "\0");
	
	if(bind==1){
		return 1;
	}
	return 0;
}
double eval(char cal[]){
	STACK opd;
	int cind=0;
	int nind=0;
	char num[MAXLINE];
	char ch;
	double number, n1, n2, re;
	int flag=0;
	
	while(cal[cind]!='\0'){
		ch=cal[cind++];
		if(ch==' '&&flag==0){
			number=atof(num);
			//printf("%f", number);
			for(int i=0; i<nind; i++){
				num[i]=NULL;
			}
			nind=0;
			PushNum(&opd, number);
			//printf("\nSTACK[%d]: %lf\n", opd.top-1, opd.stackNum[opd.top-1]);
		}
		else if(ch=='+'){
			flag=1;
			n2=PopNum(&opd);
			//printf("N2: %lf",n2);
			n1=PopNum(&opd);
			//printf(" N1: %lf\n",n1);
			re=n1+n2;
			PushNum(&opd, re);
		}
		else if(ch=='-'){
			flag=1;
			n2=PopNum(&opd);
			//printf("N2: %lf",n2);
			n1=PopNum(&opd);
			//printf(" N1: %lf\n",n1);
			re=n1-n2;
			PushNum(&opd, re);
		}else if(ch=='*'){
			flag=1;
			n2=PopNum(&opd);
			//printf("N2: %lf",n2);
			n1=PopNum(&opd);
			//printf(" N1: %lf\n",n1);
			re=n1*n2;
			PushNum(&opd, re);
		}else if(ch=='/'){
			flag=1;
			n2=PopNum(&opd);
			//printf("N2: %lf",n2);
			n1=PopNum(&opd);
			//printf(" N1: %lf\n",n1);
			re=n1/n2;
			PushNum(&opd, re);
		}
		else{
			num[nind++]=ch;
			flag=0;
		}
	}
	return opd.stackNum[opd.top-1];
}

int main(void){
	char formula[MAXLINE*2];
	char postfix[MAXLINE]={""};
	char calculation[MAXLINE];
	int postin=0;
	int n, bn;
	double result;
	
	printf("������ �Է��ϼ���:\n");
	gets(formula);
	
	n=findError(formula, postfix, &postin);
	/*printf("\nN: %d ",n);
	printf("POSTIN: %d\n", postin);*/
	if(n!=-1){
		for(int i=0; i<n; i++){
			printf(" ");
		}
		printf("^ �� ��ġ�� ������ �ֽ��ϴ�.");
		return 0;
	}
	/*else{
		for(int i=0; i<postin; i++){
			printf("%c", postfix[i]);
		}
	}*/
	
	printf("\n");
	bn=infixTopostfix(postfix, calculation);
	if(bn==1){
		for(int i=0; i<strlen(formula); i++){
			printf(" ");
		}
		printf("^ �� ��ġ�� ������ �ֽ��ϴ�.\n");
		return 0;
	}
	//printf("%s\n", calculation);
	
	result=eval(calculation);
	printf("= %f", result);
	
	return 0;

} 
