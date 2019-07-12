#ifndef SIMHEADER_H
#define SIMHEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

#define AMAX 100000
#define A1MAX 10000
#define UMAX 50
#define KMAX 100

//#define RAND_MAX 32767
//#define RAND_MAX 2147483647

#ifndef CARDEFINED
#define CARDEFINED
typedef struct wroom {
	int timeToFix;
	char VIPBool;
	//char miemuory[1024 * 1024];
}car;
#endif // !CARDEFINED

#include "../longInt/adsIlgas_h.h"
#include "../pQueue/pqueue.h"
typedef struct priorq *pQueue;
//typedef ppQueue *pQueue;

#ifndef SIMULATIONDEFINED
#define SIMULATIONDEFINED
typedef struct aSim {
	char workTime;
	int totalOvertime;

	int A;
	int A1;
	int B;
	int U;
	int K;

	double T1;
	double T2;

	ilgasSveikas *longA;
	ilgasSveikas *longA1;
	ilgasSveikas *longB;
	ilgasSveikas *profit;
	ilgasSveikas *longUxK;
	pQueue queue;
}simulation;
#endif // !SIMULATIONDEFINED


int readSimulationsFromFile(FILE *file, simulation ***simArray);

char coinFlip(double chance);
int randBetween(int low, int high);
char enqueCar(pQueue *queue, double chance, int hrs, char VIP);

int longIntAddToSelf(ilgasSveikas **self, ilgasSveikas *notSelf);
int longIntSubtractFromSelf(ilgasSveikas **self, ilgasSveikas *notSelf);

int doATick(simulation *simArray);
int calcAndCleanLeftovers(simulation *singleSimulation, int *VIPs);

#endif // !SIMHEADER_H
