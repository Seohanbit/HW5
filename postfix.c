

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20


typedef enum{
	lparen = 0, 									//   ( 왼쪽 괄호
	rparen = 9,  									//   ) 오른쪽 괄호
	times = 7,  									//   * 곱셈
	divide = 6,  									//   / 나눗셈
	plus = 5,   									//   + 덧셈
	minus = 4,   									//   - 뺄셈
	operand = 1 									//   피연산자
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   				//infix expression 을 저장하는 배열
char postfixExp[MAX_EXPRESSION_SIZE];				//postfix로 변경된 문자열을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];					//postfix로 변환을 위해 필요한 스택
int evalStack[MAX_STACK_SIZE];						//계산을 위해 필요한 스택

int postfixStackTop = -1;  							//postfix의 스택의 top을 -1로 초기화
int evalStackTop = -1;	 							//eval의 스택의 top을 -1로 초기화

int evalResult = 0;	 								//계산의 결과값을 저장할 변수

void postfixpush(char x);							//postfix로 바꾸기 위해 postfix 스택에 저장하는 함수
char postfixPop();									//postfix를 만들기 위해서 스택에서 pop하는 함수
void evalPush(int x);								//postfix를 계산하기 위해서 eval 스택에 저장하는 함수
int evalPop();										//postfix를 계산하기 위해서 eval 스택에서 pop하는 함수
void getInfix();									//계산할 식을 입력받는 함수
precedence getToken(char symbol);					//입력 받은 수식으로부터 토큰을 가져오는 함수
precedence getPriority(char x);						//토큰의 우선순위를 판단하는 함수
void charCat(char* c);								//문자 하나를 postfixExp에 저장하는 함수
void toPostfix();									//infix를 postfix로 변환하기 위한 함수
void debug();										//입력받은 식과 postfix로 바뀐 식, 계산 결과, postfixstack을 출력해주는 함수
void reset();										//입력 받은 식이든 변환 된 식이든 스택이든 다 리셋 시키는 함수
void evaluation();									//postfix를 계산하는 함수

int main()
{

	printf("[-----[Seo han bit]   [2019038043]-----]\n");

	char command;

	do{
		printf("----------------------------------------------------------------\n");				//메뉴판
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix(); 				//식을 infix형식으로 입력받음
			break;
		case 'p': case 'P':
			toPostfix();				//infix 형식의 식을 postfix로 바꿈
			break;
		case 'e': case 'E':
			evaluation();				//postfix로 바뀐 식을 계산
			break;
		case 'd': case 'D':
			debug();					//모든 것을 출력
			break;
		case 'r': case 'R':
			reset();					//모든 것을 초기화
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; 					//연산자든 피 연산자든 한가지를 postfixStack의 Top을 1증가 하고 top의 위치에 저장
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)								//postfixStackTop이 -1이면 스택 안에 아무것도 없으니까 널 값 리턴
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];				//char형 변수 x에 스택에 있는 값을 빼주고 Top의 크기를 1만큼 뺌
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;							//evalStackTop을 1증가시키고 숫자를 저장
}

int evalPop()
{
    if(evalStackTop == -1)									//Top가 -1이면 스택이 비어있다는 의미
        return -1;
    else
        return evalStack[evalStackTop--];					//top에 있는 값을 리턴해주고 top - 1
}


void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);									//infixExp에 식을 입력
}	

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;								//왼쪽 괄호면 lparen 리턴
	case ')' : return rparen;								//오른쪽 괄호면 rparen 리턴
	case '+' : return plus;									// + 연산자면 plus 리턴
	case '-' : return minus;								// - 연산자면 minus 리턴
	case '/' : return divide;								// / 연산자면 divide 리턴
	case '*' : return times;								// * 연산자면 times 리턴
	default : return operand;								// 연산자가 아니면 피연산자라고 알려주는 operand 출력
	}
}

precedence getPriority(char x)
{
	return getToken(x);										//getToken 함수 리턴
}

void charCat(char* c)
{
	if (postfixExp == '\0')									//postfixExp가 NULL이면 c의 문자를 1개 복사
		strncpy(postfixExp, c, 1);
	else													//NULL이 아니면 postfixExp문자 뒤에 c의 문자를 1개 붙임
		strncat(postfixExp, c, 1);
}

void toPostfix()
{
	
	
	char *exp = infixExp; 									//infix 형식으로 입력받은 식을 *exp에 저장
	char x; 
	
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)					//*exp가 피연산자면 postfixExp에 저장
		{
			x = *exp;
        	charCat(&x);
		}
        else if(getPriority(*exp) == lparen) {				//*exp가 왼쪽 괄호면 stack에 저장

        	postfixPush(*exp);
        }
        else if(getPriority(*exp) == rparen)				//*exp가 오른쪽 괄호면
        {
        	while((x = postfixPop()) != '(') {				//왼쪽 괄호가 pop될때까지 스택에 있는 값을 pop해서 postfixExp에 저장
        		charCat(&x);
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //스택 안에 있는 연산자가 *exp에 있는 연산자보다 우선순위가 크면
            {
            	x = postfixPop();												   //x에다가 스택에 있는 연산자를 pop해서 저장
            	charCat(&x);													   //그 연산자를 postfixExp에 뒤에 붙임
            }
            postfixPush(*exp);
        }
        exp++;																	   //1차원 배열 exp를 한칸 ++
	}

    while(postfixStackTop != -1)												   //위에 식 다 했는데도 postfix 스택에 top이 -1이 아닐경우 
    {
    	x = postfixPop();														   //스택에 남은 연산자 모두 pop해서 postfixExp에 붙임
    	charCat(&x);
    }


	

}
void debug()																		//모든 것을 출력 하는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()																		//모든 것을 초기화하는 함수
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()																
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);												//postfix의 길이만큼 for문을 돌리기위해 length에 Exp길이 저장
	char symbol;
	evalStackTop = -1;																//계산을 위해 필요한 eval 스택의 top을 -1로 초기화

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];														//postfixExp[i]의 값을 symbol에 저장
		if(getToken(symbol) == operand) {											//symbol이 피연산자면 
			evalPush(symbol - '0');													//symbol - '0'하는데 왜냐하면 숫자가 아스키코드 화 되어있기 때문에 '0'을 빼줘야 값이 됨
		}
		else {
			opr2 = evalPop();														//symbol이 연산자면 opr2와 opr1에 eval 스택에 있던 값을 저장
			opr1 = evalPop();
			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;								//case 별로 값을 계산하고 난 뒤 값을 eval 스택에 저장
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop();															//계산이 다 끝난뒤 eval스택에 있는 값을 계산 결과를 저장하는 변수에 저장
}
