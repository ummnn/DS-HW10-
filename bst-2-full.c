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

//노드구조체 선언
typedef struct node {
	int key;
	struct node *left; //왼쪽노드 (노드의 key 보다 작은값)
	struct node *right; //오른쪽노드 (노드의 key보다 큰값)
} Node;

/* for stack */
#define MAX_STACK_SIZE 20 //스택의 크기 지정
Node* stack[MAX_STACK_SIZE]; //스택선언
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE	20 //큐의 크기 지정
Node* queue[MAX_QUEUE_SIZE]; //큐선언
int front = -1;
int rear = -1;

Node* deQueue(); //dequeue 선언
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


void printStack();



int main()
{
	printf("[----- [이동현] [2019038027] -----]\n");
	char command; //명령어를 저장하는 변수
	int key;
	Node* head = NULL; //head 초기화

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
		scanf(" %c", &command); //command를 입력받는다

		switch(command) {
		case 'z': case 'Z': //command가 z나 Z일 때
			initializeBST(&head); //initializeBST함수 실행
			break;
		case 'q': case 'Q': //command가 q나 Q일 때
			freeBST(head); //freeBST함수 실행
			break;
		case 'i': case 'I': //command가 i나 I일 때
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다
			insert(head, key); //insert함수 실행
			break;
		case 'd': case 'D': //command가 d나 D일 때
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다 
			deleteNode(head, key); //deleteNode함수 실행
			break;

		case 'r': case 'R': //command가 r이나 R일 때
			recursiveInorder(head->left); //recursiveInorder함수 실행
			break;
		case 't': case 'T': //command가 t나 T일 때
			iterativeInorder(head->left); //iterativeInorder함수 실행
			break;

		case 'l': case 'L': //command가 l이나 L일 때
			levelOrder(head->left); //lebelOrder함수 실행
			break;

		case 'p': case 'P': //command가 p나 P일 때
			printStack(); //printStack함수 실행
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q나 Q일 때까지 반복

	return 1;
}

/* BST선언 함수 */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //Node의 크기만큼 메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //right초기화
	(*h)->key = -9999; //key초기화

	top = -1; //top 초기화

	front = rear = -1; //front, rear 초기화

	return 1;
}
/* Recursive */
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left); //recursiveInorder함수 실행
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right); //recursiveInorder함수 실행
	}
}


/* Iterative */
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node);
		node = pop();

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

void levelOrder(Node* ptr)
{
	if(!ptr) return; /* empty tree */

	enQueue(ptr); //enQueue함수 실행

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}

/* key 삽입 함수 */
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node의 크기만큼 메모리 할당
	newNode->key = key; //newNode의 key에 key값 저장
	newNode->left = NULL; //left초기화
	newNode->right = NULL; //right초기화

	if (head->left == NULL) { //left가 NULL이라면
		head->left = newNode; //newnode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL; //parentNode초기화
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

/* 노드 삭제 함수 */
int deleteNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //head의 left가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; 

	Node* parent = NULL; //parent 초기화
	Node* ptr = root; //ptr에 root저장

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) { //key값이 같지 않다면

			parent = ptr;	/* save the parent */

			if(ptr->key > key) //ptr의 key가 key보다 크다면
				ptr = ptr->left; //ptr의 left를 ptr에 저장
			else
				ptr = ptr->right; //작다면 right에 저장
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //left or right가 NULL이라면
	{
		Node* child;
		if (ptr->left != NULL) //left가 NULL이 아니라면
			child = ptr->left; //left 저장
		else //right가 NULL이 아니라면
			child = ptr->right; //right 저장

		if(parent != NULL) //parent가 NULL이 아니라면
		{
			if(parent->left == ptr) //parent의 left와 ptr이 같다면
				parent->left = child; //left에 child저장
			else
				parent->right = child; //right에 child 저장
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr); //ptr 할당 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //candidate선언
	parent = ptr;

	candidate = ptr->right; //ptr의 right저장

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}

/* 메모리 할당 해제 함수 */
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //freeNode 함수로 left 해제
		freeNode(ptr->right); //freeNode 함수로 right 해제
		free(ptr);
	}
}

/* BST 해제 함수 */
int freeBST(Node* head)
{

	if(head->left == head) //head의 left와 head가 같다면
	{
		free(head); //head 메모리 할당 해제
		return 1;
	}

	Node* p = head->left; //p에 head의 left저장

	freeNode(p); //freenode 함수 실행

	free(head); //head 메모리 할당 해제
	return 1;
}

/* pop함수 */
Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--]; //stack[top]반환 후 top 1감소
}

/* push함수 */
void push(Node* aNode)
{
	stack[++top] = aNode; //top를 1증가시킨 후 aNode를 stack[top]에 저장
}

/* 프린트 함수 */
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

/* deQueue함수 */
Node* deQueue()
{
	if (front == rear) { //front와 rear가 같다면
		//printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front]; //queue[front] 리턴

}

/* enQueue함수 */
void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear저장
	if (front == rear) { //front와 rear가 같다면
		//printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //queue[rear]에 aNode저장
}





