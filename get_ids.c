/*
 * Author: Alessandro Coppe
 * Purpose: filter an annotated VCF file based on dbNSFP_FATHMM_rankscore 
 * Language: C
 * 
 *  (c) 2019 Coppe
 *  This code is licensed under WTFPL license (see COPYING for details)
*/

#include<stdio.h>
#include<stdlib.h>
/*#include<unistd.h>*/
/*#include<getopt.h>*/
/*#include<ctype.h>*/
#include<string.h>
#include"get_ids.h"
/*#include "uthash.h"*/
/*#include"is_a_snp_in_cosmic.h"*/


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
    /*puts("Inizio");*/

    while (start->next != NULL) {
        printf("Identifier: %s\n", start->identifier);
        start = start->next;
    }
    printf("Identifier: %s\n", start->identifier);
}
