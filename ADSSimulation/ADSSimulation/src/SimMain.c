#include "SimHeader.h"
#include <time.h>

int main(int argc, char **argv) {
	/*
	ilgasSveikas **leakas = calloc(sizeof(ilgasSveikas*), 1024);
	char *buffer;

	ivedimas(&buffer);

	printf("-------------------\n");
	getc(stdin);

	int i;
	for (i = 0; i < 1024; ++i) {
		inicijuoti(&leakas[i], buffer);
	}

	printf("====================\n");
	getc(stdin);

	for (i = 0; i < 1024; ++i) {
		salinimasSkaiciaus(&leakas[i]);
	}
	*/

	simulation **simArray = malloc(sizeof(simulation*));
	*simArray = malloc(sizeof(simulation));
	int arrayLen = 0;
	int i, j;

	int toLoop = 0;
	int VIPsLeft, totalLeft;

	{
		long seed;
		char initiatedSeed = 0, initiatedLoops = 0, initiatedFile = 0;
		char *inputFile = NULL;

		for (i = 1; i < argc; ++i) {
			if (argv[i][0] == '-') {
				switch (argv[i][1])
				{
				case 'S': {
					seed = atoi(argv[i + 1]);
					initiatedSeed = 1;
					break;
				}
				case 'F': {
					inputFile = argv[i + 1];
					initiatedFile = 1;
					break;
				}
				case 'L': {
					toLoop = atoi(argv[i + 1]);
					initiatedLoops = 1;
					break;
				}
				default: {
					break;
				}
				}
				++i;
			}
		}

		if (!initiatedFile) {
			printf("Usage:\n");
			printf("-F FILE_NAME	Needs to be provided parameters are read from the file\n");
			printf("-S [int]	If left blank it will be initiated to (system time) - seed for pseudo - random number generator\n");
			printf("-L [int]	If left blank it will be initiated to (rand() %% 32767) - how many ticks will each configuration run for\n");
			return -1;
		}
		if (inputFile != NULL) {
			arrayLen = readSimulationsFromFile(fopen(inputFile, "r"), &simArray);
		}
		if (arrayLen < 1) {
			printf("Problems with reading input file!\n");
			return -1;
		}

		if (!initiatedSeed) {
			seed = (int)time(NULL);
		}
		srand(seed);
		printf("Random number generation seed: %ld, used RAND_MAX: %d.\n", seed, RAND_MAX);

		if (!initiatedLoops) {
			toLoop = rand() % 32767;
		}
		printf("Looping every configuration %s%d time(s).\n", initiatedLoops ? "" : "rand() % 32767 = ", toLoop);
	}

	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	for (i = 0; i < arrayLen; ++i) {
		printf("A = %d\nA1 = %d\nB = %d\nU = %d\nK = %d\n\n", (simArray[i])->A, (simArray[i])->A1, (simArray[i])->B, (simArray[i])->U, (simArray[i])->K);
		printf("T1 = %f\nT2 = %f\n", (simArray[i])->T1, (simArray[i])->T2);
		for (j = 0; j < toLoop; ++j) {
			printf("(%d/%d)	", j + 1, toLoop);
			doATick(simArray[i]);
			printf("\n");
		}
		printf("Profit after: ");
		spausdintiSkaiciu(simArray[i]->profit);
		totalLeft = calcAndCleanLeftovers(simArray[i], &VIPsLeft);
		printf("Overtime hours worked: %d\n", simArray[i]->totalOvertime);
		printf("Still in queue: %d (%d VIPs and %d plebs)\n", totalLeft, VIPsLeft, totalLeft - VIPsLeft);
		printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	}

	getc(stdin);
	return 0;
}