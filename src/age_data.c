#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct chainon {
    int age;
    int tab[3][3];
    struct chainon *suivant;
} age_data;

typedef struct liste {
    age_data *tete;
} list_age;


age_data *creation(int a){
age_data *nv = malloc(sizeof(age_data));
if(nv == NULL){
exit(1);
}
nv->age = a;
for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
        nv->tab[i][j] = 0;
    }
}
return nv;
}

void remplir_chainon (age_data *a, int g, int t){
    if (a == NULL){
        exit(4);
    }
        int indice_g = g-1;
        int indice_t = t-1;
        if (indice_t >= 0 && indice_t < 3 && indice_g >= 0 && indice_g < 3){
        a->tab[indice_t][indice_g]++;
        }
}

void ajouter (list_age *l, age_data *a){
    if (l == NULL || a == NULL){
        exit(5);
    }
    a->suivant = l->tete;
    l->tete = a;
}

age_data *verif_exist (list_age *l, int age){
    if (l == NULL){
        exit(3);
    }
    age_data *a = l->tete;
    while (a != NULL){
        if (a->age == age){
            return a;
        }
        a = a->suivant;
    }
    age_data *nv = creation(age);
    ajouter(l, nv);
    return nv;
}

void lire_ficher (FILE *f, age_data *a_d, char *nom_fichier, list_age *l){
    if (f == NULL || a_d == NULL || nom_fichier == NULL){
        exit(2);
    }
    int age;
    int année;
    int naissance;
    int gender;
    int types;
    char ligne [200];
    f = fopen (nom_fichier, "r");
    fgets (ligne, 199, f);
    while ((fgetc(f)) != EOF){
        fseek (f, -1, SEEK_CUR);
        fscanf (f, "%d;%*d;%*d;%*d;%d;%*d;%d;%d", &année, &types, &gender, &naissance);
        age = année - naissance;
        a_d = verif_exist(l, age);
        remplir_chainon(a_d, gender, types);
        fgets (ligne, 199, f);
    }
    fclose(f);
}

float calcul_pct (int valeur, int total){
    if (total == 0){
        return 0.0f;
    }
    return ((float)valeur/total)*100;
}

int calcul_total_filtre (age_data *a, int filtre_type, int filtre_genre){
    if (a == NULL){
        return 0;
    }
    int total = 0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if ((filtre_type == 0 || filtre_type == i+1) && (filtre_genre == 0 || filtre_genre == j+1)){
                total += a->tab[i][j];
            }
        }
    }
    return total;
}

void affichage (list_age *l, int  filtre_type, int filtre_genre){
    if (l == NULL){
        exit(7);
    }
    age_data *courant = l->tete;
    while (courant != NULL){
        printf ("%d ans : ", courant->age);
        int total_tous = calcul_total_filtre (courant, 0, 0);
        int total_filtre = calcul_total_filtre(courant, filtre_type, filtre_genre);
        int pct_filtre = calcul_pct (total_filtre, total_tous);
        printf ("   %f%\n", pct_filtre);
        courant = courant->suivant;
    }
}

int main (int argc, char **argv){
    list_age *Liste = NULL;
    age_data *Chaine = NULL;
    
}
