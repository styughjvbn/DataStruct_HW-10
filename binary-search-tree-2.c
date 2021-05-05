/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;
Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;
Node* deQueue();
void enQueue(Node* aNode);

int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr)//재귀적으로 중위순회
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)//반복문을 이용하여 중위순회
{
	while(1){//계속 반복한다.
		for(;node;node=node->left)//노드의 왼쪽 자식노드를 스택에 푸쉬하며 왼쪽 자식노드가 없는 노드까지 간다.
			push(node);
		node=pop();//왼쪽 자식노드가 없는 노드를 만나면 그 노드를 빼낸다.
		if(!node)break;//빼낼 노드가 없다면 모든 순회가 끝난것이므로 반복문을 나가고 함수를 종료한다.
		printf(" [%d] ", node->key);//중위순회이므로 빼낸 노드의 키값을 출력한다.
		node = node->right;//빼낸 노드의 오른쪽 자식노드부터 다시 위의 반복문을 실행한다.
	}
}

void levelOrder(Node* ptr)
{
	if (!ptr) return;//트리가 비었다면 함수를 종료한다.
	enQueue(ptr);//루트노드를 인큐한다.
	while(1){//반복문을 실행한다.
		ptr=deQueue();//큐에서 한개의 노드를 뺀다.
		if(ptr){//큐에서 뺀 노드가 존재한다면
			printf("[ %d ]",ptr->key);//레벨 순회방식이므로 우선적으로 노드의 키값을 출력한다.
			if(ptr->left)//뺸 노드의 왼쪽 자식노드가 존재한다면
				enQueue(ptr->left);//왼쪽 자식노드를 인큐한다.
			if(ptr->right)//뺀 노드의 오른쪽 자식노드가 존재한다면
				enQueue(ptr->right);//오른쪽 자식노드를 인큐한다.
		}//큐에서 뺀 노드가 존재하지않는다면 트리의 모든 노드를 출력한 것이기 때문에 반복문을 멈추고 함수를 종료한다.
		else
			break;
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
}

void freeNode(Node* ptr)
{
	if(ptr) {//후위순회방식으로 해제한다.
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)//해드노드라면 해드 노드를 해제하고 함수를 종료한다.
	{
		free(head);
		return 1;
	}

	Node* p = head->left;//루트노드부터 해제한다.

	freeNode(p);//루트노드부터 해제한다.

	free(head);//마지막으로 해드노드를 해제한다.
	return 1;
}

Node* pop(){
	if(top<=-1)//스택이 비었다면 NULL리턴
		return NULL;
	else//아니라면 스택의 top 리턴
		return stack[top--];
}

void push(Node* aNode)
{
	if(top+1>=MAX_STACK_SIZE)//스택이 꽉찼다면
		printf("스택이 꽉찼습니다\n");//안내메시지출력
	else//아니라면 top에 저장
		stack[++top]=aNode;
}

Node* deQueue()
{
	if(front==rear)//큐가 비었다면
		return NULL;//NULL 리턴
	else//아니라면 front 리턴
		return queue[++front];
}

void enQueue(Node* aNode)
{
	if(rear+1>=MAX_QUEUE_SIZE)//큐가 꽉찼다면
		printf("큐가 꽉찼습니다\n");//안내메시지출력
	else//아니라면 rear에 저장
		queue[++rear]=aNode;
}
