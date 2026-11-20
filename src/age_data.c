typedef struct {
int femme;
int homme;
int non-genre;
} Genre;

typedef struct {
int conducteur;
int passager;
int pieton;
} Type;

typedef struct chainon {
    int age;
    Genre *g;
    Type *p;
    struct chainon *suivant;
} age_data;

age_data creation
