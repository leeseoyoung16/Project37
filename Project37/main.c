#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_QUEUE 1000
typedef int element;
typedef struct {
	element data[MAX_QUEUE];
	int front, rear;
}DequeType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_deque(DequeType* q) {
	q->front = q->rear = 0;
}
int is_empty(DequeType* q) {
	return (q->front == q->rear);
}
int is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_QUEUE == q->front);
}
//void deque_print(DequeType* q) {
//	printf("DEQUE (front = %d rear = %d) = ", q ->front, q ->rear);
//	if (!is_empty(q)) {
//		int i = q->front;
//		do {
//			i = (i + 1) % (MAX_QUEUE);
//			printf("%d | ", q->data[i]);
//			if (i == q->rear)
//				break;
//		} while (i != q->front);
//	}
//	printf("\n");
//}

// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE;
	return q->data[q->front];
}

element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE) % MAX_QUEUE;

}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE) % MAX_QUEUE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");

	return q->data[q->rear];
}

int palindrome_check(DequeType* q) {
	int count = 0;

	while (!is_empty(q)) {
		element front = get_front(q);
		element rear = get_rear(q);

		if (front != rear) {
			count += 1;
		}

		delete_front(q);
		if (!is_empty(q)) {
			delete_rear(q);
		}
	}

	if (count > 0)
		return 0;
	else
		return 1;
}

int main() {
	char pal[MAX_QUEUE] = { 0 };
	DequeType dq;
	init_deque(&dq);


	while (1) {
		printf("Enter a string (or input 'exit') : ");
		scanf_s(" %[^\n]s", &pal, MAX_QUEUE);

		if (strcmp(pal, "exit") == 0) {
			printf("Program exit.");
			exit(1);
		}

		else {
			for (int i = 0; i < strlen(pal); i++) {
				if (isalpha(pal[i])) {
					add_rear(&dq, tolower(pal[i]));
				}
			}
			if (palindrome_check(&dq) == 1) {
				printf("%s is a palindrome.\n\n", pal);
			}
			else {
				printf("%s is not a palindrome.\n\n", pal);
			}

		}
		
		
	}
	return 0;
}

