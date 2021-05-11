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
	int initial = 0;//초기화가 진행됐는지 확인한다.
	Node* head = NULL;

	printf("[----- [서종원] [2018038031] -----]\n");

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
			initial++;
			break;
		case 'q': case 'Q':
			if(initial)
				freeBST(head);
			break;
		case 'i': case 'I':
			if(initial){
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'd': case 'D':
			if(initial){
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'r': case 'R':
			if(initial)
				recursiveInorder(head->left);
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 't': case 'T':
			if(initial)
				iterativeInorder(head->left);
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'l': case 'L':
			if(initial)
				levelOrder(head->left);
			else
				printf("초기화를 먼저 실행해주세요\n");
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
	top=-1;//스택의 탑을 초기화한다.
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
	front = -1;//큐의 프론트와 리어를 초기화한다.
	rear = -1;
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
	Node* newNode = (Node*)malloc(sizeof(Node));//삽입될 노드이다.
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {//트리가 비어있다면 해드노드에 연결하고 함수를 종료한다.
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

int deleteNode(Node* head, int key)//노드를 삭제한다.
{
	Node* tmp = head->left;//삭제할 노드를 찾는다.
	Node* tmp_ = head;//삭제한 노드의 부모노드를 저장한다.
	Node* Rtree=NULL;//삭제할 노드의 오른쪽 서브트리에서 가장 작은 값을 가지는 노드를 저장한다.
	Node* Rtree_sub=NULL;//삭제할 노드의 오른쪽 서브트리에서 가장 작은 값을 가지는 노드가 오른쪽 서브트리를 가지고있다면 오른쪽 자식노드를 저장한다.
	Node* Rtree_parents=NULL;//삭제할 노드의 오른쪽 서브트리의 가장 작은 값을 가지는 노드의 부모노드를 저장한다.
	while (tmp) {//삭제할 노드를 찾을 때까지 반복한다.
		if (key == tmp->key)//삭제할 키값을 가지는 노드를 찾았다면
			break;//반복문을 종료한다.
		else if (key < tmp->key) {//삭제할 키값이 비교하는 노드보다 작다면
			tmp_ = tmp;//부모노드를 저장한다.
			tmp = tmp->left;//왼쪽자식노드로 이동한다.
		}
		else {//삭제할 키값이 비교하는 노드보다 크다면
			tmp_ = tmp;//부모노드를 저장한다.
			tmp = tmp->right;//오른쪽 자식노드로 이동한다.
		}
	}
	if (!tmp) {//노드를 찾지못했다면 메시지를 출력하고 함수를 종료한다.
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}
	else if (tmp->left != NULL && tmp->right != NULL) {//노드의 왼쪽, 오른쪽 자식노드가 둘다 존재할 경우 오른쪽 트리에서 가장 작은 값이랑 바꾼다.
		for(Rtree=tmp->right;Rtree->left!=NULL;Rtree=Rtree->left){//삭제할 노드의 오른쪽 서브트리에서 가장 작은 값을 가지는 노드를 찾는다.
			Rtree_parents=Rtree;
		}
		Rtree_sub=Rtree->right;/*오른쪽 서브트리에서 가장 작은 값을 가지는 노드의 왼쪽 자식노드는
		절대 존재하지 않고 오른쪽 자식노드는 존재할 수도 있다 이때, 오른쪽 자식노드가 존재한다면 오른쪽
		자식노드를 가장작은 값을 가지는 노드의 부모노드의 왼쪽 자식노드에 연결한다.*/

		Rtree->left=tmp->left;//가장 작은 값을 가지는 노드와 삭제할노드를 바꾼다.
		if(!Rtree_parents)//가장 작은 값을 가지는 노드의 부모노드가 없다면 즉, 오른쪽 서브트리에 노드가 하나밖에 없다면
			Rtree->right=NULL;//가장 작은 값을 가지는 노드의 오른쪽 자식노드를 NULL로 만든다.
		else{//아니라면 정상적으로 바꾼다.
			Rtree->right=tmp->right;
			Rtree_parents->left = Rtree_sub;//가장 작은 값을 가지는 노드의 오른쪽 자식노드와 부모노드를 연결한다.
		}
		free(tmp);//삭제할 노드를 해제한다.
		if (tmp_==head||key < tmp_->key)//삭제할 키값이 부모노드의 키값보다 작거나 부모노드가 해드노드라면
			tmp_->left=Rtree;//부모노드의 왼쪽 자식링크에 오른쪽 트리의 가장 작은 값을 가지는 노드를 연결한다.
		else//크다면
			tmp_->right=Rtree;//부모노드의 오른쪽 자식링크에 오른쪽 트리의 가장 작은 값을 가지는 노드를 연결한다.
	}
	else if(tmp->left == NULL && tmp->right == NULL){//노드가 리프노드일 경우
		if (tmp_==head||key < tmp_->key)//삭제할 키값이 부모노드의 키값보다 작거나 부모노드가 해드노드라면
			tmp_->left = NULL;//왼쪽 자식노드의 링크를 NULL로 만든다.
		else//삭제할 키값이 부모노드의 키값보다 크다면
			tmp_->right = NULL;//오른쪽 자식노드의 링크를 NULL로 만든다.
		free(tmp);//해당 키값을 가지는 노드를 삭제한다.
	}
	else{//노드에 한개의 자식노드만 존재할 경우
		if (tmp_==head||key < tmp_->key)//삭제할 키값이 부모노드의 키값보다 작거나 부모노드가 해드노드라면
			if(tmp->left==NULL)//왼쪽 자식노드가 없다면
				tmp_->left = tmp->right;//부모노드의 왼쪽링크에 삭제할 노드의 오른쪽 자식노드를 저장한다.
			else//오른쪽 자식노드가 없다면
				tmp_->left = tmp->left;//부모노드의 왼쪽링크에 삭제할 노드의 왼쪽 자식노드를 저장한다.
		else//삭제할 키값이 부모노드의 키값보다 크고
			if(tmp->left==NULL)//왼쪽 자식노드가 없다면
				tmp_->right=tmp->right;//부모노드의 오른쪽링크에 삭제할 노드의 오른쪽 자식노드를 저장한다.
			else//오른쪽 자식노드가 없다면
				tmp_->right = tmp->left;//부모노드의 오른쪽링크에 삭제할 노드의 왼쪽 자식노드를 저장한다.
		free(tmp);//해당 키값을 가지는 노드를 삭제한다.
	}
	return 0;//함수를 종료한다.
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
