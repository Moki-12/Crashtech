#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TITRE   "\033[1;36m"
#define AGE_COL "\033[1;33m"
#define BLEU    "\033[0;34m"
#define ROSE    "\033[0;35m"
#define ROUGE   "\033[0;31m"
#define RESET   "\033[0m"

#define PAS_PCT_GENRE 0.2f
#define PAS_PCT_TYPE 10.0f
#define LARGEUR_BARRE_GENRE 20
#define LARGEUR_BARRE_TYPE  10

typedef struct chainon {
    int age;
    int tab[3][3];
    struct chainon *suivant;
} age_data;

typedef struct liste {
    age_data *tete;
} list_age;


void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

age_data *creation(int a){
age_data *nv = malloc(sizeof(age_data));
if(nv == NULL){
exit(1);
}
nv->age = a;
nv->suivant = NULL;
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
        int indice_g;
    if (g == 1) indice_g = 0;
    else if (g == 2) indice_g = 1;
        else indice_g = 2;
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
    if(l == NULL){
        exit(3);
    }
    age_data *p = l->tete;
    age_data *prece = NULL;
    while(p != NULL && p->age < age){
        prece = p;
        p = p->suivant;
    }
    if(p!= NULL && p->age == age){
        return p;
    }
    age_data *nv = creation(age);
    nv->suivant = p;
    if(prece == NULL){
        l->tete = nv;
    }
    else{
        prece->suivant = nv;
    }
    return nv;
}

void libere_liste(list_age *l){
    if (l == NULL){
        exit(1);
    }
    age_data *p = l->tete;
    age_data *suivant = NULL;

    while(p!= NULL){
        suivant = p->suivant;
        free(p);
        p = suivant;
    }
}

void lire_ficher (FILE *f, age_data *a_d, char *nom_fichier, list_age *l){
    /*if (f == NULL || a_d == NULL || nom_fichier == NULL){
        exit(2);
    }*/
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

char *nom_type(int t){
    switch(t){
        case 1: return "Conducteurs";
        case 2 : return "Passagers";
        case 3: return "Piétons";
        default: return "Tous les types";
    }
}

char *nom_genre(int s){
    switch (s){
        case 1: return "Hommes";
        case 2: return "Femmes";
        case 3: return "pas de genre";
        default: return "Tous les genres";
    }
}

void afficher_colonne_barre(float pct, float pas_pct, int largeur_max, char *couleur) {
    int bloc = (int)(pct / pas_pct);
    if (bloc < 0) {
        bloc = 0;
    }
    if (bloc > largeur_max) {
        bloc = largeur_max;
    }

    printf("%5.1f%% %s", pct, couleur);
    for (int i = 0; i < bloc; i++) {
        printf('#');
    }
    printf("%s", RESET);
    for (int i = bloc; i < largeur_max; i++) {
        printf(' ');
    }
}

void affichage_genre(list_age *l, int filtre_type, int filtre_genre) {
    if (l == NULL) {
        exit(7);
    }
    int total_h = 0;
    int total_f = 0;
    age_data *courant = l->tete;
    while (courant != NULL) {
        total_h += calcul_total_filtre(courant, filtre_type, 1);
        total_f += calcul_total_filtre(courant, filtre_type, 2);
        courant = courant->suivant;
    }
    int total_hf = total_h + total_f;
    float pct_total_h = calcul_pct(total_h, total_hf);
    float pct_total_f = calcul_pct(total_f, total_hf);

    printf("==============================================================\n");
    printf("%s REPARTITION PAR AGE - %-22s (1 # = 0.2 %%)%s\n", COULEUR_TITRE, nom_type(filtre_type), RESET);
    printf("==============================================================\n");
    printf("%s  AGE      | HOMMES                    FEMMES%s\n", COULEUR_TITRE, RESET);
    printf("-------------------------------------------------------------\n");

    courant = l->tete;
    while (courant != NULL) {
        int nb_h = calcul_total_filtre(courant, filtre_type, 1);
        int nb_f = calcul_total_filtre(courant, filtre_type, 2);
        float pct_h = calcul_pct(nb_h, total_hf);
        float pct_f = calcul_pct(nb_f, total_hf);

        printf(" %s%3d ans%s | ", COULEUR_AGE, courant->age, RESET);
        if (filtre_genre == 0 || filtre_genre == 1) {
            afficher_colonne_barre(pct_h, 0.2f, LARGEUR_BARRE_GENRE, BLEU);
        } else {
            printf("       %-*s", LARGEUR_BARRE_GENRE, "");
        }
        printf("  ");
        if (filtre_genre == 0 || filtre_genre == 2) {
            afficher_colonne_barre(pct_f, 0.2f, LARGEUR_BARRE_GENRE, ROSE);
        } else {
            printf("       %-*s", LARGEUR_BARRE_GENRE, "");
        }
        printf('\n');
        courant = courant->suivant;
    }

    printf("==============================================================\n");
    printf(" Total hommes : %5.1f %%        Total femmes : %5.1f %%\n", pct_total_h, pct_total_f);
    printf("==============================================================\n");
}

void affichage_type(list_age *l, int filtre_type, int filtre_genre) {
    if (l == NULL) {
        exit(8);
    }
    int total_retenu = 0;
    age_data *courant = l->tete;
    while (courant != NULL) {
        total_retenu += calcul_total_filtre(courant, filtre_type, filtre_genre);
        courant = courant->suivant;
    }

    printf("==================================================================\n");
    printf("%s REPARTITION PAR TYPE - %-21s (1 # = 10 %%)%s\n", COULEUR_TITRE, nom_genre(filtre_genre), RESET);
    printf("==================================================================\n");
    printf("%s  AGE      | CONDUCTEURS       PASSAGERS         PIETONS%s\n", ROUGE, RESET);
    printf("------------------------------------------------------------------\n");

    courant = l->tete;
    while (courant != NULL) {
        int total_age = calcul_total_filtre(courant, 0, filtre_genre);
        int nb_cond = calcul_total_filtre(courant, 1, filtre_genre);
        int nb_pass = calcul_total_filtre(courant, 2, filtre_genre);
        int nb_piet = calcul_total_filtre(courant, 3, filtre_genre);
        float pct_cond = calcul_pct(nb_cond, total_age);
        float pct_pass = calcul_pct(nb_pass, total_age);
        float pct_piet = calcul_pct(nb_piet, total_age);

        printf(" %s%3d ans%s | ", COULEUR_AGE, courant->age, RESET);
        if (filtre_type == 0 || filtre_type == 1) {
            afficher_colonne_barre(pct_cond, 10.0f, LARGEUR_BARRE_TYPE, COULEUR_COND);
        } else {
            printf("       %-*s", LARGEUR_BARRE_TYPE, "");
        }
        printf("  ");
        if (filtre_type == 0 || filtre_type == 2) {
            afficher_colonne_barre(pct_pass, 10.0f, LARGEUR_BARRE_TYPE, COULEUR_PASS);
        } else {
            printf("       %-*s", LARGEUR_BARRE_TYPE, "");
        }
        printf("  ");
        if (filtre_type == 0 || filtre_type == 3) {
            afficher_colonne_barre(pct_piet, 10.0f, LARGEUR_BARRE_TYPE, COULEUR_PIET);
        } else {
            printf("       %-*s", LARGEUR_BARRE_TYPE, "");
        }
        putchar('\n');
        courant = courant->suivant;
    }

    printf("------------------------------------------------------------------\n");
    printf(" Victimes retenues : %d (pourcentages calcules par age)\n", total_retenu);
    printf("==================================================================\n");
}

void menu(list_age *l) {
    if (l == NULL) {
        exit(10);
    }
    int choix = 0;
    int ok = 0;
    int filtre_genre = 0;
    int filtre_type = 0;

    printf("============================\n");
    printf("STATISTIQUES PAR AGE\n");
    printf("============================\n");

    do {
        do {
            printf("Choisissez la vue :\n -1 Vue par genre (Hommes / Femmes)\n -2 Vue par type (Conducteurs / Passagers / Pietons)\nChoix : ");
            if (scanf("%d", &ok) != 1 || (ok != 1 && ok != 2)) {
                viderBuffer();
                printf("Erreur : entrez 1 ou 2.\n");
                ok = 0;
            }
        } while (ok != 1 && ok != 2);

        do {
            printf("Choisissez le genre de la personne :\n -0 Tous\n -1 Homme\n -2 Femme\n -3 Non genre\nChoix : ");
            if (scanf("%d", &filtre_genre) != 1 || filtre_genre < 0 || filtre_genre > 3) {
                viderBuffer();
                printf("Erreur : entrez un chiffre entre 0 et 3.\n");
                filtre_genre = -1;
            }
        } while (filtre_genre < 0 || filtre_genre > 3);

        do {
            printf("Choisissez le type de personne :\n -0 Tous\n -1 Conducteur\n -2 Passager\n -3 Pieton\nChoix : ");
            if (scanf("%d", &filtre_type) != 1 || filtre_type < 0 || filtre_type > 3) {
                viderBuffer();
                printf("Erreur : entrez un chiffre entre 0 et 3.\n");
                filtre_type = -1;
            }
        } while (filtre_type < 0 || filtre_type > 3);

        if (ok == 1) {
            affichage_genre(l, filtre_type, filtre_genre);
        } else {
            affichage_type(l, filtre_type, filtre_genre);
        }

        printf("Souhaitez-vous consulter d'autres statistiques ?\n -1 Oui\n -2 Non (quitter)\nChoix : ");
        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            choix = 2;
        }
    } while(choix == 1);
}

int main(int argc, char **argv) {
    char *nom_fichier;

    if (argc == 2) {
        nom_fichier = argv[1];
    } else if (argc >= 3 && strcmp(argv[1], "AGE_DATA") == 0) {
        nom_fichier = argv[2];
    } else {
        fprintf(stderr, "Usage : %s AGE_DATA <fichier.csv>\n", argv[0]);
        return 1;
    }

    list_age *Liste = malloc(sizeof(list_age));
    if (Liste == NULL) {
        perror("Erreur allocation liste");
        return 1;
    }
    Liste->tete = NULL;

    lire_ficher(NULL, NULL, nom_fichier, Liste);
    menu(Liste);

    return 0;
}
