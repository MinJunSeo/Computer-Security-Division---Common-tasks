// Visual Studio 2019���� �ۼ��� �ڵ��Դϴ�.

#ifndef __AL_GRAPH_H__
#define __AL_GRAPH_H__

#include "CLinkedList.h"
// ���ο� edge�� ���� �߰��Ǳ� ������ ���� ���� ����Ʈ�� ����ϸ� �۾��� ��������.

enum { A, B, C, D, E, F, G, H, I, J }; // �׷����� �ش� �ε����� ���ڷ� ����ϱ� ���� ����

typedef int Ldata;

typedef struct _ual
{
	int numV; // ������ ����
	int numE; // ������ ����
	List* adjList; // ���� ����Ʈ
	int* infovisit; // �湮 ���
} ALGraph;

typedef ALGraph Graph;

void GraphInit(Graph* pg, int nv); // �׷��� �ʱ�ȭ
void GraphDestroy(Graph* pg); // �׷��� �ı�
void AddEdge(Graph* pg, Ldata fromV, Ldata toV); // ���ο� ���� �߰�

#endif