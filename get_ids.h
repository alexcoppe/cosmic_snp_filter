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
/*#include<string.h>*/
/*#include "uthash.h"*/
/*#include"is_a_snp_in_cosmic.h"*/


char *get_ids(char *);

typedef struct bio_id {
    char *identifier;
    struct bio_id *next;
} bio_id;

bio_id *get_cosmic_ids(char *);

void print_cosmic_ids_list(bio_id *);

void free_cosmic_ids(bio_id *cosmic_ids);
