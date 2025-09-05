#include <stdio.h>
#include <stdlib.h>

#define N 10


// STRUCTURES

typedef struct bucket{
    int value;
    char *key;
    struct bucket *next;
}Bucket;

typedef struct hashtable{
    Bucket **table;
    int size;
}Hashtable;


// FUNCTIONS

Hashtable *create_table(int size){
    if(size>0){
        Hashtable *new_hash = (Hashtable*)malloc(sizeof(Hashtable));
        new_hash->size = size;
        
        Bucket **new_table = (Bucket**)calloc(size, sizeof(Bucket*));
        new_hash->table = new_table;
    }
    else{
        printf("You inserted %d but is an invalid size number!", size);
        return NULL;
    }
    return new_hash;
}



// MAIN

int main(void){
    
    Hashtable *hashtable1 = create_table(N);
    
}
