#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <Windows.h>
#define NAME_MAX 20 //�궨��   �ĳ�
#define Email_MAX 40
#define MAX 40
#define LEN sizeof(struct land)//�йص�¼ϵͳ�Ľṹ��

struct land//��¼��Ϣ
{
	char account[MAX];
	char password[MAX];
	struct land* next;
};




// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

