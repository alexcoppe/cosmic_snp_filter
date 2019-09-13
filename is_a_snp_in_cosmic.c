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
#include<unistd.h>
#include<getopt.h>
#include<ctype.h>
#include<string.h>
#include "uthash.h"
#include"is_a_snp_in_cosmic.h"



void print_HASH_FIND_STR_RESULT(struct cosmic_entry *s) {
    if (s != NULL)
        printf("Found COSM: %s\n", s->name);
    else
        puts("Could not find COSM");
}


char *is_a_snp_in_cosmic(char *line) {
    char delim[] = "\t";
    char *field = NULL;
    int field_number = 0;
    char *cosmic_id = NULL;
    char *found_SNP = NULL;
    char *snp = ";SNP;";
    char *no = "NO";

    field = strtok(line, delim);

    while (field != NULL) {
        if (field_number == 2) {
            cosmic_id = field;
        }

        if (field_number == 7) {
            found_SNP = strstr(field, snp);

            if (found_SNP != NULL) {
                return cosmic_id;
            }
        }

        field = strtok(NULL, delim);
        field_number++;
    }
    return "NO";
}


struct cosmic_entry *create_cosmic_hash(char *file, struct cosmic_entry *cosmic_hash) {
    char *line;
    size_t len = 0;
    FILE *vcf;
    ssize_t read;
    char *is_a_snp = NULL;
    int is_no_snp;
    struct cosmic_entry *s;


    /*If the VCF file is not present */
    if (!(vcf = fopen(file, "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", file);
        exit(-1);
    }

    while ((read = getline(&line, &len, vcf) ) != -1) {
        if (line[0] == '#')
            continue;
        else {
            is_a_snp = is_a_snp_in_cosmic(line);
            is_no_snp = strcmp(is_a_snp, "NO");
            if (is_no_snp != 0) {
                s = (struct cosmic_entry *) malloc(sizeof *s);
                strcpy(s->name, is_a_snp);
                s->id = 1;

                HASH_ADD_STR( cosmic_hash, name, s );
            }
        }
    }

    free(line);

    return cosmic_hash;
}

void delete_cosmic_hash(struct cosmic_entry *cosmic_hash, struct cosmic_entry *s) {
    struct cosmic_entry *tmp;

    HASH_ITER(hh, cosmic_hash, s, tmp) {
        HASH_DEL(cosmic_hash, s);
        free(s);
    }
 
}
