#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <Windows.h>
#define NAME_MAX 20 //宏定义   改成
#define Email_MAX 40
#define MAX 40
#define LEN sizeof(struct land)//有关登录系统的结构体

struct land//登录信息
{
	char account[MAX];
	char password[MAX];
	struct land* next;
};




// TODO:  在此处引用程序需要的其他头文件

