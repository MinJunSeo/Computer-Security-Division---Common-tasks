// Visual Studio 2019���� �ۼ��� �ڵ��Դϴ�.

#ifndef __ARRAY_LIST_H__

#define __ARRAY_LIST_H__

#define LIST_LEN 100
typedef int Ldata; // ����ü�� ���� �������� Ÿ�Կ� ���� typedef ����

typedef struct _ArrayList // �迭��� ����Ʈ�� ������ ����ü
{
	Ldata array[LIST_LEN]; // ����� �������� ��
	int numOfData; // ����� �������� ��
	int curPosition; // ������ ������ġ�� ���
} ArrayList;

typedef ArrayList List; // ArrayList��� ���� �� ���� �ٽ� �� �� �̸��� ����ȭ�Ͽ���.

void ListInit(List* plist); // ����Ʈ �ʱ�ȭ �Լ�

int LFirst(List* plist, Ldata* pdata); // ����Ʈ�� ó������ �Ǻ��ϴ� �Լ�
int LNext(List* plist, Ldata* pdata); // ������ �����Ͱ� �ִ��� Ȯ���ϴ� �Լ�

void LInsert(List* plist, Ldata data); // �����͸� �߰��ϴ� �Լ�
Ldata LRemove(List* plist); // �����͸� �����ϴ� �Լ�

int LCount(List* plist); // ����� �������� ���� ��ȯ�ϴ� �Լ�
void LMInsert(List* plist, Ldata data, int index);

#endif