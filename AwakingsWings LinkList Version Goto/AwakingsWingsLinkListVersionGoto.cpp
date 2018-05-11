// AwakingsWingsLinkListVersionGoto.cpp: 定义控制台应用程序的入口点。
// 学号：2220162448；专业班级：16-地理信息科学；姓名：石梓豪；环境：VS2017；

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>

typedef int ElemType;
typedef int status;

#define TRUE 1
#define ERROR 0
#define FALSE 0
#define NULL 0
#define OK 1
#define OVERFLOW -2
#define list_init_size 100
#define listincrement 10

//链表定义
typedef struct LNode {
	ElemType	data;
	struct LNode *next;
}LNode, *LinkList;
//链表L的初始化--防止变量的未定义无法判断；
void InitList(LinkList &L) {
	L = (LNode *)malloc(sizeof(LNode));
	L->next = NULL;
}
//建立带头结点的链表L，其长度为int n；scanf逆序输入；
void CreateList_L(LinkList &L, int n) {
	LNode *p;
	int i;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (i = n; i > 0; --i) {
		p = (LinkList)malloc(sizeof(LNode));
		scanf_s("%d", &p->data);//书上原句scanf（&p->data)报错，网一说此句错误，二说scanf函数在VS环境中不能正常使用，故改。
		p->next = L->next;
		L->next = p;
	}
}
//链表L的打印 “当前链表的具体数据为xxxxxxxx”
void PrintList(LinkList &L)
{
	LNode *p;//建遍历用的指针 不要直接用头指针移动
	printf("\n当前单链表的具体数据为:");
	p = L->next;//从头开始
	while (p != NULL)//p=null时到尾部 跳出循环
	{
		printf("%d ", p->data);//打印节点内容
		p = p->next;//向后移一个位置
	}
	printf("\n");
}
//双升序链表La，Lb合并成升序Lc，结合ListRank使用
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;
	while (pa&&pb) {
		if (pa->data <= pb->data) {
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else { pc->next = pb; pc = pb; pb = pb->next; }
	}
	pc->next = pa ? pa : pb;
	free(Lb);
}
//逆置链表L，与ListRank结合使用可以输出逆序
void reverse(LinkList &L)//逆置链表  
{
	LNode *p, *q, *r;//三个指针  
	p = L->next;//头结点后的第一个结点  
	if (p == NULL) return; //空表  
	q = p->next;
	if (q == NULL) return;//只有一个结点  
	r = q->next;
	while (r != NULL)//修改各结点的指针使其指向前一个节点  
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;//r将保持之后的结点不变  
	}
	q->next = p;//修改最后一个结点  
	L->next->next = NULL;//将原先的第一个结点变为现在的最后一个null  
	L->next = q;//头结点后的第一个结点
}
//在链表L中的第i个值之后插入元素e
status ListInsert(LinkList &L, int i, ElemType e) {
	LinkList p, s;
	int j;
	p = L; j = 0;
	while (p&&j<i) { p = p->next; ++j; }
	if (!p || j>i) return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e; s->next = p->next;
	p->next = s;
	return OK;
}
//在链表L中删除第i个元素并用e返回其值
status ListDelete(LinkList &L, int i, ElemType &e) {
	LinkList p, q;
	int j;
	p = L; j = 0;
	while (p->next&&j<i - 1) {
		p = p->next; ++j;
	}
	if (!(p->next) || j>i - 1) return ERROR;
	q = p->next; p->next = q->next;
	e = q->data; free(q);
	return OK;
}
//抓取第i个元素的值赋给e并返回OK，元素不存在时返回ERROR
status GetElem(LinkList &L, int i, ElemType &e){
	LinkList p;
	int j;
	p = L->next; j = 1;
	while (p&&j<i) {
		p = p->next; ++j;
	}
	if (!p || j>i) return ERROR;
	e = p->data;
	return OK;
}
/*以上是书中定义或刚需函数*/

//检查链表L，消灭所有相同元素
void SameOut(LinkList &L)
{
	LNode *p, *q;
	p = L;
	q = L->next;
	while (q)
	{
		if (p->data == q->data)
		{
			q = q->next;
			p->next = q;
		}
		p = p->next;
		q = q->next;
	}
}
//将链表L升序排列
void ListRank(LNode *head)
{
	LNode *p = head->next, *q = NULL, *r = NULL;
	if (p != NULL)
	{
		r = p->next;
		p->next = NULL;
		p = r;
		while (p != NULL)
		{
			r = p->next;
			q = head;
			while (q->next != NULL && q->next->data < p->data)
				q = q->next;
			p->next = q->next;
			q->next = p;
			p = r;
		}
	}
}
/*以上是自定义一般函数*/

//自定义创建长度为a链表L,自然顺序
void LinkStart(LinkList &L, int a) {
	CreateList_L(L, a);
	reverse(L);
	PrintList(L);
}
//系统菜单
void menu()
{
	printf("操作菜单\n");
	printf("1.链表初始化；\n");
	printf("2.链表的后插；\n");
	printf("3.链表元素的定位删除；\n");
	printf("4.查找数据是否存在；\n");
	printf("5.在新链表中合并两个链表并排除不同元素；\n");
	printf("6.链表降序排列；\n");
	printf("7.将辅助链表合并到主链表并升序排列；\n");
	printf("0.退出管理系统；\n\n");
	printf("请输入对应数值并按回车确定；\n");
}
//系统错误结束提示
void donotknow() {
	printf("你想让我干嘛？我可不会哦。\n");
	exit(0);
}
/*以上是专用自定义函数*/

int main()
{
	int m;
	menu();
	printf("提示：要使用其他功能，请先初始化主链表。\n");
	scanf_s("%d", &m);
	if (m != 0 && m != 1)
	{
		donotknow();
	}
	if (m == 0)
	{
		exit(0);
	}
	if (m == 1)
	{
		LinkList La, Lb, Lc;
		InitList(Lb);
		int lenA;
		int lenB = 0;
		printf("链表初始化开始。\n");
		printf("请决定链表长度=");
		scanf_s("%d", &lenA);
		LinkStart(La, lenA);
		printf("\n");
		//以上首先定义主链表，空置辅助链表。其他操作退出系统。
		SystemMenu:int t;
		menu();
		scanf_s("%d", &t);
		if (t > 7 || t < 0)
			{
				donotknow();
			}
		if (t == 1)
			{
				int a, len;
				printf("链表初始化开始。\n");
				printf("请选择要定义的列表类型\n");
				printf("0.La（主链表）\n");
				printf("1.Lb（辅助链表）\n");
				scanf_s("%d", &a);
				printf("请决定链表长度=");
				scanf_s("%d", &len);
				if (a < 0 || a>2)
				{
					donotknow();
				}
				if (a == 0)
				{
					LinkStart(La, len);
					lenA = len;
					printf("\n");
				}
				if (a == 1)
				{
					LinkStart(Lb, len);
					lenB = len;
					printf("\n");
				}
				goto SystemMenu;
			}
		if (t == 2)
			{
				int b, c;
				printf("请输入要插入的值=\n");
				scanf_s("%d", &b);
				printf("请输入要插入的位置=\n");
				scanf_s("%d", &c);
				if (c <= lenA)
				{
					ListInsert(La, c, b);
					PrintList(La);
					lenA++;
					printf("\n");
					goto SystemMenu;
				}
				else donotknow();
			}
		if (t == 3)
			{
				int d;
				ElemType e;
				printf("请输入要删除的值的位置=\n");
				scanf_s("%d", &d);
				if (d <= lenA)
				{
					ListDelete(La, d, e);
					PrintList(La);
					lenA--;
					printf("\n");
					goto SystemMenu;
				}
				else donotknow();
			}
		if (t == 4)
			{
				int f, i;
				int count = 0;
				printf("请输入要查找的值=\n");
				scanf_s("%d", &f);
				for (i = 1; i <= lenA; i++)
				{
					int e;
					GetElem(La, i, e);
					if (e == f)
						count++;
				}
				if (count != 0)
					printf("存在。\n");
				else
					printf("不存在。\n");
				goto SystemMenu;
			}
		if (t == 5)
			{
				ListRank(La);
				SameOut(La);
				ListRank(Lb);
				SameOut(Lb);
				MergeList_L(La, Lb, Lc);
				SameOut(Lc);
				PrintList(Lc);
				printf("\n");
				goto SystemMenu;
			}
		if (t == 6)
			{
				ListRank(La);
				reverse(La);
				PrintList(La);
				printf("\n");
				goto SystemMenu;
			}
		if (t == 7)
			{
				ListRank(La);
				ListRank(Lb);
				MergeList_L(La, Lb, La);
				lenA = lenA + lenB;
				PrintList(La);
				printf("\n");
				goto SystemMenu;
			}
		if (t == 0)
		{
			exit(0);
		}
	}
	return 0;
}
