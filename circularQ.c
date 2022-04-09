/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;							//자료형 char를 element로 지정
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; 									//별명이 QueueType인 구조체 생성 구조체에는 front와 rear가 있음


QueueType *createQueue();						
int freeQueue(QueueType *cQ);					//사용이 끝난 원형 큐의 메모리를 해제하는 함수
int isEmpty(QueueType *cQ);						//원형 큐가 비어있는지 확인하는 함수
int isFull(QueueType *cQ);						//원형 큐가 가득 차있는지 확인하는 함수
void enQueue(QueueType *cQ, element item);		//원형 큐의 rear를 이동시켜 큐 안에 데이터를 저장하는 함수
void deQueue(QueueType *cQ, element* item);		//원형 큐의 front를 이동시켜 큐 안에 데이터를 삭제하는 함수
void printQ(QueueType *cQ);						//원형 큐 안에 데이터 값을 출력하는 함수
void debugQ(QueueType *cQ);						//데이터가 어느 위치에 있는지 알려주는 함수
element getElement();

int main(void)
{

	printf("[-----[Seo han bit]   [2019038043]-----]\n");

	QueueType *cQ = createQueue();												//원형 큐 만들기
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();		//사용자로부터 데이터를 입력받음
			enQueue(cQ, data);			//입력받은 데이터를 원형 큐에 저장
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);			//원형 큐 안의 데이터 삭제
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);					//원형 큐 안의 데이터들의 위치와 front, rear위치 확인
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);				//메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));				//큐에 메모리 할당
	cQ->front = 0;												//처음엔 front와 rear를 0으로 초기화
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;									
    free(cQ);
    return 1;
}

element getElement()
{
	element item;												//사용자에게 입력받을 데이터를 저장할 변수 선언
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{

    if (cQ->front == cQ->rear){									//front 값과 rear 값이 같으면 큐가 비어있다고 알려줌
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
   if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {			//원형 큐가 가득 차 있는 상태면 rear값에 1을 더해주고 MAX로 나누면 front값과 같아짐 그걸로 원형 큐가 가득차있는지 확인
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;				//rear값을 한칸 올려주면서 
		cQ->queue[cQ->rear] = item;								//rear가 가르키는 원형 큐에 받은 데이터 저장
	}
	
}
/* complete the function */
void deQueue(QueueType *cQ, element* item){
    if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;				//front를 한칸 올려주면서 front가 가르키는 원형 큐 자리의 데이터 삭제
		*item = (cQ->queue[cQ->front]);							//큐의 front에 있는 값을 item으로 빼줌 (나중에 출력할때 그 자리에 다른 값이 있어도 사실상 없다고 침)
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){											//큐의 인덱스 값이 last랑 같아질때까지 큐 데이터 출력후 같아지면 while 종료
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) 										//데이터들의 위치와 front, rear의 위치를 출력해주는 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);						//i가 front랑 같아지면 데이터에 출력 자리에 front 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);
	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  	//front, rear 위치 출력
}

