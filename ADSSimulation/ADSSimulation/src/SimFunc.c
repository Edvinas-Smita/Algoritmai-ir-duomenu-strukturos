#include "SimHeader.h"


int readSimulationsFromFile(FILE *file, simulation ***simArray) {
	if (file == NULL) {
		return -1;
	}

	int simulationsRead = 1;
	char ARead = 0, A1Read = 0, URead = 0, KRead = 0, T1Read = 0, T2Read = 0;

	char line[256];
	while (fgets(line, 256, file) != NULL) {
		switch (line[0])
		{
		case '+': {
			//<finalise>
			if (!ARead) {
				(*simArray)[simulationsRead - 1]->A = rand() % AMAX;
			}
			if (!A1Read) {
				(*simArray)[simulationsRead - 1]->A1 = rand() % A1MAX;
			}
			if (!URead) {
				(*simArray)[simulationsRead - 1]->U = rand() % UMAX;
			}
			if (!KRead) {
				(*simArray)[simulationsRead - 1]->K = rand() % KMAX;
			}
			if (!T1Read) {
				(*simArray)[simulationsRead - 1]->T1 = ((double)rand()) / RAND_MAX;
			}
			if (!T2Read) {
				(*simArray)[simulationsRead - 1]->T2 = ((double)rand()) / RAND_MAX;
			}
			(*simArray)[simulationsRead - 1]->B = (*simArray)[simulationsRead - 1]->A - (*simArray)[simulationsRead - 1]->A1;
			(*simArray)[simulationsRead - 1]->workTime = 0;
			(*simArray)[simulationsRead - 1]->totalOvertime = 0;

			(*simArray)[simulationsRead - 1]->longA = NULL;
			sprintf(line, "%d", (*simArray)[simulationsRead - 1]->A);
			inicijuoti(&(*simArray)[simulationsRead - 1]->longA, line);

			(*simArray)[simulationsRead - 1]->longA1 = NULL;
			sprintf(line, "%d", (*simArray)[simulationsRead - 1]->A1);
			inicijuoti(&(*simArray)[simulationsRead - 1]->longA1, line);

			(*simArray)[simulationsRead - 1]->longB = NULL;
			sprintf(line, "%d", (*simArray)[simulationsRead - 1]->B);
			inicijuoti(&(*simArray)[simulationsRead - 1]->longB, line);

			(*simArray)[simulationsRead - 1]->longUxK = NULL;
			sprintf(line, "%d", (*simArray)[simulationsRead - 1]->U * (*simArray)[simulationsRead - 1]->K);
			inicijuoti(&(*simArray)[simulationsRead - 1]->longUxK, line);

			(*simArray)[simulationsRead - 1]->profit = NULL;
			inicijuoti(&(*simArray)[simulationsRead - 1]->profit, "0");
			//CreatePQ(&((*simArray)[simulationsRead - 1]->queue));
			(*simArray)[simulationsRead - 1]->queue = NULL;
			//</finalise>

			++simulationsRead;
			*simArray = realloc(*simArray, simulationsRead * sizeof(simulation*));
			(*simArray)[simulationsRead - 1] = malloc(sizeof(simulation));

			ARead = A1Read = URead = KRead = T1Read = T2Read = 0;
			break;
		}
		case 'A': {
			if (line[1] == '1') {
				(*simArray)[simulationsRead - 1]->A1 = atoi(line + 3);
				ARead = 1;
			}
			else {
				(*simArray)[simulationsRead - 1]->A = atoi(line + 2);
				A1Read = 1;
			}
			break;
		}
		case 'U': {
			(*simArray)[simulationsRead - 1]->U = atoi(line + 2);
			URead = 1;
			break;
		}
		case 'K': {
			(*simArray)[simulationsRead - 1]->K = atoi(line + 2);
			KRead = 1;
			break;
		}
		case 'T': {
			if (line[1] == '1') {
				(*simArray)[simulationsRead - 1]->T1 = atof(line + 3);
				T1Read = 1;
			}
			else {
				(*simArray)[simulationsRead - 1]->T2 = atof(line + 3);
				T2Read = 1;
			}
			break;
		}
		default: {
			break;
		}
		}
	}

	//<finalise>
	if (!ARead) {
		(*simArray)[simulationsRead - 1]->A = rand() % AMAX;
	}
	if (!A1Read) {
		(*simArray)[simulationsRead - 1]->A1 = rand() % A1MAX;
	}
	if (!URead) {
		(*simArray)[simulationsRead - 1]->U = rand() % UMAX;
	}
	if (!KRead) {
		(*simArray)[simulationsRead - 1]->K = rand() % KMAX;
	}
	if (!T1Read) {
		(*simArray)[simulationsRead - 1]->T1 = ((double)rand()) / RAND_MAX;
	}
	if (!T2Read) {
		(*simArray)[simulationsRead - 1]->T2 = ((double)rand()) / RAND_MAX;
	}
	(*simArray)[simulationsRead - 1]->B = (*simArray)[simulationsRead - 1]->A - (*simArray)[simulationsRead - 1]->A1;
	(*simArray)[simulationsRead - 1]->workTime = 0;
	(*simArray)[simulationsRead - 1]->totalOvertime = 0;

	(*simArray)[simulationsRead - 1]->longA = NULL;
	sprintf(line, "%d", (*simArray)[simulationsRead - 1]->A);
	inicijuoti(&(*simArray)[simulationsRead - 1]->longA, line);

	(*simArray)[simulationsRead - 1]->longA1 = NULL;
	sprintf(line, "%d", (*simArray)[simulationsRead - 1]->A1);
	inicijuoti(&(*simArray)[simulationsRead - 1]->longA1, line);

	(*simArray)[simulationsRead - 1]->longB = NULL;
	sprintf(line, "%d", (*simArray)[simulationsRead - 1]->B);
	inicijuoti(&(*simArray)[simulationsRead - 1]->longB, line);

	(*simArray)[simulationsRead - 1]->longUxK = NULL;
	sprintf(line, "%d", (*simArray)[simulationsRead - 1]->U * (*simArray)[simulationsRead - 1]->K);
	inicijuoti(&(*simArray)[simulationsRead - 1]->longUxK, line);

	(*simArray)[simulationsRead - 1]->profit = NULL;
	inicijuoti(&(*simArray)[simulationsRead - 1]->profit, "0");
	//CreatePQ(&((*simArray)[simulationsRead - 1]->queue));
	(*simArray)[simulationsRead - 1]->queue = NULL;
	//</finalise>
	fclose(file);
	return simulationsRead;
}

char coinFlip(double chance) {
	return ((double)rand() / RAND_MAX) < chance;
}
int randBetween(int low, int high) {
	return rand() % (high - low) + low;
}
char enqueCar(pQueue *queue, double chance, int hrs, char VIP) {
	car *dummy;
	if (coinFlip(chance)) {
		dummy = malloc(sizeof(car));
		*dummy = (car) { hrs, VIP };
		//dummy->timeToFix = hrs;
		//dummy->VIPBool = VIP;
		Insert(queue, dummy, VIP);
		//printf("New car: @%p, %dhrs, %s\n", dummy, dummy->timeToFix, dummy->VIPBool ? "VIP" : "pleb");
		return 1;
	}
	else {
		return 0;
	}
}

int longIntAddToSelf(ilgasSveikas **self, ilgasSveikas *notSelf) {
	ilgasSveikas *copy = NULL;
	int returnCode = sudetis(*self, notSelf, &copy);
	salinimasSkaiciaus(self);
	*self = copy;
	return returnCode;
}
int longIntSubtractFromSelf(ilgasSveikas **self, ilgasSveikas *notSelf) {
	ilgasSveikas *copy = NULL;
	int returnCode = atimti(*self, notSelf, &copy);
	salinimasSkaiciaus(self);
	*self = copy;
	return returnCode;
}

char doOvertime(pQueue queue) {
	return IsEmpty(queue) ? 0 : queue->value->VIPBool;
}

int doATick(simulation *singleSimulation) {
	int VIPcarHrs = randBetween(1, 5 * singleSimulation->K);
	int nonVIPcarHrs = randBetween(1, 5 * singleSimulation->K);

	car *topCar = NULL;

	char vipArrived = 0;
	char nonVipArrived = 0;

	if (singleSimulation->workTime > 7 && doOvertime(singleSimulation->queue) == 0) {
		singleSimulation->workTime = 0;
	}
	printf("Time of day: %d\n", singleSimulation->workTime);
	if (singleSimulation->workTime < 8) {
		vipArrived = enqueCar(&(singleSimulation->queue), singleSimulation->T1, VIPcarHrs, 1);
		nonVipArrived = enqueCar(&(singleSimulation->queue), singleSimulation->T2, nonVIPcarHrs, 0);

		if (vipArrived || nonVipArrived) {
			printf("New clients:	");
			if (vipArrived) {
				printf("VIP: %dhrs	", VIPcarHrs);
			}
			if (nonVipArrived) {
				printf("regular: %dhrs", VIPcarHrs);
			}
		}
	}
	printf("\n");

	int hoursInAnHour = singleSimulation->K;
	while (hoursInAnHour > 0 && !IsEmpty(singleSimulation->queue)) {
		topCar = singleSimulation->queue->value;
		printf("Working on a car: %dh, %s	", topCar->timeToFix, topCar->VIPBool ? "VIP" : "pleb");
		if (topCar->timeToFix > hoursInAnHour) {
			topCar->timeToFix -= hoursInAnHour;
			hoursInAnHour = 0;
		}
		else {
			hoursInAnHour -= topCar->timeToFix;
			longIntAddToSelf(&(singleSimulation->profit), topCar->VIPBool ? singleSimulation->longA : singleSimulation->longB);

			printf("FIXED! Profit: %d", topCar->VIPBool ? singleSimulation->A : singleSimulation->B);

			free(topCar);
			Remove(&(singleSimulation->queue));
		}
		printf("\n");
	}

	printf("Paying workers: %d %s\n", singleSimulation->workTime > 7 ? 2 * singleSimulation->U * singleSimulation->K : singleSimulation->U * singleSimulation->K, singleSimulation->workTime > 7 ? "(overtime)" : "");
	longIntSubtractFromSelf(&(singleSimulation->profit), singleSimulation->longUxK);
	if (singleSimulation->workTime > 7) {
		longIntSubtractFromSelf(&(singleSimulation->profit), singleSimulation->longUxK);
		++singleSimulation->totalOvertime;
	}

	++(singleSimulation->workTime);
	printf("\n");
	return 0;
}

int calcAndCleanLeftovers(simulation *singleSimulation, int *VIPs) {
	*VIPs = 0;
	int plebs = 0, total;
	while (!IsEmpty(singleSimulation->queue)) {
		if (singleSimulation->queue->value->VIPBool) {
			++*VIPs;
		}
		else {
			++plebs;
		}
		free(singleSimulation->queue->value);
		Remove(&(singleSimulation->queue));
	}
	return *VIPs + plebs;
}