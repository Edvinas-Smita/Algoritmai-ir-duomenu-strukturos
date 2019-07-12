#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

/*
void Spausdinti (struct priorq *head)
{
	if (head!=NULL)
	{
		while (head->fwd !=NULL)
		{
			printf ("reiksme : %d ,prioritetas : %d ,pointeris bwd : %p ,\npointeris fwd : %p ,jo pacio pointeris : %p \n", head->value, head->prior, head->bwd, head->fwd, head);
			head=head->fwd;
		}
		printf ("reiksme : %d ,prioritetas : %d ,pointeris bwd : %p ,\npointeris fwd : %p ,jo pacio pointeris : %p \n", head->value, head->prior, head->bwd, head->fwd, head);
	}
	else
	{
		printf ("Prioritetine eile yra tuscia");
	}
}
*/

int Insert (struct priorq **head, data_type value, int prior)
{
	struct priorq *a, **temp=head;
	a = (struct priorq *) malloc (sizeof(struct priorq));
	if (a == NULL)
	{
		//printf ("Nepavyko isskirti atminties naujam elementui\n");
		return 0;
	}
	a->prior=prior;
	a->value=value;
	a->bwd=NULL;
	a->fwd=NULL;
	if (*head==NULL)							//Jei tuscias, head'a padarom nauju elementu
	{
		*head=a;
		return 1;
	}
	else
	{
		if (prior > (*head)->prior)				//Ar iterpiamas pries head'a
		{
			a->fwd=*head;
			(*head)->bwd=a;
			*head=a;
			return 1;
		}
		else
		{
			while ((*head)->prior >= prior)
			{
				if ((*head)->fwd == NULL)		//Jei iterpti i paskutini elementa
				{
					(*head)->fwd=a;
					a->bwd=*head;
					while ((*head)->bwd != NULL)
					{
						(*head)=(*head)->bwd;
					}
					return 1;
				}
				else
				{
					*head=(*head)->fwd;
				}
			}
			a->bwd=(*head)->bwd;				//Paprastas iterpimas
			a->fwd=*head;
			(*head)->bwd=a;
			(a->bwd)->fwd=a;
			while ((*head)->bwd!=NULL)			//Graziname galva i pradzia
			{
				(*head)=(*head)->bwd;
			}
			return 1;
		}
	}
	return 0;
}

int Remove (struct priorq **head)
{
	if (*head==NULL)
	{
		return 2;
	}
	else
	{
		if ((*head)->fwd==NULL)
		{
			free (*head);
			*head=NULL;
			return 1;
		}
		else
		{
			*head=(*head)->fwd;
			free ((*head)->bwd);
																					(*head)->bwd = NULL;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			return 1;
		}
	}
	return 0;
}

int IsEmpty (struct priorq *head)
{
	if (head==NULL)			//arba head->fwd==null
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
void MemoryLeak (struct priorq **head)
{
	for (int i=0;i<10000;i++)
	{
		for (int i=0;i<10000;i++)
		{
			Insert (head, 22, i);
		}
		for (int i=0;i<10000;i++)
		{
			Remove(head);
		}
	}
	printf ("baigesi. Paspauskite mygtuka noredami testi.\n");
	int prior;
	scanf ("%d", &prior);
}
*/

int CreatePQ (struct priorq **head)
{
	*head = (struct priorq *) malloc (sizeof(struct priorq));
	if (*head==NULL)
	{
		free (*head);
		*head=NULL;
		return 0;
	}
	else
	{
		free (*head);
		*head=NULL;
		return 1;
	}
}

/*
void PrintInstruction ()
{
	printf ("\n1) Sukurti tuščią prioritetinę eilę (Create)");
	printf ("\n2) Nustatyti, ar eilė tuščia (IsEmpty)");
	printf ("\n3) Įdėti naują elementą (Insert)");
	printf ("\n4) Išmesti elementą su didžiausiu prioritetu (Remove)");
	printf ("\n5) Atspausdinti prioritetine eile.");
	printf ("\n6) Patikrinti memory leak'us.");
	printf ("\n7) Sunaikinti visa prioritetine eile\n");
}
*/

void Delete (struct priorq **head) 
{
	while (*head!=NULL)
	{
		Remove (head);
	}
}
