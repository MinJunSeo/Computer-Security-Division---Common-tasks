// Visual Studio 2019���� �ۼ��� �ڵ��Դϴ�.

#include <stdio.h>
#include "stackInfo.h"

int main()
{
	// ���� ���� �� �ʱ�ȭ
	Stack stack;
	StackInit(&stack);

	// ������ �ֱ�
	SPush(&stack, 100);
	SPush(&stack, 200);
	SPush(&stack, 300);
	SPush(&stack, 400);
	SPush(&stack, 500);

	// ������ ������
	while (!SIsEmpty(&stack))
	{
		printf("%d ", SPop(&stack));
	}
	
	return 1;
}