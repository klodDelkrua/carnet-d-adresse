//
// Created by lcdelcroix on 01/12/2025.
//
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int c_scanf() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin)) {  // Lire une ligne
        char *endptr;
        const int n = (int)strtol(buffer, &endptr, 10);   // Base 10
        if (endptr == buffer || *endptr != '\n') {
            //printf("Entrée invalide !\n");
            return -1;
        } else {
            return n;
        }
    }
    return -1;
}

void vide_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void save_f_gets(char *name) {
    // supposer que name est la chaîne lue par fgets
    const size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';  // remplacer '\n' par '\0'
    }

}
