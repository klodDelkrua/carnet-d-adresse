//
// Created by lcdelcroix on 01/12/2025.
//

#include "carnet.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#define MAX_SIZE 26

int hash(const char letter) {
    const char c = (char)toupper(letter);
    if (c < 'A' || c > 'Z')
        return 26;
    return c - 'A';
}

HashTable * create_hash_table() {
    HashTable * table = malloc(sizeof(HashTable));
    if (!table) {
        fprintf(stderr, "malloc failed in create_table\n");
        exit(EXIT_FAILURE);
    }
    table->buckets = calloc(MAX_SIZE, sizeof(Carnet*));
    if (!table->buckets) {
        fprintf(stderr, "malloc failed in create_buckets\n");
        exit(EXIT_FAILURE);
    }
    printf("The Carnet have been created successfully...\nSave yours contact now \n\n\n");
    return table;
}


Carnet* init_carnet() {
    Carnet* carnet = (Carnet*) malloc(MAX_SIZE * sizeof(Carnet));
    if (!carnet) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    printf("Carnet initialized...\n");
    return carnet;
}

void show_person(Person* person) {
    if (person == NULL) {
        printf("There is no person to show...\n");
        return;
    }
    printf("Name: %s\n", person->name);
    printf("Last Name : %s\n",person->last_name);
    printf("Gender : %c\n",person->gender);
    printf("Age : %d\n", person->age);
}

void show_adress(Adress* adress) {
    if (adress == NULL) {
        printf("There is no adress to show...\n");
        return;
    }
    printf("Address: %s\n",adress->adress);
    printf("City: %s\n", adress->city);
}

void look_at_carnet(HashTable *table) {
    if (!table) {
        printf("There is no carnet to look at...\n");
        return;
    }
    printf("\t\t~~~CARNET~~\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (table->buckets[i] != NULL) {
            Carnet* carnet = table->buckets[i];
            while (carnet != NULL) {
                show_person(&carnet->person);
                show_adress(&carnet->adress);
                printf("Number : %s\n\n",carnet->number);
                carnet = carnet->next;
            }

        }

    }
    printf("\t\t~~~END~~~\n");
}

void add_adress(Adress* adress) {
    printf("Adress : ");
    fgets(adress->adress, LEN_ADRESS, stdin);
    save_f_gets(adress->adress);
    printf("City : ");
    fgets(adress->city, LEN, stdin);
    save_f_gets(adress->city);
}

void add_person(Person* person) {
    printf("Name : ");
    fgets(person->name  , LEN, stdin);
    save_f_gets(person->name);
    printf("Last Name : ");
    fgets(person->last_name , LEN, stdin);
    save_f_gets(person->last_name);
    printf("Gender : ");
    person->gender = (char)getchar();
    vide_buffer();
    printf("Age : ");
    person->age = c_scanf();
    //vide_buffer();
}

void add_in_carnet(const HashTable* table) {
    Carnet* carnet = malloc(sizeof(Carnet));
    if (!carnet) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    printf("\t\t~~~ADD CONTACT~~~\n");
    add_person(&carnet->person);
    add_adress(&carnet->adress);
    printf("Phone number : ");
    fgets(carnet->number, LEN, stdin);
    carnet->number_contact += 1;
    const int index = hash(carnet->person.name[0]);
    carnet->next = table->buckets[index];
    table->buckets[index] = carnet;
    printf("\t\t~~~END~~~\n");
}

void show_one_carnet(Carnet* carnet) {
    if (!carnet) {
        printf("There is no carnet to show...\n");
        return;
    }
    show_person(&carnet->person);
    show_adress(&carnet->adress);
    printf("Phone number : %s",carnet->number);
}


bool search_contact(const HashTable *table,char * name) {
    const int index = hash(name[0]);
    if (table->buckets[index] == NULL) {
        printf("We find no one with the name : %s...\n",name);
        return false;
    }
    Carnet* carnet = table->buckets[index];
    while (carnet != NULL) {
        if (strcmp(carnet->person.name, name) == 0) {
            printf("We find someone\n");
            show_one_carnet(carnet);
            return true;
        }
        carnet = carnet->next;
    }
    return false;
}

void delete_contact(const HashTable *table, char *name) {
    const int index = hash(name[0]);
    if (table->buckets[index] == NULL) {
        printf("There is no contact to delete with the name : %s ...\n",name);
        return;
    }
    Carnet* carnet = table->buckets[index];
    Carnet* prev = nullptr;
    while (carnet != NULL) {
        if (strcmp(carnet->person.name, name) == 0) {
            if (prev) {
                prev->next = carnet->next;
            }else {
                table->buckets[index] = carnet->next;
            }
            carnet->number_contact--;
            free(carnet);
            printf("The contact have been deleted...\n");
            return;
        }
        prev = carnet;
        carnet = carnet->next;
    }
}

void free_carnet(HashTable *table) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (table->buckets[i] != NULL) {
            Carnet* carnet = table->buckets[i];
            while (carnet != NULL) {
                Carnet* tmp = carnet;
                carnet = carnet->next;
                free(tmp);
            }
        }
    }
    free(table->buckets);
    free(table);
}

void export_data(const HashTable *table) {
    FILE *file = fopen("/home/lcdelcroix/Documents/j_ai_grandi_12.11.2025/Project/C/carnet_d_adress/carnet.txt", "w");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    int n = 0, x = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (table->buckets[i] != NULL) {
            Carnet* carnet = table->buckets[i];
            x = carnet->number_contact;
            while (carnet != NULL) {
                fprintf(file,"Contact Number %d\n",n);
                fprintf(file, "name : %s \n", carnet->person.name);
                fprintf(file, "last name : %s \n", carnet->person.last_name);
                fprintf(file, "gender : %c \n", carnet->person.gender);
                fprintf(file, "age : %d \n", carnet->person.age);
                fprintf(file, "Adress : %s \n",carnet->adress.adress);
                fprintf(file, "City : %s \n", carnet->adress.city);
                fprintf(file, "Phone number : %s \n",carnet->number);

                carnet = carnet->next;
                n++;
            }
            n--;
        }
    }
    fclose(file);
    if (x != n) {
        printf("Le nombre de contact ne correspond pas au moment de l'exportation des donnee\n");
        printf("x = %d and n = %d\n", x, n);
    }
    printf("Total contact : %d\n",n);
}
