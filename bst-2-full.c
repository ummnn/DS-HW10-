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

//��屸��ü ����
typedef struct node {
	int key;
	struct node *left; //���ʳ�� (����� key ���� ������)
	struct node *right; //�����ʳ�� (����� key���� ū��)
} Node;

/* for stack */
#define MAX_STACK_SIZE 20 //������ ũ�� ����
Node* stack[MAX_STACK_SIZE]; //���ü���
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE	20 //ť�� ũ�� ����
Node* queue[MAX_QUEUE_SIZE]; //ť����
int front = -1;
int rear = -1;

Node* deQueue(); //dequeue ����
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
	printf("[----- [�̵���] [2019038027] -----]\n");
	char command; //��ɾ �����ϴ� ����
	int key;
	Node* head = NULL; //head �ʱ�ȭ

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
		scanf(" %c", &command); //command�� �Է¹޴´�

		switch(command) {
		case 'z': case 'Z': //command�� z�� Z�� ��
			initializeBST(&head); //initializeBST�Լ� ����
			break;
		case 'q': case 'Q': //command�� q�� Q�� ��
			freeBST(head); //freeBST�Լ� ����
			break;
		case 'i': case 'I': //command�� i�� I�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´�
			insert(head, key); //insert�Լ� ����
			break;
		case 'd': case 'D': //command�� d�� D�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´� 
			deleteNode(head, key); //deleteNode�Լ� ����
			break;

		case 'r': case 'R': //command�� r�̳� R�� ��
			recursiveInorder(head->left); //recursiveInorder�Լ� ����
			break;
		case 't': case 'T': //command�� t�� T�� ��
			iterativeInorder(head->left); //iterativeInorder�Լ� ����
			break;

		case 'l': case 'L': //command�� l�̳� L�� ��
			levelOrder(head->left); //lebelOrder�Լ� ����
			break;

		case 'p': case 'P': //command�� p�� P�� ��
			printStack(); //printStack�Լ� ����
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q�� Q�� ������ �ݺ�

	return 1;
}

/* BST���� �Լ� */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //Node�� ũ�⸸ŭ �޸� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //right�ʱ�ȭ
	(*h)->key = -9999; //key�ʱ�ȭ

	top = -1; //top �ʱ�ȭ

	front = rear = -1; //front, rear �ʱ�ȭ

	return 1;
}
/* Recursive */
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left); //recursiveInorder�Լ� ����
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right); //recursiveInorder�Լ� ����
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

	enQueue(ptr); //enQueue�Լ� ����

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

/* key ���� �Լ� */
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node�� ũ�⸸ŭ �޸� �Ҵ�
	newNode->key = key; //newNode�� key�� key�� ����
	newNode->left = NULL; //left�ʱ�ȭ
	newNode->right = NULL; //right�ʱ�ȭ

	if (head->left == NULL) { //left�� NULL�̶��
		head->left = newNode; //newnode ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL; //parentNode�ʱ�ȭ
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

/* ��� ���� �Լ� */
int deleteNode(Node* head, int key)
{
	if (head == NULL) { //head�� NULL�̶��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //head�� left�� NULL�̶��
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; 

	Node* parent = NULL; //parent �ʱ�ȭ
	Node* ptr = root; //ptr�� root����

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) { //key���� ���� �ʴٸ�

			parent = ptr;	/* save the parent */

			if(ptr->key > key) //ptr�� key�� key���� ũ�ٸ�
				ptr = ptr->left; //ptr�� left�� ptr�� ����
			else
				ptr = ptr->right; //�۴ٸ� right�� ����
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
	if ((ptr->left == NULL || ptr->right == NULL)) //left or right�� NULL�̶��
	{
		Node* child;
		if (ptr->left != NULL) //left�� NULL�� �ƴ϶��
			child = ptr->left; //left ����
		else //right�� NULL�� �ƴ϶��
			child = ptr->right; //right ����

		if(parent != NULL) //parent�� NULL�� �ƴ϶��
		{
			if(parent->left == ptr) //parent�� left�� ptr�� ���ٸ�
				parent->left = child; //left�� child����
			else
				parent->right = child; //right�� child ����
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr); //ptr �Ҵ� ����
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

	Node* candidate; //candidate����
	parent = ptr;

	candidate = ptr->right; //ptr�� right����

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

/* �޸� �Ҵ� ���� �Լ� */
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //freeNode �Լ��� left ����
		freeNode(ptr->right); //freeNode �Լ��� right ����
		free(ptr);
	}
}

/* BST ���� �Լ� */
int freeBST(Node* head)
{

	if(head->left == head) //head�� left�� head�� ���ٸ�
	{
		free(head); //head �޸� �Ҵ� ����
		return 1;
	}

	Node* p = head->left; //p�� head�� left����

	freeNode(p); //freenode �Լ� ����

	free(head); //head �޸� �Ҵ� ����
	return 1;
}

/* pop�Լ� */
Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--]; //stack[top]��ȯ �� top 1����
}

/* push�Լ� */
void push(Node* aNode)
{
	stack[++top] = aNode; //top�� 1������Ų �� aNode�� stack[top]�� ����
}

/* ����Ʈ �Լ� */
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

/* deQueue�Լ� */
Node* deQueue()
{
	if (front == rear) { //front�� rear�� ���ٸ�
		//printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front]; //queue[front] ����

}

/* enQueue�Լ� */
void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear����
	if (front == rear) { //front�� rear�� ���ٸ�
		//printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //queue[rear]�� aNode����
}





