#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUM 48406
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct {
	char word[20];
	char mean[51];
}VOCAB;

typedef struct TreeNode {
	VOCAB note;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

TreeNode* search(TreeNode* node, char key[], int *levelCount) {
	while (node != NULL) {
		if (strcmp(strlwr(key), strlwr(node->note.word)) == 0)
			return node;
		else if (strcmp(strlwr(key), strlwr(node->note.word)) < 0){
			node = node->lchild;
			(*levelCount)++;
		}
		else{
			node = node->rchild;
			(*levelCount)++;
		}
	}
}

TreeNode* insertNode(TreeNode** root, VOCAB key) {
	TreeNode* p, * t;
	TreeNode* n;
	t = *root;
	p = NULL;

	while (t != NULL) {
		if (strcmp(key.word, t->note.word) == 0){
			printf("NULL!! %s\n", key.word);
			return *root;
		}
		p = t;
		if (strcmp(strlwr(key.word), strlwr(t->note.word)) < 0)
			t = t->lchild;
		else
			t = t->rchild;
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return *root;
	n->note = key;
	n->lchild = n->rchild = NULL;

	if (p != NULL) {
		if (strcmp(strlwr(key.word), strlwr(p->note.word)) < 0)
			p->lchild = n;
		else
			p->rchild = n;
	}
	else
		*root = n;
	return *root;
}

void inorder(TreeNode* t, int* count) {
	if (t != NULL) {
		inorder(t->lchild, count);
		(*count)++;
		//printf("%d : %s %s\n", *count, t->note.word, t->note.mean);
		inorder(t->rchild, count);
	}
	return;
}
/*int inorder_ret(TreeNode* t) {
	static int count=0;
	if (t != NULL) {
		count=inorder_ret(t->lchild);
		count+=1;
		//printf("%d : %s %s\n", *count, t->note.word, t->note.mean);
		count=inorder_ret(t->rchild);
	}
	//printf("%d ", count);
	return count;
}*/

int get_height(TreeNode* node) {
	int height=0;
	if (node != NULL) {
		height = 1 + MAX(get_height(node->lchild), get_height(node->rchild));
	}
	//printf("%d ", height);
	return height;
}

void fin(TreeNode* t) {
	if (t != NULL) {
		fin(t->lchild);
		fin(t->rchild);
		free(t);
		return;
	}
}


int main(void) {
	FILE* fp;
	char str[100];
	int ind = 0;

	TreeNode* head = NULL;
	VOCAB temp;
	int nodeCount=0;
	int treeHeight;
	char tmp[20];
	TreeNode* result;
	int levelCount=1;

	fp = fopen("randdict.txt", "r");

	while (1) {
		fgets(str, 100, fp);
		char* ptr = strtok(str, ":");
		strcpy(temp.word, ptr);
		ptr = strtok(NULL, "\n");
		strcpy(temp.mean, ptr);
		//printf("%s %s\n", temp.word, temp.mean);
		head = insertNode(&head, temp);
		ind++;
		if (ind == MAX_NUM)
			break;
	}

	fclose(fp);

	inorder(head, &nodeCount);
	//nodeCount=inorder_ret(head);
	treeHeight=get_height(head);

	printf("사전파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n", ind);
	printf("A트리의 전체 높이는 %d입니다.", treeHeight);
	printf(" A트리의 노드 수는 %d개 입니다.\n", nodeCount);
	
	printf(">>");
	scanf("%s", &tmp);
	strcat(tmp, " ");
	result=search(head, tmp, &levelCount);
	printf("%s (레벨 %d)", result->note.mean, levelCount);

	fin(head);

	return 0;
}

