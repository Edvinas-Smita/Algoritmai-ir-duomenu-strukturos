#include "adsIlgas_h.h"

// Skaiciaus ivedimas
void ivedimas(char **skaicius) {
    int mem = 64;
	char *eilute = malloc(mem);
	fgets(eilute, mem, stdin);
	
	while(eilute[strlen(eilute) - 1] != '\n'){
		mem *= 2;
		eilute = realloc(eilute, mem);
		fgets(eilute + mem / 2 - 1, mem / 2 + 1, stdin);
	}

    for (int i = 0; i < strlen(eilute); i++) {
        if (*(eilute + i) == '\n')
           *(eilute + i) = 0; 
    }

	*skaicius = eilute;
}

// Tikrina, ar simbolis yra skaicius nuo 0 iki 9. 
// Jei taip, tai grazina 1, ne - 0
int yraSkaicius(int simbolis) {
    if (simbolis >= 48 && simbolis <= 57)
        return 1;
    return 0;
}

// Tikrina, ar skaiciusEilutej masyvo elementai yra skaiciai nuo 0 iki 9 arba pirmas elementas '-' 
// Jei taip, tai grazina 1, ne - 0
int arEgzistuojaSkaicius(char * skaiciusEilutej) {
    int arEgzistuoja = 1;
    for (int i = 0; skaiciusEilutej[i++] != 0; ) {
        if (skaiciusEilutej[i - 1] == '-' && i - 1 == 0) {
            
        } else if (yraSkaicius(skaiciusEilutej[i - 1])  == 0)
                arEgzistuoja = 0;
	else if (skaiciusEilutej[i - 1] == '0' && skaiciusEilutej[i - 2] == '-')
		arEgzistuoja = 0;
    }
    return arEgzistuoja;
}

// Grazina indekso reiksme - indeksas, kuri yra pirmas masyvo skaiciusEilutej indeksas, kai jos elementas nelygus '0' arba '-'
int pirmoElementoIndekas(char * skaiciusEilutej) {
    int indeksas = 0;
    int rastasNeNulis = 0;
    for (int i = 0; i < skaiciusEilutej[i++] != 0; ) {
        //printf("%s ", skaiciusEilutej);
        if (skaiciusEilutej[i - 1]  == '-' &&  i - 1 == 0)
            indeksas++;
        if (skaiciusEilutej[i - 1] - 48 != 0)
            rastasNeNulis = 1;
        if (skaiciusEilutej[i - 1] - 48 == 0 && rastasNeNulis == 0)
            indeksas++;
    } 
    return indeksas;
}

// Grazina skaiciaus skaiciusEilutej skaiciaus skaitmenu skaiciu
int eilutesElementuSkaicius(char * skaiciusEilutej) {
    int ilgis = 0;
    for (int i = 0; skaiciusEilutej[i++] != 0; )
        ilgis++;
    return ilgis;
}

// Sukuria nauja skaiciu su pradzia ir pabaiga, ir iterpia simbolis i skaiciaus pradzia - pradzia.
// pabaiga - skaiciaus pabaiga
void iterpimasPirmoElemento(ilgasSveikas **pradzia, ilgasSveikas **pabaiga, char simbolis) {
    ilgasSveikas *elem;
    elem = (ilgasSveikas*) malloc (sizeof(ilgasSveikas));
    elem->duom = simbolis;
    elem->priekin = NULL;
    elem->atgal = NULL;
    *pabaiga = elem;
    *pradzia = elem;
}

// Iterpia simbolis i skaiciaus pabaiga - pabaiga
void iterpimasPabaigosElemento(ilgasSveikas **pabaiga, char simbolis) {
    ilgasSveikas *elem;
    elem = (ilgasSveikas*)malloc(sizeof(ilgasSveikas));
    elem->duom = simbolis;
    elem->priekin = NULL;
    elem->atgal = *pabaiga;
    (*pabaiga)->priekin = elem;
    *pabaiga = elem;
}

// Iterpia simbolis i skaiciaus pradzia - pradzia
void iterpimasPradziosElemento(ilgasSveikas **pradzia, char simbolis) {
    ilgasSveikas *elem;
    elem = (ilgasSveikas*)malloc(sizeof(ilgasSveikas));
    elem->duom = simbolis;
    elem->priekin = *pradzia;
    elem->atgal = NULL;
    (*pradzia)->atgal = elem;
    *pradzia = elem;
}

// Pasalina skaiciaus elementa - pradzia, is atminties
void elementoSalinimas(ilgasSveikas **pradzia) {
    ilgasSveikas *elem;
    //elem = *pradzia;
    //*pradzia = (*pradzia)->priekin;
    //(*pradzia)->atgal = NULL;
    //free(elem);
	elem = (*pradzia)->priekin;
	free(*pradzia);
	*pradzia = elem;
	(*pradzia)->atgal = NULL;
}

// Pasalina skaiciu - pradzia, is atminties
void salinimasSkaiciaus(ilgasSveikas **pradzia) {
    if(*pradzia != NULL)
    {
        while((*pradzia)->priekin != NULL)
            elementoSalinimas(pradzia);

        ilgasSveikas *elem;
        elem = *pradzia;
        *pradzia = NULL;
        free(elem);
    }
}

// Spausdina skaiciu - pradzia
void spausdintiSkaiciu(ilgasSveikas *pradzia) {
    while(pradzia != NULL)
    {
        printf("%c", pradzia->duom);
        pradzia = pradzia->priekin;
    }
    printf("\n");
}

// Grazina skaiciaus pradzia skaiciaus skaitmenu skaiciu
int skaiciausIlgis(ilgasSveikas *pradzia) {
    int ilgis = 0;
    while(pradzia != NULL) {
        ilgis++;
        pradzia = pradzia->priekin;
    }
    return ilgis;
}

// Skaiciui pradzia priskiriama string reiksme skaiciusEilutej
int inicijuoti(ilgasSveikas **pradzia, char * skaiciusEilutej) {

    // Pasalina skaiciu pradzia is atminties
    salinimasSkaiciaus(pradzia);
    
    // Tikrina, ar eilute skaiciusEilutej gali egzistuoti kaip skaicius.
    // Jei egzistuoja, tai grazina 1, jei ne - 0
    if (arEgzistuojaSkaicius(skaiciusEilutej) == 0) {
        //printf("Ivyko klaida. Neteisingas skaicius.\n");
        return 0;
    } else {

        if (*pradzia != NULL) {
            salinimasSkaiciaus(pradzia);
        } 
        
        *pradzia = NULL;
        ilgasSveikas *pabaiga = NULL;
        
        // Randa ir grazina pirmo iterpiamo elemento i skaiciu pradzia indeksa
        int pirmoElementoIndeksas = pirmoElementoIndekas(skaiciusEilutej);
        
        int ilgis = eilutesElementuSkaicius(skaiciusEilutej);

        if (skaiciusEilutej[0] == '-') {
            iterpimasPirmoElemento(pradzia, &pabaiga, '-');
        }
        
        for (int i = pirmoElementoIndeksas; i < ilgis; i++) {
            if(*pradzia == NULL)
                iterpimasPirmoElemento(pradzia, &pabaiga, skaiciusEilutej[i]);
            else
               iterpimasPabaigosElemento(&pabaiga, skaiciusEilutej[i]);
        }

        if(*pradzia == NULL)
            iterpimasPirmoElemento(pradzia, &pabaiga, '0');
    }
    
    return 1;
}

// Grazina 1, jei skaicius1 >= skaicius2, priesingu atveju - 0
int skaiciusDidesnisArbaLygus(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2) {
    if (skaiciausIlgis(skaicius1) == skaiciausIlgis(skaicius2)) {
        while (skaicius1 != NULL) {
            if (skaicius1->duom > skaicius2->duom)
                return 1;
            else if (skaicius1->duom < skaicius2->duom)
                return 0;
            else {
                skaicius1 = skaicius1->priekin;
                skaicius2 = skaicius2->priekin;
            }
        }
        return 1;
    }
    else if (skaiciausIlgis(skaicius1) < skaiciausIlgis(skaicius2))
        return 0;
    else
        return 1;
}
    
// Grazina 1, jei skaicius1 = skaicius2, priesingu atveju - 0
int arLygus(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2) {
    if (skaiciusDidesnisArbaLygus(skaicius1, skaicius2) == 1 && skaiciusDidesnisArbaLygus(skaicius2, skaicius1) == 1)
        return 1;
    return 0;
}
    
// Grazina 1, jei skaicius1 > skaicius2, priesingu atveju - 0
int arDaugiau(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2) {
   if (skaicius1->duom != '-' && skaicius2->duom != '-') {
        if (skaiciusDidesnisArbaLygus(skaicius1, skaicius2) == 1 && arLygus(skaicius1, skaicius2) == 0)
            return 1;
    } else if (skaicius1->duom == '-' && skaicius2->duom == '-') {
        if (skaiciusDidesnisArbaLygus(skaicius1, skaicius2) == 0 && arLygus(skaicius1, skaicius2) == 0)
            return 1;
    } else if (skaicius1->duom != '-' && skaicius2->duom == '-') {
        return 1;
    }
    return 0;
}
    
// Grazina 1, jei skaicius1 < skaicius2, priesingu atveju - 0
int arMaziau(ilgasSveikas *skaicius1, ilgasSveikas *skaicius2) {
    if (skaicius1->duom != '-' && skaicius2->duom != '-') {
        if (skaiciusDidesnisArbaLygus(skaicius2, skaicius1) == 1 && arLygus(skaicius1, skaicius2) == 0)
            return 1;
    } else if (skaicius1->duom == '-' && skaicius2->duom == '-') {
        if (skaiciusDidesnisArbaLygus(skaicius2, skaicius1) == 0 && arLygus(skaicius1, skaicius2) == 0)
            return 1;
    } else if (skaicius1->duom == '-' && skaicius2->duom != '-') {
        return 1;
    }
    return 0;
}

// pabaiga priskiria skaiciaus pradzia pabaigos adresa
void pabaigosElementas(ilgasSveikas *pradzia, ilgasSveikas **pabaiga) {
    while (pradzia != NULL) {
        if (pradzia->priekin == NULL) {
            *pabaiga = pradzia;
            break;
        }
        pradzia = pradzia->priekin;
    }
}

// Konvertuoja skaiciu i simboli ir grazina ji
char gautiSimboliIsSkaiciaus(int skaicius) {
    return (char) skaicius + 48;
}

// Sudeda pabaiga1 ir pabaiga2, rezultatas - atsakymoPradzia
void skaiciuSudejimas(ilgasSveikas *pabaiga1, ilgasSveikas *pabaiga2, ilgasSveikas **atsakymoPradzia) {
    if (*atsakymoPradzia != NULL) {
        salinimasSkaiciaus(atsakymoPradzia);
    }
    
    *atsakymoPradzia = NULL;
    ilgasSveikas *atsakymoPabaiga = NULL;
   
    int sveikasSkaicius = 0;
    int papildomasSkaicius = 0;
    char laikinasSimbolis;
    do {
        sveikasSkaicius = (pabaiga1->duom - 48) + (pabaiga2->duom - 48) + papildomasSkaicius;
        papildomasSkaicius = sveikasSkaicius / 10;
        sveikasSkaicius = sveikasSkaicius % 10;
        
        laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
 
        if (*atsakymoPradzia == NULL) {
            iterpimasPirmoElemento(atsakymoPradzia, &atsakymoPabaiga, laikinasSimbolis);
        } else {
            iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
        }
        
        pabaiga1 = pabaiga1->atgal;
        pabaiga2 = pabaiga2->atgal;
        
    } while (pabaiga1 != NULL && pabaiga2 != NULL);
     
    
    if (pabaiga1 != NULL && pabaiga2 == NULL) {
        do {
            sveikasSkaicius = (pabaiga1->duom - 48) + papildomasSkaicius;
            papildomasSkaicius = sveikasSkaicius / 10;
            sveikasSkaicius = sveikasSkaicius % 10;
            
            laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
            
            iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
            
            pabaiga1 = pabaiga1->atgal;
            
        } while (pabaiga1 != NULL);
        
    } else if (pabaiga1 == NULL && pabaiga2 != NULL) {
        do {
            sveikasSkaicius = (pabaiga2->duom - 48) + papildomasSkaicius;
            papildomasSkaicius = sveikasSkaicius / 10;
            sveikasSkaicius = sveikasSkaicius % 10;
            
            laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
            
            iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
            
            pabaiga2 = pabaiga2->atgal;
            
        } while (pabaiga2 != NULL);
    
    }
    
    if (papildomasSkaicius != 0) {
        laikinasSimbolis = gautiSimboliIsSkaiciaus(papildomasSkaicius);
        
        iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
    }
    
    while ((*atsakymoPradzia)->duom == '0' && *atsakymoPradzia !=  atsakymoPabaiga) 
        elementoSalinimas(atsakymoPradzia);
}

// Atima pabaiga1 is pabaiga2, rezultatas - atsakymoPradzia
void SkaiciuAtimtis(ilgasSveikas *pabaiga1, ilgasSveikas *pabaiga2, ilgasSveikas **atsakymoPradzia) {
    salinimasSkaiciaus(atsakymoPradzia);

    ilgasSveikas *pabaigaPapildomas1 = pabaiga1;
    ilgasSveikas *pabaigaPapildomas2 = pabaiga2;
    
    if (*atsakymoPradzia != NULL) {
        salinimasSkaiciaus(atsakymoPradzia);
    }
    
    *atsakymoPradzia = NULL;
    ilgasSveikas *atsakymoPabaiga = NULL;
    
    int sveikasSkaicius = 0;
    int papildomasAteminysSkaicius = 0;
    char laikinasSimbolis; 
    
    do {
        if (pabaiga1->duom >= pabaiga2->duom) {
            if (pabaiga1->duom  == '0' && papildomasAteminysSkaicius > 0) {
                sveikasSkaicius = (pabaiga1->duom - 48) + 10  - (pabaiga2->duom - 48) - papildomasAteminysSkaicius;
                
                laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);   
            } else {
                sveikasSkaicius = (pabaiga1->duom - 48)  - (pabaiga2->duom - 48) - papildomasAteminysSkaicius;
                
                laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);  
                papildomasAteminysSkaicius = 0;
            }
            
        } else {
            sveikasSkaicius = (pabaiga1->duom - 48) + 10 - (pabaiga2->duom - 48) - papildomasAteminysSkaicius;
            
            if ((pabaiga1->atgal)->duom != '0') {
                ((pabaiga1->atgal)->duom)--;
                papildomasAteminysSkaicius = 0;
            } else
                papildomasAteminysSkaicius = 1;
                
            laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
        }
        
        if (*atsakymoPradzia == NULL) {
            iterpimasPirmoElemento(atsakymoPradzia, &atsakymoPabaiga, laikinasSimbolis);
        } else {
            iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
        }
        
        pabaiga1 = pabaiga1->atgal;
        pabaiga2 = pabaiga2->atgal;
        
    } while (pabaiga1 != NULL && pabaiga2 != NULL);
    
    if (pabaiga1 != NULL && pabaiga2 == NULL) {
        do {
            if (pabaiga1->duom == '0' && papildomasAteminysSkaicius != 0) {
                /////////////////////////////////////////////////////////////////////////////////////////////printf("uzejo.\n");
                sveikasSkaicius = 10 - papildomasAteminysSkaicius;
                
            }  else {
                sveikasSkaicius = (pabaiga1->duom) - 48 - papildomasAteminysSkaicius ;
                papildomasAteminysSkaicius = 0;
            }
            laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
            
            iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
  
            pabaiga1 = pabaiga1->atgal;
        } while (pabaiga1 != NULL);
    } else if (pabaiga1 == NULL && pabaiga2 != NULL) {
        do {
            iterpimasPradziosElemento(atsakymoPradzia, '1');
  
            pabaiga2 = pabaiga2->atgal;
        } while (pabaiga2 != NULL);
    }

    while ((*atsakymoPradzia)->duom == '0' && *atsakymoPradzia !=  atsakymoPabaiga) 
        elementoSalinimas(atsakymoPradzia);
        
    pabaiga1 = pabaigaPapildomas1;
    pabaiga2 = pabaigaPapildomas2;
}

// Kopijuoja skaiciaus pradzia duomenis (skaiciu reiksmes) i kopijuotiPradzia
void kopijuotiSkaiciu(ilgasSveikas *pradzia, ilgasSveikas **kopijuotiPradzia) {
    *kopijuotiPradzia = NULL;

    ilgasSveikas *kopijuotiPabaiga;
    pabaigosElementas(*kopijuotiPradzia, &kopijuotiPabaiga);


    while (pradzia != NULL) {
	if (*kopijuotiPradzia == NULL) {
	    iterpimasPirmoElemento(kopijuotiPradzia, &kopijuotiPabaiga, pradzia->duom);
	} else {
	    iterpimasPabaigosElemento(&kopijuotiPabaiga, pradzia->duom);
	}

  	pradzia = pradzia->priekin;
    }

    //spausdintiSkaiciu(*kopijuotiPradzia);

}

// Dveju skaiciu - pradzia1 ir pradzia2, sudetis, rezultatas- atsakymoPradzia
// Grazina 1, jei sekmingai sudejo, jei klaida - 0
int sudetis(ilgasSveikas *kopijuotiPradzia1, ilgasSveikas *kopijuotiPradzia2, ilgasSveikas **atsakymoPradzia) {
    salinimasSkaiciaus(atsakymoPradzia);

    ilgasSveikas *pradzia1 = NULL;
    ilgasSveikas *pradzia2 = NULL;
    kopijuotiSkaiciu(kopijuotiPradzia1, &pradzia1);
    kopijuotiSkaiciu(kopijuotiPradzia2, &pradzia2);

    ilgasSveikas *pabaiga1;
    ilgasSveikas *pabaiga2;
    ilgasSveikas *atsakymoPabaiga;
    
    // Randa ir priskiria pabaigos elementu adresus
    pabaigosElementas(pradzia1, &pabaiga1);
    pabaigosElementas(pradzia2, &pabaiga2);

    int arTeigiamasZenklas1, arTeigiamasZenklas2;
    if (pradzia1->duom == '-') {
        arTeigiamasZenklas1 = 0;
        elementoSalinimas(&pradzia1);
    }
    else
        arTeigiamasZenklas1 = 1;
        
    if (pradzia2->duom == '-') {
        arTeigiamasZenklas2 = 0;
        elementoSalinimas(&pradzia2);
    }
    else
        arTeigiamasZenklas2 = 1;
    
    // Suranda ir priskiria skaiciu pradzia1 ir pradzia2 skaiciu skaitmenu skaiciu
    int ilgis2 = skaiciausIlgis(pradzia2);
    int ilgis1 = skaiciausIlgis(pradzia1);

    //spausdintiSkaiciu(pradzia1);
    //spausdintiSkaiciu(pradzia2);

    if (ilgis1 > ilgis2) {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 1) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        } else {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        }
    } else if (ilgis1 < ilgis2) {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 1) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);    
        } else if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');  
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
        } else {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        }
        
    } else {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 1) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            if (skaiciusDidesnisArbaLygus(pradzia1, pradzia2) == 1) {
                SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
            } else {
                SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
                iterpimasPradziosElemento(atsakymoPradzia, '-');
            }
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            if (skaiciusDidesnisArbaLygus(pradzia1, pradzia2) == 1) {
                SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
                iterpimasPradziosElemento(atsakymoPradzia, '-');
            } else {
                SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
            }
        } else {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        }
    }
    
    pabaigosElementas(*atsakymoPradzia, &atsakymoPabaiga);
    while ((*atsakymoPradzia)->duom == '0' && (*atsakymoPradzia) != atsakymoPabaiga)
        elementoSalinimas(atsakymoPradzia);
        
    if ((*atsakymoPradzia)->duom == '-' && (*atsakymoPradzia)->priekin->duom == '0')
        elementoSalinimas(atsakymoPradzia);
        
    return 1;
}

// Skaiciu pradzia1 atima is pradzia2, rezultatas - atsakymoPradzia
// Grazina 1, jei sekmingai ateme, jei klaida - 0
int atimti(ilgasSveikas *kopijuotiPradzia1, ilgasSveikas *kopijuotiPradzia2, ilgasSveikas **atsakymoPradzia) {
    salinimasSkaiciaus(atsakymoPradzia);

    ilgasSveikas *pradzia1 = NULL;
    ilgasSveikas *pradzia2 = NULL;
    kopijuotiSkaiciu(kopijuotiPradzia1, &pradzia1);
    kopijuotiSkaiciu(kopijuotiPradzia2, &pradzia2);

    ilgasSveikas *pabaiga1;
    ilgasSveikas *pabaiga2;
    ilgasSveikas *atsakymoPabaiga;
    
    // Randa ir priskiria pabaigos elementu adresus
    pabaigosElementas(pradzia1, &pabaiga1);
    pabaigosElementas(pradzia2, &pabaiga2);

    int arTeigiamasZenklas1, arTeigiamasZenklas2;
    if (pradzia1->duom == '-') {
        arTeigiamasZenklas1 = 0;
        elementoSalinimas(&pradzia1);
    }
    else
        arTeigiamasZenklas1 = 1;
        
    if (pradzia2->duom == '-') {
        arTeigiamasZenklas2 = 0;
        elementoSalinimas(&pradzia2);
    }
    else
        arTeigiamasZenklas2 = 1;
    
    // Suranda ir priskiria skaiciu pradzia1 ir pradzia2 skaitmenu skaiciu
    int ilgis2 = skaiciausIlgis(pradzia2);
    int ilgis1 = skaiciausIlgis(pradzia1);

    //spausdintiSkaiciu(pradzia1);
    //spausdintiSkaiciu(pradzia2);
    
    if (ilgis1 > ilgis2) {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 1) {
            SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        } else {
            SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        }
    } else if (ilgis1 < ilgis2) {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 1) {
            SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        } else if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            skaiciuSudejimas(pabaiga2, pabaiga1, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        } else {
            SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
        }
        
    } else {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 1) {
            if (skaiciusDidesnisArbaLygus(pradzia1, pradzia2) == 1) {
                SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
            } else {
                SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
                iterpimasPradziosElemento(atsakymoPradzia, '-');
            }
        } else if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            skaiciuSudejimas(pabaiga1, pabaiga2, atsakymoPradzia);
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        } else {
            if (skaiciusDidesnisArbaLygus(pradzia1, pradzia2) == 1) {
                SkaiciuAtimtis(pabaiga1, pabaiga2, atsakymoPradzia);
                iterpimasPradziosElemento(atsakymoPradzia, '-');
            } else {
                SkaiciuAtimtis(pabaiga2, pabaiga1, atsakymoPradzia);
            }
        }
    }
    
    //spausdintiSkaiciu(pradzia1);
    //spausdintiSkaiciu(pradzia2);
    
    pabaigosElementas(*atsakymoPradzia, &atsakymoPabaiga);
    
    return 1;
}

// Sudaugina du skaicius - pradzia1 ir pradzia, rezultatas - atsakymoPradzia
// Grazina 1, jei sekmingai sudaugino, jei klaida - 0
int sandauga(ilgasSveikas *kopijuotiPradzia1, ilgasSveikas *kopijuotiPradzia2, ilgasSveikas **atsakymoPradzia) {
    salinimasSkaiciaus(atsakymoPradzia);

    ilgasSveikas *pradzia1 = NULL;
    ilgasSveikas *pradzia2 = NULL;
    kopijuotiSkaiciu(kopijuotiPradzia1, &pradzia1);
    kopijuotiSkaiciu(kopijuotiPradzia2, &pradzia2);

    ilgasSveikas *pabaiga1;
    ilgasSveikas *pabaiga2;
    ilgasSveikas *atsakymoPabaiga = NULL;

    ilgasSveikas *papildomasAtsakymoPabaiga;
    ilgasSveikas *papildomasPabaiga2;

    // Randa ir priskiria pabaigos elementu adresus
    pabaigosElementas(pradzia1, &pabaiga1);
    pabaigosElementas(pradzia2, &pabaiga2);
    
    papildomasPabaiga2 = pabaiga2;
    
    papildomasAtsakymoPabaiga = atsakymoPabaiga;
 
    int arTeigiamasZenklas1, arTeigiamasZenklas2;
    if (pradzia1->duom == '-') {
        arTeigiamasZenklas1 = 0;
        elementoSalinimas(&pradzia1);
    }
    else
        arTeigiamasZenklas1 = 1;
        
    if (pradzia2->duom == '-') {
        arTeigiamasZenklas2 = 0;
        elementoSalinimas(&pradzia2);
    }
    else
        arTeigiamasZenklas2 = 1;
    
    // Suranda ir priskiria skaiciu pradzia1 ir pradzia2 skaiciu skaitmenu skaiciu
    int ilgis2 = skaiciausIlgis(pradzia2);
    int ilgis1 = skaiciausIlgis(pradzia1);
 
    //spausdintiSkaiciu(pradzia1);
    //spausdintiSkaiciu(pradzia2);
    
    int sveikasSkaicius = 0;
    int papildomasSkaicius = 0;
    int maksimalusSkaiciausIndeksas = 0;
    int pirmoSkaiciausIndeksas = 0;
    int antroSkaiciausIndeksas = 0;
    int papildomasSkaiciusSudejimas = 0;
    char laikinasSimbolis;
    
    while (pabaiga1 != NULL) {
        antroSkaiciausIndeksas = 0;
        papildomasSkaiciusSudejimas = 0;
        papildomasSkaicius = 0;
        while (pabaiga2 != NULL) {
            sveikasSkaicius = (pabaiga1->duom - 48) * (pabaiga2->duom - 48) + papildomasSkaicius;
            papildomasSkaicius = sveikasSkaicius / 10;
            sveikasSkaicius = sveikasSkaicius % 10;
            
            laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
            
            if (*atsakymoPradzia == NULL) {
                iterpimasPirmoElemento(atsakymoPradzia, &atsakymoPabaiga, laikinasSimbolis);
            } else if (maksimalusSkaiciausIndeksas < pirmoSkaiciausIndeksas + antroSkaiciausIndeksas + 1) {
                iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
            } else {
                if (atsakymoPabaiga != NULL) {
                    char turimasSimbolis = atsakymoPabaiga->duom;
                    sveikasSkaicius = (turimasSimbolis - 48) + (laikinasSimbolis - 48) + papildomasSkaiciusSudejimas;
                    papildomasSkaiciusSudejimas = sveikasSkaicius / 10;
                    sveikasSkaicius = sveikasSkaicius % 10;
                    laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
                    
                    
                    atsakymoPabaiga->duom = laikinasSimbolis;
                    
                    atsakymoPabaiga = atsakymoPabaiga->atgal; 
                } else {
                    sveikasSkaicius = (laikinasSimbolis - 48) + papildomasSkaiciusSudejimas;
                    papildomasSkaiciusSudejimas = sveikasSkaicius / 10;
                    sveikasSkaicius = sveikasSkaicius % 10;
                    laikinasSimbolis = gautiSimboliIsSkaiciaus(sveikasSkaicius);
                    iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
                }
                
            }
            
            pabaiga2 = pabaiga2->atgal;
            antroSkaiciausIndeksas++;
        }
        pabaiga1 = pabaiga1->atgal;
        
        
        
        if (maksimalusSkaiciausIndeksas < pirmoSkaiciausIndeksas + antroSkaiciausIndeksas + 1)
                maksimalusSkaiciausIndeksas = pirmoSkaiciausIndeksas + antroSkaiciausIndeksas + 1;
        
        if (papildomasSkaicius > 0 || papildomasSkaiciusSudejimas > 0) {
            laikinasSimbolis = gautiSimboliIsSkaiciaus(papildomasSkaicius + papildomasSkaiciusSudejimas) ;
            iterpimasPradziosElemento(atsakymoPradzia, laikinasSimbolis);
            papildomasSkaicius = 0;
        }

        pabaigosElementas(*atsakymoPradzia, &atsakymoPabaiga);
        if (atsakymoPabaiga != NULL) {
            for (int i = 0; i < pirmoSkaiciausIndeksas + 1 ; i++) {
                atsakymoPabaiga = atsakymoPabaiga->atgal;
            }
        }
        
        pirmoSkaiciausIndeksas++;
        pabaiga2 = papildomasPabaiga2;
    }
    atsakymoPabaiga = papildomasAtsakymoPabaiga;
    
    pabaigosElementas(*atsakymoPradzia, &atsakymoPabaiga);
    while ((*atsakymoPradzia)->duom == '0' && (*atsakymoPradzia) != atsakymoPabaiga)
        elementoSalinimas(atsakymoPradzia);
    
    if ((*atsakymoPradzia)->duom != '0') {
        if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
            iterpimasPradziosElemento(atsakymoPradzia, '-');
        }
    }
    
    return 1;
}

// pradzia1 dalina is pradzia2, dalmuo - atsakymoSveikasisSkaiciusPradzia, dalybos liekana - atsakymoLiekanaPradzia
// Grazina 1, jei sekmingai padalija, jei ne - 0
int dalyba(ilgasSveikas *pradzia1, ilgasSveikas *pradzia2, ilgasSveikas **atsakymoSveikasisSkaiciusPradzia, ilgasSveikas **atsakymoLiekanaPradzia) {
    salinimasSkaiciaus(atsakymoSveikasisSkaiciusPradzia);
    salinimasSkaiciaus(atsakymoLiekanaPradzia);

    ilgasSveikas *pabaiga1;
    ilgasSveikas *pabaiga2;
    //ilgasSveikas *atsakymoPabaiga;

    ilgasSveikas *nulisPradzia;
    ilgasSveikas *nulisPabaiga;
    iterpimasPirmoElemento(&nulisPradzia, &nulisPabaiga, '0');

    ilgasSveikas *atsakymoSveikasisSkaiciusPabaiga;
    ilgasSveikas *atsakymoLiekanaPabaiga;
 
    ilgasSveikas *kopijuotiPradzia1 = NULL;
    ilgasSveikas *kopijuotiPradzia2 = NULL;
    kopijuotiSkaiciu(pradzia1, &kopijuotiPradzia1);
    kopijuotiSkaiciu(pradzia2, &kopijuotiPradzia2);

    // Randa ir priskiria pabaigos elementu adresus
    pabaigosElementas(kopijuotiPradzia1, &pabaiga1);
    pabaigosElementas(kopijuotiPradzia2, &pabaiga2);

    int arTeigiamasZenklas1, arTeigiamasZenklas2;
    if (kopijuotiPradzia1->duom == '-') {
        arTeigiamasZenklas1 = 0;
        elementoSalinimas(&kopijuotiPradzia1);
    }
    else
        arTeigiamasZenklas1 = 1;
        
    if (kopijuotiPradzia2->duom == '-') {
        arTeigiamasZenklas2 = 0;
        elementoSalinimas(&kopijuotiPradzia2);
    }
    else
        arTeigiamasZenklas2 = 1;
    
    // Suranda ir priskiria skaiciu pradzia1 ir pradzia2 skaiciu skaitmenu skaiciu
    int ilgis2 = skaiciausIlgis(kopijuotiPradzia2);
    int ilgis1 = skaiciausIlgis(kopijuotiPradzia1);
 
    //spausdintiSkaiciu(kopijuotiPradzia1);
    //spausdintiSkaiciu(pradzia2);
    
    
    if (arLygus(nulisPradzia, kopijuotiPradzia2) == 1) {
        //printf("Dalyba is nulio negalima.");
        return 0;
    }
    else if (arLygus(kopijuotiPradzia1, kopijuotiPradzia2) == 1) {
        iterpimasPirmoElemento(atsakymoSveikasisSkaiciusPradzia, &atsakymoSveikasisSkaiciusPabaiga, '1');
        
        iterpimasPirmoElemento(atsakymoLiekanaPradzia, &atsakymoLiekanaPabaiga, '0');
    } else if (arMaziau(kopijuotiPradzia1, kopijuotiPradzia2) == 1) {
        iterpimasPirmoElemento(atsakymoSveikasisSkaiciusPradzia, &atsakymoSveikasisSkaiciusPabaiga, '0');
        
        *atsakymoLiekanaPradzia = kopijuotiPradzia1;
    } else {
        ilgasSveikas *dalisPradzia = NULL;
        ilgasSveikas *dalisPabaiga = NULL;
        
        ilgasSveikas *tempPradzia;
        ilgasSveikas *tempPabaiga;
        ilgasSveikas *tempPradzia2;
        
        int kiek = 0;
        char simb;
        
        while (kopijuotiPradzia1 != NULL) {
            kiek = 0;

            if (dalisPradzia == NULL) {

                iterpimasPirmoElemento(&dalisPradzia, &dalisPabaiga, kopijuotiPradzia1->duom);
                kopijuotiPradzia1 = kopijuotiPradzia1->priekin;
                while (!skaiciusDidesnisArbaLygus(dalisPradzia, kopijuotiPradzia2)) {
                    if (kopijuotiPradzia1 == NULL)
                        break;
                    iterpimasPabaigosElemento(&dalisPabaiga, kopijuotiPradzia1->duom);
                    kopijuotiPradzia1 = kopijuotiPradzia1->priekin;
                }
            }

            if (dalisPradzia->duom == '0' && dalisPradzia != dalisPabaiga)
                elementoSalinimas(&dalisPradzia);
                
            if (!skaiciusDidesnisArbaLygus(dalisPradzia, kopijuotiPradzia2)) {
                if (kopijuotiPradzia1 == NULL)
                    break;
                iterpimasPabaigosElemento(&dalisPabaiga, kopijuotiPradzia1->duom);
                kopijuotiPradzia1 = kopijuotiPradzia1->priekin;
            }
            
            if (dalisPradzia->duom == '0' && dalisPradzia != dalisPabaiga)
                elementoSalinimas(&dalisPradzia);


            while (skaiciusDidesnisArbaLygus(dalisPradzia, kopijuotiPradzia2)) {

                 if (dalisPradzia->duom == '0' && dalisPradzia != dalisPabaiga)
                elementoSalinimas(&dalisPradzia);
                
                tempPradzia = NULL;
                tempPabaiga = NULL;

                tempPradzia2 = dalisPradzia;
                while (tempPradzia2 != NULL) {
                    if (tempPradzia == NULL)
                        iterpimasPirmoElemento(&tempPradzia, &tempPabaiga, tempPradzia2->duom);
                    else
                        iterpimasPabaigosElemento(&tempPabaiga, tempPradzia2->duom);
                    tempPradzia2 = tempPradzia2->priekin;
                }
                
                salinimasSkaiciaus(&dalisPradzia);
                
                SkaiciuAtimtis(tempPabaiga, pabaiga2, &dalisPradzia);
                salinimasSkaiciaus(&tempPradzia);
                pabaigosElementas(dalisPradzia, &dalisPabaiga);
                
                if (dalisPradzia->duom == '0' && dalisPradzia != dalisPabaiga)
                    elementoSalinimas(&dalisPradzia);
                    
                    
                
                kiek++;
            }

            simb = kiek + 48;

            if (*atsakymoSveikasisSkaiciusPradzia == NULL)
                iterpimasPirmoElemento(atsakymoSveikasisSkaiciusPradzia, &atsakymoSveikasisSkaiciusPabaiga, simb);
            else
                iterpimasPabaigosElemento(&atsakymoSveikasisSkaiciusPabaiga, simb);
        }

        
        *atsakymoLiekanaPradzia = dalisPradzia;

        if ((*atsakymoLiekanaPradzia)->duom != '0') {
            if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
                iterpimasPradziosElemento(atsakymoLiekanaPradzia, '-');
            } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 0) {
                iterpimasPradziosElemento(atsakymoLiekanaPradzia, '-');
            }
        }
    }


    if ((*atsakymoSveikasisSkaiciusPradzia)->duom != '0') {
            if (arTeigiamasZenklas1 == 1 && arTeigiamasZenklas2 == 0) {
                iterpimasPradziosElemento(atsakymoSveikasisSkaiciusPradzia, '-');
            } else if (arTeigiamasZenklas1 == 0 && arTeigiamasZenklas2 == 1) {
                iterpimasPradziosElemento(atsakymoSveikasisSkaiciusPradzia, '-');
        }
    }

    return 1;
}
