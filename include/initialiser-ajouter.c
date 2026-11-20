

//pour age

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
