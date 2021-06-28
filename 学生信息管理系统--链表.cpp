#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Nsize 10
#define Gsize 7

void Print_message();		//打印信息（个人/全部）
void Add_Del();				//增删学生信息	
void Change_message();		//修改学生信息
void Sore_message();		//对学生信息进行排序（姓名/学号/单科成绩）
void IQ_message();			//查询学生信息
char * input(char * st, int n);//输入学生信息
struct student
{
	char title[Nsize];
	char ID[10];
	int grade[Gsize];
};

struct message
{
	struct student Stu;
	struct message * next;
};
struct message * head = NULL;
struct message * front, *current;

int main(void)
{

	char name[Nsize];
	int i, j = 0;
	char id[10];
	//收集学生信息
	printf("请输入学生姓名：");
	while (input(name, Nsize) != NULL && name[0] != '\0')
	{
		current = (struct message*)malloc(sizeof(struct message));
		if (head == NULL)
			head = current;			//定头结点
		else
			front->next = current;
		current->next = NULL;
		strcpy_s(current->Stu.title, name);
		printf("请输入学号：");
		gets_s(current->Stu.ID,10);
		printf("请输入：班级、语文、数学、英语、物理、化学、生物成绩\n");
		for (i = 0; i<Gsize; i++)
		{
			printf("       ");
			scanf_s("%d", &current->Stu.grade[i]);
		}
		while (getchar() != '\n')			//输入不为换行，跳至前一个while继续执行
			continue;
		printf("请输入下一个学生姓名（空一行结束）：");
		front = current;
	}
	do
	{
		printf("请输入相应序号：\n");
		printf("1.打印学生信息：\n");
		printf("2.增删学生信息：\n");
		printf("3.修改学生信息：\n");
		printf("4.对学生信息进行排序：\n");
		printf("5.查询学生信息：\n");
		printf("6.退出\n");
		scanf_s("%d", &j);
		switch (j)
		{
		case 1:Print_message(); break;
		case 2:Add_Del(); break;
		case 3:Change_message(); break;
		case 4:Sore_message(); break;
		case 5:IQ_message();; break;
		default:
			break;
		}
	} while (j<6);

	return 0;
}


char * input(char * st, int n)
{
	char *adress;
	char * find;
	adress = fgets(st, n, stdin);		//遇到EOF时将返回NULL
	if (adress)
	{
		find = strchr(st, '\n');		//查找换行符，如有退出主函数循环,即表示NULL
		if (find)					//若地址非NULL，进行进行操作
			*find = '\0';
		else
			while (getchar() != '\0')
				continue;
	}
	return adress;
}

void Print_message()		//打印全部学生信息
{
	if (current->Stu.title == '\0' || current == NULL)
		printf("没有输入数据。\n");
	else
	{
		printf("姓名\t学号\t班级\t语文\t数学\t英语\t物理\t化学\t生物成绩\n");
		current = head;
		while (current != NULL)
		{
			printf("%s\t", current->Stu.title);
			printf("%s\t", current->Stu.ID);
			for (int i = 0; i<Gsize; i++)
				printf("%d\t", current->Stu.grade[i]);
			printf("\n");
			if (current->next == NULL)
				break;
			current = current->next;
		}
	}
}
void IQ_message()
{
	char iq[Nsize];
	printf("请输入想要查询的学生姓名或学号\n");
	scanf_s("%s", iq);
	current = head;
	while (current != NULL)
	{
		if (strcmp(iq, current->Stu.title) == 0 || strcmp(iq, current->Stu.ID) == 0)
		{
			printf("姓名\t学号\t班级\t语文\t数学\t英语\t物理\t化学\t生物成绩\n");
			printf("%s\t", current->Stu.title);
			printf("%s\t", current->Stu.ID);
			for (int i = 0; i<Gsize; i++)
				printf("%d\t", current->Stu.grade[i]);
			printf("\n");
		}
		current = current->next;
	}

}

void Add_Del()
{
	char iq[Nsize];
	char j[10];
	int i = 0;
	struct message * p, *q;
	current = head;
	do
	{
		printf("请输入需要操作的序号\n");
		printf("1.增加学生信息\n");
		printf("2.删除学生信息\n");
		printf("3.退出\n");
		scanf_s("%d", &i);
		if (i == 1)
		{
			p = (struct message*)malloc(sizeof(struct message));
			if (p == NULL)
				head = p;
			else
			{
				while (current->next != NULL)
					current = current->next;
				current->next = p;
				p->next = NULL;
			}
			printf("请输入学生姓名：");
			scanf_s("%s", p->Stu.title);
			printf("请输入学号：");
			scanf_s("%s", &p->Stu.ID);
			printf("请输入：班级、语文、数学、英语、物理、化学、生物成绩\n");
			for (i = 0; i<Gsize; i++)
			{
				printf("       ");
				scanf_s("%d", &p->Stu.grade[i]);
			}
			while (getchar() != '\n')			//输入不为换行，跳至前一个while继续执行
				continue;
		}
		else if (i == 2)
		{
			p = current;
			printf("请输入需要删除的学生姓名或学号\n");
			scanf_s("%s", &j);
			if (p->next == NULL)			//若只有一个数据，或最后一个直接清空当前数据
			{
				free(p);
				current = NULL;
				printf("已成功删除%s的学生信息,其只有一个\n", j);
			}
			else
			{
				while (p != NULL)
				{
					if (strcmp(j, p->Stu.title) == 0 || strcmp(j, p->Stu.ID) == 0)
					{
						q->next = p->next;
						free(p);
						printf("已成功删除%s的学生信息\n", j);
						break;
					}
					q = p;
					p = p->next;
				}
			}

		}
	} while (i<3);

}

void Sore_message()
{
	char message[10];
	struct message * pnew = NULL, *pre = NULL,tre;
	struct student temp ;
	int i, j, grade[Gsize];
	char name[Nsize], ID[10];

	printf("请输入相应序号\n");
	printf("1.按姓名进行排序\n");
	printf("2.按学号进行排序\n");
	printf("3.按单科成绩进行排序\n");
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
		for (pre = head; pre != NULL; pre = pre->next)
			for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
			{
				if (strcmp(pre->Stu.title, pnew->Stu.title)<0)			//姓名排序
				{
					temp= pre->Stu;				//交换结点里面的数据域
					pre->Stu = pnew->Stu;
					pnew->Stu = temp;

					//temp->next = pre->next;		//交换指针域
					//pre->next = pnew->next;
					//pnew->next = temp->next;
				}
			}
		Print_message();
		break;
	case 2:
		for (pre = head; pre != NULL; pre = pre->next)
			for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
			{
				if (strcmp(pre->Stu.ID, pnew->Stu.ID)<0)
				{
					temp = pre->Stu;				//交换结点里面的数据域
					pre->Stu = pnew->Stu;
					pnew->Stu = temp;

					//temp->next = pre->next;		//交换指针域
					//pre->next = pnew->next;
					//pnew->next = temp->next;
				}
			}
		Print_message();
		break;
	case 3:
		printf("按单科成绩排序：\n");
		printf("1.语文\n2.数学\n3.英语\n4.物理\n5.化学\n6.生物\n");				//好像还有一些问题，需要修改
		scanf_s("%d", &j);
		
		for (pre = head; pre != NULL; pre = pre->next)
			for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
			{
				if (pre->Stu.grade[j]<pnew->Stu.grade[j])		//因为前面有班级，语文排第二
				{
					temp = pre->Stu;					
					pre->Stu = pnew->Stu;
					pnew->Stu = temp;
				}
			}
		Print_message();
		break;
	default:
		break;
	}

}

void Change_message()
{
	char change_ID[Nsize];
	struct message * p;
	printf("请输入想要修改信息的学生姓名或学号\n");
	scanf_s("%s", change_ID);
	current = head;
	while (current != NULL)
	{
		if (strcmp(change_ID, current->Stu.title) == 0 || strcmp(change_ID, current->Stu.ID) == 0)
		{
			p = (struct message *)malloc(sizeof(struct message));
			printf("请输入姓名：");
			scanf_s("%s", p->Stu.title);
			strcpy_s(current->Stu.title, p->Stu.title);
			printf("请输入学号：");
			scanf_s("%s", p->Stu.ID);
			strcpy_s(current->Stu.ID, p->Stu.ID);
			printf("请输入班级、语文、数学、英语、物理、化学、生物成绩：\n");
			for (int i = 0; i<Gsize; i++)
			{
				scanf_s("%d", &p->Stu.grade[i]);
				current->Stu.grade[i] = p->Stu.grade[i];
			}
			break;
		}
		current = current->next;

	}
}