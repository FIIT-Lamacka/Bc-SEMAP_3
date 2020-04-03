#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
TROCHU SOM SI TO STAZIL A OPYTAL SA CI TO NEMOZE HLADAT AJ PALINDROMY MIESTO IBA POCTU PISMEN NA DOPLNENIE
NAVRH RIESENIA: ABSOLUTNE NEVIEM CO MAM ROBIT. BUDEM MUSIET PORIADNE POPREMYSLAT. AKO MOZE POCITAC VEDIET SPRAVNE NA SPRAVNU
POZICIU DOPLNIT PALINDROM

OK TU DENIS Z BUDUCNOSTI. PO PREMARNENEJ NOCI KDE SOM SA POKUSAL ZISTIT AKO TO RIESIT MA NAPADLO RIESENIE
    VYTVORIM LOOP KTORY AUTOMATICKY DOPLNI PISMENO Z JEDNEJ STRANY DO DRUHEJ. NEVYSLO TO. NEVYCHADZALI ZDROVNA EFEKTIVNE PALINDROMY
    ZISTIL SOM ZE Z ABB MY TO VYTVORILO BBABB JE TO SICE PALINDROM ALE NIE NAJEFEKTIVNEJSI A NAJKRATSI CO SA DA VYTVORIT

ZNOVA ZACALI MYSLIENKOVE POCHODY. AKO ZISTIM ZE KTORA STRANA JE TA "SPRAVNA" NA DOPLNENIE. ABY TO DOPLNILO Z ABB NA ABBA A NIE NA BBABB
NAPADLO MA POUZIT TOTO RIESIENIE. REKURZIVNE VOLANIE FUNKCII KTORE VEZMU ORIGINALNY TEXT A ZAVOLAJU SAMI SEBA ABY DOPLNILI DO OPACNEJ STRANY PISMENO

    NA TOTO BUDEM POTREBOVAT FUNKCIU NA ZISTOVANIE CI JE SLOVO PALINDROM, FUNKCIU KTORA PREFERUJE PRAVU STRANU NA DOPLNENIE A JEDNA CO LAVU

REKURZIA SA BUDE OPAKOVAT DOVTEDY DOKIAL SA NENAJDE PALINDROM.
*/

int is_palindrome(char input[]);
void right_dominant(char input[],char vysledok[], int *longest); //HLADANIE PALINDROMU JE AKO BONUS
void left_dominant(char input[],char vysledok[], int *longest);
/*
worst-case tohoto programu je to ze by boli vsetky pismena rozne
medium-case su stringy kde sa nejako uz pismena opakuju
best-case je ciastocne vyskladany alebo hotovy palindrom

program je v podstate brute-force cize ma ylozitost O(n^2) ale vysledky sa drasticky lisia medzi worst case a medium case a best case

testy:
==============
worst-case(26 unikatnych pismen) 50 - 70 sekund
medium-case(26 pismen, niektore sa opakuju) 2-20 sekund
best case(26 pismenovy SKORO palindrom) niekolko milisekund az 1 sekunda
*/

// v prilohe som prilozil aj graf worst-case ked som postupne pridaval pismena

int main() {
    char input[1001], vysledok[2001]; //VYSLEDOK MA DLZKU 2000 LEBO NAJDLHSI PALINDROM CO SA DA VYTVORIT MA IBA DVOJNASOBNU DLZKU
    int input_len, longest = 9999; //LONGEST - DLZKA DOTERAZ NAJKRATSIEHO NAJDENEHO PALINDROMU

    while (fgets(input, 1000, stdin) != NULL) { //NACITAVANIE DOKYM NIE JE VSTUP IBA ENTER
        if (input[1] == '\0')
        return 0;

        input_len = strlen(input);
        input[input_len - 1] = '\0'; //Vyradenie \n z pola
        input_len--;

        if (is_palindrome(input)) { //OKONTROLOVANIE CI NIE JE VSTUP PALINDROM
            printf("0\n\n");
            continue;
        }

        left_dominant(input, vysledok, & longest); //VOLANIE REKURZIVNEJ FUNKCIE CO DOPLNI ZNAK PRV Z LAVA (HLADANIE NAJKRATSIEHO PALINDROMU)
        right_dominant(input, vysledok, & longest); //VOLANIE REKURZIVNEJ FUNKCIE CO DOPLNI ZNAK PRV Z LAVA

        printf("Najkratsi najdeny palindrom: \"%s\"; \nPocet pridanych pismen: %d\n\n", vysledok, longest - input_len);

        longest = 9999; //RESET
  }
}

int is_palindrome(char input[]) {
    int i, strlen_input = strlen(input);

    for (i = 0; i < strlen_input; i++) {
        if (input[i] != input[strlen_input - 1 - i]) //SKEN ZOZADU A ZPREDU AK SA NIECO NEROVNA, NIE JE TO PALINDROM
        return 0;
    }

    return 1;
}
void left_dominant(char input[],char vysledok[], int * longest) {
    /*
    REKURZIVNA FUNKCIA KTORA DOPLNI PRI PRVEJ NEROVNOSTI ZNAKOV ZNAK Z LAVA NAPR. AABCA UROBI NA ACABCA
    A POSLE REKURZIVNE DALEJ NA DOPLNENIE DO OBOCH STRAN
    */
    char copy_input[strlen(input) + 2]; //VYTVORENIE LOKALNEJ KOPIE ABY SA NEPREPISALA PRI UPRAVE ORIGINALNA + MIESTO PRE NOVY ZNAK
    int i, j;

    if (strlen(input) >= * longest) { //SETRENIE VYKONU. FUNKCIA NEPOKRACUJE AK BY MALA NAJST NIECO DLHSIE AKO NASLI FUNKCIE PRED NOU
        return; //AK JE LONGEST 14 TAK SA UKONCIA VSETKY REKURZIE CO MAJU DLZKU VACSIU ROVNU 14
    }

    for (i = 0; i <= strlen(input); i++) {
        copy_input[i] = input[i]; //PREKOPIROVANIE ORIGINALNEHO STRINGU DO LOKALNEJ KOPIE
    }

    for (i = 0; i < strlen(copy_input); i++) {
        if (copy_input[i] != copy_input[strlen(copy_input) - 1 - i]) { //KONTROLA ZNAKOV ZNAK PO ZNAKU KYM SA NAJDE NEZHODA
        for (j = strlen(input); j >= strlen(copy_input) - 1 - i; j--) {
            copy_input[j + 1] = copy_input[j];                  //VYTVORENIE MIESTA PRE NOVE PISMENO NA PRAVOM KRIDLE PALINDROMU
        }
        copy_input[strlen(copy_input) - 1 - i] = copy_input[i]; //DOPLNENIE PISMENA NA PRAZDNE MIESTO OPROTI Z LAVA
        break;                                                  //UKONCENIE LOOPU
        }
    }
    if (is_palindrome(copy_input)) {                    //AK BY NAHODOU FUNKCIA PREDOSLOU UPRAVOU VYTVORILA PALINDROM
        if (strlen(copy_input) < * longest)             // A JEJ DLZKA JE NIZSIA AKO NAJKRATSIA DOTERAZ NAJDENA
            *longest = strlen(copy_input);                 //ULOZI NAJKRATSIU DLZKU
            for(i = 0; i <= strlen(copy_input); i++){
                vysledok[i]=copy_input[i];              //A ULOZI/PREPISE NAJKRATSI PALINDROM
            }
        //printf("%s %d\n",copy_input);
        return;
    }
                                                    //AK SA PALINDROM NENASIEL
    right_dominant(copy_input, vysledok, longest); //DALSIE VOLANIE DOPRAVA
    left_dominant(copy_input, vysledok, longest); //DALSIE VOLANIE DOLAVA
    return;

}

void right_dominant(char input[],char vysledok[], int * longest) {
    /*
    REKURZIVNA FUNKCIA KTORA DOPLNI PRI PRVEJ NEROVNOSTI ZNAKOV ZNAK Z PRAVA NAPR. AABCA UROBI NA AABCAA
    A POSLE REKURZIVNE DALEJ NA DOPLNENIE DO OBOCH STRAN
    */

    char copy_input[strlen(input) + 2]; //VYTVORENIE LOKALNEJ KOPIE ABY SA NEPREPISALA PRI UPRAVE ORIGINALNA + MIESTO PRE NOVY ZNAK
    int i, j;

    if (strlen(input) >= * longest) {//SETRENIE VYKONU. FUNKCIA NEPOKRACUJE AK BY MALA NAJST NIECO DLHSIE AKO NASLI FUNKCIE PRED NOU
        return;     //AK JE LONGEST 14 TAK SA UKONCIA VSETKY REKURZIE CO MAJU DLZKU VACSIU ROVNU 14
    }

    for (i = 0; i <= strlen(input); i++) {
        copy_input[i] = input[i]; //PREKOPIROVANIE ORIGINALNEHO STRINGU DO LOKALNEJ KOPIE
    }

    for (i = 0; i < strlen(copy_input); i++) {
        if (copy_input[i] != copy_input[strlen(copy_input) - 1 - i]) { //KONTROLA ZNAKOV ZNAK PO ZNAKU KYM SA NAJDE NEZHODA
            for (j = strlen(input); j >= i; j--) {
                copy_input[j + 1] = copy_input[j];      //VYTVORENIE MIESTA PRE NOVE PISMENO NA LAVOM KRIDLE PALINDROMU
            }
            copy_input[i] = copy_input[strlen(copy_input) - 1 - i]; //RIGHT DOMINANT - CIZE FUNKCIA PREFERUJE DOPLNANIE Z PRAVEHO KRIDLA NA LAVE
            break;
        }
    }

    if (is_palindrome(copy_input)) { //AK BY SA PODARILO PREDOSLIM KROKOM VYTVORIT PALINDROM
        if (strlen(copy_input) < * longest) //OKONTROLUJE SA JEHO DLZKA, AK JE KRATSIA AKO HOCIJAKA DOTERAZ NAJDENA TAK SA ULOZI
        *longest = strlen(copy_input);
        for(i = 0; i <= strlen(copy_input); i++){ //AK BY BOL DOTARAZ NAJKRATSI NAJDENY TAK SA TIEZ ULOZI A PREPISE DOTERAZ NAJKRATSI PALINDROM
            vysledok[i]=copy_input[i];
        }
        //printf("%s %d\n",copy_input);
        return;
    }

    right_dominant(copy_input, vysledok, longest); //AK SA NENASIEL PALINDROM, VOLANIE DOPLNENIA Z PRAVA A Z LAVA
    left_dominant(copy_input,vysledok, longest);
    return;
}
