/*
 * Author: Alessandro Coppe
 * Purpose: removes variants annotated with Cosmic that are indicated as SNP
 * Language: C
 * 
 *  (c) 2019 Coppe
 *  This code is licensed under WTFPL license (see COPYING for details)
*/


#include "uthash.h"

char *is_a_snp_in_cosmic(char *);

struct cosmic_entry *create_cosmic_hash(char *, struct cosmic_entry *);

void print_HASH_FIND_STR_RESULT(struct cosmic_entry *);

void delete_cosmic_hash(struct cosmic_entry *, struct cosmic_entry *);

struct cosmic_entry {
    char name[20];
    int id;
    UT_hash_handle hh;
};
