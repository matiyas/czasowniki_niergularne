#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Struktura przechowująca czasowniki nieregularne.
   ------------------------------------------------ */
typedef struct word {
    char slowo[15];             /* W j. polskim             */
    char verb[15];              /* Podst. w j. ang.         */
    char past_simple[15];       /* Past simple w j. ang.    */
    char past_participle[15];   /* Past participle w j. ang */
}word;

/* Wczytywanie ile-u słów do pliku binarnego "verbs".
   -------------------------------------------------- */
void wczytaj(int ile) {
    int i, wszystkie;
    FILE *plik;

    /* Alokacja pamięci na słowa. */
    word *tab = (word *)malloc(ile*sizeof(word));

    /* Wczytywanie ile-u słów do tablicy. */
    for(i=0; i<ile ; ++i){
            printf("%d: ", i+1);  /* Które z kolei słowo wczytujesz. */
            scanf("%15s %15s %15s %15s",
                  tab[i].slowo,
                  tab[i].verb,
                  tab[i].past_simple,
                  tab[i].past_participle
            );
    }

    /* Jeśli plik "verbs" istnieje to ... */
    if(fopen("verbs","rb") != NULL) {
        plik = fopen("verbs", "ab"); /* ... otwórz go w trybie binarnym do dopisywania na koniec pliku. */

    }

    /* W przeciwnym wypadku... */
    else {
        plik = fopen("verbs", "wb"); /*  Utwórz nowy plik i otwórz go w trybie binarny do zapisu. */
    }

    /* Zapis do pliku */
    fwrite(tab, sizeof(word), ile, plik); /* Zapisz tablicę struktur ze słowami do pliku. */
    fclose(plik);                         /* Zamknij plik "verbs".                        */
    free(tab);                            /* Zwolnij pamięć.                              */

    /* Jeśli plik "verbs_count" istnieje to... */
    if(fopen("verbs_count","r") != NULL) {
        plik = fopen("verbs_count", "r+");/* otwórz go w trybie do odczytu i zapisu.                */
        fscanf(plik, "%d", &wszystkie);   /* Sprawdź ile słów dotychczas wczytano do pliku "verbs". */
        wszystkie += ile;                 /* Zwiększ ilość o aktualnie wczytane słowa.              */
        fclose(plik);                     /* Zamknij plik.                                          */
        plik = fopen("verbs_count", "w"); /* Utwórz ponownie plik "verbs_count".                    */
        fprintf(plik, "%d", wszystkie);   /* Uaktualnij plik.                                       */
        fclose(plik);                     /* Zamknij plik.                                          */

    }

    /* W przeciwnym wypadku... */
    else {
        plik = fopen("verbs_count", "w");/* Otwórz nowy plik w trybie do zapisu.                                   */
        fprintf(plik, "%d", ile);  /* Wczytywano słowa poraz pierwszy, więc ilość wszystkich wczytanych słów */
                                   /* jest równa aktualnie wczytanym słowom.                                 */
        fclose(plik);              /* Zamknij plik.                                                          */
    }
}

/* Wyświetl wszystkie zapisane dotąd słowa z pliku "verbs".
   -------------------------------------------------------- */
void drukuj() {
    int ile_w_pliku, i;
    FILE *plik;
    word *tab;

    /* Jeśli plik "verbs_count" istnieje to ... */
    if(fopen("verbs_count", "r") != NULL) {
        plik = fopen("verbs_count", "r");           /* Otwórz plik przechowujący ilość słów w pliku "verbs". */
        fscanf(plik, "%d", &ile_w_pliku);           /* Odczytaj ile słów.                                    */
        fclose(plik);                               /* Zamknij plik                                          */
        tab = (word *)malloc(ile_w_pliku*sizeof(word)); /* Zaalokuj pamięć do wczytania słów.                */

        /* Sprawdź czy plik "verbs" istnieje. */
        if(fopen("verbs", "rb") != NULL) {
            plik = fopen("verbs", "rb");                 /* Otwórz plik "verbs" w trybie binarnym do odczytu. */
            fread(tab, sizeof(word), ile_w_pliku, plik); /* Odczytaj wszystkie słowa z pliku.                 */
            fclose(plik);                                /* Zamknij plik.                                     */

            /* Wyświetl na ekranie wszystkie wczytane słowa. */
            printf("\n");
            for(i=0; i<ile_w_pliku; ++i){
                printf("%d: %15s %15s %15s %15s\n",
                       i+1,
                       tab[i].slowo,
                       tab[i].verb,
                       tab[i].past_simple,
                       tab[i].past_participle);
            }
            printf("\n");
        }

        /* Jeśli mimo tego, że plik "verbs_count" istnieje i podaje pewną liczbę słów,
           nie ma pliku "verbs", to ... */
        else {
            printf("Wystąpił błąd. Plik o nazwie ""verbs" " nie istnieje.\n"); /* Wyświetl komunikat o błędzie */
        }
    }

    /* Jeśli nie ma pliku "verbs_count" to ... */
    else {
        printf("Brak wczytanych słów.\n");
    }
}

void nauka(int down, int up) {
    srand(time(NULL));

    char v[20], ps[20], pp[20];
    int ile, i, j, x, zlicz, *wylosowane;
    FILE *plik;
    word *tab;

    if(fopen("verbs_count", "r") != NULL) {
        plik = fopen("verbs_count", "r");
        fscanf(plik, "%d", &ile);
        fclose(plik);

        if(down < 1 || up > ile)
            return;

        if(fopen("verbs", "r") != NULL) {
            plik = fopen("verbs", "rb");
            tab = (word *)malloc(ile*sizeof(word));
            fread(tab, sizeof(word), ile, plik);
            fclose(plik);

            wylosowane = (int *)malloc((up-down)*sizeof(int));

            j = 1;
            while(1){
                for(i=0; i<(up-down); ++i)
                    wylosowane[i] = 0;
                zlicz = 0;

                while(zlicz < (up-down+1)) {
                x = (rand()%(up-down+1))+down-1;
                i = 0;

                    while(1){
                        if(x == wylosowane[i] || i == zlicz)
                            break;
                        ++i;
                    }

                    if(i == zlicz) {
                        wylosowane[zlicz] = x;
                        ++zlicz;

                        printf("%d: %s ", j, tab[x].slowo);
                        scanf("%s %s %s", v, ps, pp);

                        if(strcmp(tab[x].verb, v) != 0)
                            printf("Źle verb (%s)\n", tab[x].verb);
                        if(strcmp(tab[x].past_simple, ps) != 0)
                            printf("Źle past simple (%s)\n", tab[x].past_simple);
                        if(strcmp(tab[x].past_participle, pp) != 0)
                            printf("Źle past participle (%s)\n", tab[x].past_participle);
                        else
                            printf("OK\n");
                        ++j;

                    } /* if(i == zlicz) */
                } /* while(zlicz < (up-down+1)) */
            } /* while(1) */
        } /* if(fopen("verbs", "r") != NULL) */

        else {
            printf("Wystąpił błąd. Plik o nazwie verbs nie istnieje. \n");
            return;
        }
    } /* if(fopen("verbs_count", "r") != NULL) */

    else {
        printf("Wystąpił błąd. Brak pliku o nazwie verbs_count.\n");
        return;
    }
}

/* Edytuj pojedyńcze słowa.
   ------------------------ */
void edycja(int slowo, int forma) {
    int ile;
    FILE *plik;
    word *tab;

    /* Jeśli plik "verbs_count" istnieje to ... */
    if(fopen("verbs_count", "r") != NULL ) {
        plik = fopen("verbs_count", "r"); /* Otwoórz plik "verbs_count" w trybie do odczytu. */
        fscanf(plik, "%d", &ile);         /* Wczytaj liczbę dotychczas wczytanych słów.      */
        if(slowo > ile) {
            printf("Dotychczas wczytano %d słów.\n",ile);
            return;
        }
        fclose(plik);                     /* Zamknij plik.                                   */

        /* Jeśli plik "verbs" istnieje to ... */
        if(fopen("verbs","r") != NULL) {

            /* Odczytywanie słów. */
            plik = fopen("verbs", "rb");            /* Otwórz plik w trybie binarnym do odczytu. */
            tab = (word *)malloc(ile*sizeof(word)); /* Zaalokuj pamięć na słowa.                 */
            fread(tab, sizeof(word), ile, plik);    /* Odczytaj wszystkie słowa z pliku.         */
            fclose(plik);                           /* Zamknij plik.                             */

            /* Edycja wybranego słowa. I jego formy. */
            switch(forma) {
            case 1:
                printf("(%s): ", tab[slowo].slowo);
                scanf("%s", tab[slowo].slowo);
                break;
            case 2:
                printf("(%s): ", tab[slowo].verb);
                scanf("%s", tab[slowo].verb);
                break;
            case 3:
                printf("(%s): ", tab[slowo].past_simple);
                scanf("%s", tab[slowo].past_simple);
                break;
            case 4:
                printf("(%s): ", tab[slowo].past_participle);
                scanf("%s", tab[slowo].past_participle);
                break;
            }

            printf("%s\n",tab[slowo].slowo);
            /* Zapis tablicy do pliku. */
            plik = fopen("verbs", "wb");          /* Otwórz plik.             */
            fwrite(tab, sizeof(word), ile, plik); /* Zapisz tablicę do pliku. */
            fclose(plik);                         /* Zamknij plik.            */
            free(tab);                            /* Zwolnij pamięć.          */
        }


        /* Jeśli mimo, że plik "verbs_count" istnieje, ale plik "verbs" nie istnieje ... */
        else {
            printf("Wystąpił błąd. Plik o nazwie verbs nie istnieje.\n"); /* Wyświetl komunikat o błędzie. */
        }
    }
    else {
        printf("Brak wczytanych słów.\n"); /* Jeśli brak pliku "verbs_count" to program powinien sprawdzić, */
                                           /* czy plik "verbs" istnieje i wczytać go do statycznej tablicy. */
    }
}

/* Menu programu
   ------------- */
void menu() {
    int wybor, ile_slow, i, ktore, forma, down, up;

    do {
        printf("[1] Wczytaj nowe słowa\n"
               "[2] Wyświetl wszystkie słowa\n"
               "[3] Nauka\n"
               "[4] Edytuj słowa\n"
               "[0] Koniec\n"
               ":"); /* Wyświetl dostępne opcje. */
        scanf("%d", &wybor);    /* Wczytaj wybór opcji      */

        /* Po dokonaniu wyboru wykonaj odpowiednie funkcje. */
        switch(wybor) {

        /* Wczytywanie słów */
        case 1:
            printf("Ile słów chcesz wczytać? ");
            scanf("%d", &ile_slow);
            wczytaj(ile_slow);
            printf("\n");
            break;

        /* Wyświetlanie słów */
        case 2:
            drukuj();
        break;

        case 3:
            printf("Które słowa chcesz wczytać (od - do)? ");
            scanf("%d - %d", &down, &up);
            nauka(down, up);
            break;

        /* Edycja słów */
        case 4:
            drukuj();
            printf("\nKtóre słowo chcesz edytować? ");

            scanf("%d", &ktore);
            printf("[1] Polska nazwa\n"
                   "[2] Angielska nazwa\n"
                   "[3] Past Simple\n"
                   "[4] Past Participle\n"
                   "[0] Powrót\n"
                   "Wybierz formę słowa, które chcesz edytować: ");
            scanf("%d", &forma);
            if(forma > 0 && forma <= 4)
                edycja(ktore-1, forma);
            printf("\n");
            break;
        }

    } while(wybor != 0); /* Wyświetlaj menu dopóki ne zostanie wybrane 0. */
}

int main() {
    printf("Czasowniki nieregularne v0.21\n\n");
    menu();

    return 0;
}
