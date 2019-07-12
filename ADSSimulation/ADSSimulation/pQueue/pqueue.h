#ifndef PQUEUE_H_INCLUDED
#define PQUEUE_H_INCLUDED
#endif
#include "datatype.h"

struct priorq {
	struct priorq *bwd;
	int prior;
	data_type value;
	struct priorq *fwd;
};

//void Spausdinti (struct priorq *head);							//Funkcija, kuri atspausdina visą eilę su adresais

int Insert (struct priorq **head, data_type value, int prior);	//Funkcija grąžina :
																	// 1, jei pavyksta įterpti;
																	// 0 kitais atvejais.

int Remove (struct priorq **head);								//Funkcija grąžina :
																	// 1, jei pavyksta ištrinti
																	// 2, jeigu sąrašas yra tuščias ir nėra ką ištrinti
																	// 0, kitais atvejais.

int IsEmpty (struct priorq *head);								//Funkcija grąžina :
																	// 1, jei sąrašas yra tuščias;
																	// 0, kitais atvejais;

//void MemoryLeak (struct priorq **head);							//Į sąrašą prideda 10000 elementų ir juos vėl ištrina. Kartoja 10000 kartų.
																//Stebėti atminties naudojimą.

int CreatePQ (struct priorq **head);							//Funkcija grąžina : 
																	// 1, jei pavyksta išskirti atmintį
																	// 0, kitais atvejais.

//void PrintInstruction ();										//Išveda main'o instrukcijas

void Delete (struct priorq **head);										//Funkcija sunaikina visą prioritetinę eilę
