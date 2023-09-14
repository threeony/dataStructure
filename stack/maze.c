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


//STACK 관련 함수
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
DATA Pop(STACK* stack) {    //스택이 비어있을 때 구조체를 반환하지 않기 위해, Pop을 호출하기 전 isEmpty 호출 필요
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


    // maze를 채운다. 
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i % 2 == 1 && j % 2 == 1) {
                if (mazeorg[i][j + 1] == ' ') {				//오른쪽으로 갈 수 있는 경우 
                    if (mazeorg[i + 1][j] == ' ') {			//아래로 갈 수 있는 경우 
                        *(maze + i * (width + 1) + j) = 'd';
                    }
                    else {	//오른쪽으로 갈 수 있으나, 아래로 갈 수 없는 경우 
                        *(maze + i * (width + 1) + j) = 'b';
                    }
                }
                else {									//오른쪽으로 갈 수 없는 경우 
                    if (mazeorg[i + 1][j] == ' ') {			//아래로 갈 수 있는 경우 
                        *(maze + i * (width + 1) + j) = 'c';
                    }
                    else {	//오른쪽으로 갈 수 없고, 아래로 갈 수 없는 경우 
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

    for (int i = 0; i < height; i++) {                              //초기화
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
                    x += 2; 	//오른쪽으로 이동 
                    flag = 1;	//왼쪽에서 들어옴
                }
                else if (*(maze + y * (width + 1) + x) == 'c') {
                    y += 2; 	//아래로 이동 
                    flag = 3;	//위에서 들어옴
                }
            }
            else if (flag == 1) {
                if (*(maze + y * (width + 1) + x) == 'c') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        y += 2; 	//아래로 이동 
                        flag = 3;	//위에서 들어옴
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'b') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        x += 2; 	//오른쪽으로 이동 
                        flag = 1;	//왼쪽에서 들어옴
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'a') {
                    if (*(maze + (y - 1) * (width + 1) + x) == ' ') {
                        y -= 2;	//위로 이동
                        flag = 4;	//아래에서 들어옴 
                    }
                }
            }
            else if (flag == 2) {
                if (*(maze + y * (width + 1) + x) == 'd') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            y += 2; 	//아래로 이동 
                            flag = 3;	//위에서 들어옴
                        }
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'b') {
                    if (*(maze + (y - 1) * (width + 1) + x) == ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            y -= 2;	//위로 이동
                            flag = 4;	//아래에서 들어옴 
                        }
                    }
                    else {
                        if (*(maze + y * (width + 1) + (x - 1)) == ' ') {
                            x -= 2; 	//왼쪽으로 이동 
                            flag = 2;	//오른쪽에서 들어옴
                        }
                    }
                }
            }
            else if (flag == 3) {
                if (*(maze + y * (width + 1) + x) == 'd') {
                }
                else if (*(maze + y * (width + 1) + x) == 'c') {
                    if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                        y += 2; flag = 3;       //아래로 이동
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'b') {
                    if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                        x += 2; flag = 1;       //오른쪽으로 이동
                    }
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {
                        x -= 2; flag = 2;       //왼쪽으로 이동
                    }
                }
            }
            else if (flag == 4) {
                if (*(maze + y * (width + 1) + x) == 'd') {
                    if (*(maze + (y - 1) * (width + 1) + x) != ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            x += 2; flag = 1; //오른쪽으로 이동
                        }
                    }
                }
                else if (*(maze + y * (width + 1) + x) == 'c') {
                    if (*(maze + (y - 1) * (width + 1) + x) == ' ') {
                        if (*(maze + y * (width + 1) + (x - 1)) != ' ') {
                            y -= 2; flag = 4; //위로 이동
                        }
                    }
                    else {
                        if (*(maze + y * (width + 1) + (x - 1)) == ' ') {
                            x -= 2; flag = 2;   //왼쪽으로 이동
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
    STACK* express;     //경로를 표현할 DATA를 담는 스택
    DATA datainfo;
    char* newmaze;
    int flag = 0;       //시작
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
            printf("\n도착!\n경로%d:\n", *count);
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
            Pop(express);      //맞는 길이 아닌 경우 길을 표시할 스택에서 지우고, 스택에서 새로운 좌표를 받아옴
            //printf("막힘 %d %d FLAG=%d\n", x, y, flag);
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
                printf("길 없음\n");
                break;   //길 없음
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {
                x += 2; 	//오른쪽으로 이동 
                flag = 1;	//왼쪽에서 들어옴
                //printf("%d %d\n", x, y);
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {
                y += 2; 	//아래로 이동 
                flag = 3;	//위에서 들어옴
                //printf("%d %d\n", x, y);
            }
            else if (*(maze + y * (width + 1) + x) == 'd') {		//갈림길(오, 아)
                //printf("PUSH(%d,%d)\n", x, y);//PUSH 프린트(스택에는 좌표와 방향을 저장하나, 출력결과의 간소화를 위해 좌표만 출력
                datainfo.x = x;
                datainfo.y = y;
                datainfo.dir = 'r';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);      //길을 표시하기 위해 갈림길을 저장하는 스택에도 Push해야 하는데
                                                                                            //PUSH함수 안에서 프린트 할 경우 중복 프린트 되어 함수 밖에서 프린트
                datainfo.dir = 'd';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                whenPOP(datainfo, stack, express, &x, &y, &flag);
                //printf("%d %d %c\n", x, y, datainfo.dir);
            }
        }
        else if (flag == 1) {        //왼쪽에서 들어온 경우 -> 오른쪽, 아래, 위 고려
            if (*(maze + y * (width + 1) + x) == 'd') {				//갈림길(오, 아) 
                //printf("PUSH(%d,%d)\n", x, y);
                datainfo.x = x;
                datainfo.y = y;
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//위쪽 길이 있는 경우 -> 갈림길(오, 아, 위) 
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
                //printf("FLAG: 1 갈림길 오/아 or 오/아/위 %d %d %c\n", x, y, datainfo.dir);
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//갈림길(아, 위) 
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
                    //printf("FLAG: 1 갈림길 아/위 %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    y += 2; 	//아래로 이동 
                    flag = 3;	//위에서 들어옴
                    //printf("FLAG: 1 아래로 이동 %d %d\n", x, y);
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//갈림길(오, 위) 
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
                    //printf("FLAG: 1 갈림길 오/위 %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    x += 2; 	//오른쪽으로 이동 
                    flag = 1;	//왼쪽에서 들어옴
                    //printf("FALG: 1 오른쪽으로 이동 %d %d\n", x, y);
                }
            }
            else {
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {		//위로 이동 가능 
                    y -= 2;	//위로 이동
                    flag = 4;	//아래에서 들어옴 
                    //printf("FLAG: 1 위로 이동 %d %d\n", x, y);
                }
                else {          //막힘
                    Pop(express);      //맞는 길이 아닌 경우 길을 표시할 스택에서 지우고, 스택에서 새로운 좌표를 받아옴
                    if (isEmpty(stack) != 1) {
                        //printf("막힘 %d %d %c\n", x, y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("POP(%d,%d)\n", datainfo.x, datainfo.y);         //길이 없을 때 스택의 좌표로 돌아가기 위해 POP, POP정보 출력
                    }
                    else {
                        break;
                    }
                }
            }
        }
        else if (flag == 2) {                                                //오른쪽에서 들어왔을 때
            if (*(maze + y * (width + 1) + x) == 'd') {                  //아래로 이동 가능
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {        //위로 이동 가능한 경우
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;                                     //갈림길(아, 위)
                    datainfo.y = y;
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        datainfo.dir = 'l';                               //갈림길(아, 왼, 위)
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
                    //printf("FLAG: 2 갈림길 아/왼 or 아/왼/위 %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;                                   //갈림길(아, 왼)
                        datainfo.y = y;
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'd';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("FLAG: 2 갈림길 아/왼 %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        y += 2; 	//아래로 이동 
                        flag = 3;	//위에서 들어옴
                        //printf("FLAG: 2 아래로 이동 %d %d\n", x, y);
                    }
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {           //아래로 이동 불가
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {      //위로 이동 가능한 경우
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;
                        datainfo.y = y;
                        datainfo.dir = 'u';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag); //갈림길(왼, 위)
                        //printf("FLAG: 2 갈림길 왼/위 %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        y -= 2;	//위로 이동
                        flag = 4;	//아래에서 들어옴 
                        //printf("FLAG: %d 위로 이동 %d %d\n", flag, x, y);
                    }
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        x -= 2; 	//왼쪽으로 이동 
                        flag = 2;	//오른쪽에서 들어옴
                        //printf("FLAG: 2 왼쪽으로 이동 %d %d\n", x, y);
                    }
                    else {//막힘    express에서 pop하고, stack에서 pop해서 express에 push, 정보 저장해서 좌표 지정+이동
                        Pop(express);      //맞는 길이 아닌 경우 길을 표시할 스택에서 지우고, 스택에서 새로운 좌표를 받아옴
                        if (isEmpty(stack) != 1) {
                            //printf("막힘 %d %d %c\n", x, y, datainfo.dir);
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
            if (*(maze + y * (width + 1) + x) == 'd') {//갈림길(오른, 아래)
                //printf("PUSH(%d,%d)\n", x, y);
                datainfo.x = x;
                datainfo.y = y;
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                    datainfo.dir = 'l';
                    Push(stack, datainfo);       //갈림길(오른, 아래, 왼)
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                }
                datainfo.dir = 'r';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                datainfo.dir = 'd';
                Push(stack, datainfo);
                printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                whenPOP(datainfo, stack, express, &x, &y, &flag);
                //printf("FLAG: 3 갈림길 오/아 or 오/아/왼 %d %d %c\n", x, y, datainfo.dir);
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {        //오x 아래o
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {       //갈림길(아래, 왼)
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
                    //printf("FLAG: 3 갈림길 아/왼 %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    y += 2; flag = 3;       //아래로 이동
                    //printf("FLAG: 3 아래로 이동 %d %d\n", x, y);
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'b') {            //아래x 오른쪽o
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;                                   //갈림길(오른, 왼)
                    datainfo.y = y;
                    datainfo.dir = 'l';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'r';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 3 갈림길 오/왼 %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    x += 2; flag = 1;       //오른쪽으로 이동
                    //printf("FLAG: 3 오른쪽으로 이동 %d %d\n", x, y);
                }
            }
            else {                                                      //아래, 오른 둘 다 x
                if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                    x -= 2; flag = 2;       //왼쪽으로 이동
                    //printf("FLAG: 3 왼쪽으로 이동 %d %d\n", x, y);
                }
                else {                  //막힘
                    Pop(express);      //맞는 길이 아닌 경우 길을 표시할 스택에서 지우고, 스택에서 새로운 좌표를 받아옴
                    if (isEmpty(stack) != 1) {
                        //printf("막힘 %d %d %c\n", x, y, datainfo.dir);
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
            if (*(maze + y * (width + 1) + x) == 'd') {                  //오른쪽로 이동 가능한 경우
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {        //위로 이동 가능한 경우
                    //printf("PUSH(%d,%d)\n", x, y);
                    datainfo.x = x;                                     //갈림길(오, 위)
                    datainfo.y = y;
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        datainfo.dir = 'l';
                        Push(stack, datainfo);                           //갈림길(오, 왼, 위)
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    }
                    datainfo.dir = 'u';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    datainfo.dir = 'r';
                    Push(stack, datainfo);
                    printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                    whenPOP(datainfo, stack, express, &x, &y, &flag);
                    //printf("FLAG: 4 갈림길 아/위 or 아/위/왼 %d %d %c\n", x, y, datainfo.dir);
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;
                        datainfo.y = y;                                   //갈림길(오, 왼)
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'r';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);
                        //printf("FLAG: 4 갈림길 아/왼 %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        x+=2; flag = 1; //오른쪽으로 이동
                        //printf("FLAG: 4 아래로 이동 %d %d\n", x, y);
                    }
                }
            }
            else if (*(maze + y * (width + 1) + x) == 'c') {              //오른쪽x
                if (*(maze + (y - 1) * (width + 1) + x) == ' ') {      //위로 이동 가능한 경우
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        //printf("PUSH(%d,%d)\n", x, y);
                        datainfo.x = x;
                        datainfo.y = y;
                        datainfo.dir = 'u';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        datainfo.dir = 'l';
                        Push(stack, datainfo);
                        printf("PUSH(%d,%d) DIR: %c\n", datainfo.x, datainfo.y, datainfo.dir);
                        whenPOP(datainfo, stack, express, &x, &y, &flag);        //갈림길(왼, 위)
                        //printf("FLAG: 4 갈림길 위/왼 %d %d %c\n", x, y, datainfo.dir);
                    }
                    else {
                        y -= 2; flag = 4; //위로 이동
                       //printf("FLAG: 4 위로 이동 %d %d\n", x, y);
                    }
                }
                else {
                    if (*(maze + y * (width + 1) + (x - 1)) == ' ') {      //왼쪽으로 이동 가능한 경우
                        x -= 2; flag = 2;   //왼쪽으로 이동
                        //printf("FLAG: 4 왼쪽으로 이동 %d %d\n", x, y);
                    }
                    else {//막힘
                        Pop(express);      //맞는 길이 아닌 경우 길을 표시할 스택에서 지우고, 스택에서 새로운 좌표를 받아옴
                        if (isEmpty(stack) != 1) {
                            //printf("막힘 %d %d %c\n", x, y, datainfo.dir);
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

    printf("\n발견한 길의 수: %d\n", *count);

    free(stack);
    free(newmaze);      //함수 반환에서 문제가 생기는 듯 함

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
    //printf("\n발견한 길의 수: %d\n", count);

    /*for (int i = 0; i < express->top; i++) {
        printf("%d %d %c\n", express->info[i].x, express->info[i].y, express->info[i].dir);
    }*/


    free(maze);
    free(express);

    return 0;
}