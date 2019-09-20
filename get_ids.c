/*
 * Author: Alessandro Coppe
 * Purpose: removes variants annotated with Cosmic that are indicated as SNP
 * Language: C
 * 
 *  (c) 2019 Coppe
 *  This code is licensed under WTFPL license (see COPYING for details)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"get_ids.h"


char *get_ids(char *line){
    char delim[] = "\t";
    char *field = NULL;
    int field_number = 0;
    char *cosmic_id = NULL;

    field = strtok(line, delim);

    while (field != NULL) {
        if (field_number == 2) {
            cosmic_id = field;
        }

        field = strtok(NULL, delim);
        field_number++;
    }

    return cosmic_id;
}


bio_id *create_bio_id(char *single_id) {
    bio_id *identifier = malloc(sizeof(bio_id));
    identifier->identifier = strdup(single_id);
    identifier->next = NULL;
    return identifier;
}

bio_id *get_cosmic_ids(char *line){
    char delim[] = ";";
    char *single_id = strtok(line, "; ,"); 
    struct bio_id *start = NULL;
    struct bio_id *identifier = NULL;
    struct bio_id *new = NULL;


    while (single_id != NULL) {
        new = create_bio_id(single_id);
        /*printf("%s\n", single_id);*/
        if (start == NULL) {
            start = new;
            /*puts("Start");*/
        }
        if (identifier != NULL) {
            if (start->next == NULL)
                start->next = identifier;
            /*printf("%s\n", identifier->identifier);*/
            identifier->next = new;
        }
        identifier = new;
        single_id = strtok(NULL, "; ,");
    }

    /*printf("%s\t%p\n", start->identifier, start->next);*/

    return start;
}


void print_cosmic_ids_list(bio_id *start) {
    while (start->next != NULL) {
        printf("Identifier: %s\n", start->identifier);
        start = start->next;
    }
    printf("Identifier: %s\n", start->identifier);
}


void free_cosmic_ids(bio_id *cosmic_ids) {
    bio_id *deleted_bio_id = cosmic_ids;
    bio_id *next = NULL;

    while (deleted_bio_id != NULL) {
        next = deleted_bio_id->next;
        free(deleted_bio_id->identifier);
        free(deleted_bio_id);
        deleted_bio_id = next;
    }
}
