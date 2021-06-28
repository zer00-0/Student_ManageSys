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
	puts("ѧ����Ϣ������������");
	printf("�������%d��ѧ��������",i);
	while (input(name, 20) != NULL &&name[0] != '\0')
	{
		pnew = (Stu *)malloc(sizeof(Stu));
		strcpy_s(pnew->name, name);
		printf("�������%d��ѧ��ѧ�ţ�",i);
		gets_s(pnew->id, 20);
		i++;
		if (temp == NULL)
			puts("���ǿո����������ͷ");
			
		pnew->clo = NULL;						//���������˼·���ȶ���һ����ʱ������ṹ�壬�븸��������ϵ��֮��ʹ�õݹ飨���Ƹ���������������
		pnew->clo = Add_sonlink(pnew->clo);		//�����������븸������ϵ����󷵻��������һ����ַ��Ϣ�������ػᶪʧ����			
												//
		printf("�������%d��ѧ����������س���������",i);
		pnew->size++;
		pre = temp;

		if (temp == NULL)
		{
			phead = pnew;				//phead��¼�˸������׽ڵ��ַ���Ժ�Ҫ��
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
	adress = fgets(st, n, stdin);		//����EOFʱ������NULL
	if (adress)
	{
		find = strchr(st, '\n');		//���һ��з��������˳�������ѭ��,����ʾNULL
		if (find)					//����ַ��NULL�����н��в���
			*find = '\0';
		else
			while (getchar() != '\0')
				continue;
	}
	return adress;
}

int menu()
{
	puts("�밴������ʾ��������");
	puts("1.��ӡѧ����Ϣ\n2.����ѧ����Ϣ");
	puts("3.�޸�ѧ����Ϣ\n4.��ѯѧ����Ϣ");
	puts("5.��ѧ����Ϣ��������\n6.�˳�");
	int choice;
	scanf_s("%d",&choice,1);
	switch (choice)
	{
	case 1:PrintMessage(); break;
	case 2:Add_Delmessage(); break;
	case 3:Change_message(); break;
	case 4:IQ_message(); break;
	case 5:Sort_message(); break;		//��������ͬ�Ĺ�����
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
		puts("û����������\n");
	else	
	{	
		pnew = phead;		//ָ��ͷ��㣬���ڱ���
		
		while (pnew != NULL)
		{
			puts("����\tѧ��\t");
			i = 1;
			printf("%s\t", pnew->name);
			printf("%s\t", pnew->id);
			printf("\n");
			temp = pnew->clo;					//����temp��������Ϣ
			while (temp != NULL)
			{
				printf("��Ŀ%d: %s ", i,temp->title);
				printf("�ɼ�: %d\t", temp->grade);
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
	char title[20] = "����";	
	char test[20] = {"end"};
	int i = 1;
	puts("������ѧ���γ���Ϣ");
	printf("�������Ŀ%d������:",i);
	scanf_s("%s",title,20);					//�����gets_sһ�����������,�����ϵ���ڴ档����һ�·��ֻ���Ҫgets_s�������¸��ַ�������
											//���淢��scanf_s��������Ҫһ��������Ϣ�����鳤�ȣ������Է�ֹ�ڴ�Խ��
	while (strcmp(title,test) != 0)		
	{
		clonew = (Clo *)malloc(sizeof(Clo));	
		strcpy_s(clonew->title, title);
		printf("�������Ŀ%d������",i);
		scanf_s("%d",&clonew->grade,4);
		fflush(stdin);					//scanf_s���������ʹ��ʱ������������ֹ������ң���������˼�������һ�������Ӱ�죬���Թ����α���
		clopre = temp;					//�ʲ������ϵõ������ַ�����1.scanf_s����%s\n��,i������\n,�����У�2.ʹ��fflush(stdin);
		if (temp == NULL)
		{
			temp = clonew;
			clonew->next = NULL;
			puts("������Ϊ���������ݼ����ͷ");
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
		printf("�������Ŀ%d����(������end����)��",i);
		scanf_s("%s", title, 20);
		fflush(stdin);
	}
	return temp;		//����������Ľڵ���Ϣ��һ��ʼû�з�����ɽڵ���ϢΪNULL
}

void Add_Delmessage()
{
	int choice;
	Stu *temp,*p,*q = NULL;
	char name[20],id[20];
	do
	{	
		puts("��������Ҫִ�е�ѡ��");
		puts("1.����ѧ����Ϣ");
		puts("2.ɾ��ѧ����Ϣ");
		puts("3.�˳�");
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
			puts("�������ӵ�ѧ����Ϣ");
			puts("������");
			scanf_s("%s",temp->name, 20);
			puts("ѧ�ţ�");
			scanf_s("%s", temp->id, 20);
			temp->clo = NULL;
			temp->clo = Add_sonlink(temp->clo);
			break;
		case 2:
			puts("��������Ҫɾ����ѧ��������ѧ��");
			scanf_s("%s", name, 20);
			p = phead;
			if (p->next == NULL)
			{
				free(p);
				pnew = NULL;
				printf("�ѳɹ�ɾ��%s��ѧ����Ϣ,��ֻ��һ��\n", name);

			}
			else
			{ 
				while (p!= NULL)
				{	
					
					if (strcmp(p->name ,name) == 0 || strcmp(p->id, name) == 0)		
					{
									
						if (p == phead)						//��һ���ڵ�
						{
							phead = p->next;
							free(p);
							puts("ɾ����һ���ڵ�ɹ�");
							
						}
						else if (p->next == NULL)			//���һ���ڵ�
						{					
							free(p);
							p = q;				//���ڵ�λ����ǰһ��
							p->next = NULL;
							puts("ɾ�����һ���ڵ�ɹ�");
						}
						else								//�м�ڵ�
						{
							q->next = p->next;
							free(p);
							printf("�ѳɹ�ɾ��%s��ѧ����Ϣ\n", name);
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

void Change_message()			//�޸�ѧ����Ϣ
{
	Clo *temp;
	int i = 1,j;
	char change[20];
	puts("������Ҫ�޸�ѧ����������ѧ��");
	scanf_s("%s", change, 20);
	pnew = phead;
	while (pnew != NULL)
	{
		if (strcmp(pnew->name, change) == 0 || strcmp(pnew->id, change) == 0)
		{
			puts("��ѯ��ѧ����ϢΪ��\n");
			puts("����\tѧ��");
			printf("%s\t", pnew->name);
			printf("%s\t\n", pnew->id);
			temp = pnew->clo;					//����temp��������Ϣ
			while (temp != NULL)
			{
				printf("��Ŀ%d: %s ", i, temp->title);
				printf("�ɼ�: %d\t", temp->grade);
				if (i % 3 == 0)
					printf("\t");
				i++;
				temp = temp->next;
			}
			puts("\n");
			
			do
			{
				puts("��������Ҫ�޸ĵ�ѡ��");
				puts("1.�޸�����");
				puts("2.�޸�ѧ��");
				puts("3.�޸ĳɼ�");
				puts("4.�˳�");
				scanf_s("%d", &j);
				switch (j)
				{
				case 1:
					puts("��������Ҫ�޸ĵ�����");
					scanf_s("%s", pnew->name, 20);
					break;
				case 2:
					puts("��������Ҫ�޸ĵ�ѧ��");
					scanf_s("%s", pnew->id, 20);
					break;
				case 3:
					temp = pnew->clo;
					i = 1;
					puts("��������Ҫ�޸ĵĿ�Ŀ");
					scanf_s("%s", change, 20);
					while (temp != NULL)
					{
						if (strcmp(temp->title, change) == 0)
						{
							puts("������ɼ�");
							scanf_s("%d", &temp->grade);
							printf("�ѳɹ����ĵ�%d��Ŀ�ɼ�", i);
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
			puts("����\tѧ��");
			printf("%s\t", pnew->name);
			printf("%s\t\n", pnew->id);
			temp = pnew->clo;					//����temp��������Ϣ
			while (temp != NULL)
			{
				printf("��Ŀ%d: %s ", i, temp->title);
				printf("�ɼ�: %d\t", temp->grade);
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
	puts("��������Ҫ��ѯ��ѧ����Ϣ");
	scanf_s("%s", iq,20);
	pnew = phead;
	while (pnew != NULL)
	{
		if (strcmp(pnew->name, iq) == 0 || strcmp(pnew->id, iq) == 0)
		{
			puts("����\tѧ��");
			printf("%s\t", pnew->name);
			printf("%s\t", pnew->id);
			printf("\n");
			temp = pnew->clo;					//����temp��������Ϣ
			while (temp != NULL)
			{
				printf("��Ŀ%d: %s ", i, temp->title);
				printf("�ɼ�: %d\t", temp->grade);
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
		puts("��������Ҫ�޸ĵ�ѡ��");
		puts("1.����������");
		puts("2.��ѧ������");
		puts("3.�����Ƴɼ�����");
		puts("4.��ͬһ��ͬѧ�����п�Ŀ�ɼ�����");
		puts("5.�˳�");
		scanf_s("%d", &i);
		switch (i)
		{
		case 1:
				//�˷�Ϊ��������
				//for (pre = phead; pre != NULL;  pre = pre->next) 
				//	for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
				//	{
				//		if (strcmp(pre->name, pnew->name)<0)			//��������
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
						if (b>0)			//��һ�ν���
							pre->next = temp;
						pre = temp;
						if (b == 0)			//ά��ͷ���
							phead = pre;
					}
					else
					{
						pre = pnew;
						pnew = pnew->next;
					}
					b++;
					
				}
				last = pnew;			//���ó�β�ڵ�
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
								if (b>0)			//��һ�ν���
									pre->next = temp;
								pre = temp;
								if (b == 0)			//ά��ͷ���
									phead = pre;
							}
							else
							{
								pre = pnew;
								pnew = pnew->next;
							}
							b++;
						}
						last = pnew;			//���ó�β�ڵ㣬
						pnew = phead;			//��һ��Ϊn-1��
						pre = phead;
					}
					PrintMessage();
					break;
					case 3:
						puts("��������Ҫ����Ŀ�Ŀ");							
						scanf_s("%s", clouse, 20);

						pnew = phead;
						while (pnew != NULL)		//������¼β���
						{
							if (pnew->next == NULL)
								tail = pnew;
							pnew = pnew->next;
						}

						for (pnew = phead; pnew != NULL; pnew = pnew->next)
						{
							sonnew = pnew->clo;
							sonpre = pnew->clo;
							sonlink = pnew->clo;			//��¼ԭ����������ͷ���
							sonlast = NULL;

							while (sonnew != NULL)					//ʵ��ͷ���������һ�ڵ㽻�������ڹ۲����н��
							{
								if (strcmp(sonnew->title, clouse) == 0)
								{
									if (sonnew == pnew->clo)			//ͷ�ڵ�
										break;
									else if(sonnew == pnew->clo->next)		//�ڶ����ڵ�
									{
										sonlink->next = sonnew->next;
										sonnew->next = sonlink;
										pnew->clo = sonnew;
									}
									else									//�����������Ͻڵ㽻��
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
									if (b>0)			//��һ�ν���
										pre->next = temp;
									pre = temp;
									if (b == 0)			//ά��ͷ���
										phead = pre;
								}
								else											
								{
									pre = pnew;
									pnew = pnew->next;
								}
								b++;
							}
							last = pnew;			//���ó�β�ڵ�
							pnew = phead;
							pre = phead;
						}

						pnew = phead;
						while (pnew != NULL)
						{
							sontemp = pnew->clo;					//����temp��������Ϣ
							sonlink = pnew->clo;
							while (sontemp != NULL)
							{
								if (strcmp(sontemp->title,clouse) == 0)
								{
									puts("����\tѧ��\t");
									c = 1;
									printf("%s\t", pnew->name);
									printf("%s\t", pnew->id);
									printf("\n");

									while (sonlink != NULL)
									{
										printf("��Ŀ%d: %s ", c, sonlink->title);
										printf("�ɼ�: %d\t", sonlink->grade);
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
							if (b>0)			//��һ�ν���
								sonpre->next = sontemp;
							sonpre = sontemp;
							if (b == 0)			//ά��ͷ���
								pre->clo = sonpre;
						}
						else
						{
							sonpre = sonnew;
							sonnew = sonnew->next;
						}
						b++;
					}
					sonlast = sonnew;			//���ó�β�ڵ�
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

