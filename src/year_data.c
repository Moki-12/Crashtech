#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int annee;
    int accidents;
    int severite[4];
} year_data;

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void initTab (year_data *tab){
    for (int i=0; i<20; i++){
        tab[i].annee = 2005 + i;
        tab[i].accidents = 0;
        for (int j=0; j<4; j++){
            tab[i].severite[j] = 0;
        }
    }
}

int trouver_indice (year_data *tab, int année){
    if (tab == NULL){
        return -1;
    }
    for (int i=0; i<20; i++){
        if (tab[i].annee == année){
            return i;
        }
    }
    return -1;
}


void lire_fichier_année_accidents(FILE *f, year_data *tab, char *nom_fichier){

    if (nom_fichier == NULL || tab == NULL){
        exit(2);
    }

    f = fopen(nom_fichier, "r");

    if (f == NULL){
        perror("Erreur ouverture fichier");
        exit(2);
    }

    char ligne[200];
    int annee_fichier;
    int accident_act;
    int victime;

    int annee_prec = -1;
    int accident_prec = -1;

    fgets(ligne, sizeof(ligne), f); // Ignore l'en-tête

    while (fgets(ligne, sizeof(ligne), f) != NULL){

        if (sscanf(ligne, "%d;%d;%*d;%*d;%*d;%d",
                   &annee_fichier,
                   &accident_act,
                   &victime) != 3){
            continue;
        }

        int i = trouver_indice(tab, annee_fichier);

        if (i == -1){
            continue;
        }
        
        // Comptage des accidents
        if (annee_fichier != annee_prec ||
            accident_act != accident_prec){

            tab[i].accidents++;

            annee_prec = annee_fichier;
            accident_prec = accident_act;
        }

        // Comptage des victimes par sévérité
        if (victime >= 1 && victime <= 4){
            tab[i].severite[victime - 1]++;
        }
    }

    fclose(f);
}


void affichage (year_data *tab, int annee){
    if (tab == NULL){
        exit(4);
    }
    int p = annee - 2005;
    if(p <0 || p>= 20){
        printf("L'année est hors de portée.\n");
        exit(5);
    }
    printf("-----En %d-----\n", annee);
    printf("Nombre d'accident : %d\n", tab[p].accidents);
    printf("indemnes          : %d\n", tab[p].severite[0]);
    printf("tués              : %d\n", tab[p].severite[1]);
    printf("Blésés graves     : %d\n", tab[p].severite[2]);
    printf("Blésés légés      : %d\n", tab[p].severite[3]);
}


void menu(year_data *tab){
    if(tab == NULL){
        exit(6);
    }
    int annee;
    int choix;
    printf("============================\n");
    printf("STATISTIQUES PAR ANNEE\n"),
    printf("============================\n");
    do{
        printf("Quelle année souhaitez-vous consulter ?\n");
            if (scanf("%d", &annee) != 1){
                viderBuffer();
            }
            else if(annee >= 2005 && annee <= 2024 ){
                affichage(tab, annee);
            }
            else{
                printf("l'année n'est pas valide");
            }
        printf("Souhaitez-vous consulter une autre année ?\n-1 Oui \n-0 Non (quitter))\nChoix: ");
        if(scanf ("%d", &choix) != 1){
            printf("Erreur\n");
            viderBuffer();
        }
    }while(choix == 1);

}


int main (int arc, char **argv){
    year_data tab[20];
    FILE *f = fopen(argv[1], "r");
initTab(tab);
lire_fichier_année_accidents (f, tab, argv[1]);
menu(tab);
    return 0;
}
