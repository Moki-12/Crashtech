typedef struct liste2 {     // faire max collision par année 
    int type;
    int genre;
    int age;
    int gravite;
    struct liste2 *suivant;
} Liste_victimes;

typedef struct liste {
    int vehicule_id;
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

Liste_vehicules ajouterl_ve (int p, int v_id){
    if (v == NULL){
        return NULL;
    }
    Liste_vehicules *nouveau = malloc(sizeof(Liste_vehicules));
    if (nouveau == NULL){
        return NULL;
    }
    nouveau->purpose = p;
    nouveau->vehicule_id = v_id;
    nouveau->suivant = NULL;
    return nouveau;
}

pArbre rotationgauche (pArbre a){
    if (a == NULL){
        return NULL;
    }
    pArbre pivot;
    int eq_a;
    int eq_p;
    pivot = a->droit;
    a->droit = pivot->gauche;
    pivot->gauche = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max(eq_p - 0) - 1;
    pivot->equilibre = min(eq_a-2, eq_a+eq_p-2, eq_p-1);
    a = pivot;
    return a;
}

pArbre rotationdroit (pArbre a){
    if (a == NULL){
        return NULL;
    }
    pArbre pivot;
    int eq_a;
    int eq_p;
    pivot = a->gauche;
    a->gauche = pivot->droit;
    pivot->droit = a;
    eq_a = a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min(eq_p, 0) + 1;
    pivot->equilibre = max(eq_a+2, eq_a+eq_p+2, eq_p+1);
    a = pivot;
    return a;
}

pArbre doublerotationgauche (pArbre a){
    if (a == NULL){
        return NULL;
    }
    a->droit = rotationdroit(a->droit);
    return rotationgauche(a);
}

pArbre doublerotationdroit(pArbre a){
    if (a == NULL){
        return NULL;
    }
    a->gauche = rotationgauche(a->gauche);
    return rotationdroit(a);
}

pArbre equilibrage (pArbre a){
    if (a == NULL){
        return NULL;
    }
    if (a->equilibre >= 2){
        if (a->droit->equilibre >= 0){
            return rotationgauche(a);
        }
        else {
            return doublerotationgauche(a);
        }
    }
    else if (a->equilibre <= -2){
        if (a->gauche->equilibre <= 0){
            return rotationdroit(a);
        }
        else {
            return doublerotationdroit(a);
        }
    }
    return a;
}

pArbre ajouter_noeud (pArbre a, int c, int *h){
    if (a == NULL){
        *h = 1;
        return creerNoeud(c);
    }
    if (c < a->clé){
        a->gauche = ajouter_noeud(a->gauche, c, h);
        *h = -*h;
    }
    else if (c > a->clé){
        a->droit = ajouter_noeud(a->droit, c, h);
    }
    if (*h != 0){
        a->equilibre += *h;
        a = equilibrage(a);
        if (a->equilibre == 0){
            *h = 0;
        }
        else {
            *h = 1;
        }
    }
    return a;
}

pArbre verif_existe (pArbre a, int c){
    if (a == NULL || a->clé == c){
        return a;
    }
    else if (c < a->clé){
        return a->gauche = verif_existe(a->gauche, c);
    }
    else {
        return a->droit = verif_existe(a->droit, c);
    }
}

int collée_chaine (int nb1, int nb2){
    char collée[30];
    sprintf (collée, "%d%d", nb1, nb2);
    int result = atoi(collée);
    return result;
}

Liste_vehicules *verif_vehicules (pArbre a, int v_id){
    if (a == NULL){
        return NULL;
    }
    Liste_vehicules *courant = a->l_ve;
    while (courant != NULL){
        if (courant->vehicule_id == v_id){
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;;
}

void lire_fichier (FILE *f, pArbre a, char *nom_fichier){
    if (f == NULL || nom_fichier == NULL){
        exit (1);
    }
    char ligne[200];
    int year;
    int collision_id;
    int c;
    int purpose;
    int v_id;
    f = fopen(nom_fichier, "r");
    fgets(ligne, 199, f);
    while ((fgetc(f)) != NULL){
        fseek(f, -1, SEEK_CUR);
        fscanf (f, "%d;%d;%d;%*d;%*d;%*d;%*d;%*d;%d", &year, &collision_id, &v_id, &purpose);
        c = collée_chaine(year, collision_id);
        pArbre existe_noeud = verif_existe(a, c);
        if (existe_noeud == NULL){
            int h = 0;
            a = ajouter_noeud(a, c, &h);
         existe_noeud = verif_existe(a, c);   
        }
        Liste_vehicules *existe_vehicule;
        existe_vehicule = verif_vehicules(a, v_id);
        if (existe_vehicule != NULL){
            if (existe_vehicule->purpose == 0 || existe_vehicule->purpose == -1){
                existe_vehicule->purpose = purpose;
            }
        }
        else {
            Liste_vehicules *new_vehicules = ajouterl_ve(purpose, v_id);
            new_vehicules->suivant = existe_noeud->l_ve;
            existe_noeud->l_ve = new_vehicules;
            existe_vehicule = new_vehicules;
        }
    }
}
