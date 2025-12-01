//
// Created by lcdelcroix on 01/12/2025.
//

#ifndef CARNET_D_ADRESS_CARNET_H
#define CARNET_D_ADRESS_CARNET_H
//#include <stdio.h>
#define LEN 30
#define LEN_ADRESS 50

typedef struct Adress Adress;
struct Adress {
    char adress[LEN_ADRESS];
    char city[LEN];
};

typedef struct Person Person;
struct Person {
    char name[LEN];
    char last_name[LEN];
    int age;
    char gender;
};

typedef struct Carnet Carnet;
struct Carnet {
    Person person;
    Adress adress;
    char number[LEN];
    int number_contact;
    Carnet* next;
};

typedef struct HashTable HashTable;
struct HashTable {
    Carnet** buckets;
};

int hash(char letter);
HashTable* create_hash_table();
Carnet* init_carnet();
void show_person(Person* person);
void show_adress(Adress* adress) ;
void look_at_carnet(HashTable* table);
void add_adress(Adress* adress);
void add_person(Person* person) ;
void add_in_carnet(const HashTable* table);
bool search_contact(const HashTable* table, char* name);
void show_one_carnet(Carnet* carnet);
void delete_contact(const HashTable* table,char* name);
void free_carnet(HashTable* table);
void export_data(const HashTable* table);

#endif //CARNET_D_ADRESS_CARNET_H