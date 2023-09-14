#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000


typedef struct {
    int x;
    int y;
    char dir;
}DATA;

typedef struct {
    DATA info[MAX];
    int top;
}STACK;


//STACK ���� �Լ�
STACK* Create(void) {
    STACK* temp;

    temp = (STACK*)malloc(sizeof(STACK));
    temp->top = 0;
    return temp;
}
int isEmpty(STACK* stack) {
    if (stack->top == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
int isFull(STACK* stack) {
    if (stack->top == MAX) {
        return 1;
    }
    else {
        return 0;
    }
}
void Push(STACK* stack, DATA data) {
    if (isFull(stack) == 1) {
        return;
    }
    stack->info[stack->top++] = data;
    return;
}
DATA Pop(STACK* stack) {    //������ ������� �� ����ü�� ��ȯ���� �ʱ� ����, Pop�� ȣ���ϱ� �� isEmpty ȣ�� �ʿ�
    return stack->info[--stack->top];
}
int indexOf(DATA datainfo, STACK* express) {
    if (isEmpty(express) == 1)
        return -1;

    for (int i = express->top - 1; i >= 0; i--) {
        if (datainfo.x == express->info[i].x) {
            if (datainfo.y == express->info[i].y) {
                return i;
            }
        }
    }

    return -1;
}

char* read_maze(char* str, int* mwidth, int* mheight)
{
    char mazeorg[30][100];
    char buffer[100];
    char* maze;
    char* ret;
    int index;
    int i, j;
    int width, height;


    FILE* fp = fopen(str, "r");


    index = 0;


    fscanf(fp, "%d %d\n", &width, &height);


    while (!feof(fp)) {
        ret = fgets(buffer, 100, fp);
        if (ret == 0) break;
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = 0;
        strcpy(mazeorg[index++], buffer);
    }


    fclose(fp);

    width = width * 2 + 1;
    height = height * 2 + 1;
    *mwidth = width;
    *mheight = height;


    maze = (char*)malloc((height) * (width));


    // maze�� ä���. 
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i % 2 == 1 && j % 2 == 1) {
                if (mazeorg[i][j + 1] == ' ') {				//���������� �� �� �ִ� ��� 
                    if (mazeorg[i + 1][j] == ' ') {			//�Ʒ��� �� �� �ִ� ��� 
                        *(maze + i * (width + 1) + j) = 'd';
                    }
                    else {	//���������� �� �� ������, �Ʒ��� �� �� ���� ��� 
                        *(maze + i * (width + 1) + j) = 'b';
                    }
                }
                else {									//���������� �� �� ���� ��� 
                    if (mazeorg[i + 1][j] == ' ') {			//�Ʒ��� �� �� �ִ� ��� 
                        *(maze + i * (width + 1) + j) = 'c';
                    }
                    else {	//���������� �� �� ����, �Ʒ��� �� �� ���� ��� 
                        *(maze + i * (width + 1) + j) = 'a';
                    }
                }
            }
            else {
                *(maze + i * (width + 1) + j) = mazeorg[i][j];
            }
        }
    }

    /*for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", *(maze + i * (width + 1) + j));
        }
        printf("\n");
    }*/

    return maze;
}

void whenPOP(DATA datainfo, STACK* stack, STACK* express, int* x, int* y, int* flag) {
    int toN;
    datainfo = Pop(stack);
    printf("POP(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
    //printf("//////%d %d %c ", datainfo.x, datainfo.y, datainfo.dir); printf(": %d %d %c\n", express->info[express->top - 1].x, express->info[express->top - 1].y, express->info[express->top - 1].dir);
    toN = indexOf(datainfo, express);
    if (toN != -1) {
        while (express->top - 1 >= toN) {
            Pop(express);
        }
    }
    Push(express, datainfo);
    *x = datainfo.x;
    *y = datainfo.y;
    if (datainfo.dir == 'u') {
        *y -= 2; *flag = 4;
    }
    else if (datainfo.dir == 'd') {
        *y += 2; *flag = 3;
    }
    else if (datainfo.dir == 'l') {
        *x -= 2; *flag = 2;
    }
    else {
        *x += 2; *flag = 1;
    }
}

int draw_maze(char* maze, char* newmaze, STACK* express, int width, int height) {
    int x = 1, y = 1;
    int nextx, nexty;
    int t = 0;
    int flag=0;

    for (int i = 0; i < height; i++) {                              //�ʱ�ȭ
       for (int j = 0; j < width; j++) {
            if (i % 2 != 0 && j % 2 == 1) {
                *(newmaze + i * (width + 1) + j) = ' ';
            }
            else {
                *(newmaze + i * (width + 1) + j) = *(maze + i * (width + 1) + j);
            }
        }
    }

    while (1) {
        nextx = express->info[t].x;
        nexty = express->info[t].y;

        *(newmaze + y * (width + 1) + x) = 'o';

        if (x == width - 2 && y == height - 2) {
            break;
        }

        if (x == nextx && y == nexty) {
            if (express->info[t].dir == 'u') {
                y -= 2; flag = 4;
            }
            else if (express->info[t].dir == 'd') {
                y += 2; flag = 3;
            }
            else if (express->info[t].dir == 'l') {
                x -= 2; flag = 2;
            }
            else {
                x += 2; flag = 1;
            }
            t++;
        }
        else {
            if (flag == 0) {
                if (*(maze + y * (width + 1) + x) == 'b') {
                    x += 2; 	//���������� �̵� 
                    flag = 1;	//���ʿ��� ����
                }
                else if (*(maze + y * (width + 1) + x) == 'c') {
                    y += 2; 	//�Ʒ��� �̵� 
                    flag = 3;	//������ ����
                }
            }
            else if (flag == 1) {
                if (*(maze + y * (width + 1) + x) == 'c') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        y += 2; 	//�Ʒ��� �̵� 
                        flag = 3;	//������ ����
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'b') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        x += 2; 	//���������� �̵� 
                        flag = 1;	//���ʿ��� ����
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'a') {
                    if (*(maze + (y - 1) * (width + 1) + x) == ' ') {
                        y -= 2;	//���� �̵�
                        flag = 4;	//�Ʒ����� ���� 
                    }
                }
            }
            else if (flag == 2) {
                if (*(maze + y * (width + 1) + x) == 'd') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            y += 2; 	//�Ʒ��� �̵� 
                            flag = 3;	//������ ����
                        }
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'b') {
                    if (*(maze + (y - 1) * (width + 1) + x) == ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            y -= 2;	//���� �̵�
                            flag = 4;	//�Ʒ����� ���� 
                        }
                    }
                    else {
                        if (*(maze + y * (width + 1) + (x - 1)) == ' ') {
                            x -= 2; 	//�������� �̵� 
                            flag = 2;	//�����ʿ��� ����
                        }
                    }
                }
            }
            else if (flag == 3) {
                if (*(maze + y * (width + 1) + x) == 'd') {
                }
                else if (*(maze + y * (width + 1) + x) == 'c') {
                    if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                        y += 2; flag = 3;       //�Ʒ��� �̵�
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'b') {
                    if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                        x += 2; flag = 1;       //���������� �̵�
                    }
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {
                        x -= 2; flag = 2;       //�������� �̵�
                    }
                }
            }
            else if (flag == 4) {
                if (*(maze + y * (width + 1) + x) == 'd') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            x += 2; flag = 1; //���������� �̵�
                        }
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'c') {
                    if (*(maze + (y - 1) * (width + 1) + x) == ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            y -= 2; flag = 4; //���� �̵�
                        }
                    }
                    else {
                        if (*(maze + y * (width + 1) + (x - 1)) == ' ') {
                            x -= 2; flag = 2;   //�������� �̵�
                        }
                    }
                }
            }
        }
    }
        
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", *(newmaze + i * (width + 1) + j));
        }
        printf("\n");
    }
    printf("\n");
    
    return 1;
}

STACK* find_way(char* maze, int width, int height, int* count)
{
    STACK* stack;
    STACK* express;     //��θ� ǥ���� DATA�� ��� ����
    DATA datainfo;
    char* newmaze;
    int flag = 0;       //����
    int x = 1;
    int y = 1;
    int next;

    printf("");
    stack = Create();
    express = Create();
    newmaze = (char*)malloc((height) * (width));

    while (1) {

        if (x == width - 2 && y == height - 2) {
            (*count)++;
            printf("\n����!\n���%d:\n", *count);
            for (int i = 0; i < express->top; i++) {
                printf("%d %d %c\n", express->info[i].x, express->info[i].y, express->info[i].dir);
            }
            printf("\n");
            next = draw_maze(maze, newmaze, express, width, height);
            if (next == 1) {
                if (isEmpty(stack) != 1) {
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                }
                else {
                    break;
                }
            }
        }

        if (x == 1 && y == 1 && flag != 0) {
            Pop(express);      //�´� ���� �ƴ� ��� ���� ǥ���� ���ÿ��� �����, ���ÿ��� ���ο� ��ǥ�� �޾ƿ�
            //printf("���� %d %d FLAG=%d\n", x, y, flag);
            if (isEmpty(stack) != 1) {
                whenPOP(datainfo, stack, express, &x, &y, &flag);
                //printf("POP(%d,%d)\n", datainfo.x, datainfo.y);
            }
            else {
                break;
            }
        }

        if (flag == 0) {
            if (*(maze + y * (width + 1) + x) == 'a') {
                printf("�� ����\n");
                break;   //�� ����
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {
                x += 2; 	//���������� �̵� 
                flag = 1;	//���ʿ��� ����
                //printf("%d %d\n", x, y);
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {
                y += 2; 	//�Ʒ��� �̵� 
                flag = 3;	//������ ����
                //printf("%d %d\n", x, y);
            }
            else if (*(maze + y * (width + 1) + x) == 'd') {		//������(��, ��)
                //printf("PUSH(%d,%d)\n", x, y);//PUSH ����Ʈ(���ÿ��� ��ǥ�� ������ �����ϳ�, ��°���� ����ȭ�� ���� ��ǥ�� ���
                datainfo.x = x;
                datainfo.y = y;
                datainfo.dir = 'r';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);      //���� ǥ���ϱ� ���� �������� �����ϴ� ���ÿ��� Push�ؾ� �ϴµ�
                                                                                            //PUSH�Լ� �ȿ��� ����Ʈ �� ��� �ߺ� ����Ʈ �Ǿ� �Լ� �ۿ��� ����Ʈ
                datainfo.dir = 'd';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                whenPOP(datainfo, stack, express, &x, &y, &flag);
                //printf("%d %d %c\n", x, y, datainfo.dir);
            }
        }
        else if (flag == 1) {        //���ʿ��� ���� ��� -> ������, �Ʒ�, �� ���
            if (*(maze + y * (width + 1) + x) == 'd') {				//������(��, ��) 
                //printf("PUSH(%d,%d)\n", x, y);
                datainfo.x = x;
                datainfo.y = y;
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//���� ���� �ִ� ��� -> ������(��, ��, ��) 
                    datainfo.dir = 'u';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                }
                datainfo.dir = 'r';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                datainfo.dir = 'd';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                whenPOP(datainfo, stack, express, &x, &y, &flag);
                //printf("FLAG: 1 ������ ��/�� or ��/��/�� %d %d %c\n", x, y, datainfo.dir);
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//������(��, ��) 
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;
                    datainfo.y = y;
                    datainfo.dir = 'u';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'd';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 1 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    y += 2; 	//�Ʒ��� �̵� 
                    flag = 3;	//������ ����
                    //printf("FLAG: 1 �Ʒ��� �̵� %d %d\n", x, y);
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//������(��, ��) 
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;
                    datainfo.y = y;
                    datainfo.dir = 'u';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'r';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 1 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    x += 2; 	//���������� �̵� 
                    flag = 1;	//���ʿ��� ����
                    //printf("FALG: 1 ���������� �̵� %d %d\n", x, y);
                }
            }
            else {
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//���� �̵� ���� 
                    y -= 2;	//���� �̵�
                    flag = 4;	//�Ʒ����� ���� 
                    //printf("FLAG: 1 ���� �̵� %d %d\n", x, y);
                }
                else {          //����
                    Pop(express);      //�´� ���� �ƴ� ��� ���� ǥ���� ���ÿ��� �����, ���ÿ��� ���ο� ��ǥ�� �޾ƿ�
                    if (isEmpty(stack) != 1) {
                        //printf("���� %d %d %c\n", x, y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("POP(%d,%d)\n", datainfo.x, datainfo.y);         //���� ���� �� ������ ��ǥ�� ���ư��� ���� POP, POP���� ���
                    }
                    else {
                        break;
                    }
                }
            }
        }
        else if (flag == 2) {                                                //�����ʿ��� ������ ��
            if (*(maze + y * (width + 1) + x) == 'd') {                  //�Ʒ��� �̵� ����
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {        //���� �̵� ������ ���
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;                                     //������(��, ��)
                    datainfo.y = y;
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        datainfo.dir = 'l';                               //������(��, ��, ��)
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    }
                    datainfo.dir = 'u';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'd';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 2 ������ ��/�� or ��/��/�� %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;                                   //������(��, ��)
                        datainfo.y = y;
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'd';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("FLAG: 2 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        y += 2; 	//�Ʒ��� �̵� 
                        flag = 3;	//������ ����
                        //printf("FLAG: 2 �Ʒ��� �̵� %d %d\n", x, y);
                    }
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {           //�Ʒ��� �̵� �Ұ�
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {      //���� �̵� ������ ���
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;
                        datainfo.y = y;
                        datainfo.dir = 'u';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag); //������(��, ��)
                        //printf("FLAG: 2 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        y -= 2;	//���� �̵�
                        flag = 4;	//�Ʒ����� ���� 
                        //printf("FLAG: %d ���� �̵� %d %d\n", flag, x, y);
                    }
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        x -= 2; 	//�������� �̵� 
                        flag = 2;	//�����ʿ��� ����
                        //printf("FLAG: 2 �������� �̵� %d %d\n", x, y);
                    }
                    else {//����    express���� pop�ϰ�, stack���� pop�ؼ� express�� push, ���� �����ؼ� ��ǥ ����+�̵�
                        Pop(express);      //�´� ���� �ƴ� ��� ���� ǥ���� ���ÿ��� �����, ���ÿ��� ���ο� ��ǥ�� �޾ƿ�
                        if (isEmpty(stack) != 1) {
                            //printf("���� %d %d %c\n", x, y, datainfo.dir);
                            whenPOP(datainfo, stack, express, &x, &y, &flag);
                            //printf("POP(%d,%d)\n", datainfo.x, datainfo.y);
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
        else if (flag == 3) {
            if (*(maze + y * (width + 1) + x) == 'd') {//������(����, �Ʒ�)
                //printf("PUSH(%d,%d)\n", x, y);
                datainfo.x = x;
                datainfo.y = y;
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                    datainfo.dir = 'l';
                    Push(stack, datainfo);       //������(����, �Ʒ�, ��)
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                }
                datainfo.dir = 'r';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                datainfo.dir = 'd';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                whenPOP(datainfo, stack, express, &x, &y, &flag);
                //printf("FLAG: 3 ������ ��/�� or ��/��/�� %d %d %c\n", x, y, datainfo.dir);
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {        //��x �Ʒ�o
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {       //������(�Ʒ�, ��)
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;
                    datainfo.y = y;
                    datainfo.dir = 'l';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'd';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);        
                    //printf("FLAG: 3 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    y += 2; flag = 3;       //�Ʒ��� �̵�
                    //printf("FLAG: 3 �Ʒ��� �̵� %d %d\n", x, y);
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {            //�Ʒ�x ������o
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;                                   //������(����, ��)
                    datainfo.y = y;
                    datainfo.dir = 'l';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'r';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 3 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    x += 2; flag = 1;       //���������� �̵�
                    //printf("FLAG: 3 ���������� �̵� %d %d\n", x, y);
                }
            }
            else {                                                      //�Ʒ�, ���� �� �� x
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                    x -= 2; flag = 2;       //�������� �̵�
                    //printf("FLAG: 3 �������� �̵� %d %d\n", x, y);
                }
                else {                  //����
                    Pop(express);      //�´� ���� �ƴ� ��� ���� ǥ���� ���ÿ��� �����, ���ÿ��� ���ο� ��ǥ�� �޾ƿ�
                    if (isEmpty(stack) != 1) {
                        //printf("���� %d %d %c\n", x, y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("POP(%d,%d)\n", datainfo.x, datainfo.y);
                    }
                    else {
                        break;
                    }
                }
            }
        }
        else if (flag == 4) {
            if (*(maze + y * (width + 1) + x) == 'd') {                  //�����ʷ� �̵� ������ ���
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {        //���� �̵� ������ ���
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;                                     //������(��, ��)
                    datainfo.y = y;
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        datainfo.dir = 'l';
                        Push(stack, datainfo);                           //������(��, ��, ��)
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    }
                    datainfo.dir = 'u';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'r';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 4 ������ ��/�� or ��/��/�� %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;
                        datainfo.y = y;                                   //������(��, ��)
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'r';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("FLAG: 4 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        x+=2; flag = 1; //���������� �̵�
                        //printf("FLAG: 4 �Ʒ��� �̵� %d %d\n", x, y);
                    }
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {              //������x
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {      //���� �̵� ������ ���
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;
                        datainfo.y = y;
                        datainfo.dir = 'u';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);        //������(��, ��)
                        //printf("FLAG: 4 ������ ��/�� %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        y -= 2; flag = 4; //���� �̵�
                       //printf("FLAG: 4 ���� �̵� %d %d\n", x, y);
                    }
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //�������� �̵� ������ ���
                        x -= 2; flag = 2;   //�������� �̵�
                        //printf("FLAG: 4 �������� �̵� %d %d\n", x, y);
                    }
                    else {//����
                        Pop(express);      //�´� ���� �ƴ� ��� ���� ǥ���� ���ÿ��� �����, ���ÿ��� ���ο� ��ǥ�� �޾ƿ�
                        if (isEmpty(stack) != 1) {
                            //printf("���� %d %d %c\n", x, y, datainfo.dir);
                            whenPOP(datainfo, stack, express, &x, &y, &flag);
                            //printf("POP(%d,%d)\n", datainfo.x, datainfo.y);
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
    }

    printf("\n�߰��� ���� ��: %d\n", *count);

    free(stack);
    free(newmaze);      //�Լ� ��ȯ���� ������ ����� �� ��

    return express;
}


int main()
{
    printf("");
    char* maze;
    STACK* express;
    int width, height;
    int count = 0;
    int roadnum;

    maze = read_maze("maze3.txt", &width, &height);
    /*for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", *(maze + i * (width + 1) + j));
        }
        printf("\n");
    }*/

    express=find_way(maze, width, height, &count);
    //printf("\n�߰��� ���� ��: %d\n", count);

    /*for (int i = 0; i < express->top; i++) {
        printf("%d %d %c\n", express->info[i].x, express->info[i].y, express->info[i].dir);
    }*/


    free(maze);
    free(express);

    return 0;
}