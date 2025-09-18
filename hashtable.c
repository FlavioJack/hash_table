#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7 // Better if prime numberR


// STRUCTURES

typedef struct bucket{
    int value;
    char *key;
    struct bucket *next;
}Bucket;

typedef struct hashtable{
    Bucket **table;
    size_t size; 
}Hashtable;


// FUNCTIONS

unsigned long hash_djb2(const char *key){
    unsigned long int hash = 5381;
    int c;
    
    while((c=*key++)){
        hash = hash*33 + c;
    }
    return hash;
}

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

void insert(Hashtable *ht, int value, const char *key){
    if(!ht || !key){
        puts("Can't insert with null hashtable or null key!");
        return;
    }

    size_t index = hash_djb2(key) % ht->size;

    if(index >= ht->size){ 
        puts("Can't insert over the table boundaries!");
        return;
    }
    
    Bucket *new_bucket = (Bucket*)malloc(sizeof(Bucket));
    if(!new_bucket){
        puts("New bucket allocation error!");
        return;
    }
    new_bucket->value = value;
    new_bucket->key = strdup(key); 
    new_bucket->next = NULL;

    
    if(ht->table[index]==NULL)
        ht->table[index] = new_bucket;
    else{
        Bucket *last_bucket = ht->table[index];
        while(last_bucket->next != NULL)
            last_bucket = last_bucket->next;

        last_bucket->next = new_bucket;
    }
    puts("New element inserted succesfully!");
}

void print_bucket(Hashtable *ht, const char *key){
    if(!ht || !key){
        puts("Can't print null hashtable or null key!");
        return;
    }   

    size_t index = hash_djb2(key) % ht->size;

    if(index >= ht->size){
        puts("Can't print over the table boundaries!");
        return;
    }
    if(!ht->table || !ht->table[index]){
        printf("Table not allocated or element at %zu is empty!\n", index);
        return;
    }
    puts("Hash table elements: ");
    Bucket *bucket = ht->table[index];
    while(bucket != NULL){
        printf("\tCouple key-value: %s-%d;\n",bucket->key, bucket->value);
        bucket = bucket->next;
    }
}

int *search(Hashtable *ht, const char *key){
    if(!ht || !key){
        puts("Can't search with null hashtable or null key!");
        return NULL;
    }

    size_t index = hash_djb2(key) % ht->size;
   
    if(index >= ht->size){
        puts("Can't search over the table boundaries!");
        return NULL;
    }
    if(!ht->table || !ht->table[index]){
        printf("Searching aborted: table not allocated or element at %zu is empty!\n", index);
        return NULL;
    }
    Bucket *bucket = ht->table[index];
    while(bucket != NULL){
        int cmp = strcmp(bucket->key, key);
        if(cmp == 0)
            return &(bucket->value);
        else bucket = bucket->next;
    }
    return NULL;
}

void delete(Hashtable *ht, const char *key){
    if(!ht || !key){
        puts("Can't delete if null hashtable or null key!");
        return;
    }   

    size_t index = hash_djb2(key) % ht->size;

    if(index >= ht->size){
        puts("Can't delete over the table boundaries!");
        return;
    }
    if(!ht->table || !ht->table[index]){
        printf("Deleting aborted: table not allocated or element at %zu is empty\n", index);
        return;
    }
    
    Bucket *current = ht->table[index];
    Bucket *prev = NULL;

    while(current){
        if( strcmp(current->key, key)==0 ){
            if(!prev)
                ht->table[index] = current->next;
            else
                prev->next = current->next;
            
            printf("Key \"%s\" with value |%d| deleted succesfully!\n", current->key, current->value);    
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// MAIN

int main(void){

    Hashtable *hashtable1 = create_table(N);
    insert(hashtable1, 100, "giorgio");
    insert(hashtable1, 200, "flavio");

    print_bucket(hashtable1, "giorgio");

    int* result = search(hashtable1, "giorgio");
    if (result) {
        printf("Key searched value is: %d\n", *result);
    } 
    else {
        printf("Key not found.\n");
    }

    delete(hashtable1, "giorgio");

}

/* Here i learned strdup and strcmp functions of string.h */
