#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

int main ()
{
	struct priorq *head;
	int a = 0, value, prior;
	while (1)
	{
		PrintInstruction();
		printf ("\nIveskite operacijos numeri: ");	//3 1 0 3 2 0 3 3 0 3 4 0 3 5 0 3 6 0 3 7 0 3 8 0 3 9 0 3 10 0 3 11 0
		scanf ("%d", &a);
		if (a == 1)
		{
			if (CreatePQ (&head))
				printf ("Inicializacija pavyko\n");
			else
				printf ("Inicializacija nepavyko\n");
		}
		if (a == 2)
		{
			if (IsEmpty (head))
			{
				printf ("Prioritetine eile yra tuscia\n");
			}
			else
			{
				printf ("Prioritetine eile nera tuscia\n");
			}
		}
		if (a == 3)
		{
			printf ("Iveskite elemento reiksme ir prioriteta, atskirtus tarpais : ");
			scanf ("%d %d", &value, &prior);
			printf ("\n");
			Insert (&head, value, prior);
		}
		if (a == 4)
		{
			printf("Removing: %d\n", head->value);
			Remove(&head);
			/*if (Remove (&head)==2)
			{
				printf ("Eile tuscia, nera ka isimti.\n");
			}
			else
			{
				if (Remove(&head)==1)
				{
					printf ("Elementas sėkmingai pašalintas.\n");
				}
				else
				{
					printf ("Įvyko neaprašyta klaida.\n");
				}
			}*/
		}
		if (a == 5)
		{
			Spausdinti (head);
		}
		if (a == 6)
		{
			MemoryLeak (&head);
		}
		if (a == 7)
		{
			Delete (&head);
		}
	}

	return 0;
}
