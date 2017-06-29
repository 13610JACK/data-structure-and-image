#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"linklist.h"
typedef struct Tlinklist
{
	Linklistnode head;
	int length;
}Tlinklist;
Linklistv * Linklist_Create()
{
	Tlinklist * list = NULL;
	list = (Tlinklist *)malloc(sizeof(Tlinklist));
	if (list == NULL)
	{
		cout << "create list is error:" << endl;
		return NULL;
	}
	memset(list, 0, sizeof(Tlinklist));
	list->head.next = NULL;
	list->length = 0;
	return list;
};
void Linklist_Clear(Linklistv * list)
{
	Tlinklist * temp = NULL;
	temp = (Tlinklist *)list;
	if (list == NULL)
	{
		cout << "list is not exit:error" << endl;
		return;
	}
	temp->head.next = NULL;
	temp->length = 0;
};
void Linklist_Destory(Linklistv * list)
{
	Tlinklist * temp = NULL;
	temp = (Tlinklist *)list;
	if (temp != NULL)
	{
		free(temp);
	}
	return;
};
int Linklist_Length(Linklistv * list)
{
	Tlinklist * temp = NULL;
	temp = (Tlinklist*)list;
	if (list == NULL || temp->length < 0)
	{
		cout << "list is err" << endl;
		return -1;
	}
	return temp->length;
};
Linklistnode* Linklist_Delete(Linklistv * list, int pos)
{
	Tlinklist * temp = NULL;
	temp = (Tlinklist*)list;
	if (temp == NULL || pos < 0 || temp->length < 0)
	{
		cout << "£å£ò£ò£ï£ò" << endl;
		return NULL;
	}
	Linklistnode * current = NULL;
	current = &(temp->head);
	for (int i = 0; i < (pos)&&(current->next != NULL); i++)
	{
		current = current->next;
	}
	Linklistnode * tem = NULL;
	tem = current->next;
	current->next = tem->next;
	temp->length--;
	return tem;
};
void * Linklist_Insert(Linklistv * list, Linklistnode * node, int pos)
{
	Tlinklist * temp = NULL;
	temp = (Tlinklist *)list;
	if (temp == NULL)
	{
		return NULL;
	}
	Linklistnode * current = NULL;
	current = &(temp->head);
	for (int i = 0; i < pos && (current->next != NULL); i++)
	{
		current = current->next;
	}
	node->next = current->next;
	current->next = node;
	temp->length++;
	return NULL;
};
Linklistv * Linklist_Get(Linklistv * list, int pos)
{
	Tlinklist * temp = NULL;
	temp = (Tlinklist*)list;
	if (temp == NULL)
	{
		return "error no have";
	}
	Linklistnode * current = NULL;
	current = &(temp->head);
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	return current;
};