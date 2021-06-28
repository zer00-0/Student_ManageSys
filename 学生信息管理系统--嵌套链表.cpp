#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct clouse Clo;
typedef struct student Stu;

int menu();
void PrintMessage();
char * input(char * st, int n);
Clo * Add_sonlink(Clo *temp);
void Add_Delmessage();
void Change_message();
void IQ_message();
void Sort_message();
struct clouse
{
	char title[20];
	int grade;
	Clo * next;
};

struct student
{
	char name[20];
	char id[20];
	Clo * clo;
	Stu * next;
	int size = 1;
};

Stu *pnew,*pre ,*phead = NULL;


void main()
{
	Stu * temp = NULL;
	char name[20];
	int i = 1;
	puts("学生信息管理数据输入");
	printf("请输入第%d个学生姓名：",i);
	while (input(name, 20) != NULL &&name[0] != '\0')
	{
		pnew = (Stu *)malloc(sizeof(Stu));
		strcpy_s(pnew->name, name);
		printf("请输入第%d个学生学号：",i);
		gets_s(pnew->id, 20);
		i++;
		if (temp == NULL)
			puts("这是空父链，加入表头");
			
		pnew->clo = NULL;						//子链表基本思路，先定义一个临时子链表结构体，与父链表建立关系，之后使用递归（类似父链表），进行输入
		pnew->clo = Add_sonlink(pnew->clo);		//建立子链表与父链表联系，最后返回子链表第一个地址信息，不返回会丢失数据			
												//
		printf("请输入第%d个学生姓名（或回车结束）：",i);
		pnew->size++;
		pre = temp;

		if (temp == NULL)
		{
			phead = pnew;				//phead记录了父链表首节点地址，以后不要动
			temp = pnew;
			pnew->next = NULL;
			pre = temp;
		}
		else
		{
			while (pre->next != NULL)
				pre = pre->next;
			pre->next = pnew;
			pnew->next = NULL;
		}
	}
	int num = 1;
	while (num > 0 && num < 6)
		num = menu();

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

int menu()
{
	puts("请按下列提示进行输入");
	puts("1.打印学生信息\n2.增减学生信息");
	puts("3.修改学生信息\n4.查询学生信息");
	puts("5.对学生信息进行排序\n6.退出");
	int choice;
	scanf_s("%d",&choice,1);
	switch (choice)
	{
	case 1:PrintMessage(); break;
	case 2:Add_Delmessage(); break;
	case 3:Change_message(); break;
	case 4:IQ_message(); break;
	case 5:Sort_message(); break;		//假设有相同的公共课
	default:
		break;
	}
	return choice;
}

void PrintMessage()
{
	Clo * temp;
	int i ;
	if (phead->name == '\0' || phead == NULL)
		puts("没有输入数据\n");
	else	
	{	
		pnew = phead;		//指向头结点，用于遍历
		
		while (pnew != NULL)
		{
			puts("姓名\t学号\t");
			i = 1;
			printf("%s\t", pnew->name);
			printf("%s\t", pnew->id);
			printf("\n");
			temp = pnew->clo;					//赋与temp子链表信息
			while (temp != NULL)
			{
				printf("科目%d: %s ", i,temp->title);
				printf("成绩: %d\t", temp->grade);
				if (i % 3 == 0 && temp->next != NULL)
					printf("\n");
				i++;
				temp = temp->next;
			}
			puts("\n");
			pnew = pnew->next;
		}
	}
	
	pnew = phead;
}

Clo * Add_sonlink(Clo * temp)
{
	Clo *clonew, *clopre;
	char title[20] = "语文";	
	char test[20] = {"end"};
	int i = 1;
	puts("请输入学生课程信息");
	printf("请输入科目%d的名称:",i);
	scanf_s("%s",title,20);					//如果用gets_s一输入就锁死了,好像关系到内存。测试一下发现还是要gets_s才能重新改字符串数据
											//后面发现scanf_s，输入需要一个长度信息（数组长度），可以防止内存越界
	while (strcmp(title,test) != 0)		
	{
		clonew = (Clo *)malloc(sizeof(Clo));	
		strcpy_s(clonew->title, title);
		printf("请输入科目%d分数：",i);
		scanf_s("%d",&clonew->grade,4);
		fflush(stdin);					//scanf_s函数，多次使用时，可以用来防止输入混乱（好像大概意思是清楚上一次输入的影响，尝试过几次报错）
		clopre = temp;					//故查找资料得到，两种方法：1.scanf_s（“%s\n”,i）；加\n,好像不行；2.使用fflush(stdin);
		if (temp == NULL)
		{
			temp = clonew;
			clonew->next = NULL;
			puts("子链表为空链表，数据加入表头");
			clopre = temp;
		}
		else
		{
			while (clopre->next != NULL)
				clopre = clopre->next;
			clopre->next = clonew;
			clonew->next = NULL;
		}
		i++;
		printf("请输入科目%d名称(或输入end结束)：",i);
		scanf_s("%s", title, 20);
		fflush(stdin);
	}
	return temp;		//返回子链表的节点信息，一开始没有返回造成节点信息为NULL
}

void Add_Delmessage()
{
	int choice;
	Stu *temp,*p,*q = NULL;
	char name[20],id[20];
	do
	{	
		puts("请输入想要执行的选项");
		puts("1.增加学生信息");
		puts("2.删除学生信息");
		puts("3.退出");
		scanf_s("%d", &choice, 1);
		switch (choice)
		{
		case 1:
			p = phead;
			temp = (Stu *)malloc(sizeof(Stu));
			if (temp == NULL)
				phead = temp;
			else
			{
				while (p->next != NULL)
					p = p->next;
				p->next = temp;
				temp->next = NULL;
			}
			puts("输入增加的学生信息");
			puts("姓名：");
			scanf_s("%s",temp->name, 20);
			puts("学号：");
			scanf_s("%s", temp->id, 20);
			temp->clo = NULL;
			temp->clo = Add_sonlink(temp->clo);
			break;
		case 2:
			puts("请输入想要删除的学生姓名或学号");
			scanf_s("%s", name, 20);
			p = phead;
			if (p->next == NULL)
			{
				free(p);
				pnew = NULL;
				printf("已成功删除%s的学生信息,其只有一个\n", name);

			}
			else
			{ 
				while (p!= NULL)
				{	
					
					if (strcmp(p->name ,name) == 0 || strcmp(p->id, name) == 0)		
					{
									
						if (p == phead)						//第一个节点
						{
							phead = p->next;
							free(p);
							puts("删除第一个节点成功");
							
						}
						else if (p->next == NULL)			//最后一个节点
						{					
							free(p);
							p = q;				//将节点位置提前一个
							p->next = NULL;
							puts("删除最后一个节点成功");
						}
						else								//中间节点
						{
							q->next = p->next;
							free(p);
							printf("已成功删除%s的学生信息\n", name);
						}
						break;
					}
					q = p;
					p = p->next;
				}
			}
			break;
		default:
			break;
		}
	} while (choice > 0 &&choice <3);
	
}

void Change_message()			//修改学生信息
{
	Clo *temp;
	int i = 1,j;
	char change[20];
	puts("请输入要修改学生的姓名或学号");
	scanf_s("%s", change, 20);
	pnew = phead;
	while (pnew != NULL)
	{
		if (strcmp(pnew->name, change) == 0 || strcmp(pnew->id, change) == 0)
		{
			puts("查询的学生信息为：\n");
			puts("姓名\t学号");
			printf("%s\t", pnew->name);
			printf("%s\t\n", pnew->id);
			temp = pnew->clo;					//赋与temp子链表信息
			while (temp != NULL)
			{
				printf("科目%d: %s ", i, temp->title);
				printf("成绩: %d\t", temp->grade);
				if (i % 3 == 0)
					printf("\t");
				i++;
				temp = temp->next;
			}
			puts("\n");
			
			do
			{
				puts("请输入需要修改的选项");
				puts("1.修改姓名");
				puts("2.修改学号");
				puts("3.修改成绩");
				puts("4.退出");
				scanf_s("%d", &j);
				switch (j)
				{
				case 1:
					puts("请输入需要修改的名字");
					scanf_s("%s", pnew->name, 20);
					break;
				case 2:
					puts("请输入需要修改的学号");
					scanf_s("%s", pnew->id, 20);
					break;
				case 3:
					temp = pnew->clo;
					i = 1;
					puts("请输入需要修改的科目");
					scanf_s("%s", change, 20);
					while (temp != NULL)
					{
						if (strcmp(temp->title, change) == 0)
						{
							puts("请输入成绩");
							scanf_s("%d", &temp->grade);
							printf("已成功更改第%d科目成绩", i);
							break;
						}
						i++;
						temp = temp->next;
					}
				default:
					break;
				}
			} while (j>0 && j<4);
			i = 1;
			puts("姓名\t学号");
			printf("%s\t", pnew->name);
			printf("%s\t\n", pnew->id);
			temp = pnew->clo;					//赋与temp子链表信息
			while (temp != NULL)
			{
				printf("科目%d: %s ", i, temp->title);
				printf("成绩: %d\t", temp->grade);
				if (i % 3 == 0 && temp->next != NULL)
					printf("\n");
				i++;
				temp = temp->next;
			}
			printf("\n");
			break;
		}
		pnew = pnew->next;
	}
}

void IQ_message()
{
	Clo * temp;
	char iq[20];
	int i = 1;
	puts("请输入想要查询的学生信息");
	scanf_s("%s", iq,20);
	pnew = phead;
	while (pnew != NULL)
	{
		if (strcmp(pnew->name, iq) == 0 || strcmp(pnew->id, iq) == 0)
		{
			puts("姓名\t学号");
			printf("%s\t", pnew->name);
			printf("%s\t", pnew->id);
			printf("\n");
			temp = pnew->clo;					//赋与temp子链表信息
			while (temp != NULL)
			{
				printf("科目%d: %s ", i, temp->title);
				printf("成绩: %d\t", temp->grade);
				if (i % 3 == 0 &&temp->next != NULL)
					printf("\n");
				i++;
				temp = temp->next;
			}
			puts("\n");
			break;
		}
		pnew = pnew->next;
	}
}

void Sort_message()
{
	int i, n = 0,b = 0, c = 0;
	Stu * pnext,*temp ,*tail,*last;
	tail = NULL;
	Clo * sonlast, *sontemp,*sonnew,*sonpre,*sonlink;
	char clouse[20];
	do
	{
		puts("请输入需要修改的选项");
		puts("1.按姓名排序");
		puts("2.按学号排序");
		puts("3.按单科成绩排序");
		puts("4.按同一个同学的所有科目成绩排序");
		puts("5.退出");
		scanf_s("%d", &i);
		switch (i)
		{
		case 1:
				//此法为交换数据
				//for (pre = phead; pre != NULL;  pre = pre->next) 
				//	for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
				//	{
				//		if (strcmp(pre->name, pnew->name)<0)			//姓名排序
				//		{
				//			temp = *pre;
				//			*pre = *pnew;
				//			*pnew = temp;
				//			temp.next = pre->next;
				//			pre->next = pnew->next;
				//			pnew->next = temp.next;
				//		}	
				//	}
			pnew = phead;
			pre = phead;
			last = NULL;

			while (pnew != last)
			{
				b = 0;
				while (pnew != NULL && pnew->next != last)
				{
					if (strcmp(pnew->name , pnew->next->name)<0)
					{
						temp = pnew->next;
						pnew->next = pnew->next->next;
						temp->next = pnew;
						if (b>0)			//第一次交换
							pre->next = temp;
						pre = temp;
						if (b == 0)			//维护头结点
							phead = pre;
					}
					else
					{
						pre = pnew;
						pnew = pnew->next;
					}
					b++;
					
				}
				last = pnew;			//设置成尾节点
				pnew = phead;
				pre = phead;
			}
			PrintMessage();
			break;
				case 2:
					pnew = phead;
					pre = phead;
					last = NULL;

					while (pnew != last)
					{
						b = 0;
						while (pnew != NULL && pnew->next != last)
						{
							if (strcmp(pnew->id, pnew->next->id)<0)
							{
								temp = pnew->next;
								pnew->next = pnew->next->next;
								temp->next = pnew;
								if (b>0)			//第一次交换
									pre->next = temp;
								pre = temp;
								if (b == 0)			//维护头结点
									phead = pre;
							}
							else
							{
								pre = pnew;
								pnew = pnew->next;
							}
							b++;
						}
						last = pnew;			//设置成尾节点，
						pnew = phead;			//下一次为n-1次
						pre = phead;
					}
					PrintMessage();
					break;
					case 3:
						puts("请输入需要排序的科目");							
						scanf_s("%s", clouse, 20);

						pnew = phead;
						while (pnew != NULL)		//遍历记录尾结点
						{
							if (pnew->next == NULL)
								tail = pnew;
							pnew = pnew->next;
						}

						for (pnew = phead; pnew != NULL; pnew = pnew->next)
						{
							sonnew = pnew->clo;
							sonpre = pnew->clo;
							sonlink = pnew->clo;			//记录原先首子链表头结点
							sonlast = NULL;

							while (sonnew != NULL)					//实现头结点与任意一节点交换，便于观察排列结果
							{
								if (strcmp(sonnew->title, clouse) == 0)
								{
									if (sonnew == pnew->clo)			//头节点
										break;
									else if(sonnew == pnew->clo->next)		//第二个节点
									{
										sonlink->next = sonnew->next;
										sonnew->next = sonlink;
										pnew->clo = sonnew;
									}
									else									//第三个及以上节点交换
									{
										sontemp = pnew->clo->next;
										pnew->clo->next = sonnew->next;
										sonpre->next = pnew->clo;
										sonnew->next = sontemp;
										pnew->clo = sonnew;
									}
									break;
								}
								sonpre = sonnew;
								sonnew = sonnew->next;
							}
							pre = pnew;
						}

						pnew = phead;
						pre = phead;
						last = NULL;

						while (pnew != last)
						{
							b = 0;
							while (pnew != NULL && pnew->next != last)
							{
								if (pnew->clo->grade < pnew->next->clo->grade &&strcmp(pnew->next->clo->title, clouse) == 0)
								{
									temp = pnew->next;
									pnew->next = pnew->next->next;
									temp->next = pnew;
									if (b>0)			//第一次交换
										pre->next = temp;
									pre = temp;
									if (b == 0)			//维护头结点
										phead = pre;
								}
								else											
								{
									pre = pnew;
									pnew = pnew->next;
								}
								b++;
							}
							last = pnew;			//设置成尾节点
							pnew = phead;
							pre = phead;
						}

						pnew = phead;
						while (pnew != NULL)
						{
							sontemp = pnew->clo;					//赋与temp子链表信息
							sonlink = pnew->clo;
							while (sontemp != NULL)
							{
								if (strcmp(sontemp->title,clouse) == 0)
								{
									puts("姓名\t学号\t");
									c = 1;
									printf("%s\t", pnew->name);
									printf("%s\t", pnew->id);
									printf("\n");

									while (sonlink != NULL)
									{
										printf("科目%d: %s ", c, sonlink->title);
										printf("成绩: %d\t", sonlink->grade);
										if (c % 3 == 0 && sonlink->next != NULL)
											printf("\n");
										c++;
										sonlink = sonlink->next;
									}
									printf("\n\n");
								}
								sontemp = sontemp->next;
							}
							pnew = pnew->next;
						}
						break;
		case 4:
			for (pre = phead;pre != NULL;pre = pre->next)
			{
				sonnew = pre->clo;
				sonpre = pre->clo;
				sonlast = NULL;

				while (sonnew != sonlast)
				{
					b = 0;
					while (sonnew != NULL && sonnew->next != sonlast)
					{
						if (sonnew->grade < sonnew->next->grade)
						{
							sontemp = sonnew->next;
							sonnew->next = sonnew->next->next;
							sontemp->next = sonnew;
							if (b>0)			//第一次交换
								sonpre->next = sontemp;
							sonpre = sontemp;
							if (b == 0)			//维护头结点
								pre->clo = sonpre;
						}
						else
						{
							sonpre = sonnew;
							sonnew = sonnew->next;
						}
						b++;
					}
					sonlast = sonnew;			//设置成尾节点
					sonnew = pre->clo;
					sonpre = pre->clo;
				}
			}
			PrintMessage();
			break;
		default:
			break;
		}
	} while (i>0 && i<5);
}

