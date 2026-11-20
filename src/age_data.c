typedef struct chainon {
    int age;
    int femme;
int homme;
int non_genre;
int pieton;
int conducteur;
int passager;
    struct chainon *suivant;
} age_data;

age_data *creation(int a){
age_data *nv = malloc(sizeof(age_data));
if(nv == NULL){
exit(1);
}
nv->age = a;
nv->femme = 0;
nv->homme = 0;
nv->non_genre = 0;
nv->pieton = 0;
nv->conducteur = 0;
nv->passager = 0;
}

age_data zjout(age_data tete, int a)[
age_data *p = tete;
while( p!= NULL){
if ( a <= 
