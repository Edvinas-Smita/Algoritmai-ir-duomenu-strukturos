#ifndef ILGASSVEIKAS_H
#define ILGASSVEIKAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct skaicius {
	struct skaicius * priekin;
	int duom;
	struct skaicius * atgal;
} ilgasSveikas;

// Skaiciui pr priskiriama string reiksme sk
int inicijuoti(ilgasSveikas **pr, char * sk);
// Pasalina skaiciu - pradzia, ir atlaisvina atminti
void salinimasSkaiciaus(ilgasSveikas **pradzia);
// Grazina 1, jei skaicius1 < skaicius2, priesingu atveju - 0
int arMaziau(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2);
// Grazina 1, jei skaicius1 > skaicius2, priesingu atveju - 0
int arDaugiau(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2);
// Grazina 1, jei skaicius1 = skaicius2, priesingu atveju - 0
int arLygus(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2);

// Spausdina skaiciaus reiksme pr
void spausdintiSkaiciu(ilgasSveikas *pr);
void ivedimas(char **skaicius);

// Dveju skaiciu - pradzia1 ir pradzia2, sudetis, rezultatas- atsakymoPradzia
// Grazina 1, jei nera klaidos sudedant, priesingu atveju - 0
int sudetis(ilgasSveikas *pradzia1, ilgasSveikas *pradzia2, ilgasSveikas **atsakymoPradzia);
// Skaiciu pradzia1 atima is pradzia2, rezultatas - atsakymoPradzia
// Grazina 1, jei nera klaidos atimant skaicius, priesingu atveju - 0
int atimti(ilgasSveikas *pradzia1, ilgasSveikas *pradzia2, ilgasSveikas **atsakymoPradzia);
// Sudaugina du skaicius - pradzia1 ir pradzia, rezultatas - atsakymoPradzia
// Grazina 1, jei nera klaidos dauginant, priesingu atveju - 0
int sandauga(ilgasSveikas *pradzia1, ilgasSveikas *pradzia2, ilgasSveikas **atsakymoPradzia);
// pradzia1 dalina is pradzia2, dalmuo - atsakymoSveikasisSkaiciusPradzia, dalybos liekana - atsakymoLiekanaPradzia
// Grazina 1, jei nera klaidos dalijant, priesingu atveju - 0 (dalyba is nulio)
int dalyba(ilgasSveikas *pradzia1, ilgasSveikas *pradzia2, ilgasSveikas **atsakymoSveikasisSkaiciusPradzia, ilgasSveikas **atsakymoLiekanaPradzia);

#endif // !LONGDEFINED