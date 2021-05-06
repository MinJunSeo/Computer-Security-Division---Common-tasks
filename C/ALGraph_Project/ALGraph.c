// Visual Studio 2019���� �ۼ��� �ڵ��Դϴ�.

#include <stdio.h>
#include <stdlib.h> // stdlib �Լ��� ����� ���� ����
#include <string.h> // memset �Լ��� ����� ���� ����
#include "ALGraph.h"

int WhoIsPred(Ldata d1, Ldata d2)
{
	if (d1 < d2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void GraphInit(Graph* pg, int nv)
{
	int i;

	pg->adjList = (List*)malloc(sizeof(List) * nv);
	pg->numV = nv;
	pg->numE = 0;
	pg->infovisit = (Ldata*)malloc(sizeof(Ldata) * nv);

	for (i = 0; i < nv; i++) // �����Ҵ��� ���� ����Ʈ�� �ʱ�ȭ
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPred);
	}

	memset(pg->infovisit, 0, sizeof(int) * nv);
	// infovisit�� �� ������ ������ 0�� 1�� ���� ������ int Ÿ������ �ص� �������.
}

void GraphDestroy(Graph* pg)
{

}