typedef struct liste2 {
    int type;
    int genre;
    int age;
    int gravite;
    struct liste2 *suivant;
} Liste_victimes;

typedef struct liste {
    char *vehicule_id;
    int purpose;
    struct liste *suivant;
    Liste_victimes *l_vi;
} Liste_vehicules;

typedef struct chainon {
    int clé;
    struct chainon *gauche;
    struct chainon *droit;
    Liste_vehicules *l_ve;
} Noeud;

typedef Noeud *pArbre;

pArbre creerNoeud (int c){
    pArbre nouveau = malloc(sizeof(Noeud));
    if (nouveau == NULL){
        return NULL;
    }
    nouveau->clé = c;
    nouveau->gauche = NULL;
    nouveau->droit = NULL;
    return nouveau;
}

Liste_victimes ajouterl_vi (int t, int ge, int a, int gr){
Liste_victimes *nouveau = malloc(sizeof(Liste_victimes));
if (nouveau == NULL){
    return NULL;
}
nouveau->type = t;
nouveau->genre = ge;
nouveau->age = a;
nouveau->gravite = gr;
nouveau->suivant = NULL;
return nouveau;
}

Liste_vehicules ajouterl_ve (int p, char *v){
    if (v == NULL){
        return NULL;
    }
    Liste_vehicules *nouveau = malloc(sizeof(Liste_vehicules));
    if (nouveau == NULL){
        return NULL;
    }
    nouveau->purpose = p;
    nouveau->vehicule_id = malloc(sizeof((strlen(v))+1));
    strcpy(vehicule_id, v);
    nouveau->suivant = NULL;
    return nouveau;
}

pArbre ajouter_noeud (pArbre a, int c){
    if (a == NULL){
        return creerNoeud(c);
    }
    if (c < a->clé){
        a->gauche = ajouter_noeud(a->gauche, c);
    }
    else if (c > a->clé){
        a->droit = ajouter_noeud(a->gauche, c);
    }
    return a;
}

pArbre verif_existe (pArbre a, int c){
    pArbre courant = a;
    while (courant != NULL){
        if (courant->clé == c){
            return courant;
            courant = courant->suivant;
        }
    }
    return ajouter_noeud(a, c);
}

int collée_chaine (int nb1, int nb2){
    char collée[30];
    sprintf (collée, "%d%d", nb1, nb2);
    int result = atoi(collée);
    return result;
}

void lire_fichier (FILE *f, pArbre a, char *nom_fichier){
    if (f == NULL || nom_fichier == NULL){
        exit (1);
    }
    char ligne[200];
    int year;
    int collision_id;
    int c;
    f = fopen(nom_fichier, "r");
    fgets(ligne, 199, f);
    while ((fgetc(f)) != NULL){
        fseek(f, -1, SEEK_CUR);
        fscanf (f, "%d;%d", &year, &collision_id);
        c = collée_chaine(year, collision_id);
        a = verif_existe(a, c);
    }
}
