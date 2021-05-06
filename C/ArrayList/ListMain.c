// Visual Studio 2019���� �ۼ��� �ڵ��Դϴ�.

#include <stdio.h>
#include "ArrayList.h"

int main()
{
	// ArrayList�� ���� �� �ʱ�ȭ //
	List list;
	int data;
	ListInit(&list);

	// 5���� ������ ���� //
	LInsert(&list, 5);
	LInsert(&list, 1);
	LInsert(&list, 1);
	LInsert(&list, 0);
	LInsert(&list, 8);

	// ����� �������� ��ü ��� //
	printf("���� �������� �� : %d \n", LCount(&list));

	if (LFirst(&list, &data)) // ù ��° ������ ��ȸ
	{
		printf("%d ", data);

		while (LNext(&list, &data)) // �� ��° ������ ������ ��ȸ
		{
			printf("%d ", data);
		}
	}
	puts("\n");

	LMInsert(&list, 4, 2); // ������ ���� �߰�

	// ���� 1�� Ž���Ͽ� ��� ���� //
	if (LFirst(&list, &data))
	{
		if (data == 1)
		{
			LRemove(&list);
		}

		while (LNext(&list, &data))
		{
			if (data == 1)
			{
				LRemove(&list);
			}
		}
	}

	// ���� �� ���� �������� ��ü ��� //
	printf("���� �������� ���� �� : %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
		{
			printf("%d ", data);
		}
	}
	puts("\n");

	return 1;
}