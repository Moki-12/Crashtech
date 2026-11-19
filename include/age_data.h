#ifndef AGE_DATA_H
#define AGE_DATA_H

typedef struct chainon {
    int age;
    int type;
    int genre;
    struct chainon *suivant;
} age_data;

#endif
