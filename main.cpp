#include "head.h"
#include <stdio.h>  
#include <stdlib.h>
#include<string.h> 
#include<ctype.h>
#include<conio.h>
#include<Windows.h>
#define MAX 40//宏定义
typedef struct people   //定义变量联系人
{
	char Name[MAX];       //定义姓名
	int age;
	char Gender[5];
	char Email[MAX];
	char Mobilephonenum[MAX];
	struct people* pNext;   //定义指针域
} people_t;
int find(char*, char);
void writetext(people_t*, char*);
people_t* localize(people_t*, char*);
people_t* localnum(people_t*, int);
int getindex(people_t*, char*);
people_t* deletepeople(people_t*, char*);
void editpeople1(people_t*, char*);
void editpeople2(people_t*, int);
void editpeople3(people_t*, char*);
void editpeople4(people_t*, char*);
void editpeople5(people_t*, char*);
int checkname(char*, people_t*);
int checkgender(char*);
void outputpreinfor(people_t*);
void outputallinfor(people_t*);
people_t* rankdown(people_t*);
people_t* rankup(people_t*);
int countpeonum(people_t*);
char* login();
static int count = 0;



int main()
{   system("color 1F");
	FILE* fp = NULL;
	char account[MAX];
	strcpy(account, login());
	if (strcmp(account, "null") == 0)
		exit(0);
	people_t* Head = NULL;//
	people_t* Now;
	people_t* target;
	people_t* prep;

	char str[7];
	int p;
	int index = 1;
	int num1, num2, num3, num5, checknum, ranknum, lnum;//选择功能用的数字
	int flag = 0;//
	int num4 = 0;
	char c = '@';
	char name[MAX];//查找时用的参数
	char information[MAX];//修改为的参数
	char email[MAX];//电子邮件参数
	char gender[5];// 性别参数
	char phonenum[MAX];//查找时用的参数
	people_t people1;//定义要输入的变量
	strcat(account, ".txt");
	//sprintf(account, "%s.txt", account);
	fp = fopen(account,"a+");
	while (feof(fp) == 0)
	{
		if (Head == NULL)
		{
			Head = (people_t*)malloc(sizeof(people_t));
			fread(Head, sizeof(people_t), 1, fp);
			Now = Head;
			Now->pNext = NULL;
			num4 = num4 + 1;
		}
		else
		{
			//Now = NULL;
			Now->pNext = (people_t*)malloc(sizeof(people_t));
			fread(Now->pNext, sizeof(people_t), 1, fp);
			Now = Now->pNext;
			Now->pNext = NULL;//
			num4 = num4 + 1;
		}


	}


	fclose(fp);//after processing, close the file
	if (num4 == 1) { free(Head); Head = NULL; }
	else {
		Now = Head;
		for (num5 = 1; num5<num4 - 1; num5++)
		{
			Now = Now->pNext;
		}
		free(Now->pNext);
		Now->pNext = NULL;
	}
	while (flag == 0) {
		system("cls");
		system("date/T");
		system("time/T");
		system("color 1F");
		num1 = countpeonum(Head);
		printf("\t\t\t\tYou have %d contacts\n", num1);
		printf("\t\t\t***please choose the founction*****\n");
		printf("\t\t\t***************************\n");
		printf("\t\t\t***  0.Exit              *****\n");
		printf("\t\t\t***  1.Add contact       *****\n");
		printf("\t\t\t***  2.View all contacts *****\n");
		printf("\t\t\t***  3.Find contact      *****\n");
		printf("\t\t\t***  4.delete conatct    *****\n");
		printf("\t\t\t***  5.edit contact      *****\n");
		printf("\t\t\t***  6.rank              *****\n");
		scanf("%d", &num2);
		switch (num2)
		{
		case 0:
			writetext(Head, account);
			flag = 2;
			break;

		case 1: //创建联系人
			people_t* pNode;
			pNode = (people_t*)malloc(sizeof(people_t)); //ask for the reserved memory space for a node
			system("cls");
			printf("please input name");
			scanf("%s", pNode->Name);
			checknum = checkname(pNode->Name, Head);
			while (getchar() != '\n');
			while (checknum != 0)
			{
				printf("there has same name, rewrite\n");
				scanf("%s", pNode->Name);
				checknum = checkname(pNode->Name, Head);
			}
			printf("name valid\n");
			printf("please input age (number)");
			scanf("%d", &pNode->age);
			while (getchar() != '\n');
			printf("please input gender(man/woman)");
			scanf("%s", pNode->Gender);
			checknum = checkgender(pNode->Gender);
			while (checknum == 0)
			{
				printf("not valid\n");
				scanf("%s", pNode->Gender);
				checknum = checkgender(pNode->Gender);
			}
			printf("success\n");
			while (getchar() != '\n');
			printf("please input e-mail（needs @）");
			scanf("%s", pNode->Email);
			p = find(pNode->Email, c);
			while (p != 1)
			{
				printf("please input right e-mail！");
				scanf("%s", pNode->Email);
				p = find(pNode->Email, c);
			}
			while (getchar() != '\n');
			printf("please input telephonenumber");
			scanf("%s", pNode->Mobilephonenum);
			while (getchar() != '\n'); //可以添加一个是否添加的界面
			system("cls");
			outputpreinfor(pNode);
			printf("Add?\n1.Y\n2.N\n");
			scanf("%d", &num2);
			if (num2 == 1)
			{
				pNode->pNext = Head;
				Head = pNode;
				printf("sucess\n");
				writetext(Head, account);
			}
			printf("back to the main menu?\n1.Y\n2.N\n");
			scanf("%d", &num2);
			if (num2 == 1)
			{
				flag = 0;
				system("cls");
				break;
			}
			else flag = 2;
			break;
		case 2:
			if (Head == NULL)
			{
				printf("Address book is NULL, please add first");
				while (getchar() != '\n');
				while (getchar() != '\n');
				break;
			}
			else
			{
				outputallinfor(Head);
				while (getchar() != '\n');
				printf("edit contact?\n1.Y\n2.N\n");
				scanf("%d", &num1);
				if (num1 == 1)
				{
					printf("choose the contact number");
					scanf("%d", &num1);
					prep = localnum(Head, num1);
					while (prep == NULL)
					{
						printf("no more contacts please rewrite\n");
						scanf("%d", &lnum);
						prep = localnum(Head, num1);
					}
					system("cls");
					outputpreinfor(prep);
					printf("0.exit\n1.edit\n2.delete\n");
					scanf("%d", &num1);
					switch (num1)
					{
					case 0:
						break;
					case 1:
						printf("input edit which information\n1.name\n2.gender\n3.age\n4.e-mail\n5.telephonenumber\n");
						scanf("%d", &num2);
						switch (num2)
						{
						case 1:
							printf("edit name to");
							scanf("%s", name);
							checknum = checkname(name, Head);
							while (getchar() != '\n');
							while (checknum != 0)
							{
								printf("there has same name, rewrite\n");
								scanf("%s", name);
								checknum = checkname(name, Head);
							}
							printf("name valid\n");
							editpeople1(prep, name);
							printf("success");
							writetext(Head, account);
							break;
						case 2:
							printf("edit gender to");
							scanf("%s", name);
							editpeople3(prep, name);
							printf("success");
							writetext(Head, account);
							break;
						case 3:
							printf("edit age to");
							scanf("%d", &num3);
							editpeople2(prep, num3);
							printf("success");
							writetext(Head, account);
							break;
						case 4:
							printf("edit e-mail to");
							scanf("%s", name);
							editpeople4(prep, name);
							printf("success");
							writetext(Head, account);
							break;
						case 5:
							printf("edit telephonenumber to");
							scanf("%s", name);
							editpeople5(prep, name);
							printf("success");
							writetext(Head, account);
							break;
						}
						break;
					case 2:
						printf("delete?\n1.Y\n2.N\n");
						scanf("%d", &num1);
						if (num1 == 1) {
							Head = deletepeople(Head, prep->Name);
							writetext(Head, account);
							printf("success");
						}
						break;
					}

				}
				else system("cls");
				break;
			}
		case 3:
			printf("please input the target name or telephonenumber");
			scanf("%s", information);
			checknum = checkname(information, Head);
			while (getchar() != '\n');
			while (checknum == 0)
			{
				printf("don't have this person, rewrite\n");
				scanf("%s", information);
				checknum = checkname(information, Head);
			}
			target = localize(Head, information);
			outputpreinfor(target);
			while (getchar() != '\n');
			break;

		case 4:
			if (Head == NULL)
			{
				printf("Address book is NULL, please add first");
				while (getchar() != '\n');
				while (getchar() != '\n');
				break;
			}
			else
			{
				outputallinfor(Head);
				printf("delete according to\n1.name\n2.serial number\n0.back to main menu\n");
				scanf("%d", &num2);
				switch (num2)
				{
				case 1:
					printf("please input name");
					scanf("%s", information);
					checknum = checkname(information, Head);
					while (getchar() != '\n');
					while (checknum == 0)
					{
						printf("not have this person rewrite\n");
						scanf("%s", information);
						checknum = checkname(information, Head);
					}
					printf("delete?\n1.Y\n2.N\n");
					scanf("%d", &num2);
					if (num2 == 1)
					{
						Head = deletepeople(Head, information);
						printf("success");
						writetext(Head, account);
						break;
					}
					else
						break;
				case 2:
					printf("please input serial number");
					scanf("%d", &num2);
					target = localnum(Head, num2);
					if (target == NULL)
						printf("don't have so many contacts");
					else
						printf("delete?\n1.Y\n2.N\n");
					scanf("%d", &num2);
					if (num2 == 1)
					{
						Head = deletepeople(Head, target->Name);
						printf("success");
						writetext(Head, account);
						break;
					}
					else
						break;
				case 0:
					break;
				}
				if (num2 != 0) {
					printf("back to main meun?\n1.Y\n2.N\n");
					scanf("%d", &num2);
					if (num2 == 1)
					{
						flag = 0;
						system("cls");
						break;
					}
					else flag = 2;
					break;
				}
				else system("cls");
				break;
			}
		case 5:
			if (Head == NULL)
				printf("Address book is NULL, please add first");
			else
			{
				outputallinfor(Head);
				printf("please input the name");
				scanf("%s", information);
				checknum = checkname(information, Head);
				while (getchar() != '\n');
				while (checknum == 0)
				{
					printf("Without this contact, please re-enter your first name\n");
					scanf("%s", information);
					checknum = checkname(information, Head);
				}
				target = localize(Head, information);
				printf("which information to edit:\nname：%s\n gender：%s\n gender：%d\n e-mail：%s\n telephonenumber：%s\n ", target->Name, target->Gender, target->age, target->Email, target->Mobilephonenum);
				printf("input the information\n1.name\n2.gender\n3.age\n4.e-mail\n5.telephonenumber\n");
				scanf("%d", &num2);
				switch (num2)
				{
				case 1:
					printf("edit name to");
					scanf("%s", name);
					checknum = checkname(name, Head);
					while (getchar() != '\n');
					while (checknum != 0)
					{
						printf("已有相同联系人，请重新输入名字\n");
						scanf("%s", name);
						checknum = checkname(name, Head);
					}
					printf("name valid\n");
					editpeople1(target, name);
					printf("success");
					writetext(Head, account);
					break;
				case 2:
					printf("edit gender to");
					scanf("%s", name);
					editpeople3(target, name);
					printf("修改成功");
					writetext(Head, account);
					break;
				case 3:
					printf("edit age to");
					scanf("%d", &num3);
					editpeople2(target, num3);
					printf("success");
					writetext(Head, account);
					break;
				case 4:
					printf("edit e-mail to");
					scanf("%s", name);
					editpeople4(target, name);
					printf("success");
					writetext(Head, account);
					break;
				case 5:
					printf("edit telephonenumber to");
					scanf("%s", name);
					editpeople5(target, name);
					printf("success");
					writetext(Head, account);
					break;
				}
			}
			printf("back to main menu\n1.Y\n2.N\n");
			scanf("%d", &num2);
			if (num2 == 1)
			{
				flag = 0;
				system("cls");
				break;
			}
			else flag = 2;
			break;
		case 6:

			//都没调用砸出结果
			while (1)
			{
				printf("1.rankup\n2.rankdown");
				scanf("%d", &ranknum);
				if (ranknum == 1)
				{
					Head = rankup(Head);
					break;
				}
				else if (ranknum == 2)
				{
					Head = rankdown(Head);
					break;
				}
				else
				{
					printf("serial number is wrong please rewrite：");
					Sleep(1000);
				}
			}
			outputallinfor(Head);
			printf("back to main menu\n1.Y\n2.N\n");
			scanf("%d", &num2);
			if (num2 == 1)
			{
				flag = 0;
				system("cls");
				break;
			}
			else flag = 2;
			break;
		}
	}


}

void writetext(people_t* head, char* account)
{
	FILE* fp = fopen(account, "w");
	people_t* now;
	for (now = head; now != NULL; now = now->pNext)
		fwrite(now, sizeof(people_t), 1, fp);
	fclose(fp);


}

people_t* localize(people_t* head, char* information)
{

	people_t* pTemp;//定义临时指针
	pTemp = head;

	while (pTemp != 0) //当临时指针不等于空值，也就是最多输出到链表到最后一个元素 
	{
		if (strcmp(pTemp->Name, information) == 0 || (strcmp(pTemp->Mobilephonenum, information)) == 0)//说明找到联系人
		{
			break;
		}
		else
			pTemp = pTemp->pNext;
		//移动临时指针到下一个元素
	}
	return(pTemp);
}
people_t* deletepeople(people_t* head, char* inforamtion)
{
	people_t* pTemp = NULL;//定义临时指针
	people_t* pr = NULL;
	int index = 1;//链表中该元素的序号
	int i;
	if (head == NULL)
	{
		printf("没有联系人！\n");
	}

	pTemp = head;
	while (pTemp != 0) //当临时指针不等于空值，也就是最多输出到链表到最后一个元素
	{
		if (strcmp(pTemp->Name, inforamtion) == 0 || (strcmp(pTemp->Mobilephonenum, inforamtion)) == 0)//说明找到联系人
		{
			if (pTemp == head)
			{
				head = pTemp->pNext;
			}
			else
			{
				pr = head;
				for (i = 1; i<index - 1; i++)
					pr = pr->pNext;
				pr->pNext = pTemp->pNext;
			}
			free(pTemp);     // 释放已删除节点的内存 
			break;
		}
		else
		{
			pTemp = pTemp->pNext;//移动临时指针到下一个元素
			index++;
		}
	}
	return(head);
}

void editpeople1(people_t* p, char* name)//编辑联系人      姓名
{
	strcpy(p->Name, name);//赋予name字段新值
}
void editpeople2(people_t* p, int age)  //年龄
{
	p->age = age;
}
void editpeople3(people_t* p, char* sex) //性别
{
	strcpy(p->Gender, sex);
}
void editpeople4(people_t*p, char* email) //email
{
	strcpy(p->Email, email);
}
void editpeople5(people_t*p, char* num)   //电话号
{
	strcpy(p->Mobilephonenum, num);
}



int find(char *s, char c)
{
	char *x = s;
	int num = 0;
	for (x = s; *x != 0; x++)
	{
		if (*x == c)
		{
			num++;

		}
	}
	return num;
}
int checkname(char*s, people_t* head) {
	int i = 0;
	people_t* now;
	for (now = head; now != NULL; now = now->pNext)
	{
		if (strcmp(now->Name, s) == 0)
			i++;
	}
	return i;

}

int checkgender(char*s)
{
	int i = 0;
	if (strcmp(s, "man") == 0 || strcmp(s, "woman") == 0)
		i = 1;
	return i;

}
void outputpreinfor(people_t* now)
{
	printf("Name %s\n", now->Name);
	printf("age %d\n", now->age);
	printf("Gender %s\n", now->Gender);
	printf("Mobilephonenum %s\n", now->Mobilephonenum);
	printf("Email %s\n", now->Email);
}
void outputallinfor(people_t*head) {
	people_t* now;
	int i = 1;
	if (head == NULL)
		printf("none");
	else
		for (now = head; now != NULL; now = now->pNext)
		{
			printf("%d\nname%s\n", i, now->Name);
			printf("age%d\n", now->age);
			printf("gender%s\n", now->Gender);
			printf("e-mail%s\n", now->Email);
			printf("telephonenumber%s\n", now->Mobilephonenum);
			printf("\n");
			i++;
		}
}

people_t* rankup(people_t* head)//按首字母升序
{
	people_t* cur, *tail;
	cur = head;
	tail = NULL;
	if (cur == NULL || cur->pNext == NULL) {
		return head;
	}
	while (cur != tail) {
		while (cur->pNext != tail) {
			if (strcmp(cur->Name, cur->pNext->Name)<0) {
				int temp = cur->age;
				cur->age = cur->pNext->age;
				cur->pNext->age = temp;
				char ct[MAX];
				strcpy(ct, cur->Name);
				strcpy(cur->Name, cur->pNext->Name);
				strcpy(cur->pNext->Name, ct);

				char G[5];
				strcpy(G, cur->Gender);
				strcpy(cur->Gender, cur->pNext->Gender);
				strcpy(cur->pNext->Gender, G);

				strcpy(ct, cur->Email);
				strcpy(cur->Email, cur->pNext->Email);
				strcpy(cur->pNext->Email, ct);

				strcpy(ct, cur->Mobilephonenum);
				strcpy(cur->Mobilephonenum, cur->pNext->Mobilephonenum);
				strcpy(cur->pNext->Mobilephonenum, ct);

			}
			cur = cur->pNext;
		}
		tail = cur;
		cur = head;
	}
	return head;

}
people_t* rankdown(people_t*head)//按首字母降序
{
	people_t* cur, *tail;
	cur = head;
	tail = NULL;
	if (cur == NULL || cur->pNext == NULL) {
		return head;
	}
	while (cur != tail) {
		while (cur->pNext != tail) {
			if (strcmp(cur->Name, cur->pNext->Name)>0) {
				int temp = cur->age;
				cur->age = cur->pNext->age;
				cur->pNext->age = temp;
				char ct[MAX];
				strcpy(ct, cur->Name);
				strcpy(cur->Name, cur->pNext->Name);
				strcpy(cur->pNext->Name, ct);

				char G[5];
				strcpy(G, cur->Gender);
				strcpy(cur->Gender, cur->pNext->Gender);
				strcpy(cur->pNext->Gender, G);

				strcpy(ct, cur->Email);
				strcpy(cur->Email, cur->pNext->Email);
				strcpy(cur->pNext->Email, ct);

				strcpy(ct, cur->Mobilephonenum);
				strcpy(cur->Mobilephonenum, cur->pNext->Mobilephonenum);
				strcpy(cur->pNext->Mobilephonenum, ct);

			}
			cur = cur->pNext;
		}
		tail = cur;
		cur = head;
	}
	return head;

}
people_t* localnum(people_t* head, int index)//根据位置获取结构体
{
	people_t* now;
	people_t* now1;
	int i, n;
	now = head;
	now1 = head;
	for (n = 0; now1 != NULL; now1 = now1->pNext)
		n++;
	if (index <= n)
	{
		for (i = 1; i<index; i++)
			now = now->pNext;
		return now;
	}
	else
		return NULL;

}
int getindex(people_t* head, char* name)//根据名字获取该联系人在链表中的位置
{
	people_t* now;
	int n = 1;
	if (head == NULL)
		return 0;
	else {
		for (now = head; strcmp(now->Name, name) != 0; now = now->pNext)
			n++;
		return n;
	}
}
int countpeonum(people_t* head)
{
	int  i = 0;
	people_t* now;
	for (now = head; now != NULL; now = now->pNext)
		i++;
	return i;
}


// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//


char* login()//登录成功返回1，登录失败返回0
{
	int select = 0, i = 0;
	char name[MAX], fname[MAX], password[MAX], fpassword[MAX];
	FILE* fp1;
	//读文件 建立链表
	land* p = NULL, *lhead = NULL;
	fp1 = fopen("login.txt", "a+");
	while (feof(fp1) == 0)//将文件中的数据弄成链表,当文件中有东西时执行
	{
		if (lhead == NULL)
		{
			lhead = (land*)malloc(sizeof(land));
			fscanf(fp1, "%s %s", lhead->account, lhead->password);
			lhead->next = NULL;
		}
		else
		{
			p = (land*)malloc(sizeof(land));
			//Now->pNext = Head;
			fscanf(fp1, "%s %s", p->account, p->password);
			p->next = lhead;
			lhead = p;
		}


	}
	fclose(fp1);

	while (1)
	{   system("cls");
		system("date/T");
		system("time/T");
		printf("\t\t\t***Welcome to the address book mangement    *****\n");
		printf("\t\t\t***  1.log in                               *****\n");
		printf("\t\t\t***  2.register                             *****\n");
		printf("\t\t\t***  3.modify the password                  *****\n");
		printf("\t\t\tplease choose:");
		scanf("%d", &select);
		if (select == 1)
		{
			//登录
			while (1)
			{
				system("cls");
				printf("Welcome to the address book mangement\nplease input your account：");
				scanf("%s", name);
				printf("please input your password：");
				char pass[LEN + 1];
				memset(pass, NULL, LEN + 1);
				char ch;
				if (count == 0) {
					int inputLength = 0;
					ch = _getch();
					while (isprint(ch)) {
						if (ch != ' ') {
							putchar('*');
							pass[inputLength] = ch;
							inputLength++;
							ch = _getch();
						}
						if (!isprint(ch))
							break;
						if (inputLength == LEN)
							break;
					}
					password[13] = pass[13];
					printf("\n");
					printf("what you have just input is: %s\n", pass);
			

					}
				p = lhead->next;
				while (p != NULL)
				{
					i = 0;
					if (strcmp(p->account, name) == 0)
					{
						i = 1;
						break;
					}
					p = p->next;
				}

				if (i == 1)
				{
					if (strcmp(p->account, name) == 0 && strcmp(p->password, password) == 0)
					{
						p = lhead->next;
						fp1 = fopen("login.txt", "w");
						while (p != NULL)
						{
							fprintf(fp1, "%s %s\n", p->account, p->password);
							p = p->next;
						}
						fclose(fp1);
						printf("success!");
						Sleep(1000);

						return name;
					}
					else {
						printf("account doesn't match with the password,please rewite");
						Sleep(1000);
					}
				}
				else
				{
					printf("don't find this account register now？(Y/N)");
					getchar();
					char c;
					scanf("%c", &c);
					if (c == 'y' || c == 'Y')
					{
						system("cls");
						printf("Welcome to the address book mangement\nplease input your account");
						scanf("%s", name);
						printf("please input your password:");
						scanf("%s", password);
						char lpassword[MAX];
						while (true)
						{
							printf("please input your password again：");
							scanf("%s", lpassword);
							if (strcmp(lpassword, password) == 0)
							{
								if (lhead->next == NULL)
								{
									p = lhead;
								}
								else {
									p = lhead->next;
									while (p->next != NULL) { p = p->next; }//找到为节点
								}
								p->next = (land*)malloc(sizeof(land));
								strcpy(p->next->account, name);
								strcpy(p->next->password, password);
								p->next->next = NULL;
								printf("success");
								Sleep(1000);
								system("cls");
								break;
							}
							else {
								printf("The password entered twice is different. Please re-enter it：");
								scanf("%s", password);
							}
						}

					}
					else {
						printf("failed");
						return "null";
					}
				}
			}
			break;
		}
		else if (select == 2)
		{
			while (1)
			{
				system("cls");
				printf("Welcome to the address book mangement\nplease input your account：");
				scanf("%s", name);
				p = lhead->next;
				while (p != NULL)
				{
					i = 0;
					if (strcmp(p->account, name) == 0)
					{
						i = 1;
						break;
					}
					p = p->next;
				}
				if (i == 1)
				{
					printf("The user you entered exist already. Please re-enter。");
					Sleep(1000);
				}
				else {
					break;
				}

			}

			printf("please input your password:：");
			scanf("%s", password);

			char lpassword[MAX];
			while (1)
			{
				printf("please input your password again：");
				scanf("%s", lpassword);
				if (strcmp(lpassword, password) == 0)
				{
					if (lhead->next == NULL)
					{
						p = lhead;
					}
					else {
						p = lhead->next;
						while (p->next != NULL) { p = p->next; }//找到为节点
					}
					p->next = (land*)malloc(sizeof(land));
					strcpy(p->next->account, name);
					strcpy(p->next->password, password);
					p->next->next = NULL;
					printf("success");
					Sleep(1000);
					system("cls");
					break;
				}
				else {
					printf("The passwords entered twice are different. Please re-enter them：");
					scanf("%s", password);
				}
			}
			//break;
		}
		else if (select == 3)//修改密码
		{
			while (1)
			{
				system("cls");
				printf("welcome to modify the password\n");
				printf("pleas your account");
				scanf("%s", name);
				p = lhead->next;
				while (p != NULL)
				{
					if (strcmp(p->account, name) == 0)
					{
						break;
					}
					p = p->next;
				}
				if (p != NULL)
				{
					while (1)
					{
						char lp[MAX];
						printf("please input your old password");
						scanf("%s", password);
						if (strcmp(password, p->password) != 0)
						{
							printf("your old password is wrong rewrite\n");
							Sleep(1000);
							continue;
						}
						break;
					}
					printf("please input your new password：");
					scanf("%s", password);
					char lpassword[MAX];
					while (true)
					{
						printf("please input your new password again：");
						scanf("%s", lpassword);
						if (strcmp(lpassword, password) == 0)
						{
							strcpy(p->password, password);
							printf("suceess");
							Sleep(1000);
							system("cls");
							break;
						}
						else {
							printf("The passwords entered twice are different. Please re-enter them：");
							scanf("%s", password);
						}
					}
					break;

				}
				else
				{
					printf("The user you entered does not exist. Please re-enter");
				}

			}
		}
		else {
			//setbuf(stdin, NULL); 
			getchar();
			printf("the serial number is wrong please rewrite");
			Sleep(500);
			system("cls");
		}
	}

}
