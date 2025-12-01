//
// Created by lcdelcroix on 01/12/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "user_interface.h"
#include "functions.h"
#include "carnet.h"
#include <stdbool.h>

#include "carnet.h"

int main_menu() {
    printf("1. Create Carnet\n"
                "2. Look at all contact\n"
                "3. Add contact\n"
                "4. Delete contact\n"
                "5. Delete Carnet\n"
                "6. Search contact\n"
                "7. Export data in the file.txt\n"
                "8. Exit\n");
    printf("Enter your choice: ");
    int choice = c_scanf();
    while (choice < 1 || choice > 8) {
        printf("Invalid choice\n");
        printf("Enter your choice: ");
        choice = c_scanf();
    }
    return choice;
}

void delete_(const HashTable *table) {
    char name[LEN];
    printf("\t\t~~~DELETE CONTACT~~~\n");
    printf("Enter the name to delete : ");
    fgets(name, LEN, stdin);
    save_f_gets(name);
    delete_contact(table, name);
    printf("~~~END~~~\n");
}

void add_(const HashTable *table) {
    printf("How many contacts to add: ");
    const int number = c_scanf();
    for (int i = 0; i < number; i++) {
        add_in_carnet(table);
    }
}

void search_(const HashTable *table) {
    printf("\t\t~~~SEARCH CONTACT~~~\n");
    printf("Enter the name to search : ");
    char name[LEN];
    fgets(name, LEN, stdin);
    save_f_gets(name);
    if (!search_contact(table, name)) {
        printf("Contact not found\n");
    }
    printf("~~~END~~~\n");
}

void run_application() {
    bool running = true;
    HashTable * table = nullptr;
    while (running) {
        const int choice = main_menu();
        switch (choice) {
            case 1: {
                table = create_hash_table();
                break;
            }
            case 2: {
                look_at_carnet(table);
                break;
            }
            case 3: {
                add_(table);
                break;
            }
            case 4: {
                delete_(table);
                break;
            }
            case 5: {
                free_carnet(table);
                break;
            }
            case 6: {
                search_(table);
                break;
            }
            case 7 : {
                export_data(table);
                break;
            }
            case 8:
                running = false;
                break;
            default:
                printf("There are something wrong...\n");
                break;
        }
    }
}


