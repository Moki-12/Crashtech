//pour year
void initTab (year_data *tab){
    if (tab == NULL){
        exit(1);
    }
    for (int i=0; i<20; i++){
        tab[i]->année = 2005 + i;
        tab[i]->accidents = 0;
        for (int j=0; j<4; j++){
            tab[i]->severite[j] = 0;
        }
    }
}

//pour age
age_data ajouter (int a, int t, int g){
   age_data *nouveau = malloc(sizeof(age_data));
   if (nouveau == NULL){
       return NULL;
   }
   nouveau->age = a;
   nouveau->type = t;
   nouveau->genre = g;
   nouveau->suivant = NULL;
   return nouveau;
}

// pour l'autre
pArbre ajouterArbre (int c){
    pArbre nouveau = malloc(sizeof(Noeud));
    if (nouveau == NULL){
        return NULL;
    }
    nouveau->clé = c;
    nouveau->gauche = NULL;
    nouveau->droit = NULL;
    return NULL;
}
gith
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
