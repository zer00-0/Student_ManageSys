#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Nsize 10
#define Gsize 7

void Print_message();		//��ӡ��Ϣ������/ȫ����
void Add_Del();				//��ɾѧ����Ϣ	
void Change_message();		//�޸�ѧ����Ϣ
void Sore_message();		//��ѧ����Ϣ������������/ѧ��/���Ƴɼ���
void IQ_message();			//��ѯѧ����Ϣ
char * input(char * st, int n);//����ѧ����Ϣ
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
	//�ռ�ѧ����Ϣ
	printf("������ѧ��������");
	while (input(name, Nsize) != NULL && name[0] != '\0')
	{
		current = (struct message*)malloc(sizeof(struct message));
		if (head == NULL)
			head = current;			//��ͷ���
		else
			front->next = current;
		current->next = NULL;
		strcpy_s(current->Stu.title, name);
		printf("������ѧ�ţ�");
		gets_s(current->Stu.ID,10);
		printf("�����룺�༶�����ġ���ѧ��Ӣ�������ѧ������ɼ�\n");
		for (i = 0; i<Gsize; i++)
		{
			printf("       ");
			scanf_s("%d", &current->Stu.grade[i]);
		}
		while (getchar() != '\n')			//���벻Ϊ���У�����ǰһ��while����ִ��
			continue;
		printf("��������һ��ѧ����������һ�н�������");
		front = current;
	}
	do
	{
		printf("��������Ӧ��ţ�\n");
		printf("1.��ӡѧ����Ϣ��\n");
		printf("2.��ɾѧ����Ϣ��\n");
		printf("3.�޸�ѧ����Ϣ��\n");
		printf("4.��ѧ����Ϣ��������\n");
		printf("5.��ѯѧ����Ϣ��\n");
		printf("6.�˳�\n");
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

void Print_message()		//��ӡȫ��ѧ����Ϣ
{
	if (current->Stu.title == '\0' || current == NULL)
		printf("û���������ݡ�\n");
	else
	{
		printf("����\tѧ��\t�༶\t����\t��ѧ\tӢ��\t����\t��ѧ\t����ɼ�\n");
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
	printf("��������Ҫ��ѯ��ѧ��������ѧ��\n");
	scanf_s("%s", iq);
	current = head;
	while (current != NULL)
	{
		if (strcmp(iq, current->Stu.title) == 0 || strcmp(iq, current->Stu.ID) == 0)
		{
			printf("����\tѧ��\t�༶\t����\t��ѧ\tӢ��\t����\t��ѧ\t����ɼ�\n");
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
		printf("��������Ҫ���������\n");
		printf("1.����ѧ����Ϣ\n");
		printf("2.ɾ��ѧ����Ϣ\n");
		printf("3.�˳�\n");
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
			printf("������ѧ��������");
			scanf_s("%s", p->Stu.title);
			printf("������ѧ�ţ�");
			scanf_s("%s", &p->Stu.ID);
			printf("�����룺�༶�����ġ���ѧ��Ӣ�������ѧ������ɼ�\n");
			for (i = 0; i<Gsize; i++)
			{
				printf("       ");
				scanf_s("%d", &p->Stu.grade[i]);
			}
			while (getchar() != '\n')			//���벻Ϊ���У�����ǰһ��while����ִ��
				continue;
		}
		else if (i == 2)
		{
			p = current;
			printf("��������Ҫɾ����ѧ��������ѧ��\n");
			scanf_s("%s", &j);
			if (p->next == NULL)			//��ֻ��һ�����ݣ������һ��ֱ����յ�ǰ����
			{
				free(p);
				current = NULL;
				printf("�ѳɹ�ɾ��%s��ѧ����Ϣ,��ֻ��һ��\n", j);
			}
			else
			{
				while (p != NULL)
				{
					if (strcmp(j, p->Stu.title) == 0 || strcmp(j, p->Stu.ID) == 0)
					{
						q->next = p->next;
						free(p);
						printf("�ѳɹ�ɾ��%s��ѧ����Ϣ\n", j);
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

	printf("��������Ӧ���\n");
	printf("1.��������������\n");
	printf("2.��ѧ�Ž�������\n");
	printf("3.�����Ƴɼ���������\n");
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
		for (pre = head; pre != NULL; pre = pre->next)
			for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
			{
				if (strcmp(pre->Stu.title, pnew->Stu.title)<0)			//��������
				{
					temp= pre->Stu;				//������������������
					pre->Stu = pnew->Stu;
					pnew->Stu = temp;

					//temp->next = pre->next;		//����ָ����
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
					temp = pre->Stu;				//������������������
					pre->Stu = pnew->Stu;
					pnew->Stu = temp;

					//temp->next = pre->next;		//����ָ����
					//pre->next = pnew->next;
					//pnew->next = temp->next;
				}
			}
		Print_message();
		break;
	case 3:
		printf("�����Ƴɼ�����\n");
		printf("1.����\n2.��ѧ\n3.Ӣ��\n4.����\n5.��ѧ\n6.����\n");				//������һЩ���⣬��Ҫ�޸�
		scanf_s("%d", &j);
		
		for (pre = head; pre != NULL; pre = pre->next)
			for (pnew = pre->next; pnew != NULL; pnew = pnew->next)
			{
				if (pre->Stu.grade[j]<pnew->Stu.grade[j])		//��Ϊǰ���а༶�������ŵڶ�
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
	printf("��������Ҫ�޸���Ϣ��ѧ��������ѧ��\n");
	scanf_s("%s", change_ID);
	current = head;
	while (current != NULL)
	{
		if (strcmp(change_ID, current->Stu.title) == 0 || strcmp(change_ID, current->Stu.ID) == 0)
		{
			p = (struct message *)malloc(sizeof(struct message));
			printf("������������");
			scanf_s("%s", p->Stu.title);
			strcpy_s(current->Stu.title, p->Stu.title);
			printf("������ѧ�ţ�");
			scanf_s("%s", p->Stu.ID);
			strcpy_s(current->Stu.ID, p->Stu.ID);
			printf("������༶�����ġ���ѧ��Ӣ�������ѧ������ɼ���\n");
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