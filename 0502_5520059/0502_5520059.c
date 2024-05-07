#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_queue_size 100
#define max_stack_size 100
#define max_size 100 

typedef int element;

typedef struct {
	element data[max_queue_size];
	int front, rear;
}queuetype;

typedef struct {
	int data[max_stack_size];
	int top;
}stacktype;

/*queue*/

//error
void error(char* message) {
	fprintf(stderr, "%s", message);
	return -1;
}

// is_full
int is_full_queue(queuetype* q) {
	return (q->front == ((q->rear + 1) % max_queue_size));
}

//is_empty
int is_empty_queue(queuetype* q) {
	return (q->front == q->rear);
}

//초기화
void init_queue(queuetype* q) {
	q->front = q->rear = 0;
}


//enqrueue
void enqueue(queuetype* q, element item) {
	if (is_full_queue(q)) {
		error("큐가 포화상태입니다.\n\n");
	}
	else {
		if (!ispunct(item) && !isspace(item)) {  // 특수문자나 공백이 아니면 큐에 저장
			q->rear = (q->rear + 1) % max_queue_size;
			q->data[q->rear] = tolower(item); //대문자 소문자로 변환
		}
	}
}



//dequeue
element dequeue(queuetype* q) {
	if (is_empty_queue(q)) {
		error("큐가 비어있습니다.\n\n");
	}
	else {
		q->front = (q->front + 1) % max_queue_size;
		return (q->data[q->front]);
	}
}

//print_queue
void print_queue(queuetype* q) {
	int i;
	for (i = (q->front + 1) % max_queue_size; i != q->rear; i = (i + 1) % max_queue_size) {
		printf("%c ", q->data[i]);
	}
	printf("%c\n", q->data[i]);
}

/*stack*/

//스택초기화
void init_stack(stacktype* s) {
	s->top = -1;
}

//is_empty
int is_empty_stack(stacktype* s) {
	return (s->top == -1);
}

//is_full
int is_full_stack(stacktype* s) {
	return (s->top == (max_stack_size - 1));
}


//push
void push(stacktype* s, element item) {
	if (is_full_stack(s)) {
		fprintf(stderr, "stack is full\n");
		return;
	}
	else if (!isspace(item) && !ispunct(item)) {  // 공백이 아니거나 특수문자가 아니면 stack에 push하기 
		s->data[++(s->top)] = tolower(item); // 대문자 소문자로 변환
	}
}


//pop
element pop(stacktype* s) {
	if (is_empty_stack(s)) {
		fprintf(stderr, "stack is empty\n");
		return  -1;
	}
	else {
		return s->data[(s->top)--];
	}
}



//peek
element peek(stacktype* s) {
	if (is_empty_stack(s)) {
		fprintf(stderr, "stack is empty\n");
		return -1;
	}
	else {
		return s->data[s->top];
	}
}

print_stack(stacktype* s) {

	int i;

	for (i = 0; i <= s->top; i++) {
		printf("%c ", s->data[i]);
	}
	//printf("\n%c ", s->data[0]); // data[0] 자리 뭐 들어가있나 확인하는거
}

int main() {

	queuetype queue;
	char de_q;

	stacktype stack;
	char de_s;

	int choice; //메뉴 입력
	char str[max_queue_size]; // 회문 입력 

	while (1) {
		printf("1. 회문 입력\n");
		printf("2. 회문 검사\n");
		printf("3. 종료\n");
		printf("메뉴 선택\n");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice) {
		case 1:
			printf("회문을 입력하세요: ");
			scanf("%[^\n]s", &str);  // 문자에 공백 포함
			break;

		case 2:
			//stack
			init_stack(&stack);
			for (int i = 0; str[i] != '\0'; i++) {  //입력받은 문자열 stack에 넣기 
				//special_chars(&stack, str); 
				push(&stack, str[i]);
			}
			de_s = pop(&stack); // pop되는 요소

			//queue
			init_queue(&queue);
			for (int i = 0; str[i] != '\0'; i++) {   // 입력받은 문자열 queue에 넣기
				enqueue(&queue, str[i]);
			}
			de_q = dequeue(&queue); // queue되는 요소

			//조건문으로 회문 가리기 
			if (de_q == de_s) {
				printf("회문입니다.\n");
			}
			else {
				printf("회문이 아닙니다.\n");
			}
			break;

		case 3:
			exit(0);
		default:
			printf("잘못된 메뉴 선택\n");
			break;
		}
	}

	return 0;
}
