#define _CRT_SECURE_NO_WARNINGS
 int M;
 int I=1;
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


#include "list.h"
#include "tree.h"

void takeq(char* q)
{

	scanf("%c", &(*q));
	if (*q == '\n')
		scanf("%c", &(*q));
}

void mainmenu()
{
	struct List* pHead = NULL;
	struct Tree* time = NULL;
	struct Tree* place = NULL;
	struct Tree* importance = NULL;

	for (;;)
	{
		puts("\n\t\t\t\t-------------------");
		puts("\n\t\t\t\t|1.-Add new event");
		puts("\n\t\t\t\t|2.-Delete old note");
		puts("\n\t\t\t\t|3.-Show all notes customsort");
		puts("\n\t\t\t\t|4.-Save or load f");
		puts("\n\t\t\t\t|5.-Find in string by substring");
		puts("\n\t\t\t\t|6.-Exit");
		puts("\n\t\t\t\t-------------------");
		putchar('\n');
		int i = 0;
		fflush(stdout);
		fflush(stdin);
		char q;
		takeq(&q);
		if (q == '1')
		{

			notes t = funcfromuser();
			pHead = push(pHead, t);
			AddByTime(&time, NULL, pHead);
			AddByPlace(&place, NULL, pHead);
			AddByImportance(&importance, NULL, pHead);
			int i = 0;
		}
		if (q == '2')
		{
			puts("\n\t\t\t\twhat note should be deleted ?");
			struct List* pHeadC = pHead;
			struct List* pHeadC1 = pHead;
			List* r=NULL;
			while (pHeadC)
			{
				printData1(pHeadC->Data);
				pHeadC = pHeadC->Next;
			}
			int j = 0;
			puts("\n\t\t\t\tSo enter the number");
			int x = 0;
			scanf("%d", &x);
			x = x - 1;
			while (pHeadC1 && j<x )
			{	
				pHeadC1= pHeadC1->Next;
				j++;
			}
			r = pHeadC1;
			//notes t = funcfromuser();
			//List* r = Find(pHead, t);
			//if (r == NULL) { printf("No such note"); return; }
			if (r == NULL)
			{
				puts("\n\t\t\t\tNothing left to delete");
				return;
			}
			Tree* y = FindByTime(time, r);
			DeleteTree(&time, y);

			Tree* y1 = FindByPlace(place, r);
			DeleteTree(&place, y1);

			Tree* y2 = FindByImportance(importance, r);
			DeleteTree(&importance, y2);

			pHead = Delete(pHead, r);
			I = 1;
			getchar();

		}
		if (q == '3')
		{

			puts("\n\t\t\t\tChoose the proxod");
			getchar();
			scanf("%c", &q);
			switch (q)
			{
			case 't':
			{
				traverse(time);
				break;
			}
			case 'i':
			{
				traversei(importance);
				break;
			}
			case 'p':
			{
				traversep(place);
				break;
			}
			}

		}
		if (q == '4') {
			int k = -1;
			puts("\n\t\t\t\tSave or load?");
			getchar();
			scanf("%c", &q);
			if (q == 's')
			{
				k = SaveToFile(pHead);
				if (k == 0)
					puts("\n\t\t\t\t_Success_");
				else
				{
					puts("\n\t\t\t\tNO");
				}
			}
			else
			{
				if (q == 'l')
					pHead = LoadFromFile();
				if (pHead == NULL)
					puts("\n\t\t\t\tDidn't reach the sucsess");
				ListToTimeTree(pHead, &time);
				ListToPlaceTree(pHead, &place);
				ListToImportanceTree(pHead, &importance);
				
			}

		}
		if (q == '5')
		{
			puts("\n\t\t\t\tEnter the string to find it");
			getchar();
			char query[100] = { 0 };

			gets_s(query, 100);

			ListByDescription(pHead, query);
			ListByPlace(pHead, query);
		}

		if (q == '6')
			break;
	}

}


int main()
{
	mainmenu();
	_getch();
	return 0;
}