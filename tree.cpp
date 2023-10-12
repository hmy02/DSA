#include <stdio.h>
#include <stdlib.h>
//二叉树的基本操作
typedef char Elemtype;
 
typedef struct Bitnode {
	Elemtype data;
	Bitnode *lchild, *rchild;
} Bitnode, *Bitree;
 
//前序递归建立二叉树
void Creat(Bitree &T) {
	Elemtype n;
	scanf("%c", &n);
	if (n == '#')
		T = NULL;
	else {
		T = (Bitnode *)malloc(sizeof(Bitnode));
		T->data = n;
		T->lchild = NULL;
		T->rchild = NULL;
		Creat(T->lchild);
		Creat(T->rchild);
	}
}
 
//前序递归遍历二叉树
void Inorder(Bitree T) {
	if (T) {
		printf("%c", T->data);
		Inorder(T->lchild);
		Inorder(T->rchild);
	}
}
 
//前序非递归遍历二叉树
void Fir_Inorder(Bitree T) {
	Bitree stack[100], p = T;
	int top = 0;
	while (p || top) {
		while (p) {
			stack[top] = p;
			top++;
			printf("%c", p->data);
			p = p->lchild;
		}
		top--;
		p = stack[top];
		p = p->rchild;
	}
}
 
//中序非递归遍历
void Mid_Inorder(Bitree T) {
	Bitree stack[100], p = T;
	int top = 0;
	while (p || top) {
		while (p) {
			stack[top] = p;
			top++;
			p = p->lchild;
		}
		top--;
		p = stack[top];
		printf("%c", p->data);
		p = p->rchild;
	}
}
 
//后序非递归遍历
void Las_Inorder(Bitree T) {
	Bitree stack[100], p = T;
	int tag[100];
	int top = 0;
	while (p || top) {
		while (p) {
			top++;
			stack[top] = p;
			p = p->lchild;
			tag[top] = 1;
		}
		if (tag[top] == 1) {
			p = stack[top];
			tag[top] = 2;
			p = p->rchild;
		} else {
			p = stack[top];
			printf("%c", p->data);
			top--;
			p = NULL;
		}
	}
}
 
//层序遍历
void Level(Bitree T) {
	Bitree Q[100], p = T;
	int rear, front;
	rear = front = 0;
	rear++;
	Q[rear] = p;
	while (rear != front) {
		front++;
		p = Q[front];
		printf("%c", p->data);
		if (p->lchild) {
			rear++;
			Q[rear] = p->lchild;
		}
		if (p->rchild) {
			rear++;
			Q[rear] = p->rchild;
		}
	}
}
 
//按层输出
void Lever_pro(Bitree T) {
	Bitree Q[100], p = T;
	int rear, front, tag[10], i = 1, j = 0, k = 0, num = 0;
	//i标志层数，j执行循环，k标志每层的结点数，由于k每次需要归零，
	//故还需要设置变量num记录每层的结点数并参与执行循环
	rear = front = 0;
	rear++;
	Q[rear] = p;
	num = 1;
	while (rear != front) {
		printf("第%d层的数据为：", i);
		for (j = 0; j < num; j++) {
			front++;
			p = Q[front];
			printf("%c", p->data);
			if (p->lchild) {
				rear++;
				Q[rear] = p->lchild;
				k++;
			}
			if (p->rchild) {
				rear++;
				Q[rear] = p->rchild;
				k++;
			}
		}
		num = k;
		k = 0;
		printf("\n");
		i++;
	}
}
 
void Level_pro_pro(Bitree T) {
	Bitree Q[100], p = T;
	int rear, front, nowcount = 0, nextcount = 0, i = 1, tag = 0;
	rear = front = 0;
	rear++;
	Q[rear] = p;
	nowcount = 1;
	while (rear != front) {
		if (tag == 0)
			printf("第%d层的元素为：", i);
		front++;
		p = Q[front];
		printf("%c", p->data);
		nowcount--;
		if (p->lchild) {
			rear++;
			Q[rear] = p->lchild;
			nextcount++;
		}
		if (p->rchild) {
			rear++;
			Q[rear] = p->rchild;
			nextcount++;
		}
		tag = 1;
		if (nowcount == 0) {
			nowcount = nextcount;
			nextcount = 0;
			i++;
			printf("\n");
			tag = 0;
		}
	}
}
 
 
//树的深度
int Depth(Bitree T) {
	int m, n;
	if (T == NULL)
		return 0;
	else {
		m = Depth(T->lchild);
		n = Depth(T->rchild);
		if (m > n)
			return m + 1;
		else
			return n + 1;
	}
}
 
//树的结点数
int NodeCount(Bitree T) {
	if (T)
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
	else
		return 0;
 
}
 
//统计二叉树中度为0的结点的个数
int Node0Count(Bitree T) {
	if (T) {
		if (T->lchild == NULL && T->rchild == NULL)
			return Node0Count(T->lchild) + Node0Count(T->rchild) + 1;
		else
			return Node0Count(T->lchild) + Node0Count(T->rchild);
	} else
		return 0;
}
 
//统计二叉树中度为1的结点的个数
int Node1Count(Bitree T) {
	if (T) {
		if (T->lchild != NULL && T->rchild == NULL || T->lchild == NULL && T->rchild != NULL)
			return Node1Count(T->lchild) + Node1Count(T->rchild) + 1;
		else
			return	Node1Count(T->lchild) + Node1Count(T->rchild);
	} else
		return 0;
 
}
 
//统计二叉树中度为2的结点的个数
int Node2Count(Bitree T) {
	if (T) {
		if (T->lchild != NULL && T->rchild != NULL)
			return Node2Count(T->lchild) + Node2Count(T->rchild) + 1;
		else
			return Node2Count(T->lchild) + Node2Count(T->rchild);
	}
	return 0;
}
 
int main() {
	Bitree T;
	int depth;
	Creat(T);
	printf("前序非递归的结果：");
	Fir_Inorder(T);
	printf("\n");
	printf("中序非递归的结果：");
	Mid_Inorder(T);
	printf("\n");
	printf("后序非递归的结果：");
	Las_Inorder(T);
	printf("\n");
	printf("层序递归的结果：");
	Level(T);
	printf("\n");
	Lever_pro(T);
	depth = Depth(T);
	printf("树的深度为:%d\n", depth);
	printf("树的结点的个数:");
	printf("%d\n", NodeCount(T));
	printf("度为0的结点的个数:");
	printf("%d\n", Node0Count(T));
	printf("度为1的结点的个数:");
	printf("%d\n", Node1Count(T));
	printf("度为2的结点的个数:");
	printf("%d\n", Node2Count(T));
	return 0;
}
