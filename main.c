#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
	if (is_full(s)) {
		printf("Stack full\n");
	}
	else {
		s->data[++(s->top)] = item;
	}
}

element pop(StackType* s) {
	if (is_empty(s)) {
		printf("Stack empty\n");
	}
	else {
		return s->data[(s->top)--];
	}
}

int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0'; // 입력이 피연산자이면
			push(&s, value);
		}
		else { //연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

int checkChar(char exp[]) {
	int len = strlen(exp), status = 0;
	char ch;

	for (int i = 0; i < len; i++) {
		ch = exp[i];
		if (isdigit(ch) != 0) {
			status = 1;
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			status = 1;
		}
		else {
			printf("Error: Invalid character\n");
			status = 0; return status;
		}
	}

	return status;

}

int main() {
	char exp[20];
	int result, status=0;

	do {
		printf("Enter an infix expression: ");
		scanf_s("%s", exp, 20);
		status = checkChar(exp);
	} while (status == 0);

	result = eval(exp);
	printf("Postfix expression: %s\n", exp);
	printf("Result: %d\n", result);

	system("pause");

	return 0;
}