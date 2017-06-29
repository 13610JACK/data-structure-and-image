#pragma once
#include<iostream>
#include<stdio.h>
#include<ostream>
typedef void Linklistv;
using namespace std;
typedef struct Linklistnode
{
	//int a;
	struct Linklistnode * next;
}Linklistnode;
Linklistv * Linklist_Create();
void Linklist_Clear(Linklistv * list);
void Linklist_Destory(Linklistv * list);
int Linklist_Length(Linklistv * list);
Linklistnode* Linklist_Delete(Linklistv * list,int pos);
Linklistv * Linklist_Insert(Linklistv * list,Linklistnode* node,int pos );
Linklistv * Linklist_Get(Linklistv * list , int pos);

