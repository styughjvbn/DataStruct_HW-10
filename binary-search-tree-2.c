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

void recursiveInorder(Node* ptr)//��������� ������ȸ
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)//�ݺ����� �̿��Ͽ� ������ȸ
{
	while(1){//��� �ݺ��Ѵ�.
		for(;node;node=node->left)//����� ���� �ڽĳ�带 ���ÿ� Ǫ���ϸ� ���� �ڽĳ�尡 ���� ������ ����.
			push(node);
		node=pop();//���� �ڽĳ�尡 ���� ��带 ������ �� ��带 ������.
		if(!node)break;//���� ��尡 ���ٸ� ��� ��ȸ�� �������̹Ƿ� �ݺ����� ������ �Լ��� �����Ѵ�.
		printf(" [%d] ", node->key);//������ȸ�̹Ƿ� ���� ����� Ű���� ����Ѵ�.
		node = node->right;//���� ����� ������ �ڽĳ����� �ٽ� ���� �ݺ����� �����Ѵ�.
	}
}

void levelOrder(Node* ptr)
{
	if (!ptr) return;//Ʈ���� ����ٸ� �Լ��� �����Ѵ�.
	enQueue(ptr);//��Ʈ��带 ��ť�Ѵ�.
	while(1){//�ݺ����� �����Ѵ�.
		ptr=deQueue();//ť���� �Ѱ��� ��带 ����.
		if(ptr){//ť���� �� ��尡 �����Ѵٸ�
			printf("[ %d ]",ptr->key);//���� ��ȸ����̹Ƿ� �켱������ ����� Ű���� ����Ѵ�.
			if(ptr->left)//�A ����� ���� �ڽĳ�尡 �����Ѵٸ�
				enQueue(ptr->left);//���� �ڽĳ�带 ��ť�Ѵ�.
			if(ptr->right)//�� ����� ������ �ڽĳ�尡 �����Ѵٸ�
				enQueue(ptr->right);//������ �ڽĳ�带 ��ť�Ѵ�.
		}//ť���� �� ��尡 ���������ʴ´ٸ� Ʈ���� ��� ��带 ����� ���̱� ������ �ݺ����� ���߰� �Լ��� �����Ѵ�.
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
	if(ptr) {//������ȸ������� �����Ѵ�.
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)//�ص����� �ص� ��带 �����ϰ� �Լ��� �����Ѵ�.
	{
		free(head);
		return 1;
	}

	Node* p = head->left;//��Ʈ������ �����Ѵ�.

	freeNode(p);//��Ʈ������ �����Ѵ�.

	free(head);//���������� �ص��带 �����Ѵ�.
	return 1;
}

Node* pop(){
	if(top<=-1)//������ ����ٸ� NULL����
		return NULL;
	else//�ƴ϶�� ������ top ����
		return stack[top--];
}

void push(Node* aNode)
{
	if(top+1>=MAX_STACK_SIZE)//������ ��á�ٸ�
		printf("������ ��á���ϴ�\n");//�ȳ��޽������
	else//�ƴ϶�� top�� ����
		stack[++top]=aNode;
}

Node* deQueue()
{
	if(front==rear)//ť�� ����ٸ�
		return NULL;//NULL ����
	else//�ƴ϶�� front ����
		return queue[++front];
}

void enQueue(Node* aNode)
{
	if(rear+1>=MAX_QUEUE_SIZE)//ť�� ��á�ٸ�
		printf("ť�� ��á���ϴ�\n");//�ȳ��޽������
	else//�ƴ϶�� rear�� ����
		queue[++rear]=aNode;
}
