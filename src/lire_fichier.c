int lire_ligne_fichier (FILE *f, ligne_fichier *l){
  if (f == NULL || l == NULL={
return 0;
  }
if ((fscanf (f, "%d;%d;%d;%d;%d;%d;%d;%d;%d", 
  &l->année,
  &l->collision_id,
  &l->vehicule_id,
  &l->location,
  &l->user_type,
  &l->severity,
  &l->genre,
  &l->naissance,
  &l->purpose,)) == 9) return 1;
else return 0;
}
