#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	7
#define INF	10000	/* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

typedef struct Distaceinfo {
	int beforevertex;
	int dlength;
}Distaceinfo;

Distaceinfo distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];		/* �湮�� ���� ǥ�� */

int choose(Distaceinfo distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i].dlength < min && !found[i]) {
			min = distance[i].dlength;
			minpos = i;
		}
	return minpos;
}
void print_status(GraphType* g)
{
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i].dlength == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i].dlength);
	}
	printf("\n");
	printf("     beforevertex:");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", distance[i].beforevertex);
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}
//
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i].beforevertex = start;
		distance[i].dlength = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start].dlength = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u].dlength + g->weight[u][w] < distance[w].dlength) {
					distance[w].dlength = distance[u].dlength + g->weight[u][w];
					distance[w].beforevertex = u;
				}
	}
}
int main(void)
{
	GraphType g = { 7,
	{{ 0,   4,   8, INF, INF, INF,  10 },
	{  4,   0,   2,   5,  11, INF, INF },
	{  8,   2,   0, INF,   9,   4,   5 },
	{INF,   5, INF,   0,   7, INF, INF },
	{INF,  11,   9,   7,   0,   2,   8 },
	{INF, INF,   4, INF,   2,   0, INF },
	{ 10, INF,   5, INF,   8, INF,   0 } }
	};

	int startpoint, endpoint;
	int route[MAX_VERTICES];
	int routecount = 0;
	int before;

	printf("������? ");
	scanf("%d", &startpoint);
	printf("������? ");
	scanf("%d", &endpoint);

	shortest_path(&g, startpoint);
	route[routecount++] = endpoint;

	before = endpoint;
	while(1) {
		if (before == startpoint) break;
		route[routecount++] = distance[before].beforevertex;
		before = distance[before].beforevertex;
	}
	printf("��δ� %d ", startpoint);
	for (int p = routecount - 2; p >= 0; p--) {
		printf("- %d ", route[p]);
	}
	printf("\n�Ÿ��� %d\n", distance[endpoint].dlength);
	return 0;
}