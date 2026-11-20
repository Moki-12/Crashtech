#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int année;
    int accidents;
    int severite[4];
} year_data;

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void initTab (year_data tab){
    for (int i=0; i<20; i++){
        tab[i].année = 2005 + i;
        tab[i].accidents = 0;
        for (int j=0; j<4; j++){
            tab[i].severite[j] = 0;
        }
    }
}


void lire_fichier_severite (FILE *f, year_data tab, char *nom_fichier, int i){
    if (f == NULL || nom_fichier == NULL){
        exit(3);
    }
    int victime;
    fscanf(f, "%*s;%*s;%*s;%d", &victime); // on alors tout ca dans la fonction dapres
    if (victime == 1){
        tab[i].severite[0]++;
    }
    else if (victime == 2){
        tab[i].severite[1]++;
    } pour laquelle il

//souhaite consulter les statistiques. L’utilisateur pourra regarder

//autant d’années qu’il le souhaite et quittera le programm
    else if (victime == 3){
        tab[i].severite[2]++;
    }
    else {
        tab[i].severite[3]++;
    }
}

void lire_fichier_année_accidents (FILE *f, year_data tab, char *nom_fichier){
    if (f == NULL || nom_fichier == NULL){
        exit(2);
    }
    char ligne [200];
    int i = 0;
    int année_fichier;
    int accident_prec = 0;
    int accident_act;
    f = fopen(nom_fichier, "r");
    while ((fgetc(f)) != EOF){
        fseek(f, -1, SEEK_CUR);
    fscanf (f, "%d;%d", &année_fichier, &accident_act);
    if (année_fichier != tab[i].année){
        i++;
    }
    if (accident_act != accident_prec){
        tab[i].accidents++;
        accident_prec = accident_act;
    }
    lire_fichier_severite(f, &tab, nom_fichier, i);
    fgets (ligne, 199, f);
    }
    fclose(f);
}

int main (int arc, int **argv){
    year_data tab[20];
initTab(&tab);
lire_fichier_année_accidents (argv, &tab, arc);
menu(&tab);
    return 0;
}



