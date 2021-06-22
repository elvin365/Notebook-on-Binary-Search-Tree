#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#include "list.h"

struct Tree
{
	struct Tree* Root;
	struct Tree* Left;
	struct Tree* Right;
	struct List* Data;
};

void AddByTime(struct Tree **pRoot, struct Tree *Root, struct List * data)
{
	if (*pRoot == NULL)
	{
		*pRoot = (Tree*)malloc(sizeof(Tree));
		(*pRoot)->Left = NULL;
		(*pRoot)->Right = NULL;
		(*pRoot)->Root = Root; // на родителя
		(*pRoot)->Data = data;
		return;
	}
	if (mktime(&(data->Data.time)) < mktime(&(*pRoot)->Data->Data.time))
		AddByTime(&(*pRoot)->Left, *pRoot, data);
	else
		AddByTime(&(*pRoot)->Right, *pRoot, data);
}

void AddByPlace(struct Tree **pRoot, struct Tree *Root, struct List * data)
{
	if (*pRoot == NULL)
	{
		*pRoot = (Tree*)malloc(sizeof(Tree));
		(*pRoot)->Left = NULL;
		(*pRoot)->Right = NULL;
		(*pRoot)->Root = Root; // на родителя
		(*pRoot)->Data = data;
		return;
	}
	if (strcmp((*pRoot)->Data->Data.whereto, data->Data.whereto) > 0)
		AddByPlace(&(*pRoot)->Left, *pRoot, data);
	else
		AddByPlace(&(*pRoot)->Right, *pRoot, data);
}

void AddByImportance(struct Tree **pRoot, struct Tree *Root, struct List * data)
{
	if (*pRoot == NULL)
	{
		*pRoot = (Tree*)malloc(sizeof(Tree));
		(*pRoot)->Left = NULL;
		(*pRoot)->Right = NULL;
		(*pRoot)->Root = Root; // на родителя
		(*pRoot)->Data = data;
		return;
	}
	if ((*pRoot)->Data->Data.importance > data->Data.importance) //!!!!!!!!!!
		AddByImportance(&(*pRoot)->Left, *pRoot, data);
	else
		AddByImportance(&(*pRoot)->Right, *pRoot, data);
}

struct Tree *FindByTime(struct Tree *a, struct List* pointer)
{
	if (a == NULL)
		return NULL;
	if (mktime(&(a->Data->Data.time)) == mktime(&pointer->Data.time))
		if (a->Data == pointer)
			return a;
	if (mktime(&(a->Data->Data.time)) > mktime(&pointer->Data.time))
		return FindByTime(a->Left, pointer);
	else
		return FindByTime(a->Right, pointer);
}

struct Tree *FindByPlace(struct Tree *a, struct List* pointer)
{
	if (a == NULL)
		return NULL;
	if (strcmp(a->Data->Data.whereto, pointer->Data.whereto) == 0)
		if (a->Data == pointer)
			return a;
	if (strcmp(a->Data->Data.whereto, pointer->Data.whereto) > 0)
		return FindByPlace(a->Left, pointer);
	else
		return FindByPlace(a->Right, pointer);
}

struct Tree *FindByImportance(struct Tree *a, struct List* pointer)
{
	if (a == NULL)
		return NULL;
	if (a->Data->Data.importance == pointer->Data.importance)
		if (a->Data == pointer)
			return a;
	if (a->Data->Data.importance > pointer->Data.importance)
		return FindByImportance(a->Left, pointer);
	else
		return FindByImportance(a->Right, pointer);
}

void DeleteTree(struct Tree** a, struct Tree* b)
{
	if (*a == b)
	{
		if ( ((*a)->Left) == NULL && ((*a)->Right) == NULL)
		{
			free(*a);
			(*a) = NULL;
			return;
		}
		if ((*a)->Left != NULL && (*a)->Right == NULL)
		{
			(*a) = (*a)->Left;
			(*a)->Root = NULL;
			free(b);
			return;
		}
		if ((*a)->Left == NULL && (*a)->Right != NULL)
		{
			(*a) = (*a)->Right;
			(*a)->Root = NULL;
			free(b);
			return;
		}
		struct Tree *t = (*a)->Right;
		while (t->Left != NULL)
			t = t->Left;
		t->Left = (*a)->Left;
		if (t->Right)
		{
			(t->Right)->Root = t->Root;
			(t->Root)->Left = t->Right;
		}
		else
		{
			t->Root->Left = NULL;
		}
		
		if ((*a)->Right != t)
		{
			t->Right = (*a)->Right;
		}
		//t->Right = (*a)->Right;

		if (t->Left)
			t->Left->Root = t;
		if (t->Right)
			t->Right->Root = t;

		t->Root = NULL;
		(*a) = t;
		free(b);
		return;
	}
	else
	{
		
		struct Tree *c = b->Root;
		if (b->Left == NULL && b->Right == NULL)
		{
			if (c->Left == b)
			{
				c->Left = NULL;
			}
			else
			{
				c->Right = NULL;
			}
			free(b);
			return;
		}
		if (b->Left != NULL && b->Right == NULL)
		{
			if (c->Left == b)
			{
				c->Left = b->Left;
			}
			else
			{
				c->Right = b->Left;
			}
			(b->Left)->Root = c;
			free(b);
			return;
		}
		if (b->Left == NULL && b->Right != NULL)
		{
			if (c->Left == b)
			{
				c->Left = b->Right;
			}
			else
			{
				c->Right = b->Right;
			}
			(b->Right)->Root = c;
			free(b);
			return;
		}
		struct Tree *t = b->Right;
		while (t->Left != NULL)
			t = t->Left;
		if (t->Right)
		{
			(t->Right)->Root = t->Root;
			(t->Root)->Left = t->Right;
		}
		t->Left = b->Left;
		if (b->Right != t)
		{
			t->Right = b->Right;
		}
		
		if (b->Root->Left == b)
		{
			b->Root->Left = t;
		}
		else
		{
			b->Root->Right = t;
		}

		t->Root = b->Root;

		free(b);
		return;
	}
}

void traverse(Tree* w)
{
	if (w == NULL)
		return;
	
	traverse(w->Left);
	printData(w->Data->Data);
	//traverse(w->Left);
	traverse(w->Right);
}
void traversei(Tree* w)
{
	if (w == NULL)
		return;
	
	traversei(w->Left);
	printData(w->Data->Data);
	
	traversei(w->Right);
}
void traversep(Tree* w)
{
	if (w == NULL)
		return;
	traversep(w->Left);
	putchar('\n');
	puts("\n\t\t\t\tTime:");
	printf("\n\t\t\t\t-|%d.%d.%d in time %d:%d ", w->Data->Data.time.tm_mday, w->Data->Data.time.tm_mon + 1, w->Data->Data.time.tm_year + 1900, w->Data->Data.time.tm_hour, w->Data->Data.time.tm_min);
	if (w->Data->Data.time.tm_wday== 0)
		puts("\n\t\t\t\tSunday");
	if (w->Data->Data.time.tm_wday == 1)
		puts("\n\t\t\t\tMonday");
	if (w->Data->Data.time.tm_wday == 2)
		puts("\n\t\t\t\tTuesday");
	if (w->Data->Data.time.tm_wday == 3)
		puts("\n\t\t\t\tWednesday");
	if (w->Data->Data.time.tm_wday == 4)
		puts("\n\t\t\t\tThursday");
	if (w->Data->Data.time.tm_wday == 5)
		puts("\n\t\t\t\tFriday");
	if (w->Data->Data.time.tm_wday == 6)
		puts("\n\t\t\t\tSaturday");
	//putchar('\n');
	puts("\n\t\t\t\tDescription:");
	puts(w->Data->Data.description);
	putchar(' ');
	puts("\n\t\t\t\tPlace:");
	puts(w->Data->Data.whereto);
	//putchar(' ');
	puts("\n\t\t\t\tImportance");
	printf("\n\t\t\t\t%d", w->Data->Data.importance);
	putchar('\n');
	//traverse(w->Left);
	traversep(w->Right);
}
void ListToTimeTree(List *head, Tree **Root)
{
	while (head)
	{
		AddByTime(Root, NULL, head);
		head = head->Next;
	}
}

void ListToPlaceTree(List *head, Tree **Root)
{
	while (head)
	{
		AddByPlace(Root, NULL, head);
		head = head->Next;
	}
}

void ListToImportanceTree(List *head, Tree **Root)
{
	while (head)
	{
		AddByImportance(Root, NULL, head);
		head = head->Next;
	}
}