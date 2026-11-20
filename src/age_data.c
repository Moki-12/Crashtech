typedef struct chainon {
    int age;
    int type;
    int genre;
    struct chainon *suivant;
} age_data;


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
    }
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

