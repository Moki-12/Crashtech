// pour yeardata
typedef struct {
    int année;
    int accidents;
    int severite[4];
} year_data;

// pour agedata
typedef struct chainon {
    int age;
    int type;
    int genre;
    struct chainon *suivant;
} age_data;

//pour lautre
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
    chainon liste *suivant;
    Liste_victimes *l_vi;
} Liste_vehicules;

typedef struct chainon {
    int clé;
    struct chainon *gauche;
    struct chainon *droit;
    Liste_vehicules *l_ve;
} Noeud;

typedef pArbre *Noeud;
