#define _CRT_SECURE_NO_WARNINGS
#pragma once


#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

struct notes
{
	char description[100] = { 0 };
	char whereto[100] = { 0 };
	unsigned importance = 0;
	tm time;
};

struct List
{
	notes Data;
	List *Next;
};

struct List* push(struct List* head, notes inf)
{
	struct List* New = (struct List*)malloc(sizeof(List));
	New->Data = inf;
	New->Next = head;
	return New;
};

struct List* Delete(struct List* head, struct List* removable)
{
	if ((head) == NULL)
		return 0;
	if (head == removable)
	{
		head = head->Next;
		free(removable);
	}
	else
	{
		List *prev = head;
		while (prev->Next != removable)
		{
			prev = prev->Next;
		}

		prev->Next = removable->Next;
		free(removable);
	}
	return head;
};

struct List* LoadFromFile()
{
	FILE *p;
	List* pnt = NULL;
	notes info;
	info.time.tm_sec = 0;
	info.time.tm_isdst = 0;
	info.time.tm_yday = 0;
	info.time.tm_isdst = 0;

	puts("\n\t\t\t\tEnter the name of file");
	char waytofile[100] = { 0 };
	getchar();
	gets_s(waytofile, 100);
	p = fopen(waytofile, "rb");
	if (p == NULL)
		return NULL;
	
	while (!feof(p))
	{
		if ((fscanf(p, "%d", &info.time.tm_year) != EOF) && fscanf(p, "%d", &info.time.tm_mon) != EOF && fscanf(p, "%d", &info.time.tm_mday) != EOF && fscanf(p, "%d", &info.time.tm_hour) != EOF && fscanf(p, "%d", &info.time.tm_min) != EOF && fscanf(p, "%d", &info.importance) != EOF && fgets(info.description, 100, p) && fgets(info.whereto, 100, p))
		{
			pnt = push(pnt, info);
		
		}

	}
	

	fclose(p);
	return  pnt;
}

int SaveToFile(List* pHead)
{
	FILE *p;

	p = fopen("C:\\Users\\Elvin\\source\\repos\\LabTreeTest\\LabTree\\savablenoteimeantheuserpressedsss.dat", "wb");
	if (p == NULL)
		return -1;
	while (pHead)
	{

		fprintf(p, "%d ", pHead->Data.time.tm_year);
		//fprintf(p, "%d ", pHead->Data.time.tm_yday); 
		fprintf(p, "%d ", pHead->Data.time.tm_mon);
		fprintf(p, "%d ", pHead->Data.time.tm_mday);
		//fprintf(p, "%d ", pHead->Data.time.tm_wday);
		fprintf(p, "%d ", pHead->Data.time.tm_hour);
		fprintf(p, "%d ", pHead->Data.time.tm_min);
		fprintf(p, "%d ", pHead->Data.importance);
		//fprintf(p, "%d ", pHead->Data.time.tm_sec);
		fputs(pHead->Data.description, p);
		fputs("\n", p);
		fputs(pHead->Data.whereto, p);
		fputs("\n", p);
		
		pHead = pHead->Next;
		
	}
	fclose(p);
	return 0;
}

notes funcfromuser()
{
	{

		struct notes inf;
		int i = 0;
		do
		{
			puts("\n\t\t\t\tEnter the year");
			scanf("%d", &inf.time.tm_year);
		} while (!(inf.time.tm_year >= 1900 && inf.time.tm_year <= 2100));

	//	int CopyOfYear = inf.time.tm_year;

		inf.time.tm_year = inf.time.tm_year - 1900;

		do
		{
			puts("\n\t\t\t\tEnter the month");
			scanf("%d", &inf.time.tm_mon);
			inf.time.tm_mon = inf.time.tm_mon - 1;
		} while (!(inf.time.tm_mon >= 0 && inf.time.tm_mon <= 11));
		//inf.time.tm_mon = inf.time.tm_mon - 1; // !!!!!!
		do
		{
			puts("\n\t\t\t\tEnter the date");
			scanf("%d", &inf.time.tm_mday);
		} while (!(inf.time.tm_mday >= 1 && inf.time.tm_mday <= 31));

		/*	do
		{
		puts("Enter the weekday");
		scanf("%d", &inf.time.tm_wday);
		} while (!(inf.time.tm_wday>=0 && inf.time.tm_wday<=6)); */
		do
		{
			puts("\n\t\t\t\tEnter the hour");
			scanf("%d", &inf.time.tm_hour);
		} while (!(inf.time.tm_hour >= 0 && inf.time.tm_hour <= 23));

		do
		{
			puts("\n\t\t\t\tEnter the min");
			scanf("%d", &inf.time.tm_min);
		} while (!(inf.time.tm_min >= 0 && inf.time.tm_min <= 59));

		inf.time.tm_sec = 0;
		inf.time.tm_isdst = 0;
		inf.time.tm_yday = -1;
		inf.time.tm_wday = 0;
		puts("\n\t\t\t\tEnter the description");
		getchar();
		gets_s(inf.description, 100);
		puts("\n\t\t\t\tEnter the palce");
		//	getchar();
		gets_s(inf.whereto, 100);
		puts("\n\t\t\t\tEnter the importance");

		do
		{
			scanf("%d", &inf.importance);
		} while (!(inf.importance >= 0 && inf.importance <= 10));



		return inf;

	}
}

int funccomapre(notes head, notes value)
{
	if ((head.time.tm_hour == value.time.tm_hour) && (head.time.tm_mday == value.time.tm_mday) && (head.time.tm_min == value.time.tm_min) && (head.time.tm_mon == value.time.tm_mon) && (head.time.tm_sec == value.time.tm_sec) && (head.time.tm_wday == value.time.tm_wday) && (head.time.tm_year == value.time.tm_year) && (!strcmp(head.description, value.description)) && (head.importance == value.importance) && (!strcmp(head.whereto, value.whereto)))
		return 0;
	else return 1;
}

List* Find(List *head, notes value)
{
	while (head)
	{
		int i = funccomapre(head->Data, value);
		if (i == 0)
			return head;
		else
			head = head->Next;
	}
	return NULL;
}

void printData(notes a)
{
	putchar('\n');
	puts("\n\t\t\t\t-------------------\n");
	if (a.time.tm_yday == 0)
		return;
	puts("\n\t\t\t\tTime:");
	printf("\t\t\t\t-|%d.%d.%d in time %d:%d ", a.time.tm_mday, a.time.tm_mon + 1, a.time.tm_year+1900, a.time.tm_hour, a.time.tm_min);
	if (a.time.tm_wday == 0)
		puts("\n\t\t\t\tSunday");
	if (a.time.tm_wday == 1)
		puts("\n\t\t\t\tMonday");
	if (a.time.tm_wday == 2)
		puts("\n\t\t\t\tTuesday");
	if (a.time.tm_wday == 3)
		puts("\n\t\t\t\tWednesday");
	if (a.time.tm_wday == 4)
		puts("\n\t\t\t\tThursday");
	if (a.time.tm_wday == 5)
		puts("\n\t\t\t\tFriday");
	if (a.time.tm_wday == 6)
		puts("\n\t\t\t\tSaturday");
	//putchar('\n');
	puts("\n\t\t\t\tDescription:");
	printf("\t\t\t\t%s",a.description);
	puts("\n\t\t\t\tPlace:");
	printf(" \t\t\t\t%s", a.whereto);
	//putchar(' ');
	puts("\n\t\t\t\tImportance");
	printf("\t\t\t\t%d", a.importance);
	putchar('\n');
	puts("\n\t\t\t\t-------------------\n");
}
void printData1(notes a)
{
	mktime(&a.time);
	putchar('\n');
	if (a.time.tm_yday == 0)
		return;
	puts("\n\t\t\t\t-------------------\n");
	puts("\n\t\t\t\tTime:");
	printf("\n\t\t\t\t-|%d.%d.%d in time %d:%d ", a.time.tm_mday, a.time.tm_mon + 1, a.time.tm_year + 1900, a.time.tm_hour, a.time.tm_min);
	if (a.time.tm_wday == 0)
		puts("\n\t\t\t\tSunday");
	if (a.time.tm_wday == 1)
		puts("\n\t\t\t\tMonday");
	if (a.time.tm_wday == 2)
		puts("\n\t\t\t\tTuesday");
	if (a.time.tm_wday == 3)
		puts("\n\t\t\t\tWednesday");
	if (a.time.tm_wday == 4)
		puts("\n\t\t\t\tThursday");
	if (a.time.tm_wday == 5)
		puts("\n\t\t\t\tFriday");
	if (a.time.tm_wday == 6)
		puts("\n\t\t\t\tSaturday");
	//putchar('\n');
	puts("\n\t\t\t\tDescription:");
	printf("\t\t\t\t%s", a.description);
	//putchar(' ');
	puts("\n\t\t\t\tPlace:");
	printf("\t\t\t\t%s", a.whereto);
	//putchar(' ');
	puts("\n\t\t\t\tImportance");
	printf("\n\t\t\t\t%d", a.importance);
	putchar('\n');
	printf("\n\t\t\t\tIT WAS NUMBER %d", I);
	I=I+1;
	puts("\n\t\t\t\t-------------------\n");
}

void PrintList(List *pHead)
{
	while (pHead)
	{
		printData(pHead->Data);
		pHead = pHead->Next;
	}
}


void ListByDescription(List *pHead, char *str)
{
	while (pHead)
	{
		if (strstr(pHead->Data.description, str))
			printData(pHead->Data);
		pHead = pHead->Next;
	}
}

void ListByPlace(List *pHead, char *str)
{
	while (pHead)
	{
		if (strstr(pHead->Data.whereto, str))
			printData(pHead->Data);
		pHead = pHead->Next;
	}
}