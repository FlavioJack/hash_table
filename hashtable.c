#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        return new_hash;
     }
    else{
        printf("You inserted %d but is an invalid size number!", size);
        return NULL;
    }
}

void insert_manual(Hashtable *ht, int index, int value, char *key){
    if(!ht){
        puts("Passed null hashtable");
        return;
    }
    if(index >= ht->size && index < 0){ 
        puts("Trying to access over the table bounds: index > talbe size.");
        return;
    }
    if(!key){ 
        puts("Key can't be null, it must be a string.");
        return;
    }
    
    Bucket *new_bucket = (Bucket*)malloc(sizeof(Bucket));
    if(!new_bucket){
        puts("New bucket allocation error.");
        return;
    }
    new_bucket->value = value;
    new_bucket->key = strdup(key); 
    // strdup(char *) allocate char type of the copied string size... 
    // ...and return pointer of the string with the copied string already inside.
    new_bucket->next = NULL;

    
    if(ht->table[index]==NULL)
        ht->table[index] = new_bucket;
    else{
        Bucket *last_bucket = ht->table[index];
        while(last_bucket->next != NULL){
            last_bucket = last_bucket->next;
        }
        last_bucket->next = new_bucket;
    }
}


// MAIN

int main(void){

    Hashtable *hashtable1 = create_table(N);

}
