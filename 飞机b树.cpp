#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <malloc.h>
#include<sys/types.h>
#include<regex>
#include<memory.h>
#include <fstream>  
#include <sstream>  
using namespace std;
typedef struct LinkList {
	int num;
	string name;
	vector<struct LinkList* > next;
} LinkList;
void Traverse(LinkList* head) //展示本结点的所有
{
	for (int i = 0; i < head->next.size(); i++)
	{
		Traverse(head->next[i]);
	}
}
LinkList* Search(LinkList* head, int num) // 从head开始向下寻找
{
	if (head->num == num)
	{
		return head;
	}
	for (int i = 0; i < head->next.size(); i++)
	{
		LinkList* p = Search(head->next[i], num);
		if (p)
		{
			return p;
		}
	}
	return NULL;
}
bool SearchP1(LinkList* head, int num)
{
	for (int i = 0; i < head->next.size(); i++)
	{
		if (head->next[i]->num == num)
		{
			return 1;
		}
	}
	return 0;
}
LinkList* SearchP(LinkList* head, int num) // 从head开始向下寻找
{
	if (SearchP1(head, num))
	{
		return head;
	}
	for (int i = 0; i < head->next.size(); i++)
	{
		LinkList* p = SearchP(head->next[i], num);
		if (p)
		{
			return p;
		}
	}
	return NULL;
}
void Show(LinkList* head, int num)//遍历
{
	for (int i = 0; i < num; i++)
	{
		cout << "  ";
	}
	cout << "->" << head->num << " " << head->name << endl;
	num++;
	for (int i = 0; i < head->next.size(); i++)
	{
		Show(head->next[i], num);
	}
}
void Create(LinkList* head, LinkList canshu)
{
	LinkList* p;
	p = new LinkList();
	p->num = canshu.num;
	p->name = canshu.name;
	head->next.push_back(p);
}
void Init(LinkList*& head)
{
	LinkList canshu = { 0,"main" };
	head = new LinkList();
	head->num = canshu.num;
	head->name = canshu.name;
}
void Insert(LinkList* head)
{
	cout << "请输入加入到哪个飞机下" << endl;
	int num;
	LinkList* p, canshu = { -1,"-1" };
	cin >> num;
	p = Search(head, num);
	if (p)
	{
		cout << "请输入飞机的编号和名字" << endl;
		cin >> canshu.num >> canshu.name;
		Create(p, canshu);
		cout << "创建完成" << endl;
	}
	else
	{
		cout << "没有这个飞机" << endl;
	}
}
void Delete(LinkList* head)
{
	cout << "请输入删除哪个飞机" << endl;
	int num;
	cin >> num;
	LinkList* p = Search(head, num);
	if (p)
	{
		LinkList* p1 = SearchP(head, num);
		if (!p->next.size() == 0)
		{
			cout << "这个节点下面有结点" << endl;
			for (int i = 0; i < p->next.size(); i++)
			{
				p1->next.push_back(p->next[i]);
			}
			cout << "这个结点下面子节点迁移到上一级" << endl;
		}
		//delete p;
		p = NULL;
		for (vector<LinkList*>::iterator it = p1->next.begin(); it != p1->next.end(); ++it)
		{
			if ((*it)->num == num)
			{
				it = p1->next.erase(it);
			}
		}
	}
	else
	{
		cout << "没有这个飞机" << endl;
		return;
	}
	cout << "删除完成" << endl;
}
void Delete1(LinkList* head)
{
	cout << "请输入删除哪个飞机" << endl;
	int num;
	cin >> num;
	LinkList* p = Search(head, num);
	if (p)
	{
		LinkList* p1 = SearchP(head, num);
		//delete p;
		p = NULL;
		for (vector<LinkList*>::iterator it = p1->next.begin(); it != p1->next.end(); ++it)
		{
			if ((*it)->num == num)
			{
				it = p1->next.erase(it);
			}
		}
	}
	else
	{
		cout << "没有这个飞机" << endl;
		return;
	}
	cout << "删除完成" << endl;
}
void transfer(LinkList* head, int num1, int num2)//把num2迁移到num1下面
{
	LinkList* head1 = Search(head, num1);
	LinkList* head2 = Search(head, num2);
	LinkList* head3 = SearchP(head, num2);
	for (vector<LinkList*>::iterator it = head3->next.begin(); it != head3->next.end(); ++it)
	{
		if ((*it)->num == num2)
		{
			it = head3->next.erase(it);
		}
	}
	head1->next.push_back(head2);
}
int main()
{
	LinkList* head = NULL, * p = NULL;
	Init(head);
	for (int i = 0; i < 10; i++)
	{
		LinkList canshu = { i + 1,to_string((i + 1)) };
		Create(head, canshu);
	}
	p = Search(head, 5);
	if (p)
	{
		for (int i = 10; i < 20; i++)
		{
			LinkList canshu = { i + 1,to_string((i + 1)) };
			Create(p, canshu);
		}
	}
	p = Search(head, 15);
	if (p)
	{
		for (int i = 20; i < 30; i++)
		{
			LinkList canshu = { i + 1,to_string((i + 1)) };
			Create(p, canshu);
		}
	}
	cout << "已生成简单实例，输出如所示" << endl;
	Show(head, 0);
	system("pause");
	system("cls");
	while (1)
	{
		cout << "飞机队列初始化已经完成" << endl;
		cout << "请通过输入数字选择需要的功能" << endl;
		cout << "0 退出程序" << endl;
		cout << "1 显示所有飞机队列" << endl;
		cout << "2 插入飞机" << endl;
		cout << "3 删除飞机" << endl;
		cout << "4 查找飞机" << endl;
		cout << "5 把num2（包括其子飞机）迁移到num1下面" << endl;
		cout << "6 删除飞机(包括其下子飞机)" << endl;
		cout << "7 显示某个飞机以及其子队列" << endl;
		int item;
		cin >> item;
		switch (item)
		{
		case 0:
			return 0;
		case 1:
			Show(head, 0);
			break;
		case 2:
			system("cls");
			Insert(head);
			break;
		case 3:
			system("cls");
			Delete(head);
			break;
		case 4:
			system("cls");
			int num;
			LinkList* pp;
			cout << "请输入要查找的飞机编号" << endl;
			cin >> num;
			pp = Search(head, num);
			cout << p->num << " " << p->name << endl;
			break;
		case 5:
			int num1, num2;
			cout << "请输入 num1 num2" << endl;
			cin >> num1 >> num2;
			transfer(head, 0, 15);
		case 6:
			Delete1(head);
			break;
		case 7:
			int numm;
			cout << "请输入飞机编号" << endl;
			cin >> numm;
			Show(Search(head,numm),0);
			break;
		}
	}
	return 0;
}