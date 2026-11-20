typedef struct chainon {
    int age;
    int type;
    int genre;
    struct chainon *suivant;
} age_data;

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

